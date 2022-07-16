#include "mk_hash_base_detail_sha2_512.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_inline.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../../../mk_int/src/exact/mk_uint_128.h"

#include <limits.h> /* LONG_MAX */
#include <string.h> /* memset */


static struct mk_uint64_s const mk_hash_base_detail_sha2_512_table[80] =
{
	mk_uint64_c(0x428a2f98ul, 0xd728ae22ul), mk_uint64_c(0x71374491ul, 0x23ef65cdul), mk_uint64_c(0xb5c0fbcful, 0xec4d3b2ful), mk_uint64_c(0xe9b5dba5ul, 0x8189dbbcul),
	mk_uint64_c(0x3956c25bul, 0xf348b538ul), mk_uint64_c(0x59f111f1ul, 0xb605d019ul), mk_uint64_c(0x923f82a4ul, 0xaf194f9bul), mk_uint64_c(0xab1c5ed5ul, 0xda6d8118ul),
	mk_uint64_c(0xd807aa98ul, 0xa3030242ul), mk_uint64_c(0x12835b01ul, 0x45706fbeul), mk_uint64_c(0x243185beul, 0x4ee4b28cul), mk_uint64_c(0x550c7dc3ul, 0xd5ffb4e2ul),
	mk_uint64_c(0x72be5d74ul, 0xf27b896ful), mk_uint64_c(0x80deb1feul, 0x3b1696b1ul), mk_uint64_c(0x9bdc06a7ul, 0x25c71235ul), mk_uint64_c(0xc19bf174ul, 0xcf692694ul),
	mk_uint64_c(0xe49b69c1ul, 0x9ef14ad2ul), mk_uint64_c(0xefbe4786ul, 0x384f25e3ul), mk_uint64_c(0x0fc19dc6ul, 0x8b8cd5b5ul), mk_uint64_c(0x240ca1ccul, 0x77ac9c65ul),
	mk_uint64_c(0x2de92c6ful, 0x592b0275ul), mk_uint64_c(0x4a7484aaul, 0x6ea6e483ul), mk_uint64_c(0x5cb0a9dcul, 0xbd41fbd4ul), mk_uint64_c(0x76f988daul, 0x831153b5ul),
	mk_uint64_c(0x983e5152ul, 0xee66dfabul), mk_uint64_c(0xa831c66dul, 0x2db43210ul), mk_uint64_c(0xb00327c8ul, 0x98fb213ful), mk_uint64_c(0xbf597fc7ul, 0xbeef0ee4ul),
	mk_uint64_c(0xc6e00bf3ul, 0x3da88fc2ul), mk_uint64_c(0xd5a79147ul, 0x930aa725ul), mk_uint64_c(0x06ca6351ul, 0xe003826ful), mk_uint64_c(0x14292967ul, 0x0a0e6e70ul),
	mk_uint64_c(0x27b70a85ul, 0x46d22ffcul), mk_uint64_c(0x2e1b2138ul, 0x5c26c926ul), mk_uint64_c(0x4d2c6dfcul, 0x5ac42aedul), mk_uint64_c(0x53380d13ul, 0x9d95b3dful),
	mk_uint64_c(0x650a7354ul, 0x8baf63deul), mk_uint64_c(0x766a0abbul, 0x3c77b2a8ul), mk_uint64_c(0x81c2c92eul, 0x47edaee6ul), mk_uint64_c(0x92722c85ul, 0x1482353bul),
	mk_uint64_c(0xa2bfe8a1ul, 0x4cf10364ul), mk_uint64_c(0xa81a664bul, 0xbc423001ul), mk_uint64_c(0xc24b8b70ul, 0xd0f89791ul), mk_uint64_c(0xc76c51a3ul, 0x0654be30ul),
	mk_uint64_c(0xd192e819ul, 0xd6ef5218ul), mk_uint64_c(0xd6990624ul, 0x5565a910ul), mk_uint64_c(0xf40e3585ul, 0x5771202aul), mk_uint64_c(0x106aa070ul, 0x32bbd1b8ul),
	mk_uint64_c(0x19a4c116ul, 0xb8d2d0c8ul), mk_uint64_c(0x1e376c08ul, 0x5141ab53ul), mk_uint64_c(0x2748774cul, 0xdf8eeb99ul), mk_uint64_c(0x34b0bcb5ul, 0xe19b48a8ul),
	mk_uint64_c(0x391c0cb3ul, 0xc5c95a63ul), mk_uint64_c(0x4ed8aa4aul, 0xe3418acbul), mk_uint64_c(0x5b9cca4ful, 0x7763e373ul), mk_uint64_c(0x682e6ff3ul, 0xd6b2b8a3ul),
	mk_uint64_c(0x748f82eeul, 0x5defb2fcul), mk_uint64_c(0x78a5636ful, 0x43172f60ul), mk_uint64_c(0x84c87814ul, 0xa1f0ab72ul), mk_uint64_c(0x8cc70208ul, 0x1a6439ecul),
	mk_uint64_c(0x90befffaul, 0x23631e28ul), mk_uint64_c(0xa4506cebul, 0xde82bde9ul), mk_uint64_c(0xbef9a3f7ul, 0xb2c67915ul), mk_uint64_c(0xc67178f2ul, 0xe372532bul),
	mk_uint64_c(0xca273eceul, 0xea26619cul), mk_uint64_c(0xd186b8c7ul, 0x21c0c207ul), mk_uint64_c(0xeada7dd6ul, 0xcde0eb1eul), mk_uint64_c(0xf57d4f7ful, 0xee6ed178ul),
	mk_uint64_c(0x06f067aaul, 0x72176fbaul), mk_uint64_c(0x0a637dc5ul, 0xa2c898a6ul), mk_uint64_c(0x113f9804ul, 0xbef90daeul), mk_uint64_c(0x1b710b35ul, 0x131c471bul),
	mk_uint64_c(0x28db77f5ul, 0x23047d84ul), mk_uint64_c(0x32caab7bul, 0x40c72493ul), mk_uint64_c(0x3c9ebe0aul, 0x15c9bebcul), mk_uint64_c(0x431d67c4ul, 0x9c100d4cul),
	mk_uint64_c(0x4cc5d4beul, 0xcb3e42b6ul), mk_uint64_c(0x597f299cul, 0xfc657e2aul), mk_uint64_c(0x5fcb6fabul, 0x3ad6faecul), mk_uint64_c(0x6c44198cul, 0x4a475817ul),
};
static struct mk_uint128_s const mk_hash_base_detail_sha2_512_max_bytes = mk_uint128_c(0x1ffffffful, 0xfffffffful, 0xfffffffful, 0xfffffffful);


