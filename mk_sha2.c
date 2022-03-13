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

static uint64_t const mk_sha2_512_detail_table[80] =
{
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817,
};


static inline void mk_sha2_detail_ints2be32(uint32_t const* input, int n, void* buff)
{
	unsigned char* output = (unsigned char*)buff;

	for(int i = 0; i != n; ++i)
	{
		for(int j = 0; j != sizeof(uint32_t); ++j)
		{
			output[i * sizeof(uint32_t) + j] = (unsigned char)((input[i] >> (CHAR_BIT * (sizeof(uint32_t) - 1 - j))) & 0xff);
		}
	}
}

static inline void mk_sha2_detail_be2ints32(void const* buff, uint32_t* output, int n)
{
	unsigned char const* input = (unsigned char const*)buff;

	for(int i = 0; i != n; ++i)
	{
		output[i] = 0;
		for(int j = 0; j != sizeof(uint32_t); ++j)
		{
			output[i] |= ((uint32_t)(input[i * sizeof(uint32_t) + j])) << (CHAR_BIT * (sizeof(uint32_t) - 1 - j));
		}
	}
}

static inline void mk_sha2_detail_ints2be64(uint64_t const* input, int n, void* buff)
{
	unsigned char* output = (unsigned char*)buff;

	for(int i = 0; i != n; ++i)
	{
		for(int j = 0; j != sizeof(uint64_t); ++j)
		{
			output[i * sizeof(uint64_t) + j] = (unsigned char)((input[i] >> (CHAR_BIT * (sizeof(uint64_t) - 1 - j))) & 0xff);
		}
	}
}

static inline void mk_sha2_detail_be2ints64(void const* buff, uint64_t* output, int n)
{
	unsigned char const* input = (unsigned char const*)buff;

	for(int i = 0; i != n; ++i)
	{
		output[i] = 0;
		for(int j = 0; j != sizeof(uint64_t); ++j)
		{
			output[i] |= ((uint64_t)(input[i * sizeof(uint64_t) + j])) << (CHAR_BIT * (sizeof(uint64_t) - 1 - j));
		}
	}
}

static inline uint32_t mk_sha2_256_detail_shr(uint32_t x, int n)
{
	assert(n >= 0 && n < 32);

	return x >> n;
}

static inline uint64_t mk_sha2_512_detail_shr(uint64_t x, int n)
{
	assert(n >= 0 && n < 64);

	return x >> n;
}

static inline uint32_t mk_sha2_256_detail_rotr(uint32_t x, int n)
{
	assert(n >= 0 && n < 32);

	return (x >> n) | (x << (32 - n));
}

