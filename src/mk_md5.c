#include "mk_md5.h"

#include "../utils/mk_align.h"
#include "../utils/mk_assert.h"
#include "../utils/mk_endian.h"
#include "../utils/mk_inline.h"

#include <stdint.h> /* uintptr_t */
#include <string.h> /* memcpy, memset */


#define mk_md5_detail_block_size (16 * sizeof(uint32_t)) /* 16 32bit words, 64 bytes, 512 bits */


static uint32_t const mk_md5_detail_table[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};


static mk_inline uint32_t mk_md5_detail_f(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) | ((~x) & z);
}

static mk_inline uint32_t mk_md5_detail_g(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & z) | (y & (~z));
}

static mk_inline uint32_t mk_md5_detail_h(uint32_t x, uint32_t y, uint32_t z)
{
	return x ^ y ^ z;
}

static mk_inline uint32_t mk_md5_detail_i(uint32_t x, uint32_t y, uint32_t z)
{
	return y ^ (x | (~z));
}

static mk_inline uint32_t mk_md5_detail_rot(uint32_t x, int s)
{
	mk_assert(s > 0);
	mk_assert(s < 32);

	return (x << s) | (x >> (32 - s));
}

static mk_inline uint32_t mk_md5_detail_round_1(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t const* x)
{
	mk_assert(k >= 0);
	mk_assert(k < 16);
	mk_assert(i - 1 >= 0);
	mk_assert(i - 1 < 64);
	mk_assert(x);

	return b + mk_md5_detail_rot(a + mk_md5_detail_f(b, c, d) + x[k] + mk_md5_detail_table[i - 1], s);
}

static mk_inline uint32_t mk_md5_detail_round_2(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t const* x)
{
	mk_assert(k >= 0);
	mk_assert(k < 16);
	mk_assert(i - 1 >= 0);
	mk_assert(i - 1 < 64);
	mk_assert(x);

	return b + mk_md5_detail_rot(a + mk_md5_detail_g(b, c, d) + x[k] + mk_md5_detail_table[i - 1], s);
}

static mk_inline uint32_t mk_md5_detail_round_3(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t const* x)
{
	mk_assert(k >= 0);
	mk_assert(k < 16);
	mk_assert(i - 1 >= 0);
	mk_assert(i - 1 < 64);
	mk_assert(x);

	return b + mk_md5_detail_rot(a + mk_md5_detail_h(b, c, d) + x[k] + mk_md5_detail_table[i - 1], s);
}

static mk_inline uint32_t mk_md5_detail_round_4(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int k, int s, int i, uint32_t const* x)
{
	mk_assert(k >= 0);
	mk_assert(k < 16);
	mk_assert(i - 1 >= 0);
	mk_assert(i - 1 < 64);
	mk_assert(x);

	return b + mk_md5_detail_rot(a + mk_md5_detail_i(b, c, d) + x[k] + mk_md5_detail_table[i - 1], s);
}

