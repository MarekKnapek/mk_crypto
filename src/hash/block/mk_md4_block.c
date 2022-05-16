#include "mk_md4_block.h"

#include "../base/mk_md4_base.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_jumbo.h"

#include <string.h> /* memcpy */


#define block_len 64


mk_jumbo void mk_md4_block_append(struct mk_md4_base_s* md4_base, void* block, int* pidx, void const* msg, int msg_len)
{
	unsigned char* output;
	int idx;
	unsigned char const* input;
	int remaining;
	int capacity;
	int blocks;

	mk_assert(md4_base);
	mk_assert(block);
	mk_assert(pidx && *pidx >= 0 && *pidx < block_len);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	output = (unsigned char*)block;
	idx = *pidx;
	input = (unsigned char const*)msg;
	remaining = msg_len;
	capacity = block_len - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(output + idx, input, capacity);
			mk_md4_base_append_blocks(md4_base, 1, output);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / block_len;
		mk_md4_base_append_blocks(md4_base, blocks, input);
		input += blocks * block_len;
		remaining -= blocks * block_len;
	}
	memcpy(output + idx, input, remaining);
	idx += remaining;
	*pidx = idx;
}


#undef block_len
