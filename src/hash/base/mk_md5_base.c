#include "mk_md5_base.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#include "../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memset */


static struct mk_uint32_s const mk_md5_base_detail_table[64] =
{
	mk_uint32_c(0xd76aa478), mk_uint32_c(0xe8c7b756), mk_uint32_c(0x242070db), mk_uint32_c(0xc1bdceee),
	mk_uint32_c(0xf57c0faf), mk_uint32_c(0x4787c62a), mk_uint32_c(0xa8304613), mk_uint32_c(0xfd469501),
	mk_uint32_c(0x698098d8), mk_uint32_c(0x8b44f7af), mk_uint32_c(0xffff5bb1), mk_uint32_c(0x895cd7be),
	mk_uint32_c(0x6b901122), mk_uint32_c(0xfd987193), mk_uint32_c(0xa679438e), mk_uint32_c(0x49b40821),
	mk_uint32_c(0xf61e2562), mk_uint32_c(0xc040b340), mk_uint32_c(0x265e5a51), mk_uint32_c(0xe9b6c7aa),
	mk_uint32_c(0xd62f105d), mk_uint32_c(0x02441453), mk_uint32_c(0xd8a1e681), mk_uint32_c(0xe7d3fbc8),
	mk_uint32_c(0x21e1cde6), mk_uint32_c(0xc33707d6), mk_uint32_c(0xf4d50d87), mk_uint32_c(0x455a14ed),
	mk_uint32_c(0xa9e3e905), mk_uint32_c(0xfcefa3f8), mk_uint32_c(0x676f02d9), mk_uint32_c(0x8d2a4c8a),
	mk_uint32_c(0xfffa3942), mk_uint32_c(0x8771f681), mk_uint32_c(0x6d9d6122), mk_uint32_c(0xfde5380c),
	mk_uint32_c(0xa4beea44), mk_uint32_c(0x4bdecfa9), mk_uint32_c(0xf6bb4b60), mk_uint32_c(0xbebfbc70),
	mk_uint32_c(0x289b7ec6), mk_uint32_c(0xeaa127fa), mk_uint32_c(0xd4ef3085), mk_uint32_c(0x04881d05),
	mk_uint32_c(0xd9d4d039), mk_uint32_c(0xe6db99e5), mk_uint32_c(0x1fa27cf8), mk_uint32_c(0xc4ac5665),
	mk_uint32_c(0xf4292244), mk_uint32_c(0x432aff97), mk_uint32_c(0xab9423a7), mk_uint32_c(0xfc93a039),
	mk_uint32_c(0x655b59c3), mk_uint32_c(0x8f0ccc92), mk_uint32_c(0xffeff47d), mk_uint32_c(0x85845dd1),
	mk_uint32_c(0x6fa87e4f), mk_uint32_c(0xfe2ce6e0), mk_uint32_c(0xa3014314), mk_uint32_c(0x4e0811a1),
	mk_uint32_c(0xf7537e82), mk_uint32_c(0xbd3af235), mk_uint32_c(0x2ad7d2bb), mk_uint32_c(0xeb86d391),
};
static struct mk_uint32_s const mk_md5_base_detail_init[4] =
{
	mk_uint32_c(0x67452301),
	mk_uint32_c(0xefcdab89),
	mk_uint32_c(0x98badcfe),
	mk_uint32_c(0x10325476),
};


static mk_inline void mk_md5_base_detail_f(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) | ((~x) & z); */

	mk_uint32_and(&tmp1, x, y);
	mk_uint32_cmplmnt(&tmp2, x);
	mk_uint32_and(&tmp2, &tmp2, z);
	mk_uint32_or(out, &tmp1, &tmp2);
}

static mk_inline void mk_md5_base_detail_g(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & z) | (y & (~z)); */

	mk_uint32_and(&tmp1, x, z);
	mk_uint32_cmplmnt(&tmp2, z);
	mk_uint32_and(&tmp2, y, &tmp2);
	mk_uint32_or(out, &tmp1, &tmp2);
}

static mk_inline void mk_md5_base_detail_h(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s tmp;;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return x ^ y ^ z; */

	mk_uint32_xor(&tmp, x, y);
	mk_uint32_xor(out, &tmp, z);
}

static mk_inline void mk_md5_base_detail_i(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s tmp;;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return y ^ (x | (~z)); */

	mk_uint32_cmplmnt(&tmp, z);
	mk_uint32_or(&tmp, x, &tmp);
	mk_uint32_xor(out, y, &tmp);
}

