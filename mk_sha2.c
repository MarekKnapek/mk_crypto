#include "mk_sha2.h"

#include <assert.h> /* assert static_assert */
#include <limits.h> /* CHAR_BIT */
#include <string.h> /* memcpy memset */


static_assert(CHAR_BIT == 8, "Must have 8bit byte.");


static uint32_t const mk_sha2_256_detail_table[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};


static inline uint32_t mk_sha2_256_detail_shr(uint32_t x, int n)
{
	assert(n >= 0 && n < 32);

	return x >> n;
}

static inline uint32_t mk_sha2_256_detail_rotr(uint32_t x, int n)
{
	assert(n >= 0 && n < 32);

	return (x >> n) | (x << (32 - n));
}

static inline uint32_t mk_sha2_256_detail_ch(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) ^ ((~x) & z);
}

static inline uint32_t mk_sha2_256_detail_maj(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}

static inline uint32_t mk_sha2_256_detail_sum0(uint32_t x)
{
	return
		mk_sha2_256_detail_rotr(x, 2) ^
		mk_sha2_256_detail_rotr(x, 13) ^
		mk_sha2_256_detail_rotr(x, 22);
}

static inline uint32_t mk_sha2_256_detail_sum1(uint32_t x)
{
	return
		mk_sha2_256_detail_rotr(x, 6) ^
		mk_sha2_256_detail_rotr(x, 11) ^
		mk_sha2_256_detail_rotr(x, 25);
}

static inline uint32_t mk_sha2_256_detail_sig0(uint32_t x)
{
	return
		mk_sha2_256_detail_rotr(x, 7) ^
		mk_sha2_256_detail_rotr(x, 18) ^
		mk_sha2_256_detail_shr(x, 3);
}

static inline uint32_t mk_sha2_256_detail_sig1(uint32_t x)
{
	return
		mk_sha2_256_detail_rotr(x, 17) ^
		mk_sha2_256_detail_rotr(x, 19) ^
		mk_sha2_256_detail_shr(x, 10);
}

static inline void mk_sha2_256_detail_process_block(struct mk_sha2_256_state_s* self, void const* data)
{
	assert(self);
	assert(data);

	unsigned char const* input = (unsigned char const*)data;

	uint32_t w[64];
	uint32_t hh[8];
	uint32_t t1;
	uint32_t t2;

	uint32_t* a = hh + 0;
	uint32_t* b = hh + 1;
	uint32_t* c = hh + 2;
	uint32_t* d = hh + 3;
	uint32_t* e = hh + 4;
	uint32_t* f = hh + 5;
	uint32_t* g = hh + 6;
	uint32_t* h = hh + 7;

	for(int i = 0; i != 16; ++i)
	{
		w[i] =
			(((uint32_t)(input[i * 4 + 0])) << (3 * 8)) |
			(((uint32_t)(input[i * 4 + 1])) << (2 * 8)) |
			(((uint32_t)(input[i * 4 + 2])) << (1 * 8)) |
			(((uint32_t)(input[i * 4 + 3])) << (0 * 8));
	}
	for(int i = 16; i != 64; ++i)
	{
		w[i] = mk_sha2_256_detail_sig1(w[i - 2]) + w[i - 7] + mk_sha2_256_detail_sig0(w[i - 15]) + w[i - 16];
	}

	*a = self->m_hash[0];
	*b = self->m_hash[1];
	*c = self->m_hash[2];
	*d = self->m_hash[3];
	*e = self->m_hash[4];
	*f = self->m_hash[5];
	*g = self->m_hash[6];
	*h = self->m_hash[7];

	for(int i = 0; i != 64; ++i)
	{
		t1 = *h + mk_sha2_256_detail_sum1(*e) + mk_sha2_256_detail_ch(*e, *f, *g) + mk_sha2_256_detail_table[i] + w[i];
		t2 = mk_sha2_256_detail_sum0(*a) + mk_sha2_256_detail_maj(*a, *b, *c);
		*h = *g;
		*g = *f;
		*f = *e;
		*e = *d + t1;
		*d = *c;
		*c = *b;
		*b = *a;
		*a = t1 + t2;
	}

	self->m_hash[0] += *a;
	self->m_hash[1] += *b;
	self->m_hash[2] += *c;
	self->m_hash[3] += *d;
	self->m_hash[4] += *e;
	self->m_hash[5] += *f;
	self->m_hash[6] += *g;
	self->m_hash[7] += *h;
}


