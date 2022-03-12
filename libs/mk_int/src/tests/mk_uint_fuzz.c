#include "mk_uint_fuzz_8.h"
#include "mk_uint_fuzz_16.h"
#include "mk_uint_fuzz_32.h"
#include "mk_uint_fuzz_64.h"

#include <stddef.h> /* size_t */


int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size)
{
	if(size != 2 * 8)
	{
		return 0;
	}

	mk_uint_fuzz_8(data);
	mk_uint_fuzz_16(data);
	mk_uint_fuzz_32(data);
	mk_uint_fuzz_64(data);

	return 0;
}
