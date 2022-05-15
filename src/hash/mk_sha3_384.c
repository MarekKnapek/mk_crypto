#include "mk_sha3_384.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"

#include <string.h> /* memcpy */


mk_jumbo void mk_sha3_384_init(struct mk_sha3_384_s* sha3_384)
{
	mk_assert(sha3_384);

	mk_sha3_384_base_init(&sha3_384->m_state);
	sha3_384->m_idx = 0;
}

mk_jumbo void mk_sha3_384_append(struct mk_sha3_384_s* sha3_384, void const* msg, int msg_len)
{
	unsigned char const* input;
	int remaining;
	int idx;
	int capacity;
	int blocks;

	mk_assert(sha3_384);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	input = (unsigned char const*)msg;
	remaining = msg_len;

	idx = sha3_384->m_idx;
	capacity = sizeof(sha3_384->m_block) - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(sha3_384->m_block + idx, input, capacity);
			mk_sha3_384_base_append_blocks(&sha3_384->m_state, 1, sha3_384->m_block);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / sizeof(sha3_384->m_block);
		mk_sha3_384_base_append_blocks(&sha3_384->m_state, blocks, input);
		input += blocks * sizeof(sha3_384->m_block);
		remaining -= blocks * sizeof(sha3_384->m_block);
	}
	memcpy(sha3_384->m_block + idx, input, remaining);
	sha3_384->m_idx = idx + remaining;
}

mk_jumbo void mk_sha3_384_finish(struct mk_sha3_384_s* sha3_384, void* digest)
{
	mk_assert(sha3_384);
	mk_assert(digest);

	mk_sha3_384_base_finish(&sha3_384->m_state, sha3_384->m_block, sha3_384->m_idx, digest);
}
