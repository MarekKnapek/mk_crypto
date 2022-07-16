#include "mk_hash_base_detail_sha2_256.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_inline.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../../mk_int/src/exact/mk_uint_64.h"

#include <limits.h> /* LONG_MAX */
#include <string.h> /* memset */


static struct mk_uint32_s const mk_hash_base_detail_sha2_256_table[64] =
{
	mk_uint32_c(0x428a2f98ul), mk_uint32_c(0x71374491ul), mk_uint32_c(0xb5c0fbcful), mk_uint32_c(0xe9b5dba5ul),
	mk_uint32_c(0x3956c25bul), mk_uint32_c(0x59f111f1ul), mk_uint32_c(0x923f82a4ul), mk_uint32_c(0xab1c5ed5ul),
	mk_uint32_c(0xd807aa98ul), mk_uint32_c(0x12835b01ul), mk_uint32_c(0x243185beul), mk_uint32_c(0x550c7dc3ul),
	mk_uint32_c(0x72be5d74ul), mk_uint32_c(0x80deb1feul), mk_uint32_c(0x9bdc06a7ul), mk_uint32_c(0xc19bf174ul),
	mk_uint32_c(0xe49b69c1ul), mk_uint32_c(0xefbe4786ul), mk_uint32_c(0x0fc19dc6ul), mk_uint32_c(0x240ca1ccul),
	mk_uint32_c(0x2de92c6ful), mk_uint32_c(0x4a7484aaul), mk_uint32_c(0x5cb0a9dcul), mk_uint32_c(0x76f988daul),
	mk_uint32_c(0x983e5152ul), mk_uint32_c(0xa831c66dul), mk_uint32_c(0xb00327c8ul), mk_uint32_c(0xbf597fc7ul),
	mk_uint32_c(0xc6e00bf3ul), mk_uint32_c(0xd5a79147ul), mk_uint32_c(0x06ca6351ul), mk_uint32_c(0x14292967ul),
	mk_uint32_c(0x27b70a85ul), mk_uint32_c(0x2e1b2138ul), mk_uint32_c(0x4d2c6dfcul), mk_uint32_c(0x53380d13ul),
	mk_uint32_c(0x650a7354ul), mk_uint32_c(0x766a0abbul), mk_uint32_c(0x81c2c92eul), mk_uint32_c(0x92722c85ul),
	mk_uint32_c(0xa2bfe8a1ul), mk_uint32_c(0xa81a664bul), mk_uint32_c(0xc24b8b70ul), mk_uint32_c(0xc76c51a3ul),
	mk_uint32_c(0xd192e819ul), mk_uint32_c(0xd6990624ul), mk_uint32_c(0xf40e3585ul), mk_uint32_c(0x106aa070ul),
	mk_uint32_c(0x19a4c116ul), mk_uint32_c(0x1e376c08ul), mk_uint32_c(0x2748774cul), mk_uint32_c(0x34b0bcb5ul),
	mk_uint32_c(0x391c0cb3ul), mk_uint32_c(0x4ed8aa4aul), mk_uint32_c(0x5b9cca4ful), mk_uint32_c(0x682e6ff3ul),
	mk_uint32_c(0x748f82eeul), mk_uint32_c(0x78a5636ful), mk_uint32_c(0x84c87814ul), mk_uint32_c(0x8cc70208ul),
	mk_uint32_c(0x90befffaul), mk_uint32_c(0xa4506cebul), mk_uint32_c(0xbef9a3f7ul), mk_uint32_c(0xc67178f2ul),
};
static struct mk_uint64_s const mk_hash_base_detail_sha2_256_max_bytes = mk_uint64_c(0x1ffffffful, 0xfffffffful);


