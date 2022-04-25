#include "mk_crypto.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <stdlib.h> /* malloc free NULL */


#define mk_crypt_jumbo 1
#include "mk_crypt.c"
#undef mk_crypt_jumbo


#if defined(mk_crypto_jumbo) && mk_crypto_jumbo == 1
#define mk_jumbo static mk_inline
#else
#define mk_jumbo
#endif


mk_jumbo mk_crypto_h mk_crypto_create(enum mk_crypto_operation_mode_e operation_mode, enum mk_crypto_algorithm_e algorithm, void const* iv, void const* key)
{
	mk_assert
	(
		operation_mode == mk_crypto_operation_mode_cbc  ||
		operation_mode == mk_crypto_operation_mode_cfb  ||
		operation_mode == mk_crypto_operation_mode_ctr  ||
		operation_mode == mk_crypto_operation_mode_cts  ||
		operation_mode == mk_crypto_operation_mode_ecb  ||
		operation_mode == mk_crypto_operation_mode_ofb  ||
		operation_mode == mk_crypto_operation_mode_pcbc ||
		0
	);
	mk_assert
	(
		algorithm == mk_crypto_algorithm_aes128 ||
		algorithm == mk_crypto_algorithm_aes192 ||
		algorithm == mk_crypto_algorithm_aes256 ||
		0
	);
	mk_assert(key);

	struct mk_crypt_s* crypt = (struct mk_crypt_s*)malloc(sizeof(struct mk_crypt_s));
	if(!crypt)
	{
		return NULL;
	}
	mk_crypt_init(crypt, (enum mk_crypt_operation_mode_e)operation_mode, (enum mk_crypt_algorithm_e)algorithm, iv, key);
	return (mk_crypto_h)crypt;
}

mk_jumbo void mk_crypto_encrypt(mk_crypto_h crypto, int final, void const* input, int input_len_bytes, void* output)
{
	mk_assert(crypto);

	mk_crypt_encrypt((struct mk_crypt_s*)crypto, final, input, input_len_bytes, output);
}

mk_jumbo void mk_crypto_destroy(mk_crypto_h crypto)
{
	mk_assert(crypto);

	free(crypto);
}


#undef mk_jumbo