static void mk_md5_detail_process_block(struct mk_md5_state_s* self, void const* aligned_data)
{
	uint32_t const* x;
	uint32_t aa;
	uint32_t bb;
	uint32_t cc;
	uint32_t dd;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;

	mk_assert(self);
	mk_assert(aligned_data);
	mk_assert((((uintptr_t)aligned_data) % mk_alignof(uint32_t)) == 0);

	x = (uint32_t const*)aligned_data;

	aa = self->m_abcd[0];
	bb = self->m_abcd[1];
	cc = self->m_abcd[2];
	dd = self->m_abcd[3];

	a = aa;
	b = bb;
	c = cc;
	d = dd;

	a = mk_md5_detail_round_1(a, b, c, d,  0,  7,  1, x);
	d = mk_md5_detail_round_1(d, a, b, c,  1, 12,  2, x);
	c = mk_md5_detail_round_1(c, d, a, b,  2, 17,  3, x);
	b = mk_md5_detail_round_1(b, c, d, a,  3, 22,  4, x);

	a = mk_md5_detail_round_1(a, b, c, d,  4,  7,  5, x);
	d = mk_md5_detail_round_1(d, a, b, c,  5, 12,  6, x);
	c = mk_md5_detail_round_1(c, d, a, b,  6, 17,  7, x);
	b = mk_md5_detail_round_1(b, c, d, a,  7, 22,  8, x);

	a = mk_md5_detail_round_1(a, b, c, d,  8,  7,  9, x);
	d = mk_md5_detail_round_1(d, a, b, c,  9, 12, 10, x);
	c = mk_md5_detail_round_1(c, d, a, b, 10, 17, 11, x);
	b = mk_md5_detail_round_1(b, c, d, a, 11, 22, 12, x);

	a = mk_md5_detail_round_1(a, b, c, d, 12,  7, 13, x);
	d = mk_md5_detail_round_1(d, a, b, c, 13, 12, 14, x);
	c = mk_md5_detail_round_1(c, d, a, b, 14, 17, 15, x);
	b = mk_md5_detail_round_1(b, c, d, a, 15, 22, 16, x);

	a = mk_md5_detail_round_2(a, b, c, d,  1,  5, 17, x);
	d = mk_md5_detail_round_2(d, a, b, c,  6,  9, 18, x);
	c = mk_md5_detail_round_2(c, d, a, b, 11, 14, 19, x);
	b = mk_md5_detail_round_2(b, c, d, a,  0, 20, 20, x);

	a = mk_md5_detail_round_2(a, b, c, d,  5,  5, 21, x);
	d = mk_md5_detail_round_2(d, a, b, c, 10,  9, 22, x);
	c = mk_md5_detail_round_2(c, d, a, b, 15, 14, 23, x);
	b = mk_md5_detail_round_2(b, c, d, a,  4, 20, 24, x);

	a = mk_md5_detail_round_2(a, b, c, d,  9,  5, 25, x);
	d = mk_md5_detail_round_2(d, a, b, c, 14,  9, 26, x);
	c = mk_md5_detail_round_2(c, d, a, b,  3, 14, 27, x);
	b = mk_md5_detail_round_2(b, c, d, a,  8, 20, 28, x);

	a = mk_md5_detail_round_2(a, b, c, d, 13,  5, 29, x);
	d = mk_md5_detail_round_2(d, a, b, c,  2,  9, 30, x);
	c = mk_md5_detail_round_2(c, d, a, b,  7, 14, 31, x);
	b = mk_md5_detail_round_2(b, c, d, a, 12, 20, 32, x);

	a = mk_md5_detail_round_3(a, b, c, d,  5,  4, 33, x);
	d = mk_md5_detail_round_3(d, a, b, c,  8, 11, 34, x);
	c = mk_md5_detail_round_3(c, d, a, b, 11, 16, 35, x);
	b = mk_md5_detail_round_3(b, c, d, a, 14, 23, 36, x);

	a = mk_md5_detail_round_3(a, b, c, d,  1,  4, 37, x);
	d = mk_md5_detail_round_3(d, a, b, c,  4, 11, 38, x);
	c = mk_md5_detail_round_3(c, d, a, b,  7, 16, 39, x);
	b = mk_md5_detail_round_3(b, c, d, a, 10, 23, 40, x);

	a = mk_md5_detail_round_3(a, b, c, d, 13,  4, 41, x);
	d = mk_md5_detail_round_3(d, a, b, c,  0, 11, 42, x);
	c = mk_md5_detail_round_3(c, d, a, b,  3, 16, 43, x);
	b = mk_md5_detail_round_3(b, c, d, a,  6, 23, 44, x);

	a = mk_md5_detail_round_3(a, b, c, d,  9,  4, 45, x);
	d = mk_md5_detail_round_3(d, a, b, c, 12, 11, 46, x);
	c = mk_md5_detail_round_3(c, d, a, b, 15, 16, 47, x);
	b = mk_md5_detail_round_3(b, c, d, a,  2, 23, 48, x);

	a = mk_md5_detail_round_4(a, b, c, d,  0,  6, 49, x);
	d = mk_md5_detail_round_4(d, a, b, c,  7, 10, 50, x);
	c = mk_md5_detail_round_4(c, d, a, b, 14, 15, 51, x);
	b = mk_md5_detail_round_4(b, c, d, a,  5, 21, 52, x);

	a = mk_md5_detail_round_4(a, b, c, d, 12,  6, 53, x);
	d = mk_md5_detail_round_4(d, a, b, c,  3, 10, 54, x);
	c = mk_md5_detail_round_4(c, d, a, b, 10, 15, 55, x);
	b = mk_md5_detail_round_4(b, c, d, a,  1, 21, 56, x);

	a = mk_md5_detail_round_4(a, b, c, d,  8,  6, 57, x);
	d = mk_md5_detail_round_4(d, a, b, c, 15, 10, 58, x);
	c = mk_md5_detail_round_4(c, d, a, b,  6, 15, 59, x);
	b = mk_md5_detail_round_4(b, c, d, a, 13, 21, 60, x);

	a = mk_md5_detail_round_4(a, b, c, d,  4,  6, 61, x);
	d = mk_md5_detail_round_4(d, a, b, c, 11, 10, 62, x);
	c = mk_md5_detail_round_4(c, d, a, b,  2, 15, 63, x);
	b = mk_md5_detail_round_4(b, c, d, a,  9, 21, 64, x);

	a += aa;
	b += bb;
	c += cc;
	d += dd;

	self->m_abcd[0] = a;
	self->m_abcd[1] = b;
	self->m_abcd[2] = c;
	self->m_abcd[3] = d;
}


void mk_md5_init(struct mk_md5_state_s* self)
{
	mk_assert(self);

	self->m_abcd[0] = (uint32_t)0x67452301;
	self->m_abcd[1] = (uint32_t)0xefcdab89;
	self->m_abcd[2] = (uint32_t)0x98badcfe;
	self->m_abcd[3] = (uint32_t)0x10325476;
	self->m_len = 0;
}