static mk_inline void mk_md5_base_detail_round_1(struct mk_uint32_s* a, struct mk_uint32_s const* b, struct mk_uint32_s const* c, struct mk_uint32_s const* d, unsigned char const x[64], int k, int s, int i)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;

	mk_assert(a);
	mk_assert(b);
	mk_assert(c);
	mk_assert(d);
	mk_assert(x);
	mk_assert(k >= 0 && k < 16);
	mk_assert(s > 0 && s < 32);
	mk_assert(i - 1 >= 0 && i - 1 < 64);

	/* a = b + rotl(a + f(b, c, d) + x[k] + table[i - 1], s); */

	mk_md5_base_detail_f(&tmp1, b, c, d);
	mk_uint32_from_buff_le(&tmp2, x + k * 4);

	mk_uint32_add(&tmp1, a, &tmp1);
	mk_uint32_add(&tmp2, &tmp2, &mk_md5_base_detail_table[i - 1]);
	mk_uint32_add(&tmp1, &tmp1, &tmp2);
	mk_uint32_rotl(&tmp1, &tmp1, s);
	mk_uint32_add(a, b, &tmp1);
}

static mk_inline void mk_md5_base_detail_round_2(struct mk_uint32_s* a, struct mk_uint32_s const* b, struct mk_uint32_s const* c, struct mk_uint32_s const* d, unsigned char const x[64], int k, int s, int i)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;

	mk_assert(a);
	mk_assert(b);
	mk_assert(c);
	mk_assert(d);
	mk_assert(x);
	mk_assert(k >= 0 && k < 16);
	mk_assert(s > 0 && s < 32);
	mk_assert(i - 1 >= 0 && i - 1 < 64);

	/* a = b + rotl(a + g(b, c, d) + x[k] + table[i - 1], s); */

	mk_md5_base_detail_g(&tmp1, b, c, d);
	mk_uint32_from_buff_le(&tmp2, x + k * 4);

	mk_uint32_add(&tmp1, a, &tmp1);
	mk_uint32_add(&tmp2, &tmp2, &mk_md5_base_detail_table[i - 1]);
	mk_uint32_add(&tmp1, &tmp1, &tmp2);
	mk_uint32_rotl(&tmp1, &tmp1, s);
	mk_uint32_add(a, b, &tmp1);
}

static mk_inline void mk_md5_base_detail_round_3(struct mk_uint32_s* a, struct mk_uint32_s const* b, struct mk_uint32_s const* c, struct mk_uint32_s const* d, unsigned char const x[64], int k, int s, int i)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;

	mk_assert(a);
	mk_assert(b);
	mk_assert(c);
	mk_assert(d);
	mk_assert(x);
	mk_assert(k >= 0 && k < 16);
	mk_assert(s > 0 && s < 32);
	mk_assert(i - 1 >= 0 && i - 1 < 64);

	/* a = b + rotl(a + h(b, c, d) + x[k] + table[i - 1], s); */

	mk_md5_base_detail_h(&tmp1, b, c, d);
	mk_uint32_from_buff_le(&tmp2, x + k * 4);

	mk_uint32_add(&tmp1, a, &tmp1);
	mk_uint32_add(&tmp2, &tmp2, &mk_md5_base_detail_table[i - 1]);
	mk_uint32_add(&tmp1, &tmp1, &tmp2);
	mk_uint32_rotl(&tmp1, &tmp1, s);
	mk_uint32_add(a, b, &tmp1);
}

static mk_inline void mk_md5_base_detail_round_4(struct mk_uint32_s* a, struct mk_uint32_s const* b, struct mk_uint32_s const* c, struct mk_uint32_s const* d, unsigned char const x[64], int k, int s, int i)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;

	mk_assert(a);
	mk_assert(b);
	mk_assert(c);
	mk_assert(d);
	mk_assert(x);
	mk_assert(k >= 0 && k < 16);
	mk_assert(s > 0 && s < 32);
	mk_assert(i - 1 >= 0 && i - 1 < 64);

	/* a = b + rotl(a + i(b, c, d) + x[k] + table[i - 1], s); */

	mk_md5_base_detail_i(&tmp1, b, c, d);
	mk_uint32_from_buff_le(&tmp2, x + k * 4);

	mk_uint32_add(&tmp1, a, &tmp1);
	mk_uint32_add(&tmp2, &tmp2, &mk_md5_base_detail_table[i - 1]);
	mk_uint32_add(&tmp1, &tmp1, &tmp2);
	mk_uint32_rotl(&tmp1, &tmp1, s);
	mk_uint32_add(a, b, &tmp1);
}


