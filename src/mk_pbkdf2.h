#ifndef mk_include_guard_pbkdf2
#define mk_include_guard_pbkdf2


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_pbkdf2_hash_e
{
	mk_pbkdf2_hash_md2,
	mk_pbkdf2_hash_md4,
	mk_pbkdf2_hash_md5,
	mk_pbkdf2_hash_sha1,
	mk_pbkdf2_hash_sha2_224,
	mk_pbkdf2_hash_sha2_256,
	mk_pbkdf2_hash_sha2_384,
	mk_pbkdf2_hash_sha2_512,
	mk_pbkdf2_hash_sha2_512224,
	mk_pbkdf2_hash_sha2_512256,
	mk_pbkdf2_hash_sha3_224,
	mk_pbkdf2_hash_sha3_256,
	mk_pbkdf2_hash_sha3_384,
	mk_pbkdf2_hash_sha3_512,
};


/* rfc 2898 */


mk_extern_c void mk_pbkdf2(enum mk_pbkdf2_hash_e hash_id, void const* password, int password_len, void const* salt, int salt_len, int iterations, int key_len, void* key);


#undef mk_extern_c


#endif
