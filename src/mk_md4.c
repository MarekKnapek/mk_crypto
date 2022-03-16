#include "mk_md4.h"

#include "../utils/mk_align.h"
#include "../utils/mk_assert.h"
#include "../utils/mk_endian.h"
#include "../utils/mk_inline.h"

#include <stdint.h> /* uintptr_t */
#include <string.h> /* memcpy, memset */


#define mk_md4_detail_block_size (16 * sizeof(uint32_t)) /* 16 32bit words, 64 bytes, 512 bits */


static mk_inline uint32_t mk_md4_detail_f(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) | ((~x) & z);
}

static mk_inline uint32_t mk_md4_detail_g(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) | (x & z) | (y & z);
}

static mk_inline uint32_t mk_md4_detail_h(uint32_t x, uint32_t y, uint32_t z)
{
	return x ^ y ^ z;
}

static mk_inline uint32_t mk_md4_detail_rot(uint32_t x, int s)
{
	mk_assert(s > 0);
	mk_assert(s < 32);

	return (x << s) | (x >> (32 - s));
}

static mk_inline uint32_t mk_md4_detail_round_1(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int k, int s, uint32_t const* x)
{
	mk_assert(k >= 0);
	mk_assert(k < 16);
	mk_assert(x);

	return mk_md4_detail_rot(a + mk_md4_detail_f(b, c, d) + x[k], s);
}

static mk_inline uint32_t mk_md4_detail_round_2(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int k, int s, uint32_t const* x)
{
	mk_assert(k >= 0);
	mk_assert(k < 16);
	mk_assert(x);

	return mk_md4_detail_rot(a + mk_md4_detail_g(b, c, d) + x[k] + 0x5a827999, s);
}

static mk_inline uint32_t mk_md4_detail_round_3(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int k, int s, uint32_t const* x)
{
	mk_assert(k >= 0);
	mk_assert(k < 16);
	mk_assert(x);

	return mk_md4_detail_rot(a + mk_md4_detail_h(b, c, d) + x[k] + 0x6ed9eba1, s);
}

static void mk_md4_detail_process_block(struct mk_md4_state_s* self, void const* aligned_data)
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
	mk_assert(self);

	self->m_abcd[0] = (uint32_t)0x67452301;
	self->m_abcd[1] = (uint32_t)0xefcdab89;
	self->m_abcd[2] = (uint32_t)0x98badcfe;
	self->m_abcd[3] = (uint32_t)0x10325476;
	self->m_len = 0;
}

void mk_md4_append(struct mk_md4_state_s* self, void const* data, size_t len)
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

	idx = self->m_len % mk_md4_detail_block_size;
	if(idx != 0)
	{
		capacity = mk_md4_detail_block_size - idx;
		to_copy = remaining < capacity ? (unsigned)remaining : capacity;
		memcpy(self->m_block.m_bytes + idx, input, to_copy);
		input += to_copy;
		remaining -= to_copy;
		buffer_full = to_copy == capacity;
		if(buffer_full)
		{
			mk_md4_detail_process_block(self, self->m_block.m_words);
		}
	}

	blocks = remaining / mk_md4_detail_block_size;
#if MK_ENDIAN == MK_ENDIAN_LITTLE
	if((((uintptr_t)input) % mk_alignof(uint32_t)) == 0)
	{
		for(i = 0; i != blocks; ++i)
		{
			mk_md4_detail_process_block(self, input);
			input += mk_md4_detail_block_size;
		}
	}
	else
#endif
	{
		for(i = 0; i != blocks; ++i)
		{
			memcpy(self->m_block.m_bytes, input, mk_md4_detail_block_size);
			mk_md4_detail_process_block(self, self->m_block.m_words);
			input += mk_md4_detail_block_size;
		}
	}
	remaining -= blocks * mk_md4_detail_block_size;

	mk_assert(remaining < mk_md4_detail_block_size);
	if(remaining != 0)
	{
		memcpy(self->m_block.m_bytes, input, remaining);
	}

	self->m_len += len;
}

void mk_md4_finish(struct mk_md4_state_s* self, void* digest)
{
	#define s_mandatory_padding_len (1 + sizeof(uint64_t))
	#define s_worst_case_buff_len (mk_md4_detail_block_size + s_mandatory_padding_len - 1)

	unsigned idx;
	unsigned capacity;
	unsigned padding_len;
	unsigned char buff[s_worst_case_buff_len];
	uint64_t len;

	mk_assert(self);
	mk_assert(digest);

	idx = self->m_len % mk_md4_detail_block_size;
	capacity = mk_md4_detail_block_size - idx;
	padding_len =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity + mk_md4_detail_block_size - s_mandatory_padding_len);

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
	mk_md4_append(self, buff, padding_len + s_mandatory_padding_len);
	mk_assert(self->m_len % mk_md4_detail_block_size == 0);

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


#undef mk_md4_detail_block_size
