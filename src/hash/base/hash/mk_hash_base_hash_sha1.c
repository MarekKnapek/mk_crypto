#include "mk_hash_base_hash_sha1.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_inline.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memset */


static struct mk_uint32_s const mk_sha1_base_detail_init[5] =
{
	mk_uint32_c(0x67452301ul),
	mk_uint32_c(0xefcdab89ul),
	mk_uint32_c(0x98badcfeul),
	mk_uint32_c(0x10325476ul),
	mk_uint32_c(0xc3d2e1f0ul),
};

static struct mk_uint32_s const mk_sha1_base_detail_table_k[4] =
{
	mk_uint32_c(0x5a827999ul),
	mk_uint32_c(0x6ed9eba1ul),
	mk_uint32_c(0x8f1bbcdcul),
	mk_uint32_c(0xca62c1d6ul),
};


static mk_inline void mk_sha1_base_detail_ch(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
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

static mk_inline void mk_sha1_base_detail_parity(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
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

static mk_inline void mk_sha1_base_detail_maj(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
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

static mk_inline void mk_sha1_base_detail_f(struct mk_uint32_s* out, int idx, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	mk_assert(out);
	mk_assert(idx >= 0 && idx < 80);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	switch(idx / 20)
	{
		case 0: mk_sha1_base_detail_ch(out, x, y, z); break;
		case 1: mk_sha1_base_detail_parity(out, x, y, z); break;
		case 2: mk_sha1_base_detail_maj(out, x, y, z); break;
		case 3: mk_sha1_base_detail_parity(out, x, y, z); break;
	}
}

static mk_inline void mk_sha1_base_detail_k(struct mk_uint32_s* out, int idx)
{
	mk_assert(out);
	mk_assert(idx >= 0 && idx < 80);

	*out = mk_sha1_base_detail_table_k[idx / 20];
}


mk_jumbo void mk_hash_base_hash_sha1_init(struct mk_hash_base_hash_sha1_s* self)
{
	mk_assert(self);

	self->m_state[0] = mk_sha1_base_detail_init[0];
	self->m_state[1] = mk_sha1_base_detail_init[1];
	self->m_state[2] = mk_sha1_base_detail_init[2];
	self->m_state[3] = mk_sha1_base_detail_init[3];
	self->m_state[4] = mk_sha1_base_detail_init[4];
	mk_uint64_zero(&self->m_len);
}

mk_jumbo void mk_hash_base_hash_sha1_append_blocks(struct mk_hash_base_hash_sha1_s* self, void const* pblocks, int nblocks)
{
	struct mk_uint64_s len_bytes;
	unsigned char const* input;
	struct mk_uint32_s h[5];
	struct mk_uint32_s* a;
	struct mk_uint32_s* b;
	struct mk_uint32_s* c;
	struct mk_uint32_s* d;
	struct mk_uint32_s* e;
	int iblock;
	int i;
	struct mk_uint32_s w[80];
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s t;

	mk_assert(self);
	mk_assert(pblocks || nblocks == 0);
	mk_assert(nblocks >= 0);

	if(nblocks == 0)
	{
		return;
	}

	mk_uint64_from_int(&len_bytes, 64 * nblocks);
	mk_uint64_add(&self->m_len, &self->m_len, &len_bytes);
	input = (unsigned char const*)pblocks;
	a = &h[0];
	b = &h[1];
	c = &h[2];
	d = &h[3];
	e = &h[4];
	for(iblock = 0; iblock != nblocks; ++iblock, input += 64)
	{
		h[0] = self->m_state[0];
		h[1] = self->m_state[1];
		h[2] = self->m_state[2];
		h[3] = self->m_state[3];
		h[4] = self->m_state[4];
		for(i = 0; i != 16; ++i)
		{
			mk_uint32_from_buff_be(&w[i], input + i * 4);
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
			mk_sha1_base_detail_f(&tmp2, i, b, c, d);
			mk_uint32_add(&tmp1, &tmp1, &tmp2);
			mk_uint32_add(&tmp2, e, &w[i]);
			mk_uint32_add(&tmp1, &tmp1, &tmp2);
			mk_sha1_base_detail_k(&tmp2, i);
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
}

mk_jumbo void mk_hash_base_hash_sha1_finish(struct mk_hash_base_hash_sha1_s* self, void* block, int idx, void* digest)
{
	unsigned char* input;
	unsigned char* output;
	struct mk_uint64_s len;
	int capacity;

	mk_assert(self);
	mk_assert(block);
	mk_assert(idx >= 0 && idx < 64);
	mk_assert(digest);

	input = (unsigned char*)block;
	output = (unsigned char*)digest;
	mk_uint64_from_int(&len, idx);
	mk_uint64_add(&len, &len, &self->m_len);
	mk_uint64_shl(&len, &len, 3);
	input[idx] = 0x80;
	capacity = 64 - idx - 1;
	if(capacity >= 8)
	{
		memset(input + idx + 1, 0, capacity - 8);
	}
	else
	{
		memset(input + idx + 1, 0, capacity);
		mk_hash_base_hash_sha1_append_blocks(self, input, 1);
		memset(input, 0, 64 - 8);
	}
	mk_uint64_to_buff_be(&len, input + 64 - 8);
	mk_hash_base_hash_sha1_append_blocks(self, input, 1);
	mk_uint32_to_buff_be(&self->m_state[0], output + 0 * 4);
	mk_uint32_to_buff_be(&self->m_state[1], output + 1 * 4);
	mk_uint32_to_buff_be(&self->m_state[2], output + 2 * 4);
	mk_uint32_to_buff_be(&self->m_state[3], output + 3 * 4);
	mk_uint32_to_buff_be(&self->m_state[4], output + 4 * 4);
}