void mk_sha2_224_init(struct mk_sha2_224_state_s* self)
{
	assert(self);

	self->m_hash[0] = 0xc1059ed8;
	self->m_hash[1] = 0x367cd507;
	self->m_hash[2] = 0x3070dd17;
	self->m_hash[3] = 0xf70e5939;
	self->m_hash[4] = 0xffc00b31;
	self->m_hash[5] = 0x68581511;
	self->m_hash[6] = 0x64f98fa7;
	self->m_hash[7] = 0xbefa4fa4;
	self->m_len = 0;
}

void mk_sha2_224_append(struct mk_sha2_224_state_s* self, void const* data, size_t len)
{
	mk_sha2_256_append((struct mk_sha2_256_state_s*)self, data, len);
}

void mk_sha2_224_finish(struct mk_sha2_224_state_s* self, void* digest)
{
	assert(self);
	assert(digest);

	unsigned char sha2_256_digest[32];

	mk_sha2_256_finish((struct mk_sha2_256_state_s*)self, &sha2_256_digest);

	memcpy(digest, &sha2_256_digest, 28);
}


void mk_sha2_256_init(struct mk_sha2_256_state_s* self)
{
	assert(self);

	self->m_hash[0] = 0x6a09e667;
	self->m_hash[1] = 0xbb67ae85;
	self->m_hash[2] = 0x3c6ef372;
	self->m_hash[3] = 0xa54ff53a;
	self->m_hash[4] = 0x510e527f;
	self->m_hash[5] = 0x9b05688c;
	self->m_hash[6] = 0x1f83d9ab;
	self->m_hash[7] = 0x5be0cd19;
	self->m_len = 0;
}

void mk_sha2_256_append(struct mk_sha2_256_state_s* self, void const* data, size_t len)
{
	assert(self);
	
	unsigned char const* input = (unsigned char const*)data;
	size_t remaining = len;

	unsigned idx = self->m_len % 64;
	unsigned capacity = 64 - idx;
	self->m_len += len;
	if(remaining >= capacity)
	{
		memcpy(self->m_block + idx, input, capacity);
		mk_sha2_256_detail_process_block(self, self->m_block);
		input += capacity;
		remaining -= capacity;
		size_t blocks = remaining / 64;
		for(size_t i = 0; i != blocks; ++i)
		{
			mk_sha2_256_detail_process_block(self, input);
			input += 64;
		}
		remaining -= blocks * 64;
		idx = 0;
	}
	memcpy(self->m_block + idx, input, remaining);
}

