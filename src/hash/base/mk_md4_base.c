#include "mk_md4_base.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"
#include "../../utils/mk_jumbo.h"

#include "../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memset */


static struct mk_uint32_s const mk_md4_base_detail_init[4] =
{
	mk_uint32_c(0x67452301),
	mk_uint32_c(0xefcdab89),
	mk_uint32_c(0x98badcfe),
	mk_uint32_c(0x10325476),
};
static struct mk_uint32_s const mk_md4_base_detail_round_2_constant = mk_uint32_c(0x5a827999);
static struct mk_uint32_s const mk_md4_base_detail_round_3_constant = mk_uint32_c(0x6ed9eba1);


static mk_inline void mk_md4_base_detail_f(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
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

static mk_inline void mk_md4_base_detail_g(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) | (x & z) | (y & z); */

	mk_uint32_and(&tmp1, x, y);
	mk_uint32_and(&tmp2, x, z);
	mk_uint32_and(&tmp3, y, z);
	mk_uint32_or(&tmp1, &tmp1, &tmp2);
	mk_uint32_or(out, &tmp1, &tmp3);
}

static mk_inline void mk_md4_base_detail_h(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
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

static mk_inline void mk_md4_base_detail_round_1(struct mk_uint32_s* a, struct mk_uint32_s const* b, struct mk_uint32_s const* c, struct mk_uint32_s const* d, unsigned char const x[64], int k, int s)
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

	/* a = rotl(a + f(b, c, d) + x[k], s); */

	mk_md4_base_detail_f(&tmp1, b, c, d);
	mk_uint32_from_buff_le(&tmp2, x + k * 4);

	mk_uint32_add(a, a, &tmp1);
	mk_uint32_add(a, a, &tmp2);
	mk_uint32_rotl(a, a, s);
}

static mk_inline void mk_md4_base_detail_round_2(struct mk_uint32_s* a, struct mk_uint32_s const* b, struct mk_uint32_s const* c, struct mk_uint32_s const* d, unsigned char const x[64], int k, int s)
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

	/* a = rotl(a + g(b, c, d) + x[k] + 0x5a827999, s); */

	mk_md4_base_detail_g(&tmp1, b, c, d);
	mk_uint32_from_buff_le(&tmp2, ((unsigned char const*)x) + k * 4);

	mk_uint32_add(a, a, &tmp1);
	mk_uint32_add(&tmp2, &tmp2, &mk_md4_base_detail_round_2_constant);
	mk_uint32_add(a, a, &tmp2);
	mk_uint32_rotl(a, a, s);
}

static mk_inline void mk_md4_base_detail_round_3(struct mk_uint32_s* a, struct mk_uint32_s const* b, struct mk_uint32_s const* c, struct mk_uint32_s const* d, unsigned char const x[64], int k, int s)
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

	/* a = rotl(a + h(b, c, d) + x[k] + 0x6ed9eba1, s); */

	mk_md4_base_detail_h(&tmp1, b, c, d);
	mk_uint32_from_buff_le(&tmp2, ((unsigned char const*)x) + k * 4);

	mk_uint32_add(a, a, &tmp1);
	mk_uint32_add(&tmp2, &tmp2, &mk_md4_base_detail_round_3_constant);
	mk_uint32_add(a, a, &tmp2);
	mk_uint32_rotl(a, a, s);
}


mk_jumbo void mk_md4_base_init(struct mk_md4_base_s* md4_base)
{
	mk_assert(md4_base);

	md4_base->m_state[0] = mk_md4_base_detail_init[0];
	md4_base->m_state[1] = mk_md4_base_detail_init[1];
	md4_base->m_state[2] = mk_md4_base_detail_init[2];
	md4_base->m_state[3] = mk_md4_base_detail_init[3];
	mk_uint64_zero(&md4_base->m_len);
}

