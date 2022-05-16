#include "mk_hash.h"

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
		case mk_hash_md2: return 16; break;
		case mk_hash_md4: return 64; break;
		case mk_hash_md5: return 64; break;
		case mk_hash_sha1: return 64; break;
		case mk_hash_sha2_224: return 64; break;
		case mk_hash_sha2_256: return 64; break;
		case mk_hash_sha2_384: return 128; break;
		case mk_hash_sha2_512: return 128; break;
		case mk_hash_sha2_512224: return 128; break;
		case mk_hash_sha2_512256: return 128; break;
		case mk_hash_sha3_224: return 144; break;
		case mk_hash_sha3_256: return 136; break;
		case mk_hash_sha3_384: return 104; break;
		case mk_hash_sha3_512: return 72; break;
	}
	return 0;
}

mk_jumbo int mk_hash_get_digest_len(enum mk_hash_e type)
{
	mk_assert_type(type);

	switch(type)
	{
		case mk_hash_md2: return 16; break;
		case mk_hash_md4: return 16; break;
		case mk_hash_md5: return 16; break;
		case mk_hash_sha1: return 20; break;
		case mk_hash_sha2_224: return 28; break;
		case mk_hash_sha2_256: return 32; break;
		case mk_hash_sha2_384: return 48; break;
		case mk_hash_sha2_512: return 64; break;
		case mk_hash_sha2_512224: return 28; break;
		case mk_hash_sha2_512256: return 32; break;
		case mk_hash_sha3_224: return 28; break;
		case mk_hash_sha3_256: return 32; break;
		case mk_hash_sha3_384: return 48; break;
		case mk_hash_sha3_512: return 64; break;
	}
	return 0;
}


#undef mk_assert_type
