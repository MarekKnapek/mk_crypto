#include "mk_sha1.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include "../../mk_int/src/exact/mk_uint_32.h"
#include "../../mk_int/src/exact/mk_uint_64.h"

#include <stddef.h> /* size_t */
#include <string.h> /* memcpy memset */


static mk_inline void mk_sha1_detail_ch(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s t1;
	struct mk_uint32_s t2;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ ((~x) & z); */
	
	mk_uint32_and(&t1, x, y);
	mk_uint32_cmplmnt(&t2, x);
	mk_uint32_and(&t2, &t2, z);
	mk_uint32_xor(out, &t1, &t2);
}

static mk_inline void mk_sha1_detail_parity(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s tmp;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return x ^ y ^ z; */

	mk_uint32_xor(&tmp, x, y);
	mk_uint32_xor(out, &tmp, z);
}

static mk_inline void mk_sha1_detail_maj(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s t1;
	struct mk_uint32_s t2;
	struct mk_uint32_s t3;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ (x & z) ^ (y & z); */

	mk_uint32_and(&t1, x, y);
	mk_uint32_and(&t2, x, z);
	mk_uint32_and(&t3, y, z);
	mk_uint32_xor(&t1, &t1, &t2);
	mk_uint32_xor(out, &t1, &t3);
}

static mk_inline void mk_sha1_detail_f(struct mk_uint32_s* out, int idx, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	mk_assert(out);
	mk_assert(idx >= 0 && idx <= 79);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	if(idx <= 19)
	{
		mk_sha1_detail_ch(out, x, y, z);
	}
	else if(idx <= 39)
	{
		mk_sha1_detail_parity(out, x, y, z);
	}
	else if(idx <= 59)
	{
		mk_sha1_detail_maj(out, x, y, z);
	}
	else
	{
		mk_sha1_detail_parity(out, x, y, z);
	}
}

static mk_inline void mk_sha1_detail_k(struct mk_uint32_s* out, int idx)
{
	static struct mk_uint32_s const s_k[] =
	{
		mk_uint32_c(0x5a827999),
		mk_uint32_c(0x6ed9eba1),
		mk_uint32_c(0x8f1bbcdc),
		mk_uint32_c(0xca62c1d6),
	};

	mk_assert(out);
	mk_assert(idx >= 0 && idx <= 79);

	if(idx <= 19)
	{
		*out = s_k[0];
	}
	else if(idx <= 39)
	{
		*out = s_k[1];
	}
	else if(idx <= 59)
	{
		*out = s_k[2];
	}
	else
	{
		*out = s_k[3];
	}
}

static mk_inline void mk_sha1_detail_process_block(struct mk_sha1_state_s* self, void const* data)
{
	unsigned char const* input;
	struct mk_uint32_s w[80];
	struct mk_uint32_s abcde[5];
	struct mk_uint32_s t;
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s* a;
	struct mk_uint32_s* b;
	struct mk_uint32_s* c;
	struct mk_uint32_s* d;
	struct mk_uint32_s* e;
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
		mk_uint32_from_buff_be(&w[i], input + i * sizeof(struct mk_uint32_s));
	}
	for(i = 16; i != 80; ++i)
	{
		/* w[i] = rotl(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1); */
		mk_uint32_xor(&tmp1, &w[i - 3], &w[i - 8]);
		mk_uint32_xor(&tmp2, &w[i - 14], &w[i - 16]);
		mk_uint32_xor(&tmp1, &tmp1, &tmp2);
		mk_uint32_rotl(&w[i], &tmp1, 1);
	}
	
	*a = self->m_abcde[0];
	*b = self->m_abcde[1];
	*c = self->m_abcde[2];
	*d = self->m_abcde[3];
	*e = self->m_abcde[4];

	for(i = 0; i != 80; ++i)
	{
		/* t = rotl(*a, 5) + f(i, *b, *c, *d) + *e + k(i) + w[i]; */
		mk_uint32_rotl(&tmp1, a, 5);
		mk_sha1_detail_f(&tmp2, i, b, c, d);
		mk_uint32_add(&tmp1, &tmp1, &tmp2);
		mk_uint32_add(&tmp1, &tmp1, e);
		mk_sha1_detail_k(&tmp2, i);
		mk_uint32_add(&tmp1, &tmp1, &tmp2);
		mk_uint32_add(&t, &tmp1, &w[i]);
		*e = *d;
		*d = *c;
		mk_uint32_rotl(c, b, 30);
		*b = *a;
		*a = t;
	}

	mk_uint32_add(&self->m_abcde[0], &self->m_abcde[0], a);
	mk_uint32_add(&self->m_abcde[1], &self->m_abcde[1], b);
	mk_uint32_add(&self->m_abcde[2], &self->m_abcde[2], c);
	mk_uint32_add(&self->m_abcde[3], &self->m_abcde[3], d);
	mk_uint32_add(&self->m_abcde[4], &self->m_abcde[4], e);
}


void mk_sha1_init(struct mk_sha1_state_s* self)
{
	static struct mk_uint32_s const s_init[] =
	{
		mk_uint32_c(0x67452301),
		mk_uint32_c(0xefcdab89),
		mk_uint32_c(0x98badcfe),
		mk_uint32_c(0x10325476),
		mk_uint32_c(0xc3d2e1f0),
	};

	mk_assert(self);

	self->m_abcde[0] = s_init[0];
	self->m_abcde[1] = s_init[1];
	self->m_abcde[2] = s_init[2];
	self->m_abcde[3] = s_init[3];
	self->m_abcde[4] = s_init[4];
	mk_uint64_zero(&self->m_len);
}

void mk_sha1_append(struct mk_sha1_state_s* self, void const* data, size_t len)
{
	unsigned char const* input;
	size_t remaining;
	unsigned idx;
	unsigned capacity;
	struct mk_uint64_s tmp;
	size_t blocks;
	size_t i;
	
	mk_assert(self);
	
	input = (unsigned char const*)data;
	remaining = len;

	idx = mk_uint64_to_int(&self->m_len) % 64;
	capacity = 64 - idx;
	mk_uint64_from_sizet(&tmp, len);
	mk_uint64_add(&self->m_len, &self->m_len, &tmp);
	if(remaining >= capacity)
	{
		memcpy((unsigned char*)self->m_block + idx, input, capacity);
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
	memcpy((unsigned char*)self->m_block + idx, input, remaining);
}

void mk_sha1_finish(struct mk_sha1_state_s* self, void* digest)
{
	#define s_mandatory_padding_len (1 + sizeof(struct mk_uint64_s))
	#define s_worst_padding_len (64 + s_mandatory_padding_len - 1)
	
	unsigned char padding[s_worst_padding_len];
	unsigned idx;
	unsigned capacity;
	unsigned zeros;
	struct mk_uint64_s len;
	int i;

	mk_assert(self);
	mk_assert(digest);

	idx = mk_uint64_to_int(&self->m_len) % 64;
	capacity = 64 - idx;
	zeros =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity + 64 - s_mandatory_padding_len);

	#undef s_mandatory_padding_len
	#undef s_worst_padding_len

	padding[0] = (unsigned char)(1u << 7);

	memset(padding + 1, 0, zeros);

	mk_uint64_shl(&len, &self->m_len, 3);
	mk_uint64_to_buff_be(&len, padding + 1 + zeros);

	mk_sha1_append(self, padding, 1 + zeros + sizeof(struct mk_uint64_s));

	for(i = 0; i != 5; ++i)
	{
		mk_uint32_to_buff_be(&self->m_abcde[i], (unsigned char*)digest + i * sizeof(struct mk_uint32_s));
	}
}
