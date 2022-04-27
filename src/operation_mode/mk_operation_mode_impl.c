#include "mk_operation_mode_impl.h"

#include "../../utils/mk_assert.h"


void mk_operation_mode_detail_xor(int count, unsigned char const* src1, unsigned char const* src2, unsigned char* output)
{
	int i;

	mk_assert(count >= 0);
	mk_assert(src1);
	mk_assert(src2);
	mk_assert(output);

	for(i = 0; i != count; ++i)
	{
		output[i] = src1[i] ^ src2[i];
	}
}
