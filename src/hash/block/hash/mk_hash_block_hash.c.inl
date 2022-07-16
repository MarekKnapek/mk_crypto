#include "../../base/mk_hash_base_hash.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include <string.h> /* memcpy */


#include "../../base/mk_hash_base_alg_name_def.h"


#define concat_(a, b) a ## b
#define concat(a, b) concat_(a, b)

#define hash_s concat(concat(struct mk_hash_base_hash_, alg_name), _s)
#define block_len concat(concat(mk_hash_base_hash_, alg_name), _block_len)
#define append_blocks concat(concat(mk_hash_base_hash_, alg_name), _append_blocks)
#define append concat(concat(mk_hash_block_hash_, alg_name), _append)


mk_jumbo void append(hash_s* base, void* block, int* pidx, void const* msg, int msg_len)
{
	unsigned char* output;
	int idx;
	unsigned char const* input;
	int remaining;
	int capacity;
	int blocks;

	mk_assert(base);
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
			append_blocks(base, output, 1);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / block_len;
		append_blocks(base, input, blocks);
		input += blocks * block_len;
		remaining -= blocks * block_len;
	}
	memcpy(output + idx, input, remaining);
	idx += remaining;
	*pidx = idx;
}


#undef hash_s
#undef block_len
#undef append_blocks
#undef append

#undef concat_
#undef concat


#include "../../base/mk_hash_base_alg_name_undef.h"
