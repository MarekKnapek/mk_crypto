#include "mk_md5.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"

#include <string.h> /* memcpy */


mk_jumbo void mk_md5_init(struct mk_md5_s* md5)
{
	mk_assert(md5);

	mk_md5_base_init(&md5->m_state);
	md5->m_idx = 0;
}

mk_jumbo void mk_md5_append(struct mk_md5_s* md5, void const* msg, int msg_len)
{
	unsigned char const* input;
	int remaining;
	int idx;
	int capacity;
	int blocks;

	mk_assert(md5);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	input = (unsigned char const*)msg;
	remaining = msg_len;

	idx = md5->m_idx;
	capacity = sizeof(md5->m_block) - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(md5->m_block + idx, input, capacity);
			mk_md5_base_append_blocks(&md5->m_state, 1, md5->m_block);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / sizeof(md5->m_block);
		mk_md5_base_append_blocks(&md5->m_state, blocks, input);
		input += blocks * sizeof(md5->m_block);
		remaining -= blocks * sizeof(md5->m_block);
	}
	memcpy(md5->m_block + idx, input, remaining);
	md5->m_idx = idx + remaining;
}

mk_jumbo void mk_md5_finish(struct mk_md5_s* md5, void* digest)
{
	mk_assert(md5);
	mk_assert(digest);

	mk_md5_base_finish(&md5->m_state, md5->m_block, md5->m_idx, digest);
}
