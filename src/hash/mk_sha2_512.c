#include "mk_sha2_512.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"

#include <string.h> /* memcpy */


mk_jumbo void mk_sha2_512_init(struct mk_sha2_512_s* sha2_512)
{
	mk_assert(sha2_512);

	mk_sha2_512_base_init(&sha2_512->m_state);
	sha2_512->m_idx = 0;
}

mk_jumbo void mk_sha2_512_append(struct mk_sha2_512_s* sha2_512, void const* msg, int msg_len)
{
	unsigned char const* input;
	int remaining;
	int idx;
	int capacity;
	int blocks;

	mk_assert(sha2_512);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	input = (unsigned char const*)msg;
	remaining = msg_len;

	idx = sha2_512->m_idx;
	capacity = sizeof(sha2_512->m_block) - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(sha2_512->m_block + idx, input, capacity);
			mk_sha2_512_base_append_blocks(&sha2_512->m_state, 1, sha2_512->m_block);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / sizeof(sha2_512->m_block);
		mk_sha2_512_base_append_blocks(&sha2_512->m_state, blocks, input);
		input += blocks * sizeof(sha2_512->m_block);
		remaining -= blocks * sizeof(sha2_512->m_block);
	}
	memcpy(sha2_512->m_block + idx, input, remaining);
	sha2_512->m_idx = idx + remaining;
}

mk_jumbo void mk_sha2_512_finish(struct mk_sha2_512_s* sha2_512, void* digest)
{
	mk_assert(sha2_512);
	mk_assert(digest);

	mk_sha2_512_base_finish(&sha2_512->m_state, sha2_512->m_block, sha2_512->m_idx, digest);
}
