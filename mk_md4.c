#include "mk_md4.h"

#include "mk_endian.h"

#include <assert.h> /* assert, static_assert */ /* C11 */
#include <limits.h> /* CHAR_BIT */
#include <stdalign.h> /* alignof */ /* C11 */
#include <stddef.h> /* NULL */
#include <stdint.h> /* uintptr_t */
#include <string.h> /* memcpy, memset */


static_assert(CHAR_BIT == 8, "Must have 8bit byte.");


#define mk_md4_detail_block_size (16 * sizeof(uint32_t)) /* 16 32bit words, 64 bytes, 512 bits */


static inline uint32_t mk_md4_detail_f(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) | ((~x) & z);
}

static inline uint32_t mk_md4_detail_g(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) | (x & z) | (y & z);
}

static inline uint32_t mk_md4_detail_h(uint32_t x, uint32_t y, uint32_t z)
{
	return x ^ y ^ z;
}

static inline uint32_t mk_md4_detail_rot(uint32_t x, int s)
{
	assert(s > 0);
	assert(s < 32);

	return (x << s) | (x >> (32 - s));
}

static inline uint32_t mk_md4_detail_round_1(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int k, int s, uint32_t const* x)
{
	assert(k >= 0);
	assert(k < 16);
	assert(x);

	return mk_md4_detail_rot(a + mk_md4_detail_f(b, c, d) + x[k], s);
}

static inline uint32_t mk_md4_detail_round_2(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int k, int s, uint32_t const* x)
{
	assert(k >= 0);
	assert(k < 16);
	assert(x);

	return mk_md4_detail_rot(a + mk_md4_detail_g(b, c, d) + x[k] + 0x5a827999, s);
}

static inline uint32_t mk_md4_detail_round_3(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int k, int s, uint32_t const* x)
{
	assert(k >= 0);
	assert(k < 16);
	assert(x);

	return mk_md4_detail_rot(a + mk_md4_detail_h(b, c, d) + x[k] + 0x6ed9eba1, s);
}

