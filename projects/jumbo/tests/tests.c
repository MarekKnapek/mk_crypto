#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4464) /* warning C4464: relative include path contains '..' */
#pragma warning(disable:4710)/* warning C4710: 'xxx': function not inlined */
#pragma warning(disable:4711) /* warning C4711: function 'xxx' selected for automatic inline expansion */
#endif


#include "../../../tests/mk_sha3_test_examples.h"

#include <stdio.h> /* printf */


int main(void)
{
	int tested;

	tested = mk_sha3_test_examples();
	if(tested == 0)
	{
		printf("Success!\n");
		return 0;
	}
	else
	{
		printf("Failure at line %d!\n", tested);
		return tested;
	}
}


#include "../../../tests/mk_sha3_test_examples.c"

#include "../../../src/mk_sha3_224.c"
#include "../../../src/mk_sha3_256.c"
#include "../../../src/mk_sha3_384.c"
#include "../../../src/mk_sha3_512.c"
#include "../../../src/mk_sha3_shake128.c"
#include "../../../src/mk_sha3_shake256.c"

#include "../../../src/mk_sha3_detail.c"

#include "../../../../mk_int/src/exact/mk_uint_64.c"

#include "../../../../mk_int/src/base/mk_uint_base_long.c"
#include "../../../../mk_int/src/base/mk_uint_base_llong.c"


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
