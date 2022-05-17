#include "../../../tests/mk_sha2_test_examples.h"
#include "../../../tests/mk_sha3_test_examples.h"

#include "../../../src/utils/mk_inline.h"

#include <stdio.h> /* printf */


#define mk_try(x) do{ int err_ = (x); if(err_ != 0){ return err_; } }while(0)


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


#undef mk_try


#include "../../../../mk_int/src/base/mk_uint_base_int.c"
#include "../../../../mk_int/src/base/mk_uint_base_long.c"
#include "../../../../mk_int/src/base/mk_uint_base_llong.c"
#include "../../../../mk_int/src/base/mk_uint_base_128.c"

#include "../../../../mk_int/src/exact/mk_uint_32.c"
#include "../../../../mk_int/src/exact/mk_uint_64.c"
#include "../../../../mk_int/src/exact/mk_uint_128.c"

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

#include "../../../src/hash/base/mk_md2_base.c"
#include "../../../src/hash/base/mk_md4_base.c"
#include "../../../src/hash/base/mk_md5_base.c"
#include "../../../src/hash/base/mk_sha1_base.c"
#include "../../../src/hash/base/mk_sha2_224_base.c"
#include "../../../src/hash/base/mk_sha2_256_base.c"
#include "../../../src/hash/base/mk_sha2_384_base.c"
#include "../../../src/hash/base/mk_sha2_512_base.c"
#include "../../../src/hash/base/mk_sha2_512224_base.c"
#include "../../../src/hash/base/mk_sha2_512256_base.c"
#include "../../../src/hash/base/mk_sha2_base_detail_256.c"
#include "../../../src/hash/base/mk_sha2_base_detail_512.c"
#include "../../../src/hash/base/mk_sha3_224_base.c"
#include "../../../src/hash/base/mk_sha3_256_base.c"
#include "../../../src/hash/base/mk_sha3_384_base.c"
#include "../../../src/hash/base/mk_sha3_512_base.c"
#include "../../../src/hash/base/mk_sha3_base_detail.c"
#include "../../../src/hash/base/mk_sha3_rawshake128_base.c"
#include "../../../src/hash/base/mk_sha3_rawshake256_base.c"
#include "../../../src/hash/base/mk_sha3_shake128_base.c"
#include "../../../src/hash/base/mk_sha3_shake256_base.c"
#include "../../../src/hash/block/mk_block_md2.c"
#include "../../../src/hash/block/mk_block_md4.c"
#include "../../../src/hash/block/mk_block_md5.c"
#include "../../../src/hash/block/mk_block_sha1.c"
#include "../../../src/hash/block/mk_block_sha2_224.c"
#include "../../../src/hash/block/mk_block_sha2_256.c"
#include "../../../src/hash/block/mk_block_sha2_384.c"
#include "../../../src/hash/block/mk_block_sha2_512.c"
#include "../../../src/hash/block/mk_block_sha2_512224.c"
#include "../../../src/hash/block/mk_block_sha2_512256.c"
#include "../../../src/hash/block/mk_block_sha3_224.c"
#include "../../../src/hash/block/mk_block_sha3_256.c"
#include "../../../src/hash/block/mk_block_sha3_384.c"
#include "../../../src/hash/block/mk_block_sha3_512.c"
#include "../../../src/hash/block/mk_block_sha3_rawshake128.c"
#include "../../../src/hash/block/mk_block_sha3_rawshake256.c"
#include "../../../src/hash/block/mk_block_sha3_shake128.c"
#include "../../../src/hash/block/mk_block_sha3_shake256.c"
#include "../../../src/hash/mk_hash_md2.c"
#include "../../../src/hash/mk_hash_md4.c"
#include "../../../src/hash/mk_hash_md5.c"
#include "../../../src/hash/mk_hash_sha1.c"
#include "../../../src/hash/mk_hash_sha2_224.c"
#include "../../../src/hash/mk_hash_sha2_256.c"
#include "../../../src/hash/mk_hash_sha2_384.c"
#include "../../../src/hash/mk_hash_sha2_512.c"
#include "../../../src/hash/mk_hash_sha2_512224.c"
#include "../../../src/hash/mk_hash_sha2_512256.c"
#include "../../../src/hash/mk_hash_sha3_224.c"
#include "../../../src/hash/mk_hash_sha3_256.c"
#include "../../../src/hash/mk_hash_sha3_384.c"
#include "../../../src/hash/mk_hash_sha3_512.c"
#include "../../../src/hash/mk_hash_sha3_rawshake128.c"
#include "../../../src/hash/mk_hash_sha3_rawshake256.c"
#include "../../../src/hash/mk_hash_sha3_shake128.c"
#include "../../../src/hash/mk_hash_sha3_shake256.c"
