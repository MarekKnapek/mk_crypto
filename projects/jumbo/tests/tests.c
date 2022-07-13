#include "../../../tests/mk_sha2_test_examples.h"
#include "../../../tests/mk_sha3_test_examples.h"

#include "../../../src/utils/mk_inline.h"
#include "../../../src/utils/mk_try.h"

#include <stdio.h> /* printf */


static mk_inline int test_all(void)
{
	mk_try(mk_sha2_test_examples());
	mk_try(mk_sha3_test_examples());
	return 0;
}


int main(void)
{
	int tested;

	tested = test_all();
	if(tested == 0)
	{
		printf("Success!\n");
	}
	else
	{
		printf("Failure at line %d!\n", tested);
	}
	return tested;
}


#include "../../../../mk_int/src/base/mk_uint_base_int.c"
#include "../../../../mk_int/src/base/mk_uint_base_long.c"
#include "../../../../mk_int/src/base/mk_uint_base_llong.c"
#include "../../../../mk_int/src/base/mk_uint_base_128.c"

#include "../../../../mk_int/src/exact/mk_uint_32.c"
#include "../../../../mk_int/src/exact/mk_uint_64.c"
#include "../../../../mk_int/src/exact/mk_uint_128.c"

#include "../../../src/utils/mk_try.c"

#include "../../../tests/mk_sha2_224_test_examples.c"
#include "../../../tests/mk_sha2_256_test_examples.c"
#include "../../../tests/mk_sha2_384_test_examples.c"
#include "../../../tests/mk_sha2_512_test_examples.c"
#include "../../../tests/mk_sha2_512224_test_examples.c"
#include "../../../tests/mk_sha2_512256_test_examples.c"
#include "../../../tests/mk_sha2_additional_test_examples.c"
#include "../../../tests/mk_sha2_additional_test_examples_224.c"
#include "../../../tests/mk_sha2_additional_test_examples_256.c"
#include "../../../tests/mk_sha2_additional_test_examples_384.c"
#include "../../../tests/mk_sha2_additional_test_examples_512.c"
#include "../../../tests/mk_sha2_test_examples.c"
#include "../../../tests/mk_sha3_test_examples.c"
#include "../../../tests/mk_test_utils.c"

#include "../../../src/hash/base/detail/mk_hash_base_detail_sha2_256.c"
#include "../../../src/hash/base/detail/mk_hash_base_detail_sha2_512.c"
#include "../../../src/hash/base/detail/mk_hash_base_detail_sha3.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_md2.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_md4.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_md5.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha1.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha2_224.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha2_256.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha2_384.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha2_512.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha2_512224.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha2_512256.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha3_224.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha3_256.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha3_384.c"
#include "../../../src/hash/base/hash/mk_hash_base_hash_sha3_512.c"
#include "../../../src/hash/base/xof/mk_hash_base_xof_sha3_rawshake128.c"
#include "../../../src/hash/base/xof/mk_hash_base_xof_sha3_rawshake256.c"
#include "../../../src/hash/base/xof/mk_hash_base_xof_sha3_shake128.c"
#include "../../../src/hash/base/xof/mk_hash_base_xof_sha3_shake256.c"
#include "../../../src/hash/block/mk_hash_block_hash.c"
#include "../../../src/hash/block/mk_hash_block_xof.c"
#include "../../../src/hash/hash/mk_hash_hash.c"
#include "../../../src/hash/xof/mk_hash_xof.c"
