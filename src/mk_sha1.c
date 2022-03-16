#include "mk_sha1.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <string.h> /* memcpy memset */


static mk_inline uint32_t mk_sha1_detail_rotl(uint32_t x, int n)
{
	mk_assert(n > 0 && n < 32);

	return (x << n) | (x >> (32 - n));
}

static mk_inline uint32_t mk_sha1_detail_ch(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) ^ ((~x) & z);
}

static mk_inline uint32_t mk_sha1_detail_parity(uint32_t x, uint32_t y, uint32_t z)
{
	return x ^ y ^ z;
}

static mk_inline uint32_t mk_sha1_detail_maj(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}

static mk_inline uint32_t mk_sha1_detail_f(int idx, uint32_t x, uint32_t y, uint32_t z)
{
	mk_assert(idx >= 0 && idx <= 79);

	if(idx <= 19)
	{
		return mk_sha1_detail_ch(x, y, z);
	}
	else if(idx <= 39)
	{
		return mk_sha1_detail_parity(x, y, z);
	}
	else if(idx <= 59)
	{
		return mk_sha1_detail_maj(x, y, z);
	}
	else
	{
		return mk_sha1_detail_parity(x, y, z);
	}
}

static mk_inline uint32_t mk_sha1_detail_k(int idx)
{
	mk_assert(idx >= 0 && idx <= 79);

	if(idx <= 19)
	{
		return 0x5a827999;
	}
	else if(idx <= 39)
	{
		return 0x6ed9eba1;
	}
	else if(idx <= 59)
	{
		return 0x8f1bbcdc;
	}
	else
	{
		return 0xca62c1d6;
	}
}

