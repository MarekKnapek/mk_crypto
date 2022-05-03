#ifndef mk_include_guard_hash_function
#define mk_include_guard_hash_function


#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


typedef void* mk_hash_function_h;

enum mk_hash_function_e
{
	mk_hash_function_md2,
	mk_hash_function_md4,
	mk_hash_function_md5,
	mk_hash_function_sha1,
	mk_hash_function_sha2_224,
	mk_hash_function_sha2_256,
	mk_hash_function_sha2_384,
	mk_hash_function_sha2_512,
	mk_hash_function_sha2_512224,
	mk_hash_function_sha2_512256,
	mk_hash_function_sha3_224,
	mk_hash_function_sha3_256,
	mk_hash_function_sha3_384,
	mk_hash_function_sha3_512,
};


mk_extern_c mk_hash_function_h mk_hash_function_create(enum mk_hash_function_e id);
mk_extern_c enum mk_hash_function_e mk_hash_function_get_id(mk_hash_function_h hf);
mk_extern_c int mk_hash_function_get_block_len(mk_hash_function_h hf);
mk_extern_c int mk_hash_function_get_digest_len(mk_hash_function_h hf);
mk_extern_c void mk_hash_function_reinit(mk_hash_function_h hf, enum mk_hash_function_e id);
mk_extern_c void mk_hash_function_append(mk_hash_function_h hf, void const* msg, size_t msg_len_bytes);
mk_extern_c void mk_hash_function_finish(mk_hash_function_h hf, void* digest);
mk_extern_c void mk_hash_function_destroy(mk_hash_function_h hf);


#undef mk_extern_c


#endif
