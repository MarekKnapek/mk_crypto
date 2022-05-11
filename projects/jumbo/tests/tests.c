#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4464) /* warning C4464: relative include path contains '..' */
#pragma warning(disable:4710)/* warning C4710: 'xxx': function not inlined */
#pragma warning(disable:4711) /* warning C4711: function 'xxx' selected for automatic inline expansion */
#endif


#include "../../../tests/mk_aes_test_examples.h"
#include "../../../tests/mk_sha3_test_examples.h"
#include "../../../tests/mk_test_aes_gcm.h"

#include <stdio.h> /* printf */


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err_ = (x); if(err_ != 0){ return err_; } }while(0)


int test_all(void)
{
	mk_try(mk_sha3_test_examples());
	mk_try(mk_aes_test_examples());
	mk_try(mk_test_aes_gcm());
	return 0;
}


int main(void)
{
	int tested;

	tested = test_all();
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


#undef mk_check
#undef mk_try


#include "../../../tests/mk_aes_test_examples.c"
#include "../../../tests/mk_sha3_test_examples.c"
#include "../../../tests/mk_test_aes_gcm.c"

#include "../../../src/mk_sha3_224.c"
#include "../../../src/mk_sha3_256.c"
#include "../../../src/mk_sha3_384.c"
#include "../../../src/mk_sha3_512.c"
#include "../../../src/mk_sha3_shake128.c"
#include "../../../src/mk_sha3_shake256.c"

#include "../../../src/mk_sha3_detail.c"

#include "../../../src/mk_block_cipher.c"
#include "../../../src/mk_crypt.c"
#include "../../../src/mk_crypto.c"
#include "../../../src/mk_padding.c"
#include "../../../src/operation_mode/mk_operation_mode.c"
#include "../../../src/operation_mode/mk_operation_mode_base.c"
#include "../../../src/operation_mode/mk_operation_mode_cbc.c"
#include "../../../src/operation_mode/mk_operation_mode_cfb.c"
#include "../../../src/operation_mode/mk_operation_mode_ctr.c"
#include "../../../src/operation_mode/mk_operation_mode_ecb.c"
#include "../../../src/operation_mode/mk_operation_mode_gcm.c"
#include "../../../src/operation_mode/mk_operation_mode_impl.c"
#include "../../../src/operation_mode/mk_operation_mode_ofb.c"

#include "../../../../mk_int/src/exact/mk_uint_64.c"

#include "../../../../mk_int/src/base/mk_uint_base_long.c"
#include "../../../../mk_int/src/base/mk_uint_base_llong.c"


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
