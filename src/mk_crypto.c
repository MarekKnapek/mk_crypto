#include "mk_crypto.h"

#include "mk_crypt.h"

#include "../utils/mk_assert.h"

#include <stdlib.h> /* malloc free NULL */


mk_crypto_h mk_crypto_create(enum mk_crypto_operation_mode_e operation_mode, enum mk_crypto_block_cipher_e block_cipher, enum mk_crypto_padding_e padding, void const* key, int key_len)
{
	mk_assert
	(
		operation_mode == mk_crypto_operation_mode_cbc ||
		operation_mode == mk_crypto_operation_mode_cfb ||
		operation_mode == mk_crypto_operation_mode_ctr ||
		operation_mode == mk_crypto_operation_mode_ecb ||
		operation_mode == mk_crypto_operation_mode_gcm ||
		operation_mode == mk_crypto_operation_mode_ofb ||
		0
	);
	mk_assert
	(
		block_cipher == mk_crypto_block_cipher_aes128 ||
		block_cipher == mk_crypto_block_cipher_aes192 ||
		block_cipher == mk_crypto_block_cipher_aes256 ||
		0
	);
	mk_assert
	(
		padding == mk_crypto_padding_pkcs7 ||
		padding == mk_crypto_padding_10s ||
		padding == mk_crypto_padding_10s1 ||
		padding == mk_crypto_padding_zero ||
		padding == mk_crypto_padding_none ||
		0
	);
	mk_assert(key || key_len == 0);
	mk_assert(key_len >= 0);
	mk_assert(key);

	struct mk_crypt_s* crypt = (struct mk_crypt_s*)malloc(sizeof(struct mk_crypt_s));
	if(!crypt)
	{
		return NULL;
	}
	mk_crypt_init(crypt, operation_mode, block_cipher, padding, key, key_len);
	return (mk_crypto_h)crypt;
}

void mk_crypto_set_param(mk_crypto_h crypto, enum mk_crypto_param_e param, void const* value)
{
	struct aad_s
	{
		void const* m_aad;
		int m_aad_len;
	};

	mk_assert(crypto);
	mk_assert
	(
		param == mk_crypto_param_aad_append ||
		param == mk_crypto_param_aad_finish ||
		param == mk_crypto_param_cfb_s_bytes ||
		param == mk_crypto_param_ctr_endian ||
		0
	);
	mk_assert(value);

	switch(param)
	{
		case mk_crypto_param_aad_append: mk_crypt_set_param_aad_append((struct mk_crypt_s*)crypto, ((struct aad_s*)value)->m_aad, ((struct aad_s*)value)->m_aad_len); break;
		case mk_crypto_param_aad_finish: mk_crypt_set_param_aad_finish((struct mk_crypt_s*)crypto, ((struct aad_s*)value)->m_aad, ((struct aad_s*)value)->m_aad_len); break;
		case mk_crypto_param_cfb_s_bytes: mk_crypt_set_param_cfb_s_bytes((struct mk_crypt_s*)crypto, *(int const*)value); break;
		case mk_crypto_param_ctr_endian: mk_crypt_set_param_ctr_endian((struct mk_crypt_s*)crypto, *(int const*)value); break;
		default: mk_assert(0); break;
	}
}

int mk_crypto_encrypt(mk_crypto_h crypto, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes)
{
	return mk_crypt_encrypt((struct mk_crypt_s*)crypto, final, input, input_len_bytes, output, output_len_bytes);
}

int mk_crypto_decrypt(mk_crypto_h crypto, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes)
{
	return mk_crypt_decrypt((struct mk_crypt_s*)crypto, final, input, input_len_bytes, output, output_len_bytes);
}

void mk_crypto_destroy(mk_crypto_h crypto)
{
	mk_assert(crypto);

	free(crypto);
}