void mk_md5_append(struct mk_md5_state_s* self, void const* data, size_t len)
{
	unsigned char const* input;
	size_t remaining;
	unsigned idx;
	unsigned capacity;
	unsigned to_copy;
	int buffer_full;
	size_t blocks;
	size_t i;

	mk_assert(self);

	if(len == 0)
	{
		return;
	}

	input = (unsigned char const*)data;
	remaining = len;

	idx = self->m_len % mk_md5_detail_block_size;
	if(idx != 0)
	{
		capacity = mk_md5_detail_block_size - idx;
		to_copy = remaining < capacity ? (unsigned)remaining : capacity;
		memcpy(self->m_block.m_bytes + idx, input, to_copy);
		input += to_copy;
		remaining -= to_copy;
		buffer_full = to_copy == capacity;
		if(buffer_full)
		{
			mk_md5_detail_process_block(self, self->m_block.m_words);
		}
	}

	blocks = remaining / mk_md5_detail_block_size;
#if MK_ENDIAN == MK_ENDIAN_LITTLE
	if((((uintptr_t)input) % mk_alignof(uint32_t)) == 0)
	{
		for(i = 0; i != blocks; ++i)
		{
			mk_md5_detail_process_block(self, input);
			input += mk_md5_detail_block_size;
		}
	}
	else
#endif
	{
		for(i = 0; i != blocks; ++i)
		{
			memcpy(self->m_block.m_bytes, input, mk_md5_detail_block_size);
			mk_md5_detail_process_block(self, self->m_block.m_words);
			input += mk_md5_detail_block_size;
		}
	}
	remaining -= blocks * mk_md5_detail_block_size;

	mk_assert(remaining < mk_md5_detail_block_size);
	if(remaining != 0)
	{
		memcpy(self->m_block.m_bytes, input, remaining);
	}

	self->m_len += len;
}

void mk_md5_finish(struct mk_md5_state_s* self, void* digest)
{
	#define s_mandatory_padding_len (1 + sizeof(uint64_t))
	#define s_worst_case_buff_len (mk_md5_detail_block_size + s_mandatory_padding_len - 1)

	unsigned idx;
	unsigned capacity;
	unsigned padding_len;
	unsigned char buff[s_worst_case_buff_len];
	uint64_t len;

	mk_assert(self);
	mk_assert(digest);

	idx = self->m_len % mk_md5_detail_block_size;
	capacity = mk_md5_detail_block_size - idx;
	padding_len =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity + mk_md5_detail_block_size - s_mandatory_padding_len);

	buff[0] = (unsigned char)(1u << 7);
	memset(buff + 1, 0, padding_len);
	len = self->m_len * 8;
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
	mk_md5_append(self, buff, padding_len + s_mandatory_padding_len);
	mk_assert(self->m_len % mk_md5_detail_block_size == 0);

#if MK_ENDIAN == MK_ENDIAN_LITTLE
	memcpy(digest, self->m_abcd, 16);
#else
	((unsigned char*)digest)[ 0] = (unsigned char)((self->m_abcd[0] >> (8 * 0)) & 0xff);
	((unsigned char*)digest)[ 1] = (unsigned char)((self->m_abcd[0] >> (8 * 1)) & 0xff);
	((unsigned char*)digest)[ 2] = (unsigned char)((self->m_abcd[0] >> (8 * 2)) & 0xff);
	((unsigned char*)digest)[ 3] = (unsigned char)((self->m_abcd[0] >> (8 * 3)) & 0xff);
	((unsigned char*)digest)[ 4] = (unsigned char)((self->m_abcd[1] >> (8 * 0)) & 0xff);
	((unsigned char*)digest)[ 5] = (unsigned char)((self->m_abcd[1] >> (8 * 1)) & 0xff);
	((unsigned char*)digest)[ 6] = (unsigned char)((self->m_abcd[1] >> (8 * 2)) & 0xff);
	((unsigned char*)digest)[ 7] = (unsigned char)((self->m_abcd[1] >> (8 * 3)) & 0xff);
	((unsigned char*)digest)[ 8] = (unsigned char)((self->m_abcd[2] >> (8 * 0)) & 0xff);
	((unsigned char*)digest)[ 9] = (unsigned char)((self->m_abcd[2] >> (8 * 1)) & 0xff);
	((unsigned char*)digest)[10] = (unsigned char)((self->m_abcd[2] >> (8 * 2)) & 0xff);
	((unsigned char*)digest)[11] = (unsigned char)((self->m_abcd[2] >> (8 * 3)) & 0xff);
	((unsigned char*)digest)[12] = (unsigned char)((self->m_abcd[3] >> (8 * 0)) & 0xff);
	((unsigned char*)digest)[13] = (unsigned char)((self->m_abcd[3] >> (8 * 1)) & 0xff);
	((unsigned char*)digest)[14] = (unsigned char)((self->m_abcd[3] >> (8 * 2)) & 0xff);
	((unsigned char*)digest)[15] = (unsigned char)((self->m_abcd[3] >> (8 * 3)) & 0xff);
#endif

	#undef s_mandatory_padding_len
	#undef s_worst_case_buff_len
}


#undef mk_md5_detail_block_size
