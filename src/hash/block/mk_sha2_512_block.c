#include "mk_sha2_512_block.h"

#include "../base/mk_sha2_512_base.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_jumbo.h"

#include <string.h> /* memcpy */


#define block_len 128


mk_jumbo void mk_sha2_512_block_append(struct mk_sha2_512_base_s* sha2_512_base, void* block, int* pidx, void const* msg, int msg_len)
{
	unsigned char* output;
	int idx;
	unsigned char const* input;
	int remaining;
	int capacity;
	int blocks;

	mk_assert(sha2_512_base);
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
			mk_sha2_512_base_append_blocks(sha2_512_base, 1, output);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / block_len;
		mk_sha2_512_base_append_blocks(sha2_512_base, blocks, input);
		input += blocks * block_len;
		remaining -= blocks * block_len;
	}
	memcpy(output + idx, input, remaining);
	idx += remaining;
	*pidx = idx;
}


#undef block_len