void mk_sha2_256_finish(struct mk_sha2_256_state_s* self, void* digest)
{
	assert(self);
	assert(digest);

	#define s_mandatory_padding_len (1 + sizeof(uint64_t))
	#define s_worst_padding_len (64 + s_mandatory_padding_len - 1)
	
	unsigned char padding[s_worst_padding_len];

	unsigned idx = self->m_len % 64;
	unsigned capacity = 64 - idx;
	unsigned zeros =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity + 64 - s_mandatory_padding_len);

	#undef s_mandatory_padding_len
	#undef s_worst_padding_len

	padding[0] = (unsigned char)(1u << 7);

	memset(padding + 1, 0, zeros);

	uint64_t len = self->m_len * 8;
	padding[1 + zeros + 0] = (unsigned char)((len >> (8 * 7)) & 0xff);
	padding[1 + zeros + 1] = (unsigned char)((len >> (8 * 6)) & 0xff);
	padding[1 + zeros + 2] = (unsigned char)((len >> (8 * 5)) & 0xff);
	padding[1 + zeros + 3] = (unsigned char)((len >> (8 * 4)) & 0xff);
	padding[1 + zeros + 4] = (unsigned char)((len >> (8 * 3)) & 0xff);
	padding[1 + zeros + 5] = (unsigned char)((len >> (8 * 2)) & 0xff);
	padding[1 + zeros + 6] = (unsigned char)((len >> (8 * 1)) & 0xff);
	padding[1 + zeros + 7] = (unsigned char)((len >> (8 * 0)) & 0xff);

	mk_sha2_256_append(self, padding, 1 + zeros + sizeof(uint64_t));

	unsigned char* output = (unsigned char*)digest;
	output[ 0] = (unsigned char)((self->m_hash[0] >> (8 * 3)) & 0xff);
	output[ 1] = (unsigned char)((self->m_hash[0] >> (8 * 2)) & 0xff);
	output[ 2] = (unsigned char)((self->m_hash[0] >> (8 * 1)) & 0xff);
	output[ 3] = (unsigned char)((self->m_hash[0] >> (8 * 0)) & 0xff);
	output[ 4] = (unsigned char)((self->m_hash[1] >> (8 * 3)) & 0xff);
	output[ 5] = (unsigned char)((self->m_hash[1] >> (8 * 2)) & 0xff);
	output[ 6] = (unsigned char)((self->m_hash[1] >> (8 * 1)) & 0xff);
	output[ 7] = (unsigned char)((self->m_hash[1] >> (8 * 0)) & 0xff);
	output[ 8] = (unsigned char)((self->m_hash[2] >> (8 * 3)) & 0xff);
	output[ 9] = (unsigned char)((self->m_hash[2] >> (8 * 2)) & 0xff);
	output[10] = (unsigned char)((self->m_hash[2] >> (8 * 1)) & 0xff);
	output[11] = (unsigned char)((self->m_hash[2] >> (8 * 0)) & 0xff);
	output[12] = (unsigned char)((self->m_hash[3] >> (8 * 3)) & 0xff);
	output[13] = (unsigned char)((self->m_hash[3] >> (8 * 2)) & 0xff);
	output[14] = (unsigned char)((self->m_hash[3] >> (8 * 1)) & 0xff);
	output[15] = (unsigned char)((self->m_hash[3] >> (8 * 0)) & 0xff);
	output[16] = (unsigned char)((self->m_hash[4] >> (8 * 3)) & 0xff);
	output[17] = (unsigned char)((self->m_hash[4] >> (8 * 2)) & 0xff);
	output[18] = (unsigned char)((self->m_hash[4] >> (8 * 1)) & 0xff);
	output[19] = (unsigned char)((self->m_hash[4] >> (8 * 0)) & 0xff);
	output[20] = (unsigned char)((self->m_hash[5] >> (8 * 3)) & 0xff);
	output[21] = (unsigned char)((self->m_hash[5] >> (8 * 2)) & 0xff);
	output[22] = (unsigned char)((self->m_hash[5] >> (8 * 1)) & 0xff);
	output[23] = (unsigned char)((self->m_hash[5] >> (8 * 0)) & 0xff);
	output[24] = (unsigned char)((self->m_hash[6] >> (8 * 3)) & 0xff);
	output[25] = (unsigned char)((self->m_hash[6] >> (8 * 2)) & 0xff);
	output[26] = (unsigned char)((self->m_hash[6] >> (8 * 1)) & 0xff);
	output[27] = (unsigned char)((self->m_hash[6] >> (8 * 0)) & 0xff);
	output[28] = (unsigned char)((self->m_hash[7] >> (8 * 3)) & 0xff);
	output[29] = (unsigned char)((self->m_hash[7] >> (8 * 2)) & 0xff);
	output[30] = (unsigned char)((self->m_hash[7] >> (8 * 1)) & 0xff);
	output[31] = (unsigned char)((self->m_hash[7] >> (8 * 0)) & 0xff);
}