static inline uint64_t mk_sha2_512_detail_rotr(uint64_t x, int n)
{
	assert(n >= 0 && n < 64);

	return (x >> n) | (x << (64 - n));
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

static inline uint64_t mk_sha2_512_detail_ch(uint64_t x, uint64_t y, uint64_t z)
{
	return (x & y) ^ ((~x) & z);
}

static inline uint64_t mk_sha2_512_detail_maj(uint64_t x, uint64_t y, uint64_t z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}

static inline uint64_t mk_sha2_512_detail_sum0(uint64_t x)
{
	return
		mk_sha2_512_detail_rotr(x, 28) ^
		mk_sha2_512_detail_rotr(x, 34) ^
		mk_sha2_512_detail_rotr(x, 39);
}

static inline uint64_t mk_sha2_512_detail_sum1(uint64_t x)
{
	return
		mk_sha2_512_detail_rotr(x, 14) ^
		mk_sha2_512_detail_rotr(x, 18) ^
		mk_sha2_512_detail_rotr(x, 41);
}

static inline uint64_t mk_sha2_512_detail_sig0(uint64_t x)
{
	return
		mk_sha2_512_detail_rotr(x, 1) ^
		mk_sha2_512_detail_rotr(x, 8) ^
		mk_sha2_512_detail_shr(x, 7);
}

static inline uint64_t mk_sha2_512_detail_sig1(uint64_t x)
{
	return
		mk_sha2_512_detail_rotr(x, 19) ^
		mk_sha2_512_detail_rotr(x, 61) ^
		mk_sha2_512_detail_shr(x, 6);
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

	mk_sha2_detail_be2ints32(input, w, 16);
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

static inline void mk_sha2_512_detail_process_block(struct mk_sha2_512_state_s* self, void const* data)
{
	assert(self);
	assert(data);

	unsigned char const* input = (unsigned char const*)data;

	uint64_t w[80];
	uint64_t hh[8];
	uint64_t t1;
	uint64_t t2;

	uint64_t* a = hh + 0;
	uint64_t* b = hh + 1;
	uint64_t* c = hh + 2;
	uint64_t* d = hh + 3;
	uint64_t* e = hh + 4;
	uint64_t* f = hh + 5;
	uint64_t* g = hh + 6;
	uint64_t* h = hh + 7;

	mk_sha2_detail_be2ints64(input, w, 16);
	for(int i = 16; i != 80; ++i)
	{
		w[i] = mk_sha2_512_detail_sig1(w[i - 2]) + w[i - 7] + mk_sha2_512_detail_sig0(w[i - 15]) + w[i - 16];
	}

	*a = self->m_hash[0];
	*b = self->m_hash[1];
	*c = self->m_hash[2];
	*d = self->m_hash[3];
	*e = self->m_hash[4];
	*f = self->m_hash[5];
	*g = self->m_hash[6];
	*h = self->m_hash[7];

	for(int i = 0; i != 80; ++i)
	{
		t1 = *h + mk_sha2_512_detail_sum1(*e) + mk_sha2_512_detail_ch(*e, *f, *g) + mk_sha2_512_detail_table[i] + w[i];
		t2 = mk_sha2_512_detail_sum0(*a) + mk_sha2_512_detail_maj(*a, *b, *c);
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


void mk_sha2_256_224_init(struct mk_sha2_256_224_state_s* self)
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

void mk_sha2_256_224_append(struct mk_sha2_256_224_state_s* self, void const* data, size_t len)
{
	mk_sha2_256_append((struct mk_sha2_256_state_s*)self, data, len);
}

void mk_sha2_256_224_finish(struct mk_sha2_256_224_state_s* self, void* digest)
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
	mk_sha2_detail_ints2be64(&len, 1, padding + 1 + zeros);

	mk_sha2_256_append(self, padding, 1 + zeros + sizeof(uint64_t));

	mk_sha2_detail_ints2be32(self->m_hash, 8, digest);
}


void mk_sha2_512_224_init(struct mk_sha2_512_224_state_s* self)
{
	assert(self);

	self->m_hash[0] = 0x8c3d37c819544da2;
	self->m_hash[1] = 0x73e1996689dcd4d6;
	self->m_hash[2] = 0x1dfab7ae32ff9c82;
	self->m_hash[3] = 0x679dd514582f9fcf;
	self->m_hash[4] = 0x0f6d2b697bd44da8;
	self->m_hash[5] = 0x77e36f7304c48942;
	self->m_hash[6] = 0x3f9d85a86a1d36c8;
	self->m_hash[7] = 0x1112e6ad91d692a1;
	mk_uint128_zero_(&self->m_len);
}

void mk_sha2_512_224_append(struct mk_sha2_512_224_state_s* self, void const* data, size_t len)
{
	mk_sha2_512_append((struct mk_sha2_512_state_s*)self, data, len);
}

void mk_sha2_512_224_finish(struct mk_sha2_512_224_state_s* self, void* digest)
{
	assert(self);
	assert(digest);

	unsigned char sha2_512_digest[64];

	mk_sha2_512_finish((struct mk_sha2_512_state_s*)self, &sha2_512_digest);

	memcpy(digest, &sha2_512_digest, 28);
}


void mk_sha2_512_256_init(struct mk_sha2_512_256_state_s* self)
{
	assert(self);

	self->m_hash[0] = 0x22312194fc2bf72c;
	self->m_hash[1] = 0x9f555fa3c84c64c2;
	self->m_hash[2] = 0x2393b86b6f53b151;
	self->m_hash[3] = 0x963877195940eabd;
	self->m_hash[4] = 0x96283ee2a88effe3;
	self->m_hash[5] = 0xbe5e1e2553863992;
	self->m_hash[6] = 0x2b0199fc2c85b8aa;
	self->m_hash[7] = 0x0eb72ddc81c52ca2;
	mk_uint128_zero_(&self->m_len);
}

void mk_sha2_512_256_append(struct mk_sha2_512_256_state_s* self, void const* data, size_t len)
{
	mk_sha2_512_append((struct mk_sha2_512_state_s*)self, data, len);
}

void mk_sha2_512_256_finish(struct mk_sha2_512_256_state_s* self, void* digest)
{
	assert(self);
	assert(digest);

	unsigned char sha2_512_digest[64];

	mk_sha2_512_finish((struct mk_sha2_512_state_s*)self, &sha2_512_digest);

	memcpy(digest, &sha2_512_digest, 32);
}


void mk_sha2_512_384_init(struct mk_sha2_512_384_state_s* self)
{
	assert(self);

	self->m_hash[0] = 0xcbbb9d5dc1059ed8;
	self->m_hash[1] = 0x629a292a367cd507;
	self->m_hash[2] = 0x9159015a3070dd17;
	self->m_hash[3] = 0x152fecd8f70e5939;
	self->m_hash[4] = 0x67332667ffc00b31;
	self->m_hash[5] = 0x8eb44a8768581511;
	self->m_hash[6] = 0xdb0c2e0d64f98fa7;
	self->m_hash[7] = 0x47b5481dbefa4fa4;
	mk_uint128_zero_(&self->m_len);
}

void mk_sha2_512_384_append(struct mk_sha2_512_384_state_s* self, void const* data, size_t len)
{
	mk_sha2_512_append((struct mk_sha2_512_state_s*)self, data, len);
}

void mk_sha2_512_384_finish(struct mk_sha2_512_384_state_s* self, void* digest)
{
	assert(self);
	assert(digest);

	unsigned char sha2_512_digest[64];

	mk_sha2_512_finish((struct mk_sha2_512_state_s*)self, &sha2_512_digest);

	memcpy(digest, &sha2_512_digest, 48);
}


void mk_sha2_512_init(struct mk_sha2_512_state_s* self)
{
	assert(self);

	self->m_hash[0] = 0x6a09e667f3bcc908;
	self->m_hash[1] = 0xbb67ae8584caa73b;
	self->m_hash[2] = 0x3c6ef372fe94f82b;
	self->m_hash[3] = 0xa54ff53a5f1d36f1;
	self->m_hash[4] = 0x510e527fade682d1;
	self->m_hash[5] = 0x9b05688c2b3e6c1f;
	self->m_hash[6] = 0x1f83d9abfb41bd6b;
	self->m_hash[7] = 0x5be0cd19137e2179;
	mk_uint128_zero_(&self->m_len);
}

void mk_sha2_512_append(struct mk_sha2_512_state_s* self, void const* data, size_t len)
{
	assert(self);
	
	unsigned char const* input = (unsigned char const*)data;
	size_t remaining = len;

	unsigned idx = self->m_len.m_lo % 128;
	unsigned capacity = 128 - idx;
	mk_uint128_add_size_(&self->m_len, &self->m_len, len);
	if(remaining >= capacity)
	{
		memcpy(self->m_block + idx, input, capacity);
		mk_sha2_512_detail_process_block(self, self->m_block);
		input += capacity;
		remaining -= capacity;
		size_t blocks = remaining / 128;
		for(size_t i = 0; i != blocks; ++i)
		{
			mk_sha2_512_detail_process_block(self, input);
			input += 128;
		}
		remaining -= blocks * 128;
		idx = 0;
	}
	memcpy(self->m_block + idx, input, remaining);
}

void mk_sha2_512_finish(struct mk_sha2_512_state_s* self, void* digest)
{
	assert(self);
	assert(digest);

	#define s_mandatory_padding_len (1 + 2 * sizeof(uint64_t))
	#define s_worst_padding_len (128 + s_mandatory_padding_len - 1)
	
	unsigned char padding[s_worst_padding_len];

	unsigned idx = self->m_len.m_lo % 128;
	unsigned capacity = 128 - idx;
	unsigned zeros =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity + 128 - s_mandatory_padding_len);

	#undef s_mandatory_padding_len
	#undef s_worst_padding_len

	padding[0] = (unsigned char)(1u << 7);

	memset(padding + 1, 0, zeros);

	struct mk_uint128_s_ len;
	mk_uint128_shl_(&len, &self->m_len, 3);
	mk_sha2_detail_ints2be64(&len.m_hi, 1, padding + 1 + zeros + 0 * sizeof(uint64_t));
	mk_sha2_detail_ints2be64(&len.m_lo, 1, padding + 1 + zeros + 1 * sizeof(uint64_t));

	mk_sha2_512_append(self, padding, 1 + zeros + 2 * sizeof(uint64_t));

	mk_sha2_detail_ints2be64(self->m_hash, 8, digest);
}