static mk_inline void mk_hash_base_detail_sha2_512_ch(struct mk_uint64_s* out, struct mk_uint64_s const* x, struct mk_uint64_s const* y, struct mk_uint64_s const* z)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ ((~x) & z); */
	
	mk_uint64_and(&tmp1, x, y);
	mk_uint64_cmplmnt(&tmp2, x);
	mk_uint64_and(&tmp2, &tmp2, z);
	mk_uint64_xor(out, &tmp1, &tmp2);
}

static mk_inline void mk_hash_base_detail_sha2_512_maj(struct mk_uint64_s* out, struct mk_uint64_s const* x, struct mk_uint64_s const* y, struct mk_uint64_s const* z)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s tmp3;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ (x & z) ^ (y & z); */

	mk_uint64_and(&tmp1, x, y);
	mk_uint64_and(&tmp2, x, z);
	mk_uint64_and(&tmp3, y, z);
	mk_uint64_xor(&tmp1, &tmp1, &tmp2);
	mk_uint64_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_hash_base_detail_sha2_512_sum0(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 28) ^ rotr(x, 34) ^ rotr(x, 39); */

	mk_uint64_rotr(&tmp1, x, 28);
	mk_uint64_rotr(&tmp2, x, 34);
	mk_uint64_rotr(&tmp3, x, 39);
	mk_uint64_xor(&tmp1, &tmp1, &tmp2);
	mk_uint64_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_hash_base_detail_sha2_512_sum1(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 14) ^ rotr(x, 18) ^ rotr(x, 41); */

	mk_uint64_rotr(&tmp1, x, 14);
	mk_uint64_rotr(&tmp2, x, 18);
	mk_uint64_rotr(&tmp3, x, 41);
	mk_uint64_xor(&tmp1, &tmp1, &tmp2);
	mk_uint64_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_hash_base_detail_sha2_512_sig0(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 1) ^ rotr(x, 8) ^ shr(x, 7); */

	mk_uint64_rotr(&tmp1, x, 1);
	mk_uint64_rotr(&tmp2, x, 8);
	mk_uint64_shr(&tmp3, x, 7);
	mk_uint64_xor(&tmp1, &tmp1, &tmp2);
	mk_uint64_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_hash_base_detail_sha2_512_sig1(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 19) ^ rotr(x, 61) ^ shr(x, 6); */

	mk_uint64_rotr(&tmp1, x, 19);
	mk_uint64_rotr(&tmp2, x, 61);
	mk_uint64_shr(&tmp3, x, 6);
	mk_uint64_xor(&tmp1, &tmp1, &tmp2);
	mk_uint64_xor(out, &tmp1, &tmp3);
}


