#include "mk_win_pbkdf2.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <string.h> /* memcpy memset */

#include <windows.h>
#include <bcrypt.h>
#define STATUS_SUCCESS 0


void mk_win_pbkdf2(enum mk_win_pbkdf2_hash_e hash_id, void const* password, int password_len, void const* salt, int salt_len, int iterations, int key_len, void* key)
{
	wchar_t const* alg_name;
	NTSTATUS alg_provider_opened;
	BCRYPT_ALG_HANDLE alg;
	NTSTATUS key_derived;
	NTSTATUS alg_provider_closed;

	mk_assert(password || password_len == 0);
	mk_assert(password_len >= 0);
	mk_assert(salt || salt_len == 0);
	mk_assert(salt_len >= 0);
	mk_assert(iterations > 0);
	mk_assert(key_len > 0);
	mk_assert(key);

	alg_name = 0;
	switch(hash_id)
	{
		case mk_win_pbkdf2_hash_md2: alg_name = BCRYPT_MD2_ALGORITHM; break;
		case mk_win_pbkdf2_hash_md4: alg_name = BCRYPT_MD4_ALGORITHM; break;
		case mk_win_pbkdf2_hash_md5: alg_name = BCRYPT_MD5_ALGORITHM; break;
		case mk_win_pbkdf2_hash_sha1: alg_name = BCRYPT_SHA1_ALGORITHM; break;
		case mk_win_pbkdf2_hash_sha2_256: alg_name = BCRYPT_SHA256_ALGORITHM; break;
		case mk_win_pbkdf2_hash_sha2_384: alg_name = BCRYPT_SHA384_ALGORITHM; break;
		case mk_win_pbkdf2_hash_sha2_512: alg_name = BCRYPT_SHA512_ALGORITHM; break;
	}

	alg_provider_opened = BCryptOpenAlgorithmProvider(&alg, alg_name, MS_PRIMITIVE_PROVIDER, BCRYPT_ALG_HANDLE_HMAC_FLAG);
	if(!(alg_provider_opened == STATUS_SUCCESS))
	{
		goto cleanup_null;
	}

	key_derived = BCryptDeriveKeyPBKDF2(alg, (PUCHAR)password, password_len, (PUCHAR)salt, salt_len, iterations, key, key_len, 0);
	if(!(key_derived == STATUS_SUCCESS))
	{
		goto cleanup_alg;
	}

cleanup_alg:
	alg_provider_closed = BCryptCloseAlgorithmProvider(alg, 0);
	mk_assert(alg_provider_closed == STATUS_SUCCESS);
cleanup_null:
	return;
}
