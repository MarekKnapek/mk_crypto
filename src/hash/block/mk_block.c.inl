#undef stringify
#undef include_base_impl
#undef include_base
#define stringify(x) #x
#define include_base_impl(x) stringify(../base/mk_ ## x ## _base.h)
#define include_base(x) include_base_impl(x)


#include include_base(alg)

#include "../../utils/mk_assert.h"
#include "../../utils/mk_jumbo.h"

#include <string.h> /* memcpy */


#define concat2_impl(a, b) a ## b
#define concat2(a, b) concat2_impl(a, b)
#define concat3_impl(a, b, c) a ## b ## c
#define concat3(a, b, c) concat3_impl(a, b, c)


mk_jumbo void concat3(mk_, alg, _block_append)(struct concat3(mk_, alg, _base_s)* alg_base, void* block, int* pidx, void const* msg, int msg_len)
{
	unsigned char* output;
	int idx;
	unsigned char const* input;
	int remaining;
	int capacity;
	int blocks;

	mk_assert(alg_base);
	mk_assert(block);
	mk_assert(pidx && *pidx >= 0 && *pidx < concat3(mk_, alg, _base_block_len));
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	output = (unsigned char*)block;
	idx = *pidx;
	input = (unsigned char const*)msg;
	remaining = msg_len;
	capacity = concat3(mk_, alg, _base_block_len) - idx;
	if(remaining >= capacity)
	{
		if(idx != 0)
		{
			memcpy(output + idx, input, capacity);
			concat3(mk_, alg, _base_append_blocks)(alg_base, 1, output);
			input += capacity;
			remaining -= capacity;
			idx = 0;
		}
		blocks = remaining / concat3(mk_, alg, _base_block_len);
		concat3(mk_, alg, _base_append_blocks)(alg_base, blocks, input);
		input += blocks * concat3(mk_, alg, _base_block_len);
		remaining -= blocks * concat3(mk_, alg, _base_block_len);
	}
	memcpy(output + idx, input, remaining);
	idx += remaining;
	*pidx = idx;
}


#undef stringify
#undef include_base_impl
#undef include_base
#undef concat2_impl
#undef concat2
#undef concat3_impl
#undef concat3