static void mk_md4_detail_process_block(struct mk_md4_state_s* self, void const* aligned_data)
{
	assert(self);

	uint32_t const* x;
#if MK_ENDIAN == MK_ENDIAN_LITTLE
	assert(!aligned_data || (((uintptr_t)aligned_data) % alignof(uint32_t)) == 0);
	x = aligned_data ? (uint32_t const*)aligned_data : self->m_block.m_words;
#else
	(void)aligned_data;
	uint32_t xx[16];
	for(int i = 0; i != 16; ++i)
	{
		xx[i] =
			((uint32_t)(self->m_block.m_bytes[i * sizeof(uint32_t) + 0])) << (0 * 8) |
			((uint32_t)(self->m_block.m_bytes[i * sizeof(uint32_t) + 1])) << (1 * 8) |
			((uint32_t)(self->m_block.m_bytes[i * sizeof(uint32_t) + 2])) << (2 * 8) |
			((uint32_t)(self->m_block.m_bytes[i * sizeof(uint32_t) + 3])) << (3 * 8);
	}
	x = xx;
#endif

	uint32_t aa = self->m_abcd[0];
	uint32_t bb = self->m_abcd[1];
	uint32_t cc = self->m_abcd[2];
	uint32_t dd = self->m_abcd[3];

	uint32_t a = aa;
	uint32_t b = bb;
	uint32_t c = cc;
	uint32_t d = dd;

	a = mk_md4_detail_round_1(a, b, c, d,  0,  3, x);
	d = mk_md4_detail_round_1(d, a, b, c,  1,  7, x);
	c = mk_md4_detail_round_1(c, d, a, b,  2, 11, x);
	b = mk_md4_detail_round_1(b, c, d, a,  3, 19, x);

	a = mk_md4_detail_round_1(a, b, c, d,  4,  3, x);
	d = mk_md4_detail_round_1(d, a, b, c,  5,  7, x);
	c = mk_md4_detail_round_1(c, d, a, b,  6, 11, x);
	b = mk_md4_detail_round_1(b, c, d, a,  7, 19, x);

	a = mk_md4_detail_round_1(a, b, c, d,  8,  3, x);
	d = mk_md4_detail_round_1(d, a, b, c,  9,  7, x);
	c = mk_md4_detail_round_1(c, d, a, b, 10, 11, x);
	b = mk_md4_detail_round_1(b, c, d, a, 11, 19, x);

	a = mk_md4_detail_round_1(a, b, c, d, 12,  3, x);
	d = mk_md4_detail_round_1(d, a, b, c, 13,  7, x);
	c = mk_md4_detail_round_1(c, d, a, b, 14, 11, x);
	b = mk_md4_detail_round_1(b, c, d, a, 15, 19, x);

	a = mk_md4_detail_round_2(a, b, c, d,  0,  3, x);
	d = mk_md4_detail_round_2(d, a, b, c,  4,  5, x);
	c = mk_md4_detail_round_2(c, d, a, b,  8,  9, x);
	b = mk_md4_detail_round_2(b, c, d, a, 12, 13, x);

	a = mk_md4_detail_round_2(a, b, c, d,  1,  3, x);
	d = mk_md4_detail_round_2(d, a, b, c,  5,  5, x);
	c = mk_md4_detail_round_2(c, d, a, b,  9,  9, x);
	b = mk_md4_detail_round_2(b, c, d, a, 13, 13, x);

	a = mk_md4_detail_round_2(a, b, c, d,  2,  3, x);
	d = mk_md4_detail_round_2(d, a, b, c,  6,  5, x);
	c = mk_md4_detail_round_2(c, d, a, b, 10,  9, x);
	b = mk_md4_detail_round_2(b, c, d, a, 14, 13, x);

	a = mk_md4_detail_round_2(a, b, c, d,  3,  3, x);
	d = mk_md4_detail_round_2(d, a, b, c,  7,  5, x);
	c = mk_md4_detail_round_2(c, d, a, b, 11,  9, x);
	b = mk_md4_detail_round_2(b, c, d, a, 15, 13, x);

	a = mk_md4_detail_round_3(a, b, c, d,  0,  3, x);
	d = mk_md4_detail_round_3(d, a, b, c,  8,  9, x);
	c = mk_md4_detail_round_3(c, d, a, b,  4, 11, x);
	b = mk_md4_detail_round_3(b, c, d, a, 12, 15, x);

	a = mk_md4_detail_round_3(a, b, c, d,  2,  3, x);
	d = mk_md4_detail_round_3(d, a, b, c, 10,  9, x);
	c = mk_md4_detail_round_3(c, d, a, b,  6, 11, x);
	b = mk_md4_detail_round_3(b, c, d, a, 14, 15, x);

	a = mk_md4_detail_round_3(a, b, c, d,  1,  3, x);
	d = mk_md4_detail_round_3(d, a, b, c,  9,  9, x);
	c = mk_md4_detail_round_3(c, d, a, b,  5, 11, x);
	b = mk_md4_detail_round_3(b, c, d, a, 13, 15, x);

	a = mk_md4_detail_round_3(a, b, c, d,  3,  3, x);
	d = mk_md4_detail_round_3(d, a, b, c, 11,  9, x);
	c = mk_md4_detail_round_3(c, d, a, b,  7, 11, x);
	b = mk_md4_detail_round_3(b, c, d, a, 15, 15, x);

	a += aa;
	b += bb;
	c += cc;
	d += dd;

	self->m_abcd[0] = a;
	self->m_abcd[1] = b;
	self->m_abcd[2] = c;
	self->m_abcd[3] = d;
}


void mk_md4_init(struct mk_md4_state_s* self)
{
	assert(self);

	self->m_abcd[0] = (uint32_t)0x67452301;
	self->m_abcd[1] = (uint32_t)0xefcdab89;
	self->m_abcd[2] = (uint32_t)0x98badcfe;
	self->m_abcd[3] = (uint32_t)0x10325476;
	self->m_len = 0;
}

void mk_md4_append(struct mk_md4_state_s* self, void const* data, size_t len)
{
	assert(self);

	if(len == 0)
	{
		return;
	}

	unsigned char const* input = (unsigned char const*)data;
	size_t remaining = len;

	unsigned idx = self->m_len % mk_md4_detail_block_size;
	if(idx != 0)
	{
		unsigned capacity = mk_md4_detail_block_size - idx;
		unsigned to_copy = remaining < capacity ? (unsigned)remaining : capacity;
		memcpy(self->m_block.m_bytes + idx, input, to_copy);
		input += to_copy;
		remaining -= to_copy;
		int buffer_full = to_copy == capacity;
		if(buffer_full)
		{
			mk_md4_detail_process_block(self, NULL);
		}
	}

	size_t blocks = remaining / mk_md4_detail_block_size;
#if MK_ENDIAN == MK_ENDIAN_LITTLE
	if((((uintptr_t)input) % alignof(uint32_t)) == 0)
	{
		for(size_t i = 0; i != blocks; ++i)
		{
			mk_md4_detail_process_block(self, input);
			input += mk_md4_detail_block_size;
		}
	}
	else
#endif
	{
		for(size_t i = 0; i != blocks; ++i)
		{
			memcpy(self->m_block.m_bytes, input, mk_md4_detail_block_size);
			mk_md4_detail_process_block(self, NULL);
			input += mk_md4_detail_block_size;
		}
	}
	remaining -= blocks * mk_md4_detail_block_size;

	assert(remaining < mk_md4_detail_block_size);
	if(remaining != 0)
	{
		memcpy(self->m_block.m_bytes, input, remaining);
	}

	self->m_len += len;
}

