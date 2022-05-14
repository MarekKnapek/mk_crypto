#include "mk_md2.h"

#include "../utils/mk_assert.h"

#include <string.h> /* memcpy */


void mk_md2_init(struct mk_md2_s* md2)
{
	mk_assert(md2);

	mk_md2_base_init(&md2->m_state);
	md2->m_idx = 0;
}

void mk_md2_append(struct mk_md2_s* md2, void const* msg, int msg_len)
{
	unsigned char const* input;
	int remaining;
	int idx;
	int capacity;
	int blocks;

	mk_assert(md2);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	input = (unsigned char const*)msg;
	remaining = msg_len;

	idx = md2->m_idx;
	capacity = sizeof(md2->m_block) - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(md2->m_block + idx, input, capacity);
			mk_md2_base_append_blocks(&md2->m_state, 1, md2->m_block);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / sizeof(md2->m_block);
		mk_md2_base_append_blocks(&md2->m_state, blocks, input);
		input += blocks * sizeof(md2->m_block);
		remaining -= blocks * sizeof(md2->m_block);
	}
	memcpy(md2->m_block + idx, input, remaining);
	md2->m_idx = idx + remaining;
}

void mk_md2_finish(struct mk_md2_s* md2, void* digest)
{
	mk_assert(md2);
	mk_assert(digest);

	mk_md2_base_finish(&md2->m_state, md2->m_block, md2->m_idx, digest);
}
