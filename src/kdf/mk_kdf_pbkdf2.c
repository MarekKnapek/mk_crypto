#include "mk_kdf_pbkdf2.h"

#include "pbkdf2/mk_kdf_pbkdf2_md2.h"
#include "pbkdf2/mk_kdf_pbkdf2_md4.h"
#include "pbkdf2/mk_kdf_pbkdf2_md5.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha1.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha2_224.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha2_256.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha2_384.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha2_512.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha2_512224.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha2_512256.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha3_224.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha3_256.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha3_512.h"
#include "pbkdf2/mk_kdf_pbkdf2_sha3_384.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


#define mk_assert_type(type) mk_assert( \
	(type) == mk_kdf_pbkdf2_e_md2 || \
	(type) == mk_kdf_pbkdf2_e_md4 || \
	(type) == mk_kdf_pbkdf2_e_md5 || \
	(type) == mk_kdf_pbkdf2_e_sha1 || \
	(type) == mk_kdf_pbkdf2_e_sha2_224 || \
	(type) == mk_kdf_pbkdf2_e_sha2_256 || \
	(type) == mk_kdf_pbkdf2_e_sha2_384 || \
	(type) == mk_kdf_pbkdf2_e_sha2_512 || \
	(type) == mk_kdf_pbkdf2_e_sha2_512224 || \
	(type) == mk_kdf_pbkdf2_e_sha2_512256 || \
	(type) == mk_kdf_pbkdf2_e_sha3_224 || \
	(type) == mk_kdf_pbkdf2_e_sha3_256 || \
	(type) == mk_kdf_pbkdf2_e_sha3_384 || \
	(type) == mk_kdf_pbkdf2_e_sha3_512)


mk_jumbo void mk_kdf_pbkdf2(enum mk_kdf_pbkdf2_e prf, void const* password, int password_len, void const* salt, int salt_len, long iterations, int key_len, void* key)
{
	mk_assert_type(prf);
	mk_assert(password || password_len == 0);
	mk_assert(password_len >= 0);
	mk_assert(salt || salt_len == 0);
	mk_assert(salt_len >= 0);
	mk_assert(iterations > 0);
	mk_assert(key_len > 0);
	mk_assert(key);

	switch(prf)
	{
		case mk_kdf_pbkdf2_e_md2: mk_kdf_pbkdf2_md2(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_md4: mk_kdf_pbkdf2_md4(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_md5: mk_kdf_pbkdf2_md5(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha1: mk_kdf_pbkdf2_sha1(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha2_224: mk_kdf_pbkdf2_sha2_224(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha2_256: mk_kdf_pbkdf2_sha2_256(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha2_384: mk_kdf_pbkdf2_sha2_384(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha2_512: mk_kdf_pbkdf2_sha2_512(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha2_512224: mk_kdf_pbkdf2_sha2_512224(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha2_512256: mk_kdf_pbkdf2_sha2_512256(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha3_224: mk_kdf_pbkdf2_sha3_224(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha3_256: mk_kdf_pbkdf2_sha3_256(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha3_512: mk_kdf_pbkdf2_sha3_512(password, password_len, salt, salt_len, iterations, key_len, key); break;
		case mk_kdf_pbkdf2_e_sha3_384: mk_kdf_pbkdf2_sha3_384(password, password_len, salt, salt_len, iterations, key_len, key); break;
	}
}


#undef mk_assert_type
