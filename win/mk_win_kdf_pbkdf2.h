#ifndef mk_include_guard_win_kdf_pbkdf2
#define mk_include_guard_win_kdf_pbkdf2


#include "../src/utils/mk_jumbo.h"


enum mk_win_kdf_pbkdf2_e
{
	mk_win_kdf_pbkdf2_e_md2,
	mk_win_kdf_pbkdf2_e_md4,
	mk_win_kdf_pbkdf2_e_md5,
	mk_win_kdf_pbkdf2_e_sha1,
	mk_win_kdf_pbkdf2_e_sha2_256,
	mk_win_kdf_pbkdf2_e_sha2_384,
	mk_win_kdf_pbkdf2_e_sha2_512
};


mk_jumbo void mk_win_kdf_pbkdf2(enum mk_win_kdf_pbkdf2_e prf, void const* password, int password_len, void const* salt, int salt_len, long iterations, int key_len, void* key);


#endif