void mk_md5_base_init(struct mk_md5_base_s* md5_base)
{
	mk_assert(md5_base);

	md5_base->m_state[0] = mk_md5_base_detail_init[0];
	md5_base->m_state[1] = mk_md5_base_detail_init[1];
	md5_base->m_state[2] = mk_md5_base_detail_init[2];
	md5_base->m_state[3] = mk_md5_base_detail_init[3];
	mk_uint64_zero(&md5_base->m_len);
}

void mk_md5_base_append_blocks(struct mk_md5_base_s* md5_base, int nblocks, void const* pblocks)
{
	struct mk_uint64_s len_bytes;
	unsigned char const* input;
	struct mk_uint32_s h[4];
	struct mk_uint32_s* a;
	struct mk_uint32_s* b;
	struct mk_uint32_s* c;
	struct mk_uint32_s* d;
	int iblock;

	mk_assert(md5_base);
	mk_assert(nblocks >= 0);
	mk_assert(pblocks || nblocks == 0);

	if(nblocks == 0)
	{
		return;
	}

	mk_uint64_from_int(&len_bytes, 64 * nblocks);
	mk_uint64_add(&md5_base->m_len, &md5_base->m_len, &len_bytes);
	input = (unsigned char const*)pblocks;
	a = &h[0];
	b = &h[1];
	c = &h[2];
	d = &h[3];
	for(iblock = 0; iblock != nblocks; ++iblock, input += 64)
	{
		h[0] = md5_base->m_state[0];
		h[1] = md5_base->m_state[1];
		h[2] = md5_base->m_state[2];
		h[3] = md5_base->m_state[3];

		mk_md5_base_detail_round_1(a, b, c, d, input,  0,  7,  1);
		mk_md5_base_detail_round_1(d, a, b, c, input,  1, 12,  2);
		mk_md5_base_detail_round_1(c, d, a, b, input,  2, 17,  3);
		mk_md5_base_detail_round_1(b, c, d, a, input,  3, 22,  4);
		mk_md5_base_detail_round_1(a, b, c, d, input,  4,  7,  5);
		mk_md5_base_detail_round_1(d, a, b, c, input,  5, 12,  6);
		mk_md5_base_detail_round_1(c, d, a, b, input,  6, 17,  7);
		mk_md5_base_detail_round_1(b, c, d, a, input,  7, 22,  8);
		mk_md5_base_detail_round_1(a, b, c, d, input,  8,  7,  9);
		mk_md5_base_detail_round_1(d, a, b, c, input,  9, 12, 10);
		mk_md5_base_detail_round_1(c, d, a, b, input, 10, 17, 11);
		mk_md5_base_detail_round_1(b, c, d, a, input, 11, 22, 12);
		mk_md5_base_detail_round_1(a, b, c, d, input, 12,  7, 13);
		mk_md5_base_detail_round_1(d, a, b, c, input, 13, 12, 14);
		mk_md5_base_detail_round_1(c, d, a, b, input, 14, 17, 15);
		mk_md5_base_detail_round_1(b, c, d, a, input, 15, 22, 16);

		mk_md5_base_detail_round_2(a, b, c, d, input,  1,  5, 17);
		mk_md5_base_detail_round_2(d, a, b, c, input,  6,  9, 18);
		mk_md5_base_detail_round_2(c, d, a, b, input, 11, 14, 19);
		mk_md5_base_detail_round_2(b, c, d, a, input,  0, 20, 20);
		mk_md5_base_detail_round_2(a, b, c, d, input,  5,  5, 21);
		mk_md5_base_detail_round_2(d, a, b, c, input, 10,  9, 22);
		mk_md5_base_detail_round_2(c, d, a, b, input, 15, 14, 23);
		mk_md5_base_detail_round_2(b, c, d, a, input,  4, 20, 24);
		mk_md5_base_detail_round_2(a, b, c, d, input,  9,  5, 25);
		mk_md5_base_detail_round_2(d, a, b, c, input, 14,  9, 26);
		mk_md5_base_detail_round_2(c, d, a, b, input,  3, 14, 27);
		mk_md5_base_detail_round_2(b, c, d, a, input,  8, 20, 28);
		mk_md5_base_detail_round_2(a, b, c, d, input, 13,  5, 29);
		mk_md5_base_detail_round_2(d, a, b, c, input,  2,  9, 30);
		mk_md5_base_detail_round_2(c, d, a, b, input,  7, 14, 31);
		mk_md5_base_detail_round_2(b, c, d, a, input, 12, 20, 32);

		mk_md5_base_detail_round_3(a, b, c, d, input,  5,  4, 33);
		mk_md5_base_detail_round_3(d, a, b, c, input,  8, 11, 34);
		mk_md5_base_detail_round_3(c, d, a, b, input, 11, 16, 35);
		mk_md5_base_detail_round_3(b, c, d, a, input, 14, 23, 36);
		mk_md5_base_detail_round_3(a, b, c, d, input,  1,  4, 37);
		mk_md5_base_detail_round_3(d, a, b, c, input,  4, 11, 38);
		mk_md5_base_detail_round_3(c, d, a, b, input,  7, 16, 39);
		mk_md5_base_detail_round_3(b, c, d, a, input, 10, 23, 40);
		mk_md5_base_detail_round_3(a, b, c, d, input, 13,  4, 41);
		mk_md5_base_detail_round_3(d, a, b, c, input,  0, 11, 42);
		mk_md5_base_detail_round_3(c, d, a, b, input,  3, 16, 43);
		mk_md5_base_detail_round_3(b, c, d, a, input,  6, 23, 44);
		mk_md5_base_detail_round_3(a, b, c, d, input,  9,  4, 45);
		mk_md5_base_detail_round_3(d, a, b, c, input, 12, 11, 46);
		mk_md5_base_detail_round_3(c, d, a, b, input, 15, 16, 47);
		mk_md5_base_detail_round_3(b, c, d, a, input,  2, 23, 48);

		mk_md5_base_detail_round_4(a, b, c, d, input,  0,  6, 49);
		mk_md5_base_detail_round_4(d, a, b, c, input,  7, 10, 50);
		mk_md5_base_detail_round_4(c, d, a, b, input, 14, 15, 51);
		mk_md5_base_detail_round_4(b, c, d, a, input,  5, 21, 52);
		mk_md5_base_detail_round_4(a, b, c, d, input, 12,  6, 53);
		mk_md5_base_detail_round_4(d, a, b, c, input,  3, 10, 54);
		mk_md5_base_detail_round_4(c, d, a, b, input, 10, 15, 55);
		mk_md5_base_detail_round_4(b, c, d, a, input,  1, 21, 56);
		mk_md5_base_detail_round_4(a, b, c, d, input,  8,  6, 57);
		mk_md5_base_detail_round_4(d, a, b, c, input, 15, 10, 58);
		mk_md5_base_detail_round_4(c, d, a, b, input,  6, 15, 59);
		mk_md5_base_detail_round_4(b, c, d, a, input, 13, 21, 60);
		mk_md5_base_detail_round_4(a, b, c, d, input,  4,  6, 61);
		mk_md5_base_detail_round_4(d, a, b, c, input, 11, 10, 62);
		mk_md5_base_detail_round_4(c, d, a, b, input,  2, 15, 63);
		mk_md5_base_detail_round_4(b, c, d, a, input,  9, 21, 64);

		mk_uint32_add(&md5_base->m_state[0], &md5_base->m_state[0], &h[0]);
		mk_uint32_add(&md5_base->m_state[1], &md5_base->m_state[1], &h[1]);
		mk_uint32_add(&md5_base->m_state[2], &md5_base->m_state[2], &h[2]);
		mk_uint32_add(&md5_base->m_state[3], &md5_base->m_state[3], &h[3]);
	}
}

