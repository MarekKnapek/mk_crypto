#include "mk_md2.h"

#include "base/mk_md2_base.h"

#include "../utils/mk_assert.h"

#include <string.h> /* memcpy */


void mk_md2_init(struct mk_md2_s* self)
{
	mk_assert(self);

	mk_md2_base_init(self->m_state);
	self->m_idx = 0;
}

void mk_md2_append(struct mk_md2_s* self, void const* msg, int msg_len)
{
	unsigned char const* input;
	int remaining;
	int idx;
	int capacity;
	int blocks;

	mk_assert(self);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	input = (unsigned char const*)msg;
	remaining = msg_len;

	idx = self->m_idx;
	capacity = sizeof(self->m_block) - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(self->m_block + idx, input, capacity);
			mk_md2_base_append_blocks(self->m_state, 1, self->m_block);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / sizeof(self->m_block);
		mk_md2_base_append_blocks(self->m_state, blocks, input);
		input += blocks * 16;
		remaining -= blocks * 16;
	}
	memcpy(self->m_block + idx, input, remaining);
	self->m_idx = idx + remaining;
}

void mk_md2_finish(struct mk_md2_s* self, void* digest)
{
	mk_assert(self);
	mk_assert(digest);

	mk_md2_base_finish(self->m_state, self->m_block, self->m_idx, digest);
}
