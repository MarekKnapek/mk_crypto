#ifndef mk_include_guard_kdf_pbkdf2
#define mk_include_guard_kdf_pbkdf2


#include "../utils/mk_jumbo.h"


enum mk_kdf_pbkdf2_e
{
	mk_kdf_pbkdf2_e_md2,
	mk_kdf_pbkdf2_e_md4,
	mk_kdf_pbkdf2_e_md5,
	mk_kdf_pbkdf2_e_sha1,
	mk_kdf_pbkdf2_e_sha2_224,
	mk_kdf_pbkdf2_e_sha2_256,
	mk_kdf_pbkdf2_e_sha2_384,
	mk_kdf_pbkdf2_e_sha2_512,
	mk_kdf_pbkdf2_e_sha2_512224,
	mk_kdf_pbkdf2_e_sha2_512256,
	mk_kdf_pbkdf2_e_sha3_224,
	mk_kdf_pbkdf2_e_sha3_256,
	mk_kdf_pbkdf2_e_sha3_384,
	mk_kdf_pbkdf2_e_sha3_512
};


mk_jumbo void mk_kdf_pbkdf2(enum mk_kdf_pbkdf2_e prf, void const* password, int password_len, void const* salt, int salt_len, long iterations, int key_len, void* key);


#endif
