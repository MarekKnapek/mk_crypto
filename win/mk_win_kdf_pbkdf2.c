#include "mk_win_kdf_pbkdf2.h"

#include "../src/utils/mk_assert.h"
#include "../src/utils/mk_jumbo.h"

#include <stddef.h> /* NULL */

#include <windows.h>
#include <bcrypt.h>


#define mk_assert_type(type) mk_assert( \
	(type) == mk_win_kdf_pbkdf2_e_md2 || \
	(type) == mk_win_kdf_pbkdf2_e_md4 || \
	(type) == mk_win_kdf_pbkdf2_e_md5 || \
	(type) == mk_win_kdf_pbkdf2_e_sha1 || \
	(type) == mk_win_kdf_pbkdf2_e_sha2_256 || \
	(type) == mk_win_kdf_pbkdf2_e_sha2_384 || \
	(type) == mk_win_kdf_pbkdf2_e_sha2_512)


mk_jumbo void mk_win_kdf_pbkdf2(enum mk_win_kdf_pbkdf2_e prf, void const* password, int password_len, void const* salt, int salt_len, long iterations, int key_len, void* key)
{
	wchar_t const* alg_name;
	NTSTATUS prov_st;
	BCRYPT_ALG_HANDLE alg;
	NTSTATUS derived_st;
	NTSTATUS close_st;

	mk_assert_type(prf);
	mk_assert(password || password_len == 0);
	mk_assert(password_len >= 0);
	mk_assert(salt || salt_len == 0);
	mk_assert(salt_len >= 0);
	mk_assert(iterations > 0);
	mk_assert(key_len > 0);
	mk_assert(key);

	alg_name = NULL;
	switch(prf)
	{
		case mk_win_kdf_pbkdf2_e_md2: alg_name = BCRYPT_MD2_ALGORITHM; break;
		case mk_win_kdf_pbkdf2_e_md4: alg_name = BCRYPT_MD4_ALGORITHM; break;
		case mk_win_kdf_pbkdf2_e_md5: alg_name = BCRYPT_MD5_ALGORITHM; break;
		case mk_win_kdf_pbkdf2_e_sha1: alg_name = BCRYPT_SHA1_ALGORITHM; break;
		case mk_win_kdf_pbkdf2_e_sha2_256: alg_name = BCRYPT_SHA256_ALGORITHM; break;
		case mk_win_kdf_pbkdf2_e_sha2_384: alg_name = BCRYPT_SHA384_ALGORITHM; break;
		case mk_win_kdf_pbkdf2_e_sha2_512: alg_name = BCRYPT_SHA512_ALGORITHM; break;
	}
	prov_st = BCryptOpenAlgorithmProvider(&alg, alg_name, MS_PRIMITIVE_PROVIDER, BCRYPT_ALG_HANDLE_HMAC_FLAG);
	mk_assert(prov_st == 0);

	derived_st = BCryptDeriveKeyPBKDF2(alg, (PUCHAR)password, (ULONG)password_len, (PUCHAR)salt, (ULONG)salt_len, (ULONGLONG)iterations, (PUCHAR)key, (ULONG)key_len, 0);
	mk_assert(derived_st == 0);

	close_st = BCryptCloseAlgorithmProvider(alg, 0);
	mk_assert(close_st == 0);
}


#undef mk_assert_type
