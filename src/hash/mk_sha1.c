#include "mk_sha1.h"

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


static mk_inline void mk_sha1_detail_ch(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ ((~x) & z); */
	
	mk_uint32_and(&tmp1, x, y);
	mk_uint32_cmplmnt(&tmp2, x);
	mk_uint32_and(&tmp2, &tmp2, z);
	mk_uint32_xor(out, &tmp1, &tmp2);
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
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ (x & z) ^ (y & z); */

	mk_uint32_and(&tmp1, x, y);
	mk_uint32_and(&tmp2, x, z);
	mk_uint32_and(&tmp3, y, z);
	mk_uint32_xor(&tmp1, &tmp1, &tmp2);
	mk_uint32_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_sha1_detail_f(struct mk_uint32_s* out, int idx, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	mk_assert(out);
	mk_assert(idx >= 0 && idx < 80);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	if(idx < 20)
	{
		mk_sha1_detail_ch(out, x, y, z);
	}
	else if(idx < 40)
	{
		mk_sha1_detail_parity(out, x, y, z);
	}
	else if(idx < 60)
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
	static struct mk_uint32_s const mk_sha1_detail_table_k[] =
	{
		mk_uint32_c(0x5a827999),
		mk_uint32_c(0x6ed9eba1),
		mk_uint32_c(0x8f1bbcdc),
		mk_uint32_c(0xca62c1d6),
	};

	mk_assert(out);
	mk_assert(idx >= 0 && idx < 80);

	if(idx < 20)
	{
		*out = mk_sha1_detail_table_k[0];
	}
	else if(idx < 40)
	{
		*out = mk_sha1_detail_table_k[1];
	}
	else if(idx < 60)
	{
		*out = mk_sha1_detail_table_k[2];
	}
	else
	{
		*out = mk_sha1_detail_table_k[3];
	}
}

static mk_inline void mk_sha1_detail_process_block(struct mk_sha1_state_s* self, unsigned char const msg[64])
{
	struct mk_uint32_s h[5];
	struct mk_uint32_s w[80];
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
	mk_assert(msg);

	h[0] = self->m_state[0];
	h[1] = self->m_state[1];
	h[2] = self->m_state[2];
	h[3] = self->m_state[3];
	h[4] = self->m_state[4];

	a = &h[0];
	b = &h[1];
	c = &h[2];
	d = &h[3];
	e = &h[4];

	for(i = 0; i != 16; ++i)
	{
		mk_uint32_from_buff_be(&w[i], msg + i * sizeof(struct mk_uint32_s));
	}
	for(i = 16; i != 80; ++i)
	{
		/* w[i] = rotl(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1); */
		mk_uint32_xor(&tmp1, &w[i - 3], &w[i - 8]);
		mk_uint32_xor(&tmp2, &w[i - 14], &w[i - 16]);
		mk_uint32_xor(&tmp1, &tmp1, &tmp2);
		mk_uint32_rotl(&w[i], &tmp1, 1);
	}
	
	for(i = 0; i != 80; ++i)
	{
		/* t = rotl(a, 5) + f(i, b, c, d) + e + k(i) + w[i]; */
		mk_uint32_rotl(&tmp1, a, 5);
		mk_sha1_detail_f(&tmp2, i, b, c, d);
		mk_uint32_add(&tmp1, &tmp1, &tmp2);
		mk_uint32_add(&tmp2, e, &w[i]);
		mk_uint32_add(&tmp1, &tmp1, &tmp2);
		mk_sha1_detail_k(&tmp2, i);
		mk_uint32_add(&t, &tmp1, &tmp2);
		*e = *d;
		*d = *c;
		mk_uint32_rotl(c, b, 30);
		*b = *a;
		*a = t;
	}

	mk_uint32_add(&self->m_state[0], &self->m_state[0], &h[0]);
	mk_uint32_add(&self->m_state[1], &self->m_state[1], &h[1]);
	mk_uint32_add(&self->m_state[2], &self->m_state[2], &h[2]);
	mk_uint32_add(&self->m_state[3], &self->m_state[3], &h[3]);
	mk_uint32_add(&self->m_state[4], &self->m_state[4], &h[4]);
}


void mk_sha1_init(struct mk_sha1_state_s* self)
{
	static struct mk_uint32_s const mk_sha1_detail_init[] =
	{
		mk_uint32_c(0x67452301),
		mk_uint32_c(0xefcdab89),
		mk_uint32_c(0x98badcfe),
		mk_uint32_c(0x10325476),
		mk_uint32_c(0xc3d2e1f0),
	};

	mk_assert(self);

	self->m_state[0] = mk_sha1_detail_init[0];
	self->m_state[1] = mk_sha1_detail_init[1];
	self->m_state[2] = mk_sha1_detail_init[2];
	self->m_state[3] = mk_sha1_detail_init[3];
	self->m_state[4] = mk_sha1_detail_init[4];
	mk_uint64_zero(&self->m_len);
}

void mk_sha1_append(struct mk_sha1_state_s* self, void const* msg, size_t msg_len_bytes)
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
			mk_sha1_detail_process_block(self, self->m_block);
			input += capacity;
			remaining -= capacity;
		}
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
	#define s_mandatory_padding_len ((int)(1 + sizeof(struct mk_uint64_s)))

	static unsigned char const mk_sha1_detail_padding[64] =
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
	mk_uint64_to_buff_be(&len, &buff);

	mk_sha1_append(self, mk_sha1_detail_padding, 1 + zero_cnt);
	mk_sha1_append(self, buff, sizeof(struct mk_uint64_s));

	mk_uint32_to_buff_be(&self->m_state[0], output + 0 * 4);
	mk_uint32_to_buff_be(&self->m_state[1], output + 1 * 4);
	mk_uint32_to_buff_be(&self->m_state[2], output + 2 * 4);
	mk_uint32_to_buff_be(&self->m_state[3], output + 3 * 4);
	mk_uint32_to_buff_be(&self->m_state[4], output + 4 * 4);

	#undef s_mandatory_padding_len
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
