#ifndef mk_include_guard_hash_base_enum
#define mk_include_guard_hash_base_enum


enum mk_hash_e
{
	#include "mk_hash_base_xmacro_def.h"
	#define xcontent(alg) concat(mk_hash_e_, alg)
	xmacro_comma
	#undef xcontent
	#include "mk_hash_base_xmacro_undef.h"
};


#define mk_hash_e_is_good(e) \
	( \
		((e) == mk_hash_e_md2) || \
		((e) == mk_hash_e_md4) || \
		((e) == mk_hash_e_md5) || \
		((e) == mk_hash_e_sha1) || \
		((e) == mk_hash_e_sha2_224) || \
		((e) == mk_hash_e_sha2_256) || \
		((e) == mk_hash_e_sha2_384) || \
		((e) == mk_hash_e_sha2_512) || \
		((e) == mk_hash_e_sha2_512224) || \
		((e) == mk_hash_e_sha2_512256) || \
		((e) == mk_hash_e_sha3_224) || \
		((e) == mk_hash_e_sha3_256) || \
		((e) == mk_hash_e_sha3_384) || \
		((e) == mk_hash_e_sha3_512) \
	)


#endif