mk_jumbo void mk_hash_base_detail_sha2_512_init(struct mk_hash_base_detail_sha2_512_s* self, struct mk_uint64_s const* iv)
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
	mk_uint128_zero(&self->m_len);
}

mk_jumbo void mk_hash_base_detail_sha2_512_append_blocks(struct mk_hash_base_detail_sha2_512_s* self, void const* pblocks, int nblocks)
{
	struct mk_uint128_s len_bytes;
	struct mk_uint128_s new_len;
	unsigned char const* input;
	struct mk_uint64_s oldh[8];
	struct mk_uint64_s hh[8];
	struct mk_uint64_s* a;
	struct mk_uint64_s* b;
	struct mk_uint64_s* c;
	struct mk_uint64_s* d;
	struct mk_uint64_s* e;
	struct mk_uint64_s* f;
	struct mk_uint64_s* g;
	struct mk_uint64_s* h;
	int iblock;
	int i;
	struct mk_uint64_s w[80];
	struct mk_uint64_s t1;
	struct mk_uint64_s t2;
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;

	mk_assert(self);
	mk_assert(pblocks || nblocks == 0);
	mk_assert(nblocks >= 0);

	if(nblocks == 0)
	{
		return;
	}

	mk_assert(nblocks <= LONG_MAX / 128);
	mk_uint128_from_long(&len_bytes, 128 * (long)nblocks);
	mk_uint128_add(&new_len, &self->m_len, &len_bytes);
	mk_assert(mk_uint128_le(&new_len, &mk_hash_base_detail_sha2_512_max_bytes));
	mk_assert(mk_uint128_ge(&new_len, &self->m_len) && mk_uint128_ge(&new_len, &len_bytes));
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
		for(i = 0; i != 16; ++i, input += 8)
		{
			mk_uint64_from_buff_be(&w[i], input);
		}
		for(i = 16; i != 80; ++i)
		{
			/* w[i] = sig1(w[i - 2]) + w[i - 7] + sig0(w[i - 15]) + w[i - 16]; */
			mk_hash_base_detail_sha2_512_sig1(&tmp1, &w[i - 2]);
			mk_uint64_add(&tmp1, &tmp1, &w[i - 7]);
			mk_hash_base_detail_sha2_512_sig0(&tmp2, &w[i - 15]);
			mk_uint64_add(&tmp2, &tmp2, &w[i - 16]);
			mk_uint64_add(&w[i], &tmp1, &tmp2);
		}	
		for(i = 0; i != 80; ++i)
		{
			/* t1 = h + sum1(e) + ch(e, f, g) + table[i] + w[i]; */
			mk_hash_base_detail_sha2_512_sum1(&tmp1, e);
			mk_hash_base_detail_sha2_512_ch(&tmp2, e, f, g);
			mk_uint64_add(&tmp1, &tmp1, h);
			mk_uint64_add(&tmp2, &tmp2, &mk_hash_base_detail_sha2_512_table[i]);
			mk_uint64_add(&tmp1, &tmp1, &tmp2);
			mk_uint64_add(&t1, &tmp1, &w[i]);		
			/* t2 = sum0(a) + maj(a, b, c); */
			mk_hash_base_detail_sha2_512_sum0(&tmp1, a);
			mk_hash_base_detail_sha2_512_maj(&tmp2, a, b, c);
			mk_uint64_add(&t2, &tmp1, &tmp2);
			*h = *g;
			*g = *f;
			*f = *e;
			mk_uint64_add(e, d, &t1);
			*d = *c;
			*c = *b;
			*b = *a;
			mk_uint64_add(a, &t1, &t2);
		}
		mk_uint64_add(&oldh[0], &oldh[0], &hh[0]);
		mk_uint64_add(&oldh[1], &oldh[1], &hh[1]);
		mk_uint64_add(&oldh[2], &oldh[2], &hh[2]);
		mk_uint64_add(&oldh[3], &oldh[3], &hh[3]);
		mk_uint64_add(&oldh[4], &oldh[4], &hh[4]);
		mk_uint64_add(&oldh[5], &oldh[5], &hh[5]);
		mk_uint64_add(&oldh[6], &oldh[6], &hh[6]);
		mk_uint64_add(&oldh[7], &oldh[7], &hh[7]);
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

mk_jumbo void mk_hash_base_detail_sha2_512_finish(struct mk_hash_base_detail_sha2_512_s* self, void* block, int idx, void* digest)
{
	unsigned char* input;
	unsigned char* output;
	struct mk_uint128_s len;
	int capacity;

	mk_assert(self);
	mk_assert(block);
	mk_assert(idx >= 0 && idx < 128);
	mk_assert(digest);

	input = (unsigned char*)block;
	output = (unsigned char*)digest;
	mk_uint128_from_int(&len, idx);
	mk_uint128_add(&len, &len, &self->m_len);
	mk_uint128_shl(&len, &len, 3);
	input[idx] = 0x80;
	capacity = 128 - idx - 1;
	if(capacity >= 16)
	{
		memset(input + idx + 1, 0, capacity - 16);
	}
	else
	{
		memset(input + idx + 1, 0, capacity);
		mk_hash_base_detail_sha2_512_append_blocks(self, input, 1);
		memset(input, 0, 128 - 16);
	}
	mk_uint128_to_buff_be(&len, input + 128 - 16);
	mk_hash_base_detail_sha2_512_append_blocks(self, input, 1);
	mk_uint64_to_buff_be(&self->m_state[0], output + 0 * 8);
	mk_uint64_to_buff_be(&self->m_state[1], output + 1 * 8);
	mk_uint64_to_buff_be(&self->m_state[2], output + 2 * 8);
	mk_uint64_to_buff_be(&self->m_state[3], output + 3 * 8);
	mk_uint64_to_buff_be(&self->m_state[4], output + 4 * 8);
	mk_uint64_to_buff_be(&self->m_state[5], output + 5 * 8);
	mk_uint64_to_buff_be(&self->m_state[6], output + 6 * 8);
	mk_uint64_to_buff_be(&self->m_state[7], output + 7 * 8);
}