static mk_inline void mk_sha1_detail_process_block(struct mk_sha1_state_s* self, void const* data)
{
	unsigned char const* input;
	uint32_t w[80];
	uint32_t abcde[5];
	uint32_t t;
	uint32_t* a;
	uint32_t* b;
	uint32_t* c;
	uint32_t* d;
	uint32_t* e;
	int i;

	mk_assert(self);
	mk_assert(data);

	input = (unsigned char const*)data;

	a = abcde + 0;
	b = abcde + 1;
	c = abcde + 2;
	d = abcde + 3;
	e = abcde + 4;

	for(i = 0; i != 16; ++i)
	{
		w[i] =
			(((uint32_t)(input[i * 4 + 0])) << (3 * 8)) |
			(((uint32_t)(input[i * 4 + 1])) << (2 * 8)) |
			(((uint32_t)(input[i * 4 + 2])) << (1 * 8)) |
			(((uint32_t)(input[i * 4 + 3])) << (0 * 8));
	}
	for(i = 16; i != 80; ++i)
	{
		w[i] = mk_sha1_detail_rotl(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
	}
	
	*a = self->m_abcde[0];
	*b = self->m_abcde[1];
	*c = self->m_abcde[2];
	*d = self->m_abcde[3];
	*e = self->m_abcde[4];

	for(i = 0; i != 80; ++i)
	{
		t = mk_sha1_detail_rotl(*a, 5) + mk_sha1_detail_f(i, *b, *c, *d) + *e + mk_sha1_detail_k(i) + w[i];
		*e = *d;
		*d = *c;
		*c = mk_sha1_detail_rotl(*b, 30);
		*b = *a;
		*a = t;
	}

	self->m_abcde[0] += *a;
	self->m_abcde[1] += *b;
	self->m_abcde[2] += *c;
	self->m_abcde[3] += *d;
	self->m_abcde[4] += *e;
}


void mk_sha1_init(struct mk_sha1_state_s* self)
{
	mk_assert(self);

	self->m_abcde[0] = 0x67452301;
	self->m_abcde[1] = 0xefcdab89;
	self->m_abcde[2] = 0x98badcfe;
	self->m_abcde[3] = 0x10325476;
	self->m_abcde[4] = 0xc3d2e1f0;
	self->m_len = 0;
}

void mk_sha1_append(struct mk_sha1_state_s* self, void const* data, size_t len)
{
	unsigned char const* input;
	size_t remaining;
	unsigned idx;
	unsigned capacity;
	size_t blocks;
	size_t i;
	
	mk_assert(self);
	
	input = (unsigned char const*)data;
	remaining = len;

	idx = self->m_len % 64;
	capacity = 64 - idx;
	self->m_len += len;
	if(remaining >= capacity)
	{
		memcpy(self->m_block + idx, input, capacity);
		mk_sha1_detail_process_block(self, self->m_block);
		input += capacity;
		remaining -= capacity;
		blocks = remaining / 64;
		for(i = 0; i != blocks; ++i)
		{
			mk_sha1_detail_process_block(self, input);
			input += 64;
		}
		remaining -= blocks * 64;
		idx = 0;
	}
	memcpy(self->m_block + idx, input, remaining);
}

void mk_sha1_finish(struct mk_sha1_state_s* self, void* digest)
{
	#define s_mandatory_padding_len (1 + sizeof(uint64_t))
	#define s_worst_padding_len (64 + s_mandatory_padding_len - 1)
	
	unsigned char padding[s_worst_padding_len];
	unsigned idx;
	unsigned capacity;
	unsigned zeros;
	uint64_t len;

	mk_assert(self);
	mk_assert(digest);

	idx = self->m_len % 64;
	capacity = 64 - idx;
	zeros =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity + 64 - s_mandatory_padding_len);

	#undef s_mandatory_padding_len
	#undef s_worst_padding_len

	padding[0] = (unsigned char)(1u << 7);

	memset(padding + 1, 0, zeros);

	len = self->m_len * 8;
	padding[1 + zeros + 0] = (unsigned char)((len >> (8 * 7)) & 0xff);
	padding[1 + zeros + 1] = (unsigned char)((len >> (8 * 6)) & 0xff);
	padding[1 + zeros + 2] = (unsigned char)((len >> (8 * 5)) & 0xff);
	padding[1 + zeros + 3] = (unsigned char)((len >> (8 * 4)) & 0xff);
	padding[1 + zeros + 4] = (unsigned char)((len >> (8 * 3)) & 0xff);
	padding[1 + zeros + 5] = (unsigned char)((len >> (8 * 2)) & 0xff);
	padding[1 + zeros + 6] = (unsigned char)((len >> (8 * 1)) & 0xff);
	padding[1 + zeros + 7] = (unsigned char)((len >> (8 * 0)) & 0xff);

	mk_sha1_append(self, padding, 1 + zeros + sizeof(uint64_t));

	((unsigned char*)digest)[ 0] = (unsigned char)((self->m_abcde[0] >> (8 * 3)) & 0xff);
	((unsigned char*)digest)[ 1] = (unsigned char)((self->m_abcde[0] >> (8 * 2)) & 0xff);
	((unsigned char*)digest)[ 2] = (unsigned char)((self->m_abcde[0] >> (8 * 1)) & 0xff);
	((unsigned char*)digest)[ 3] = (unsigned char)((self->m_abcde[0] >> (8 * 0)) & 0xff);
	((unsigned char*)digest)[ 4] = (unsigned char)((self->m_abcde[1] >> (8 * 3)) & 0xff);
	((unsigned char*)digest)[ 5] = (unsigned char)((self->m_abcde[1] >> (8 * 2)) & 0xff);
	((unsigned char*)digest)[ 6] = (unsigned char)((self->m_abcde[1] >> (8 * 1)) & 0xff);
	((unsigned char*)digest)[ 7] = (unsigned char)((self->m_abcde[1] >> (8 * 0)) & 0xff);
	((unsigned char*)digest)[ 8] = (unsigned char)((self->m_abcde[2] >> (8 * 3)) & 0xff);
	((unsigned char*)digest)[ 9] = (unsigned char)((self->m_abcde[2] >> (8 * 2)) & 0xff);
	((unsigned char*)digest)[10] = (unsigned char)((self->m_abcde[2] >> (8 * 1)) & 0xff);
	((unsigned char*)digest)[11] = (unsigned char)((self->m_abcde[2] >> (8 * 0)) & 0xff);
	((unsigned char*)digest)[12] = (unsigned char)((self->m_abcde[3] >> (8 * 3)) & 0xff);
	((unsigned char*)digest)[13] = (unsigned char)((self->m_abcde[3] >> (8 * 2)) & 0xff);
	((unsigned char*)digest)[14] = (unsigned char)((self->m_abcde[3] >> (8 * 1)) & 0xff);
	((unsigned char*)digest)[15] = (unsigned char)((self->m_abcde[3] >> (8 * 0)) & 0xff);
	((unsigned char*)digest)[16] = (unsigned char)((self->m_abcde[4] >> (8 * 3)) & 0xff);
	((unsigned char*)digest)[17] = (unsigned char)((self->m_abcde[4] >> (8 * 2)) & 0xff);
	((unsigned char*)digest)[18] = (unsigned char)((self->m_abcde[4] >> (8 * 1)) & 0xff);
	((unsigned char*)digest)[19] = (unsigned char)((self->m_abcde[4] >> (8 * 0)) & 0xff);
}
