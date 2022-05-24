#include "mk_hash.h"

#include "hash/base/hash/mk_hash_base_hash_md2.h"
#include "hash/base/hash/mk_hash_base_hash_md4.h"
#include "hash/base/hash/mk_hash_base_hash_md5.h"
#include "hash/base/hash/mk_hash_base_hash_sha1.h"
#include "hash/base/hash/mk_hash_base_hash_sha2_224.h"
#include "hash/base/hash/mk_hash_base_hash_sha2_256.h"
#include "hash/base/hash/mk_hash_base_hash_sha2_384.h"
#include "hash/base/hash/mk_hash_base_hash_sha2_512.h"
#include "hash/base/hash/mk_hash_base_hash_sha2_512224.h"
#include "hash/base/hash/mk_hash_base_hash_sha2_512256.h"
#include "hash/base/hash/mk_hash_base_hash_sha3_224.h"
#include "hash/base/hash/mk_hash_base_hash_sha3_256.h"
#include "hash/base/hash/mk_hash_base_hash_sha3_384.h"
#include "hash/base/hash/mk_hash_base_hash_sha3_512.h"

#include "utils/mk_assert.h"
#include "utils/mk_jumbo.h"


#define mk_assert_type(type) mk_assert( \
	(type) == mk_hash_md2 || \
	(type) == mk_hash_md4 || \
	(type) == mk_hash_md5 || \
	(type) == mk_hash_sha1 || \
	(type) == mk_hash_sha2_224 || \
	(type) == mk_hash_sha2_256 || \
	(type) == mk_hash_sha2_384 || \
	(type) == mk_hash_sha2_512 || \
	(type) == mk_hash_sha2_512224 || \
	(type) == mk_hash_sha2_512256 || \
	(type) == mk_hash_sha3_224 || \
	(type) == mk_hash_sha3_256 || \
	(type) == mk_hash_sha3_384 || \
	(type) == mk_hash_sha3_512 || \
	0)


mk_jumbo int mk_hash_get_block_len(enum mk_hash_e type)
{
	mk_assert_type(type);

	switch(type)
	{
		case mk_hash_md2: return mk_hash_base_hash_md2_block_len; break;
		case mk_hash_md4: return mk_hash_base_hash_md4_block_len; break;
		case mk_hash_md5: return mk_hash_base_hash_md5_block_len; break;
		case mk_hash_sha1: return mk_hash_base_hash_sha1_block_len; break;
		case mk_hash_sha2_224: return mk_hash_base_hash_sha2_224_block_len; break;
		case mk_hash_sha2_256: return mk_hash_base_hash_sha2_256_block_len; break;
		case mk_hash_sha2_384: return mk_hash_base_hash_sha2_384_block_len; break;
		case mk_hash_sha2_512: return mk_hash_base_hash_sha2_512_block_len; break;
		case mk_hash_sha2_512224: return mk_hash_base_hash_sha2_512224_block_len; break;
		case mk_hash_sha2_512256: return mk_hash_base_hash_sha2_512256_block_len; break;
		case mk_hash_sha3_224: return mk_hash_base_hash_sha3_224_block_len; break;
		case mk_hash_sha3_256: return mk_hash_base_hash_sha3_256_block_len; break;
		case mk_hash_sha3_384: return mk_hash_base_hash_sha3_384_block_len; break;
		case mk_hash_sha3_512: return mk_hash_base_hash_sha3_512_block_len; break;
	}
	return 0;
}

mk_jumbo int mk_hash_get_digest_len(enum mk_hash_e type)
{
	mk_assert_type(type);

	switch(type)
	{
		case mk_hash_md2: return mk_hash_base_hash_md2_digest_len; break;
		case mk_hash_md4: return mk_hash_base_hash_md4_digest_len; break;
		case mk_hash_md5: return mk_hash_base_hash_md5_digest_len; break;
		case mk_hash_sha1: return mk_hash_base_hash_sha1_digest_len; break;
		case mk_hash_sha2_224: return mk_hash_base_hash_sha2_224_digest_len; break;
		case mk_hash_sha2_256: return mk_hash_base_hash_sha2_256_digest_len; break;
		case mk_hash_sha2_384: return mk_hash_base_hash_sha2_384_digest_len; break;
		case mk_hash_sha2_512: return mk_hash_base_hash_sha2_512_digest_len; break;
		case mk_hash_sha2_512224: return mk_hash_base_hash_sha2_512224_digest_len; break;
		case mk_hash_sha2_512256: return mk_hash_base_hash_sha2_512256_digest_len; break;
		case mk_hash_sha3_224: return mk_hash_base_hash_sha3_224_digest_len; break;
		case mk_hash_sha3_256: return mk_hash_base_hash_sha3_256_digest_len; break;
		case mk_hash_sha3_384: return mk_hash_base_hash_sha3_384_digest_len; break;
		case mk_hash_sha3_512: return mk_hash_base_hash_sha3_512_digest_len; break;
	}
	return 0;
}


#undef mk_assert_type