static mk_inline void mk_hash_base_detail_sha2_256_ch(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
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

static mk_inline void mk_hash_base_detail_sha2_256_maj(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
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

static mk_inline void mk_hash_base_detail_sha2_256_sum0(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); */

	mk_uint32_rotr(&tmp1, x, 2);
	mk_uint32_rotr(&tmp2, x, 13);
	mk_uint32_rotr(&tmp3, x, 22);
	mk_uint32_xor(&tmp1, &tmp1, &tmp2);
	mk_uint32_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_hash_base_detail_sha2_256_sum1(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); */

	mk_uint32_rotr(&tmp1, x, 6);
	mk_uint32_rotr(&tmp2, x, 11);
	mk_uint32_rotr(&tmp3, x, 25);
	mk_uint32_xor(&tmp1, &tmp1, &tmp2);
	mk_uint32_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_hash_base_detail_sha2_256_sig0(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3); */

	mk_uint32_rotr(&tmp1, x, 7);
	mk_uint32_rotr(&tmp2, x, 18);
	mk_uint32_shr(&tmp3, x, 3);
	mk_uint32_xor(&tmp1, &tmp1, &tmp2);
	mk_uint32_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_hash_base_detail_sha2_256_sig1(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10); */

	mk_uint32_rotr(&tmp1, x, 17);
	mk_uint32_rotr(&tmp2, x, 19);
	mk_uint32_shr(&tmp3, x, 10);
	mk_uint32_xor(&tmp1, &tmp1, &tmp2);
	mk_uint32_xor(out, &tmp1, &tmp3);
}


mk_jumbo void mk_hash_base_detail_sha2_256_init(struct mk_hash_base_detail_sha2_256_s* self, struct mk_uint32_s const* iv)
{
	mk_assert(self);
	mk_assert(iv);

	self->m_state[0] = iv[0];
	self->m_state[1] = iv[1];
	self->m_state[2] = iv[2];
	self->m_state[3] = iv[3];
	self->m_state[4] = iv[4];
	self->m_state[5] = iv[5];
	self->m_state[6] = iv[6];
	self->m_state[7] = iv[7];
	mk_uint64_zero(&self->m_len);
}

mk_jumbo void mk_hash_base_detail_sha2_256_append_blocks(struct mk_hash_base_detail_sha2_256_s* self, void const* pblocks, int nblocks)
{
	struct mk_uint64_s len_bytes;
	struct mk_uint64_s new_len;
	unsigned char const* input;
	struct mk_uint32_s oldh[8];
	struct mk_uint32_s hh[8];
	struct mk_uint32_s* a;
	struct mk_uint32_s* b;
	struct mk_uint32_s* c;
	struct mk_uint32_s* d;
	struct mk_uint32_s* e;
	struct mk_uint32_s* f;
	struct mk_uint32_s* g;
	struct mk_uint32_s* h;
	int iblock;
	int i;
	struct mk_uint32_s w[64];
	struct mk_uint32_s t1;
	struct mk_uint32_s t2;
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;

	mk_assert(self);
	mk_assert(pblocks || nblocks == 0);
	mk_assert(nblocks >= 0);

	if(nblocks == 0)
	{
		return;
	}

	mk_assert(nblocks <= LONG_MAX / 64);
	mk_uint64_from_long(&len_bytes, 64 * (long)nblocks);
	mk_uint64_add(&new_len, &self->m_len, &len_bytes);
	mk_assert(mk_uint64_le(&new_len, &mk_hash_base_detail_sha2_256_max_bytes));
	mk_assert(mk_uint64_ge(&new_len, &self->m_len) && mk_uint64_ge(&new_len, &len_bytes));
	input = (unsigned char const*)pblocks;
	oldh[0] = self->m_state[0];
	oldh[1] = self->m_state[1];
	oldh[2] = self->m_state[2];
	oldh[3] = self->m_state[3];
	oldh[4] = self->m_state[4];
	oldh[5] = self->m_state[5];
	oldh[6] = self->m_state[6];
	oldh[7] = self->m_state[7];
	a = &hh[0];
	b = &hh[1];
	c = &hh[2];
	d = &hh[3];
	e = &hh[4];
	f = &hh[5];
	g = &hh[6];
	h = &hh[7];
	for(iblock = 0; iblock != nblocks; ++iblock)
	{
		hh[0] = oldh[0];
		hh[1] = oldh[1];
		hh[2] = oldh[2];
		hh[3] = oldh[3];
		hh[4] = oldh[4];
		hh[5] = oldh[5];
		hh[6] = oldh[6];
		hh[7] = oldh[7];
		for(i = 0; i != 16; ++i, input += 4)
		{
			mk_uint32_from_buff_be(&w[i], input);
		}
		for(i = 16; i != 64; ++i)
		{
			/* w[i] = sig1(w[i - 2]) + w[i - 7] + sig0(w[i - 15]) + w[i - 16]; */
			mk_hash_base_detail_sha2_256_sig1(&tmp1, &w[i - 2]);
			mk_uint32_add(&tmp1, &tmp1, &w[i - 7]);
			mk_hash_base_detail_sha2_256_sig0(&tmp2, &w[i - 15]);
			mk_uint32_add(&tmp2, &tmp2, &w[i - 16]);
			mk_uint32_add(&w[i], &tmp1, &tmp2);
		}	
		for(i = 0; i != 64; ++i)
		{
			/* t1 = h + sum1(e) + ch(e, f, g) + table[i] + w[i]; */
			mk_hash_base_detail_sha2_256_sum1(&tmp1, e);
			mk_hash_base_detail_sha2_256_ch(&tmp2, e, f, g);
			mk_uint32_add(&tmp1, &tmp1, h);
			mk_uint32_add(&tmp2, &tmp2, &mk_hash_base_detail_sha2_256_table[i]);
			mk_uint32_add(&tmp1, &tmp1, &tmp2);
			mk_uint32_add(&t1, &tmp1, &w[i]);		
			/* t2 = sum0(a) + maj(a, b, c); */
			mk_hash_base_detail_sha2_256_sum0(&tmp1, a);
			mk_hash_base_detail_sha2_256_maj(&tmp2, a, b, c);
			mk_uint32_add(&t2, &tmp1, &tmp2);
			*h = *g;
			*g = *f;
			*f = *e;
			mk_uint32_add(e, d, &t1);
			*d = *c;
			*c = *b;
			*b = *a;
			mk_uint32_add(a, &t1, &t2);
		}
		mk_uint32_add(&oldh[0], &oldh[0], &hh[0]);
		mk_uint32_add(&oldh[1], &oldh[1], &hh[1]);
		mk_uint32_add(&oldh[2], &oldh[2], &hh[2]);
		mk_uint32_add(&oldh[3], &oldh[3], &hh[3]);
		mk_uint32_add(&oldh[4], &oldh[4], &hh[4]);
		mk_uint32_add(&oldh[5], &oldh[5], &hh[5]);
		mk_uint32_add(&oldh[6], &oldh[6], &hh[6]);
		mk_uint32_add(&oldh[7], &oldh[7], &hh[7]);
	}
	self->m_state[0] = oldh[0];
	self->m_state[1] = oldh[1];
	self->m_state[2] = oldh[2];
	self->m_state[3] = oldh[3];
	self->m_state[4] = oldh[4];
	self->m_state[5] = oldh[5];
	self->m_state[6] = oldh[6];
	self->m_state[7] = oldh[7];
	self->m_len = new_len;
}

mk_jumbo void mk_hash_base_detail_sha2_256_finish(struct mk_hash_base_detail_sha2_256_s* self, void* block, int idx, void* digest)
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
		mk_hash_base_detail_sha2_256_append_blocks(self, input, 1);
		memset(input, 0, 64 - 8);
	}
	mk_uint64_to_buff_be(&len, input + 64 - 8);
	mk_hash_base_detail_sha2_256_append_blocks(self, input, 1);
	mk_uint32_to_buff_be(&self->m_state[0], output + 0 * 4);
	mk_uint32_to_buff_be(&self->m_state[1], output + 1 * 4);
	mk_uint32_to_buff_be(&self->m_state[2], output + 2 * 4);
	mk_uint32_to_buff_be(&self->m_state[3], output + 3 * 4);
	mk_uint32_to_buff_be(&self->m_state[4], output + 4 * 4);
	mk_uint32_to_buff_be(&self->m_state[5], output + 5 * 4);
	mk_uint32_to_buff_be(&self->m_state[6], output + 6 * 4);
	mk_uint32_to_buff_be(&self->m_state[7], output + 7 * 4);
}
