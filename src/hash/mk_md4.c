#include "mk_md4.h"

#include "../utils/mk_assert.h"

#include <string.h> /* memcpy */


void mk_md4_init(struct mk_md4_s* md4)
{
	mk_assert(md4);

	mk_md4_base_init(&md4->m_state);
	md4->m_idx = 0;
}

void mk_md4_append(struct mk_md4_s* md4, void const* msg, int msg_len)
{
	unsigned char const* input;
	int remaining;
	int idx;
	int capacity;
	int blocks;

	mk_assert(md4);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	input = (unsigned char const*)msg;
	remaining = msg_len;

	idx = md4->m_idx;
	capacity = sizeof(md4->m_block) - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(md4->m_block + idx, input, capacity);
			mk_md4_base_append_blocks(&md4->m_state, 1, md4->m_block);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / sizeof(md4->m_block);
		mk_md4_base_append_blocks(&md4->m_state, blocks, input);
		input += blocks * 64;
		remaining -= blocks * 64;
	}
	memcpy(md4->m_block + idx, input, remaining);
	md4->m_idx = idx + remaining;
}

void mk_md4_finish(struct mk_md4_s* md4, void* digest)
{
	mk_assert(md4);
	mk_assert(digest);

	mk_md4_base_finish(&md4->m_state, md4->m_block, md4->m_idx, digest);
}
