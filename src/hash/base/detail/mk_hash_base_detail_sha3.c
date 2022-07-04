#include "mk_hash_base_detail_sha3.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_inline.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memcpy memset */


static struct mk_uint64_s const mk_sha3_base_detail_rc_numbers[24] =
{
	mk_uint64_c(0x00000000, 0x00000001),
	mk_uint64_c(0x00000000, 0x00008082),
	mk_uint64_c(0x80000000, 0x0000808a),
	mk_uint64_c(0x80000000, 0x80008000),
	mk_uint64_c(0x00000000, 0x0000808b),
	mk_uint64_c(0x00000000, 0x80000001),
	mk_uint64_c(0x80000000, 0x80008081),
	mk_uint64_c(0x80000000, 0x00008009),
	mk_uint64_c(0x00000000, 0x0000008a),
	mk_uint64_c(0x00000000, 0x00000088),
	mk_uint64_c(0x00000000, 0x80008009),
	mk_uint64_c(0x00000000, 0x8000000a),
	mk_uint64_c(0x00000000, 0x8000808b),
	mk_uint64_c(0x80000000, 0x0000008b),
	mk_uint64_c(0x80000000, 0x00008089),
	mk_uint64_c(0x80000000, 0x00008003),
	mk_uint64_c(0x80000000, 0x00008002),
	mk_uint64_c(0x80000000, 0x00000080),
	mk_uint64_c(0x00000000, 0x0000800a),
	mk_uint64_c(0x80000000, 0x8000000a),
	mk_uint64_c(0x80000000, 0x80008081),
	mk_uint64_c(0x80000000, 0x00008080),
	mk_uint64_c(0x00000000, 0x80000001),
	mk_uint64_c(0x80000000, 0x80008008)
};


static mk_inline void mk_hash_base_detail_sha3_theta(struct mk_uint64_s* state)
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

static mk_inline void mk_hash_base_detail_sha3_rho(struct mk_uint64_s* state)
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

static mk_inline void mk_hash_base_detail_sha3_pi(struct mk_uint64_s* in, struct mk_uint64_s* out)
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

static mk_inline void mk_hash_base_detail_sha3_chi(struct mk_uint64_s* in, struct mk_uint64_s* out)
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

static mk_inline void mk_hash_base_detail_sha3_iota(struct mk_uint64_s* state, int rc_idx)
{
	mk_assert(state);
	mk_assert(rc_idx >= 0 && rc_idx < 24);

	mk_uint64_xor(&state[0], &state[0], &mk_sha3_base_detail_rc_numbers[rc_idx]);
}

static mk_inline void mk_hash_base_detail_sha3_rnd(struct mk_uint64_s* state, int rc_idx)
{
	struct mk_uint64_s tmp[25];

	mk_assert(state);

	mk_hash_base_detail_sha3_theta(state);
	mk_hash_base_detail_sha3_rho(state);
	mk_hash_base_detail_sha3_pi(state, tmp);
	mk_hash_base_detail_sha3_chi(tmp, state);
	mk_hash_base_detail_sha3_iota(state, rc_idx);
}

static mk_inline void mk_hash_base_detail_sha3_keccak_p(struct mk_uint64_s* state)
{
	int ir;

	mk_assert(state);

	for(ir = 0; ir != 24; ++ir)
	{
		mk_hash_base_detail_sha3_rnd(state, ir);
	}
}

static mk_inline void mk_hash_base_detail_sha3_keccak_f(struct mk_uint64_s* state)
{
	mk_assert(state);

	mk_hash_base_detail_sha3_keccak_p(state);
}

static mk_inline void mk_hash_base_detail_sha3_mix_block(struct mk_uint64_s* state, int block_len, void const* block)
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
