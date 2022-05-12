#include "mk_md4.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include "../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../mk_int/src/exact/mk_uint_64.h"

#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4711) /* warning C4711: function 'xxx' selected for automatic inline expansion */
#pragma warning(disable:5045) /* warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified */
#endif


static mk_inline void mk_md4_detail_f(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
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

static mk_inline void mk_md4_detail_g(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
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

static mk_inline void mk_md4_detail_h(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
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

static mk_inline void mk_md4_detail_round_1(struct mk_uint32_s* a, struct mk_uint32_s const* b, struct mk_uint32_s const* c, struct mk_uint32_s const* d, unsigned char const x[64], int k, int s)
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

	mk_md4_detail_f(&tmp1, b, c, d);
	mk_uint32_from_buff_le(&tmp2, ((unsigned char const*)x) + k * 4);

	mk_uint32_add(a, a, &tmp1);
	mk_uint32_add(a, a, &tmp2);
	mk_uint32_rotl(a, a, s);
}

static mk_inline void mk_md4_detail_round_2(struct mk_uint32_s* a, struct mk_uint32_s const* b, struct mk_uint32_s const* c, struct mk_uint32_s const* d, unsigned char const x[64], int k, int s)
{
	static struct mk_uint32_s const mk_md4_detail_round_2_constant = mk_uint32_c(0x5a827999);

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

	mk_md4_detail_g(&tmp1, b, c, d);
	mk_uint32_from_buff_le(&tmp2, ((unsigned char const*)x) + k * 4);

	mk_uint32_add(a, a, &tmp1);
	mk_uint32_add(&tmp2, &tmp2, &mk_md4_detail_round_2_constant);
	mk_uint32_add(a, a, &tmp2);
	mk_uint32_rotl(a, a, s);
}

static mk_inline void mk_md4_detail_round_3(struct mk_uint32_s* a, struct mk_uint32_s const* b, struct mk_uint32_s const* c, struct mk_uint32_s const* d, unsigned char const x[64], int k, int s)
{
	static struct mk_uint32_s const mk_md4_detail_round_3_constant = mk_uint32_c(0x6ed9eba1);

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

	mk_md4_detail_h(&tmp1, b, c, d);
	mk_uint32_from_buff_le(&tmp2, ((unsigned char const*)x) + k * 4);

	mk_uint32_add(a, a, &tmp1);
	mk_uint32_add(&tmp2, &tmp2, &mk_md4_detail_round_3_constant);
	mk_uint32_add(a, a, &tmp2);
	mk_uint32_rotl(a, a, s);
}

static mk_inline void mk_md4_detail_process_block(struct mk_md4_state_s* self, unsigned char const msg[64])
{
	struct mk_uint32_s h[4];
	struct mk_uint32_s* a;
	struct mk_uint32_s* b;
	struct mk_uint32_s* c;
	struct mk_uint32_s* d;

	mk_assert(self);
	mk_assert(msg);
	
	h[0] = self->m_state[0];
	h[1] = self->m_state[1];
	h[2] = self->m_state[2];
	h[3] = self->m_state[3];

	a = &h[0];
	b = &h[1];
	c = &h[2];
	d = &h[3];

	mk_md4_detail_round_1(a, b, c, d, msg,  0,  3);
	mk_md4_detail_round_1(d, a, b, c, msg,  1,  7);
	mk_md4_detail_round_1(c, d, a, b, msg,  2, 11);
	mk_md4_detail_round_1(b, c, d, a, msg,  3, 19);
	mk_md4_detail_round_1(a, b, c, d, msg,  4,  3);
	mk_md4_detail_round_1(d, a, b, c, msg,  5,  7);
	mk_md4_detail_round_1(c, d, a, b, msg,  6, 11);
	mk_md4_detail_round_1(b, c, d, a, msg,  7, 19);
	mk_md4_detail_round_1(a, b, c, d, msg,  8,  3);
	mk_md4_detail_round_1(d, a, b, c, msg,  9,  7);
	mk_md4_detail_round_1(c, d, a, b, msg, 10, 11);
	mk_md4_detail_round_1(b, c, d, a, msg, 11, 19);
	mk_md4_detail_round_1(a, b, c, d, msg, 12,  3);
	mk_md4_detail_round_1(d, a, b, c, msg, 13,  7);
	mk_md4_detail_round_1(c, d, a, b, msg, 14, 11);
	mk_md4_detail_round_1(b, c, d, a, msg, 15, 19);

	mk_md4_detail_round_2(a, b, c, d, msg,  0,  3);
	mk_md4_detail_round_2(d, a, b, c, msg,  4,  5);
	mk_md4_detail_round_2(c, d, a, b, msg,  8,  9);
	mk_md4_detail_round_2(b, c, d, a, msg, 12, 13);
	mk_md4_detail_round_2(a, b, c, d, msg,  1,  3);
	mk_md4_detail_round_2(d, a, b, c, msg,  5,  5);
	mk_md4_detail_round_2(c, d, a, b, msg,  9,  9);
	mk_md4_detail_round_2(b, c, d, a, msg, 13, 13);
	mk_md4_detail_round_2(a, b, c, d, msg,  2,  3);
	mk_md4_detail_round_2(d, a, b, c, msg,  6,  5);
	mk_md4_detail_round_2(c, d, a, b, msg, 10,  9);
	mk_md4_detail_round_2(b, c, d, a, msg, 14, 13);
	mk_md4_detail_round_2(a, b, c, d, msg,  3,  3);
	mk_md4_detail_round_2(d, a, b, c, msg,  7,  5);
	mk_md4_detail_round_2(c, d, a, b, msg, 11,  9);
	mk_md4_detail_round_2(b, c, d, a, msg, 15, 13);

	mk_md4_detail_round_3(a, b, c, d, msg,  0,  3);
	mk_md4_detail_round_3(d, a, b, c, msg,  8,  9);
	mk_md4_detail_round_3(c, d, a, b, msg,  4, 11);
	mk_md4_detail_round_3(b, c, d, a, msg, 12, 15);
	mk_md4_detail_round_3(a, b, c, d, msg,  2,  3);
	mk_md4_detail_round_3(d, a, b, c, msg, 10,  9);
	mk_md4_detail_round_3(c, d, a, b, msg,  6, 11);
	mk_md4_detail_round_3(b, c, d, a, msg, 14, 15);
	mk_md4_detail_round_3(a, b, c, d, msg,  1,  3);
	mk_md4_detail_round_3(d, a, b, c, msg,  9,  9);
	mk_md4_detail_round_3(c, d, a, b, msg,  5, 11);
	mk_md4_detail_round_3(b, c, d, a, msg, 13, 15);
	mk_md4_detail_round_3(a, b, c, d, msg,  3,  3);
	mk_md4_detail_round_3(d, a, b, c, msg, 11,  9);
	mk_md4_detail_round_3(c, d, a, b, msg,  7, 11);
	mk_md4_detail_round_3(b, c, d, a, msg, 15, 15);

	mk_uint32_add(&self->m_state[0], &self->m_state[0], &h[0]);
	mk_uint32_add(&self->m_state[1], &self->m_state[1], &h[1]);
	mk_uint32_add(&self->m_state[2], &self->m_state[2], &h[2]);
	mk_uint32_add(&self->m_state[3], &self->m_state[3], &h[3]);
}


void mk_md4_init(struct mk_md4_state_s* self)
{
	static struct mk_uint32_s const mk_md4_detail_init[] =
	{
		mk_uint32_c(0x67452301),
		mk_uint32_c(0xefcdab89),
		mk_uint32_c(0x98badcfe),
		mk_uint32_c(0x10325476),
	};

	mk_assert(self);

	self->m_state[0] = mk_md4_detail_init[0];
	self->m_state[1] = mk_md4_detail_init[1];
	self->m_state[2] = mk_md4_detail_init[2];
	self->m_state[3] = mk_md4_detail_init[3];
	mk_uint64_zero(&self->m_len);
}

void mk_md4_append(struct mk_md4_state_s* self, void const* msg, size_t msg_len_bytes)
{
	unsigned char const* input;
	size_t remaining;
	int idx;
	int capacity;
	struct mk_uint64_s len;
	size_t blocks;
	size_t i;

	mk_assert(self);

	input = (unsigned char const*)msg;
	remaining = msg_len_bytes;

	idx = mk_uint64_to_int(&self->m_len) % 64;
	capacity = 64 - idx;
	mk_uint64_from_sizet(&len, msg_len_bytes);
	mk_uint64_add(&self->m_len, &self->m_len, &len);

	if(remaining >= (size_t)capacity)
	{
		if(idx != 0)
		{
			memcpy(self->m_block + idx, input, capacity);
			mk_md4_detail_process_block(self, self->m_block);
			input += capacity;
			remaining -= capacity;
		}
		blocks = remaining / 64;
		for(i = 0; i != blocks; ++i)
		{
			mk_md4_detail_process_block(self, input);
			input += 64;
		}
		remaining -= blocks * 64;
		idx = 0;
	}
	memcpy(self->m_block + idx, input, remaining);
}

void mk_md4_finish(struct mk_md4_state_s* self, void* digest)
{
	#define s_mandatory_padding_len ((int)(1 + sizeof(struct mk_uint64_s)))

	static unsigned char const mk_md4_detail_padding[64] =
	{
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	unsigned char* output;
	int idx;
	int capacity;
	int zero_cnt;
	struct mk_uint64_s len;
	unsigned char buff[sizeof(struct mk_uint64_s)];

	mk_assert(self);
	mk_assert(digest);

	output = (unsigned char*)digest;
	idx = mk_uint64_to_int(&self->m_len) % 64;
	capacity = 64 - idx;
	zero_cnt =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity - s_mandatory_padding_len + 64);

	mk_uint64_shl(&len, &self->m_len, 3);
	mk_uint64_to_buff_le(&len, &buff);

	mk_md4_append(self, mk_md4_detail_padding, 1 + zero_cnt);
	mk_md4_append(self, buff, sizeof(struct mk_uint64_s));

	mk_uint32_to_buff_le(&self->m_state[0], output + 0 * 4);
	mk_uint32_to_buff_le(&self->m_state[1], output + 1 * 4);
	mk_uint32_to_buff_le(&self->m_state[2], output + 2 * 4);
	mk_uint32_to_buff_le(&self->m_state[3], output + 3 * 4);

	#undef s_mandatory_padding_len
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