void mk_md5_base_finish(struct mk_md5_base_s* md5_base, void* block, int idx, void* digest)
{
	unsigned char* input;
	unsigned char* output;
	struct mk_uint64_s len;
	int capacity;
	unsigned char buff[64];

	mk_assert(md5_base);
	mk_assert(block);
	mk_assert(idx >= 0 && idx < 64);
	mk_assert(digest);

	input = (unsigned char*)block;
	output = (unsigned char*)digest;
	mk_uint64_from_int(&len, idx);
	mk_uint64_add(&len, &len, &md5_base->m_len);
	mk_uint64_shl(&len, &len, 3);
	input[idx] = 0x80;
	capacity = 64 - idx - 1;
	if(capacity >= 8)
	{
		memset(input + idx + 1, 0, capacity - 8);
		mk_uint64_to_buff_le(&len, input + 64 - 8);
		mk_md5_base_append_blocks(md5_base, 1, input);
	}
	else
	{
		memset(input + idx + 1, 0, capacity);
		mk_md5_base_append_blocks(md5_base, 1, input);
		memset(buff, 0, 64 - 8);
		mk_uint64_to_buff_le(&len, buff + 64 - 8);
		mk_md5_base_append_blocks(md5_base, 1, buff);
	}
	mk_uint32_to_buff_le(&md5_base->m_state[0], output + 0 * 4);
	mk_uint32_to_buff_le(&md5_base->m_state[1], output + 1 * 4);
	mk_uint32_to_buff_le(&md5_base->m_state[2], output + 2 * 4);
	mk_uint32_to_buff_le(&md5_base->m_state[3], output + 3 * 4);
}