mk_jumbo void mk_md4_base_append_blocks(struct mk_md4_base_s* md4_base, int nblocks, void const* pblocks)
{
	struct mk_uint64_s len_bytes;
	unsigned char const* input;
	struct mk_uint32_s h[4];
	struct mk_uint32_s* a;
	struct mk_uint32_s* b;
	struct mk_uint32_s* c;
	struct mk_uint32_s* d;
	int iblock;

	mk_assert(md4_base);
	mk_assert(nblocks >= 0);
	mk_assert(pblocks || nblocks == 0);

	if(nblocks == 0)
	{
		return;
	}

	mk_uint64_from_int(&len_bytes, 64 * nblocks);
	mk_uint64_add(&md4_base->m_len, &md4_base->m_len, &len_bytes);
	input = (unsigned char const*)pblocks;
	a = &h[0];
	b = &h[1];
	c = &h[2];
	d = &h[3];
	for(iblock = 0; iblock != nblocks; ++iblock, input += 64)
	{
		h[0] = md4_base->m_state[0];
		h[1] = md4_base->m_state[1];
		h[2] = md4_base->m_state[2];
		h[3] = md4_base->m_state[3];

		mk_md4_base_detail_round_1(a, b, c, d, input,  0,  3);
		mk_md4_base_detail_round_1(d, a, b, c, input,  1,  7);
		mk_md4_base_detail_round_1(c, d, a, b, input,  2, 11);
		mk_md4_base_detail_round_1(b, c, d, a, input,  3, 19);
		mk_md4_base_detail_round_1(a, b, c, d, input,  4,  3);
		mk_md4_base_detail_round_1(d, a, b, c, input,  5,  7);
		mk_md4_base_detail_round_1(c, d, a, b, input,  6, 11);
		mk_md4_base_detail_round_1(b, c, d, a, input,  7, 19);
		mk_md4_base_detail_round_1(a, b, c, d, input,  8,  3);
		mk_md4_base_detail_round_1(d, a, b, c, input,  9,  7);
		mk_md4_base_detail_round_1(c, d, a, b, input, 10, 11);
		mk_md4_base_detail_round_1(b, c, d, a, input, 11, 19);
		mk_md4_base_detail_round_1(a, b, c, d, input, 12,  3);
		mk_md4_base_detail_round_1(d, a, b, c, input, 13,  7);
		mk_md4_base_detail_round_1(c, d, a, b, input, 14, 11);
		mk_md4_base_detail_round_1(b, c, d, a, input, 15, 19);

		mk_md4_base_detail_round_2(a, b, c, d, input,  0,  3);
		mk_md4_base_detail_round_2(d, a, b, c, input,  4,  5);
		mk_md4_base_detail_round_2(c, d, a, b, input,  8,  9);
		mk_md4_base_detail_round_2(b, c, d, a, input, 12, 13);
		mk_md4_base_detail_round_2(a, b, c, d, input,  1,  3);
		mk_md4_base_detail_round_2(d, a, b, c, input,  5,  5);
		mk_md4_base_detail_round_2(c, d, a, b, input,  9,  9);
		mk_md4_base_detail_round_2(b, c, d, a, input, 13, 13);
		mk_md4_base_detail_round_2(a, b, c, d, input,  2,  3);
		mk_md4_base_detail_round_2(d, a, b, c, input,  6,  5);
		mk_md4_base_detail_round_2(c, d, a, b, input, 10,  9);
		mk_md4_base_detail_round_2(b, c, d, a, input, 14, 13);
		mk_md4_base_detail_round_2(a, b, c, d, input,  3,  3);
		mk_md4_base_detail_round_2(d, a, b, c, input,  7,  5);
		mk_md4_base_detail_round_2(c, d, a, b, input, 11,  9);
		mk_md4_base_detail_round_2(b, c, d, a, input, 15, 13);

		mk_md4_base_detail_round_3(a, b, c, d, input,  0,  3);
		mk_md4_base_detail_round_3(d, a, b, c, input,  8,  9);
		mk_md4_base_detail_round_3(c, d, a, b, input,  4, 11);
		mk_md4_base_detail_round_3(b, c, d, a, input, 12, 15);
		mk_md4_base_detail_round_3(a, b, c, d, input,  2,  3);
		mk_md4_base_detail_round_3(d, a, b, c, input, 10,  9);
		mk_md4_base_detail_round_3(c, d, a, b, input,  6, 11);
		mk_md4_base_detail_round_3(b, c, d, a, input, 14, 15);
		mk_md4_base_detail_round_3(a, b, c, d, input,  1,  3);
		mk_md4_base_detail_round_3(d, a, b, c, input,  9,  9);
		mk_md4_base_detail_round_3(c, d, a, b, input,  5, 11);
		mk_md4_base_detail_round_3(b, c, d, a, input, 13, 15);
		mk_md4_base_detail_round_3(a, b, c, d, input,  3,  3);
		mk_md4_base_detail_round_3(d, a, b, c, input, 11,  9);
		mk_md4_base_detail_round_3(c, d, a, b, input,  7, 11);
		mk_md4_base_detail_round_3(b, c, d, a, input, 15, 15);

		mk_uint32_add(&md4_base->m_state[0], &md4_base->m_state[0], &h[0]);
		mk_uint32_add(&md4_base->m_state[1], &md4_base->m_state[1], &h[1]);
		mk_uint32_add(&md4_base->m_state[2], &md4_base->m_state[2], &h[2]);
		mk_uint32_add(&md4_base->m_state[3], &md4_base->m_state[3], &h[3]);
	}
}

mk_jumbo void mk_md4_base_finish(struct mk_md4_base_s* md4_base, void* block, int idx, void* digest)
{
	unsigned char* input;
	unsigned char* output;
	struct mk_uint64_s len;
	int capacity;
	unsigned char buff[64];

	mk_assert(md4_base);
	mk_assert(block);
	mk_assert(idx >= 0 && idx < 64);
	mk_assert(digest);

	input = (unsigned char*)block;
	output = (unsigned char*)digest;
	mk_uint64_from_int(&len, idx);
	mk_uint64_add(&len, &len, &md4_base->m_len);
	mk_uint64_shl(&len, &len, 3);
	input[idx] = 0x80;
	capacity = 64 - idx - 1;
	if(capacity >= 8)
	{
		memset(input + idx + 1, 0, capacity - 8);
		mk_uint64_to_buff_le(&len, input + 64 - 8);
		mk_md4_base_append_blocks(md4_base, 1, input);
	}
	else
	{
		memset(input + idx + 1, 0, capacity);
		mk_md4_base_append_blocks(md4_base, 1, input);
		memset(buff, 0, 64 - 8);
		mk_uint64_to_buff_le(&len, buff + 64 - 8);
		mk_md4_base_append_blocks(md4_base, 1, buff);
	}
	mk_uint32_to_buff_le(&md4_base->m_state[0], output + 0 * 4);
	mk_uint32_to_buff_le(&md4_base->m_state[1], output + 1 * 4);
	mk_uint32_to_buff_le(&md4_base->m_state[2], output + 2 * 4);
	mk_uint32_to_buff_le(&md4_base->m_state[3], output + 3 * 4);
}
