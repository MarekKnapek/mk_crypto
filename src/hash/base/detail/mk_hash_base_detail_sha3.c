#include "mk_hash_base_detail_sha3.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_inline.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memcpy memset */


static mk_inline void mk_hash_base_detail_sha3_theta(struct mk_uint64_s state[25])
{
	int x;
	struct mk_uint64_s tmp_1;
	struct mk_uint64_s tmp_2;
	struct mk_uint64_s c[5];
	struct mk_uint64_s d[5];
	int y;

	mk_assert(state);

	for(x = 0; x != 5; ++x)
	{
		mk_uint64_xor(&tmp_1, &state[0 * 5 + x], &state[1 * 5 + x]);
		mk_uint64_xor(&tmp_2, &state[2 * 5 + x], &state[3 * 5 + x]);
		mk_uint64_xor(&tmp_1, &tmp_1, &tmp_2);
		mk_uint64_xor(&c[x], &tmp_1, &state[4 * 5 + x]);
	}
	for(x = 0; x != 5; ++x)
	{
		mk_uint64_rotl(&tmp_1, &c[(x + 1) % 5], 1);
		mk_uint64_xor(&d[x], &c[(x + 4) % 5], &tmp_1);
	}
	for(y = 0; y != 5; ++y)
	{
		for(x = 0; x != 5; ++x)
		{
			mk_uint64_xor(&state[y * 5 + x], &state[y * 5 + x], &d[x]);
		}
	}
}

static mk_inline void mk_hash_base_detail_sha3_rho(struct mk_uint64_s state[25])
{
	int x;
	int y;
	int t;
	int old_x;

	mk_assert(state);

	x = 1;
	y = 0;
	for(t = 0; t != 24; ++t)
	{
		mk_uint64_rotl(&state[y * 5 + x], &state[y * 5 + x], (((t + 1) * (t + 2)) / 2) % 64);
		old_x = x;
		x = y;
		y = (2 * old_x + 3 * y) % 5;
	}
}

static mk_inline void mk_hash_base_detail_sha3_pi(struct mk_uint64_s in[25], struct mk_uint64_s out[25])
{
	int x;
	int y;
	int target_x;
	int target_y;

	mk_assert(in);
	mk_assert(out);
	mk_assert(in != out);

	for(y = 0; y != 5; ++y)
	{
		for(x = 0; x != 5; ++x)
		{
			target_x = y;
			target_y = (2 * x + 3 * y) % 5;
			out[target_y * 5 + target_x] = in[y * 5 + x];
		}
	}
}

static mk_inline void mk_hash_base_detail_sha3_chi(struct mk_uint64_s in[25], struct mk_uint64_s out[25])
{
	int y;
	int x;
	struct mk_uint64_s tmp;

	mk_assert(in);
	mk_assert(out);
	mk_assert(in != out);

	for(y = 0; y != 5; ++y)
	{
		for(x = 0; x != 5; ++x)
		{
			mk_uint64_cmplmnt(&tmp, &in[y * 5 + (x + 1) % 5]);
			mk_uint64_and(&tmp, &tmp, &in[y * 5 + (x + 2) % 5]);
			mk_uint64_xor(&out[y * 5 + x], &in[y * 5 + x], &tmp);
		}
	}
}

static mk_inline unsigned mk_hash_base_detail_sha3_rc_next_bit(unsigned* rc)
{
	unsigned r;
	unsigned ret;

	mk_assert(rc);

	r = *rc;
	ret = r & 0x01;

	r <<= 1;
	r = (r & ~(1u << 0)) | ((((r >> 0) & 0x1) ^ ((r >> 8) & 0x1)) << 0);
	r = (r & ~(1u << 4)) | ((((r >> 4) & 0x1) ^ ((r >> 8) & 0x1)) << 4);
	r = (r & ~(1u << 5)) | ((((r >> 5) & 0x1) ^ ((r >> 8) & 0x1)) << 5);
	r = (r & ~(1u << 6)) | ((((r >> 6) & 0x1) ^ ((r >> 8) & 0x1)) << 6);

	*rc = r;
	return ret;
}

static mk_inline void mk_hash_base_detail_sha3_rc_next_num(struct mk_uint64_s* out, unsigned* rc)
{
	struct mk_uint64_s tmp;

	mk_assert(out);
	mk_assert(rc);

	mk_uint64_zero(out);
	mk_uint64_from_int(&tmp, mk_hash_base_detail_sha3_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp,  0); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_hash_base_detail_sha3_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp,  1); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_hash_base_detail_sha3_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp,  3); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_hash_base_detail_sha3_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp,  7); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_hash_base_detail_sha3_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp, 15); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_hash_base_detail_sha3_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp, 31); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_hash_base_detail_sha3_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp, 63); mk_uint64_or(out, out, &tmp);
}

static mk_inline void mk_hash_base_detail_sha3_iota(struct mk_uint64_s state[25], unsigned* rc)
{
	struct mk_uint64_s rc_num;

	mk_assert(state);
	mk_assert(rc);

	mk_hash_base_detail_sha3_rc_next_num(&rc_num, rc);
	mk_uint64_xor(&state[0], &state[0], &rc_num);
}

static mk_inline void mk_hash_base_detail_sha3_rnd(struct mk_uint64_s state[25], unsigned* rc)
{
	struct mk_uint64_s tmp[25];

	mk_assert(state);
	mk_assert(rc);

	mk_hash_base_detail_sha3_theta(state);
	mk_hash_base_detail_sha3_rho(state);
	mk_hash_base_detail_sha3_pi(state, tmp);
	mk_hash_base_detail_sha3_chi(tmp, state);
	mk_hash_base_detail_sha3_iota(state, rc);
}

