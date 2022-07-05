#ifndef mk_include_guard_hash
#define mk_include_guard_hash


#include "utils/mk_jumbo.h"


enum mk_hash_e
{
	mk_hash_crc32,
	mk_hash_md2,
	mk_hash_md4,
	mk_hash_md5,
	mk_hash_sha1,
	mk_hash_sha2_224,
	mk_hash_sha2_256,
	mk_hash_sha2_384,
	mk_hash_sha2_512,
	mk_hash_sha2_512224,
	mk_hash_sha2_512256,
	mk_hash_sha3_224,
	mk_hash_sha3_256,
	mk_hash_sha3_384,
	mk_hash_sha3_512
};


mk_jumbo int mk_hash_get_block_len(enum mk_hash_e type);
mk_jumbo int mk_hash_get_digest_len(enum mk_hash_e type);
mk_jumbo char const* mk_hash_get_name(enum mk_hash_e type);
mk_jumbo int mk_hash_get_name_len(enum mk_hash_e type);


#endif
