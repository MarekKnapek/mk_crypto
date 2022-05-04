#ifndef mk_include_guard_win_pbkdf2
#define mk_include_guard_win_pbkdf2


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_win_pbkdf2_hash_e
{
	mk_win_pbkdf2_hash_md2,
	mk_win_pbkdf2_hash_md4,
	mk_win_pbkdf2_hash_md5,
	mk_win_pbkdf2_hash_sha1,
	mk_win_pbkdf2_hash_sha2_256,
	mk_win_pbkdf2_hash_sha2_384,
	mk_win_pbkdf2_hash_sha2_512,
};


/* rfc 2898 */


mk_extern_c void mk_win_pbkdf2(enum mk_win_pbkdf2_hash_e hash_id, void const* password, int password_len, void const* salt, int salt_len, int iterations, int key_len, void* key);


#undef mk_extern_c


#endif
