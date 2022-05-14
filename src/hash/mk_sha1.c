#include "mk_sha1.h"

#include "../utils/mk_assert.h"

#include <string.h> /* memcpy */


void mk_sha1_init(struct mk_sha1_s* sha1)
{
	mk_assert(sha1);

	mk_sha1_base_init(&sha1->m_state);
	sha1->m_idx = 0;
}

void mk_sha1_append(struct mk_sha1_s* sha1, void const* msg, int msg_len)
{
	unsigned char const* input;
	int remaining;
	int idx;
	int capacity;
	int blocks;

	mk_assert(sha1);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	input = (unsigned char const*)msg;
	remaining = msg_len;

	idx = sha1->m_idx;
	capacity = sizeof(sha1->m_block) - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(sha1->m_block + idx, input, capacity);
			mk_sha1_base_append_blocks(&sha1->m_state, 1, sha1->m_block);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / sizeof(sha1->m_block);
		mk_sha1_base_append_blocks(&sha1->m_state, blocks, input);
		input += blocks * sizeof(sha1->m_block);
		remaining -= blocks * sizeof(sha1->m_block);
	}
	memcpy(sha1->m_block + idx, input, remaining);
	sha1->m_idx = idx + remaining;
}

void mk_sha1_finish(struct mk_sha1_s* sha1, void* digest)
{
	mk_assert(sha1);
	mk_assert(digest);

	mk_sha1_base_finish(&sha1->m_state, sha1->m_block, sha1->m_idx, digest);
}
