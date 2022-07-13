#include "mk_kdf_pbkdf2.h"

#include "kdf/pbkdf2/mk_kdf_pbkdf2_hash.h"

#include "utils/mk_assert.h"
#include "utils/mk_jumbo.h"


mk_jumbo void mk_kdf_pbkdf2(enum mk_hash_e prf, void const* password, int password_len, void const* salt, int salt_len, long iterations, int key_len, void* key)
{
	mk_assert(mk_hash_e_is_good(prf));
	mk_assert(password || password_len == 0);
	mk_assert(password_len >= 0);
	mk_assert(salt || salt_len == 0);
	mk_assert(salt_len >= 0);
	mk_assert(iterations > 0);
	mk_assert(key_len > 0);
	mk_assert(key);

	switch(prf)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xpbkdf2(alg) concat(mk_kdf_pbkdf2_hash_, alg)
		#define xcontent(alg) case xenum(alg): xpbkdf2(alg)(password, password_len, salt, salt_len, iterations, key_len, key); break;
		xmacro
		#undef xenum
		#undef xpbkdf2
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
}
