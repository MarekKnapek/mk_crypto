#include "mk_crypto.h"

#include "mk_crypt.h"

#include "../utils/mk_assert.h"

#include <stdlib.h> /* malloc free NULL */


mk_crypto_h mk_crypto_create(enum mk_crypto_operation_mode_e operation_mode, enum mk_crypto_block_cipher_e block_cipher, void const* iv, void const* key)
{
	mk_assert
	(
		operation_mode == mk_crypto_operation_mode_cbc ||
		operation_mode == mk_crypto_operation_mode_cfb ||
		operation_mode == mk_crypto_operation_mode_ecb ||
		0
	);
	mk_assert
	(
		block_cipher == mk_crypto_block_cipher_aes128 ||
		block_cipher == mk_crypto_block_cipher_aes192 ||
		block_cipher == mk_crypto_block_cipher_aes256 ||
		0
	);
	mk_assert(key);

	struct mk_crypt_s* crypt = (struct mk_crypt_s*)malloc(sizeof(struct mk_crypt_s));
	if(!crypt)
	{
		return NULL;
	}
	mk_crypt_init(crypt, operation_mode, block_cipher, key);
	if(operation_mode != mk_operation_mode_ecb)
	{
		mk_crypt_set_param_iv(crypt, iv);
	}
	return (mk_crypto_h)crypt;
}

void mk_crypto_set_param(mk_crypto_h crypto, enum mk_crypto_param_e param, void const* value)
{
	mk_assert(crypto);

	mk_assert
	(
		param == mk_crypto_param_cfb_s_bytes ||
		0
	);

	switch(param)
	{
		case mk_crypto_param_cfb_s_bytes: mk_crypt_set_param_cfb_s_bytes((struct mk_crypt_s*)crypto, *(int const*)value); break;
	}
}

void mk_crypto_encrypt(mk_crypto_h crypto, int final, void const* input, int input_len_bytes, void* output)
{
	mk_assert(crypto);

	mk_crypt_encrypt((struct mk_crypt_s*)crypto, final, input, input_len_bytes, output);
}

int mk_crypto_decrypt(mk_crypto_h crypto, int final, void const* input, int input_len_bytes, void* output)
{
	mk_assert(crypto);

	return mk_crypt_decrypt((struct mk_crypt_s*)crypto, final, input, input_len_bytes, output);
}

void mk_crypto_destroy(mk_crypto_h crypto)
{
	mk_assert(crypto);

	free(crypto);
}