void mk_md4_finish(struct mk_md4_state_s* self, struct mk_md4_digest_s* digest)
{
	assert(self);
	assert(digest);

	#define s_mandatory_padding_len (1 + sizeof(uint64_t))
	#define s_worst_case_buff_len (mk_md4_detail_block_size + s_mandatory_padding_len - 1)

	unsigned idx = self->m_len % mk_md4_detail_block_size;
	unsigned capacity = mk_md4_detail_block_size - idx;
	unsigned padding_len =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity + mk_md4_detail_block_size - s_mandatory_padding_len);

	unsigned char buff[s_worst_case_buff_len];
	buff[0] = (unsigned char)(1u << 7);
	memset(buff + 1, 0, padding_len);
	uint64_t len = self->m_len * 8;
#if MK_ENDIAN == MK_ENDIAN_LITTLE
	memcpy(buff + 1 + padding_len, &len, sizeof(uint64_t));
#else
	buff[1 + padding_len + 0] = (unsigned char)((len >> (8 * 0)) & 0xff);
	buff[1 + padding_len + 1] = (unsigned char)((len >> (8 * 1)) & 0xff);
	buff[1 + padding_len + 2] = (unsigned char)((len >> (8 * 2)) & 0xff);
	buff[1 + padding_len + 3] = (unsigned char)((len >> (8 * 3)) & 0xff);
	buff[1 + padding_len + 4] = (unsigned char)((len >> (8 * 4)) & 0xff);
	buff[1 + padding_len + 5] = (unsigned char)((len >> (8 * 5)) & 0xff);
	buff[1 + padding_len + 6] = (unsigned char)((len >> (8 * 6)) & 0xff);
	buff[1 + padding_len + 7] = (unsigned char)((len >> (8 * 7)) & 0xff);
#endif
	mk_md4_append(self, buff, padding_len + s_mandatory_padding_len);
	assert(self->m_len % mk_md4_detail_block_size == 0);

#if MK_ENDIAN == MK_ENDIAN_LITTLE
	static_assert(sizeof(digest->m_data.m_words) == sizeof(self->m_abcd), "");
	memcpy(digest->m_data.m_words, self->m_abcd, sizeof(digest->m_data.m_words));
#else
	digest->m_data.m_bytes[ 0] = (unsigned char)((self->m_abcd[0] >> (8 * 0)) & 0xff);
	digest->m_data.m_bytes[ 1] = (unsigned char)((self->m_abcd[0] >> (8 * 1)) & 0xff);
	digest->m_data.m_bytes[ 2] = (unsigned char)((self->m_abcd[0] >> (8 * 2)) & 0xff);
	digest->m_data.m_bytes[ 3] = (unsigned char)((self->m_abcd[0] >> (8 * 3)) & 0xff);
	digest->m_data.m_bytes[ 4] = (unsigned char)((self->m_abcd[1] >> (8 * 0)) & 0xff);
	digest->m_data.m_bytes[ 5] = (unsigned char)((self->m_abcd[1] >> (8 * 1)) & 0xff);
	digest->m_data.m_bytes[ 6] = (unsigned char)((self->m_abcd[1] >> (8 * 2)) & 0xff);
	digest->m_data.m_bytes[ 7] = (unsigned char)((self->m_abcd[1] >> (8 * 3)) & 0xff);
	digest->m_data.m_bytes[ 8] = (unsigned char)((self->m_abcd[2] >> (8 * 0)) & 0xff);
	digest->m_data.m_bytes[ 9] = (unsigned char)((self->m_abcd[2] >> (8 * 1)) & 0xff);
	digest->m_data.m_bytes[10] = (unsigned char)((self->m_abcd[2] >> (8 * 2)) & 0xff);
	digest->m_data.m_bytes[11] = (unsigned char)((self->m_abcd[2] >> (8 * 3)) & 0xff);
	digest->m_data.m_bytes[12] = (unsigned char)((self->m_abcd[3] >> (8 * 0)) & 0xff);
	digest->m_data.m_bytes[13] = (unsigned char)((self->m_abcd[3] >> (8 * 1)) & 0xff);
	digest->m_data.m_bytes[14] = (unsigned char)((self->m_abcd[3] >> (8 * 2)) & 0xff);
	digest->m_data.m_bytes[15] = (unsigned char)((self->m_abcd[3] >> (8 * 3)) & 0xff);
#endif

	#undef s_mandatory_padding_len
	#undef s_worst_case_buff_len
}


#undef mk_md4_detail_block_size
