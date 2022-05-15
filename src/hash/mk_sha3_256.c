#include "mk_sha3_256.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"

#include <string.h> /* memcpy */


mk_jumbo void mk_sha3_256_init(struct mk_sha3_256_s* sha3_256)
{
	mk_assert(sha3_256);

	mk_sha3_256_base_init(&sha3_256->m_state);
	sha3_256->m_idx = 0;
}

mk_jumbo void mk_sha3_256_append(struct mk_sha3_256_s* sha3_256, void const* msg, int msg_len)
{
	unsigned char const* input;
	int remaining;
	int idx;
	int capacity;
	int blocks;

	mk_assert(sha3_256);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	input = (unsigned char const*)msg;
	remaining = msg_len;

	idx = sha3_256->m_idx;
	capacity = sizeof(sha3_256->m_block) - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(sha3_256->m_block + idx, input, capacity);
			mk_sha3_256_base_append_blocks(&sha3_256->m_state, 1, sha3_256->m_block);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / sizeof(sha3_256->m_block);
		mk_sha3_256_base_append_blocks(&sha3_256->m_state, blocks, input);
		input += blocks * sizeof(sha3_256->m_block);
		remaining -= blocks * sizeof(sha3_256->m_block);
	}
	memcpy(sha3_256->m_block + idx, input, remaining);
	sha3_256->m_idx = idx + remaining;
}

mk_jumbo void mk_sha3_256_finish(struct mk_sha3_256_s* sha3_256, void* digest)
{
	mk_assert(sha3_256);
	mk_assert(digest);

	mk_sha3_256_base_finish(&sha3_256->m_state, sha3_256->m_block, sha3_256->m_idx, digest);
}