static mk_inline void mk_hash_base_detail_sha3_keccak_p(struct mk_uint64_s state[25])
{
	unsigned rc;
	int ir;

	mk_assert(state);

	rc = 1;
	for(ir = 0; ir != 24; ++ir)
	{
		mk_hash_base_detail_sha3_rnd(state, &rc);
	}
}

static mk_inline void mk_hash_base_detail_sha3_keccak_f(struct mk_uint64_s state[25])
{
	mk_assert(state);

	mk_hash_base_detail_sha3_keccak_p(state);
}

static mk_inline void mk_hash_base_detail_sha3_mix_block(struct mk_uint64_s state[25], int block_len, void const* block)
{
	unsigned char const* input;
	int elements;
	int i;
	struct mk_uint64_s element;

	mk_assert(state);
	mk_assert(block_len >= 0);
	mk_assert(block);

	input = (unsigned char const*)block;
	elements = block_len / 8;
	for(i = 0; i != elements; ++i)
	{
		mk_uint64_from_buff_le(&element, input + i * 8);
		mk_uint64_xor(&state[i], &state[i], &element);
	}
}

mk_jumbo void mk_hash_base_detail_sha3_init(struct mk_hash_base_detail_sha3_s* mk_hash_base_detail_sha3)
{
	int i;

	mk_assert(mk_hash_base_detail_sha3);

	for(i = 0; i != 25; ++i)
	{
		mk_uint64_zero(&mk_hash_base_detail_sha3->m_state[i]);
	}
}

mk_jumbo void mk_hash_base_detail_sha3_append_blocks(struct mk_hash_base_detail_sha3_s* mk_hash_base_detail_sha3, int block_len, int nblocks, void const* pblocks)
{
	unsigned char const* input;
	int iblock;

	mk_assert(mk_hash_base_detail_sha3);
	mk_assert(block_len == 168 || block_len == 144 || block_len == 136 || block_len == 104 || block_len == 72);
	mk_assert(nblocks >= 0);
	mk_assert(pblocks || nblocks == 0);

	input = (unsigned char const*)pblocks;
	for(iblock = 0; iblock != nblocks; ++iblock, input += block_len)
	{
		mk_hash_base_detail_sha3_mix_block(mk_hash_base_detail_sha3->m_state, block_len, input);
		mk_hash_base_detail_sha3_keccak_f(mk_hash_base_detail_sha3->m_state);
	}
}

mk_jumbo void mk_hash_base_detail_sha3_finish(struct mk_hash_base_detail_sha3_s* mk_hash_base_detail_sha3, int block_len, void* block, int idx, enum mk_hash_base_detail_sha3_domain_e domain, int digest_len, void* digest)
{
	unsigned char* input;
	unsigned char* output;
	int remaining;
	int capacity;
	int to_copy;
	int i;
	unsigned char tmp[200];
	int chunks;
	int j;

	mk_assert(mk_hash_base_detail_sha3);
	mk_assert(block_len == 168 || block_len == 144 || block_len == 136 || block_len == 104 || block_len == 72);
	mk_assert(block);
	mk_assert(idx >= 0 && idx < block_len);
	mk_assert(domain == mk_hash_base_detail_sha3_domain_sha3 || domain == mk_hash_base_detail_sha3_domain_shake || domain == mk_hash_base_detail_sha3_domain_rawshake);
	mk_assert(digest_len > 0);
	mk_assert(digest);

	input = (unsigned char*)block;
	output = (unsigned char*)digest;
	remaining = digest_len;
	switch(domain)
	{
		case mk_hash_base_detail_sha3_domain_sha3: input[idx] = 0x06; break;
		case mk_hash_base_detail_sha3_domain_shake: input[idx] = 0x1f; break;
		case mk_hash_base_detail_sha3_domain_rawshake: input[idx] = 0x07; break;
	}
	capacity = block_len - idx - 1;
	memset(input + idx + 1, 0, capacity);
	input[block_len - 1] |= 0x80;
	mk_hash_base_detail_sha3_append_blocks(mk_hash_base_detail_sha3, block_len, 1, input);
	to_copy = block_len < remaining ? block_len : remaining;
	for(i = 0; i != 25; ++i) mk_uint64_to_buff_le(&mk_hash_base_detail_sha3->m_state[i], tmp + i * 8);
	memcpy(output, tmp, to_copy);
	remaining -= to_copy;
	output += to_copy;
	chunks = remaining / block_len;
	for(i = 0; i != chunks; ++i, output += block_len)
	{
		mk_hash_base_detail_sha3_keccak_f(mk_hash_base_detail_sha3->m_state);
		for(j = 0; j != 25; ++j) mk_uint64_to_buff_le(&mk_hash_base_detail_sha3->m_state[j], tmp + j * 8);
		memcpy(output, tmp, to_copy);
	}
	remaining -= chunks * block_len;
	if(remaining != 0)
	{
		mk_hash_base_detail_sha3_keccak_f(mk_hash_base_detail_sha3->m_state);
		for(j = 0; j != 25; ++j) mk_uint64_to_buff_le(&mk_hash_base_detail_sha3->m_state[j], tmp + j * 8);
		memcpy(output, tmp, remaining);
	}
}
