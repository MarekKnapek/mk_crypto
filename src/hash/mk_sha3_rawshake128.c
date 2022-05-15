#include "mk_sha3_rawshake128.h"

#include "../utils/mk_assert.h"

#include <string.h> /* memcpy */


void mk_sha3_rawshake128_init(struct mk_sha3_rawshake128_s* sha3_rawshake128)
{
	mk_assert(sha3_rawshake128);

	mk_sha3_rawshake128_base_init(&sha3_rawshake128->m_state);
	sha3_rawshake128->m_idx = 0;
}

void mk_sha3_rawshake128_append(struct mk_sha3_rawshake128_s* sha3_rawshake128, void const* msg, int msg_len)
{
	unsigned char const* input;
	int remaining;
	int idx;
	int capacity;
	int blocks;

	mk_assert(sha3_rawshake128);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	input = (unsigned char const*)msg;
	remaining = msg_len;

	idx = sha3_rawshake128->m_idx;
	capacity = sizeof(sha3_rawshake128->m_block) - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(sha3_rawshake128->m_block + idx, input, capacity);
			mk_sha3_rawshake128_base_append_blocks(&sha3_rawshake128->m_state, 1, sha3_rawshake128->m_block);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / sizeof(sha3_rawshake128->m_block);
		mk_sha3_rawshake128_base_append_blocks(&sha3_rawshake128->m_state, blocks, input);
		input += blocks * sizeof(sha3_rawshake128->m_block);
		remaining -= blocks * sizeof(sha3_rawshake128->m_block);
	}
	memcpy(sha3_rawshake128->m_block + idx, input, remaining);
	sha3_rawshake128->m_idx = idx + remaining;
}

void mk_sha3_rawshake128_finish(struct mk_sha3_rawshake128_s* sha3_rawshake128, int digest_len, void* digest)
{
	mk_assert(sha3_rawshake128);
	mk_assert(digest);

	mk_sha3_rawshake128_base_finish(&sha3_rawshake128->m_state, sha3_rawshake128->m_block, sha3_rawshake128->m_idx, digest_len, digest);
}
