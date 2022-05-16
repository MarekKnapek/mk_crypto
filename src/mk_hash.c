#include "mk_hash.h"

#include "hash/base/mk_md2_base.h"
#include "hash/base/mk_md4_base.h"
#include "hash/base/mk_md5_base.h"
#include "hash/base/mk_sha1_base.h"
#include "hash/base/mk_sha2_224_base.h"
#include "hash/base/mk_sha2_256_base.h"
#include "hash/base/mk_sha2_384_base.h"
#include "hash/base/mk_sha2_512_base.h"
#include "hash/base/mk_sha2_512224_base.h"
#include "hash/base/mk_sha2_512256_base.h"
#include "hash/base/mk_sha3_224_base.h"
#include "hash/base/mk_sha3_256_base.h"
#include "hash/base/mk_sha3_384_base.h"
#include "hash/base/mk_sha3_512_base.h"

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
		case mk_hash_md2: return mk_md2_base_block_len; break;
		case mk_hash_md4: return mk_md4_base_block_len; break;
		case mk_hash_md5: return mk_md5_base_block_len; break;
		case mk_hash_sha1: return mk_sha1_base_block_len; break;
		case mk_hash_sha2_224: return mk_sha2_224_base_block_len; break;
		case mk_hash_sha2_256: return mk_sha2_256_base_block_len; break;
		case mk_hash_sha2_384: return mk_sha2_384_base_block_len; break;
		case mk_hash_sha2_512: return mk_sha2_512_base_block_len; break;
		case mk_hash_sha2_512224: return mk_sha2_512224_base_block_len; break;
		case mk_hash_sha2_512256: return mk_sha2_512256_base_block_len; break;
		case mk_hash_sha3_224: return mk_sha3_224_base_block_len; break;
		case mk_hash_sha3_256: return mk_sha3_256_base_block_len; break;
		case mk_hash_sha3_384: return mk_sha3_384_base_block_len; break;
		case mk_hash_sha3_512: return mk_sha3_512_base_block_len; break;
	}
	return 0;
}

mk_jumbo int mk_hash_get_digest_len(enum mk_hash_e type)
{
	mk_assert_type(type);

	switch(type)
	{
		case mk_hash_md2: return mk_md2_base_digest_len; break;
		case mk_hash_md4: return mk_md4_base_digest_len; break;
		case mk_hash_md5: return mk_md5_base_digest_len; break;
		case mk_hash_sha1: return mk_sha1_base_digest_len; break;
		case mk_hash_sha2_224: return mk_sha2_224_base_digest_len; break;
		case mk_hash_sha2_256: return mk_sha2_256_base_digest_len; break;
		case mk_hash_sha2_384: return mk_sha2_384_base_digest_len; break;
		case mk_hash_sha2_512: return mk_sha2_512_base_digest_len; break;
		case mk_hash_sha2_512224: return mk_sha2_512224_base_digest_len; break;
		case mk_hash_sha2_512256: return mk_sha2_512256_base_digest_len; break;
		case mk_hash_sha3_224: return mk_sha3_224_base_digest_len; break;
		case mk_hash_sha3_256: return mk_sha3_256_base_digest_len; break;
		case mk_hash_sha3_384: return mk_sha3_384_base_digest_len; break;
		case mk_hash_sha3_512: return mk_sha3_512_base_digest_len; break;
	}
	return 0;
}


#undef mk_assert_type
