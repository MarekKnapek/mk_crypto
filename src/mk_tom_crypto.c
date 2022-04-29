#pragma warning(push)
#pragma warning(disable:4273) /* warning C4273: 'xxx': inconsistent dll linkage */


#include "mk_tom_crypto.h"

#include "../utils/mk_assert.h"

#include <stdlib.h> /* malloc free NULL */

#include "../../libtomcrypt/src/headers/tomcrypt.h"
#if defined(_M_IX86)
#pragma comment(lib, "../../../../libtomcrypt/MSVC_Win32_Debug/tomcryptd.lib")
#elif defined(_M_AMD64)
#pragma comment(lib, "../../../../libtomcrypt/MSVC_x64_Debug/tomcryptd.lib")
#endif


union mk_tom_systemic_u
{
	symmetric_CBC m_cbc;
	symmetric_CFB m_cfb;
	symmetric_ECB m_ecb;
	symmetric_OFB m_ofb;
};


struct mk_tom_crypto_s
{
	enum mk_tom_crypto_operation_mode_e m_operation_mode;
	enum mk_tom_crypto_block_cipher_e m_block_cipher;
	union mk_tom_systemic_u m_systemic;
};


mk_tom_crypto_h mk_tom_crypto_create(enum mk_tom_crypto_operation_mode_e operation_mode, enum mk_tom_crypto_block_cipher_e block_cipher, void const* iv, void const* key)
{
	int registered;
	struct mk_tom_crypto_s* tom_crypto;
	int key_len;
	int num_rounds;
	int om_started;

	mk_assert
	(
		operation_mode == mk_tom_crypto_operation_mode_cbc ||
		operation_mode == mk_tom_crypto_operation_mode_cfb ||
		operation_mode == mk_tom_crypto_operation_mode_ecb ||
		operation_mode == mk_tom_crypto_operation_mode_ofb ||
		0
	);
	mk_assert
	(
		block_cipher == mk_tom_crypto_block_cipher_aes128 ||
		block_cipher == mk_tom_crypto_block_cipher_aes192 ||
		block_cipher == mk_tom_crypto_block_cipher_aes256 ||
		0
	);
	mk_assert(key);

	registered = register_cipher(&aes_desc);
	mk_assert(registered != -1);

	tom_crypto = (struct mk_tom_crypto_s*)malloc(sizeof (struct mk_tom_crypto_s));
	if(!tom_crypto)
	{
		return NULL;
	}
	tom_crypto->m_operation_mode = operation_mode;
	tom_crypto->m_block_cipher = block_cipher;

	key_len = 0;
	num_rounds = 0;
	switch(block_cipher)
	{
		case mk_tom_crypto_block_cipher_aes128: key_len = 16; num_rounds = 10; break;
		case mk_tom_crypto_block_cipher_aes192: key_len = 24; num_rounds = 12; break;
		case mk_tom_crypto_block_cipher_aes256: key_len = 32; num_rounds = 14; break;
	}

	om_started = CRYPT_ERROR;
	switch(operation_mode)
	{
		case mk_tom_crypto_operation_mode_cbc: om_started = cbc_start(0, iv, key, key_len, num_rounds, &tom_crypto->m_systemic.m_cbc); break;
		case mk_tom_crypto_operation_mode_cfb: om_started = cfb_start(0, iv, key, key_len, num_rounds, &tom_crypto->m_systemic.m_cfb); break;
		case mk_tom_crypto_operation_mode_ecb: om_started = ecb_start(0,     key, key_len, num_rounds, &tom_crypto->m_systemic.m_ecb); break;
		case mk_tom_crypto_operation_mode_ofb: om_started = ofb_start(0, iv, key, key_len, num_rounds, &tom_crypto->m_systemic.m_ofb); break;
	}
	if(!(om_started == CRYPT_OK))
	{
		return NULL;
	}

	return (mk_tom_crypto_h)tom_crypto;
}

void mk_tom_crypto_encrypt(mk_tom_crypto_h tom_crypto_h, int final, void const* input, int input_len_bytes, void* output)
{
	struct mk_tom_crypto_s* tom_crypto;
	int n;
	int m;
	int encrypted;
	unsigned char last_block[16];

	mk_assert(tom_crypto_h);

	tom_crypto = (struct mk_tom_crypto_s*)tom_crypto_h;

	n = input_len_bytes / 16;
	m = input_len_bytes % 16;

	encrypted = CRYPT_ERROR;
	switch(tom_crypto->m_operation_mode)
	{
		case mk_tom_crypto_operation_mode_cbc: encrypted = cbc_encrypt(input, output, n * 16, &tom_crypto->m_systemic.m_cbc); break;
		case mk_tom_crypto_operation_mode_cfb: encrypted = cfb_encrypt(input, output, n * 16, &tom_crypto->m_systemic.m_cfb); break;
		case mk_tom_crypto_operation_mode_ecb: encrypted = ecb_encrypt(input, output, n * 16, &tom_crypto->m_systemic.m_ecb); break;
		case mk_tom_crypto_operation_mode_ofb: encrypted = ofb_encrypt(input, output, n * 16, &tom_crypto->m_systemic.m_ofb); break;
	}
	mk_assert(encrypted == CRYPT_OK);

	if(final == 1)
	{
		memcpy(last_block, (unsigned char const*)input + n * 16, m);
		memset(last_block + m, 16 - m, 16 - m);
		mk_tom_crypto_encrypt(tom_crypto_h, 0, last_block, 16, (unsigned char*)output + n * 16);
	}
}

int mk_tom_crypto_decrypt(mk_tom_crypto_h tom_crypto_h, int final, void const* input, int input_len_bytes, void* output)
{
	struct mk_tom_crypto_s* tom_crypto;
	int decrypted;
	unsigned char padding;
	int i;

	mk_assert(tom_crypto_h);
	(void)final;

	tom_crypto = (struct mk_tom_crypto_s*)tom_crypto_h;

	decrypted = CRYPT_ERROR;
	switch(tom_crypto->m_operation_mode)
	{
		case mk_tom_crypto_operation_mode_cbc: decrypted = cbc_decrypt(input, output, input_len_bytes, &tom_crypto->m_systemic.m_cbc); break;
		case mk_tom_crypto_operation_mode_cfb: decrypted = cfb_decrypt(input, output, input_len_bytes, &tom_crypto->m_systemic.m_cfb); break;
		case mk_tom_crypto_operation_mode_ecb: decrypted = ecb_decrypt(input, output, input_len_bytes, &tom_crypto->m_systemic.m_ecb); break;
		case mk_tom_crypto_operation_mode_ofb: decrypted = ofb_decrypt(input, output, input_len_bytes, &tom_crypto->m_systemic.m_ofb); break;
	}
	mk_assert(decrypted == CRYPT_OK);

	if(final == 1)
	{
		padding = ((unsigned char*)output)[input_len_bytes - 1];
		mk_assert(padding <= 16);
		for(i = 1; i != padding; ++i)
		{
			mk_assert(((unsigned char*)output)[input_len_bytes - 1 - i] == padding);
		}
		return input_len_bytes - padding;
	}
	return input_len_bytes;
}

void mk_tom_crypto_destroy(mk_tom_crypto_h tom_crypto_h)
{
	struct mk_tom_crypto_s* tom_crypto;
	int done;

	mk_assert(tom_crypto_h);
	
	tom_crypto = (struct mk_tom_crypto_s*)tom_crypto_h;

	done = CRYPT_ERROR;
	switch(tom_crypto->m_operation_mode)
	{
		case mk_tom_crypto_operation_mode_cbc: done = cbc_done(&tom_crypto->m_systemic.m_cbc); break;
		case mk_tom_crypto_operation_mode_cfb: done = cfb_done(&tom_crypto->m_systemic.m_cfb); break;
		case mk_tom_crypto_operation_mode_ecb: done = ecb_done(&tom_crypto->m_systemic.m_ecb); break;
		case mk_tom_crypto_operation_mode_ofb: done = ofb_done(&tom_crypto->m_systemic.m_ofb); break;
	}
	mk_assert(done == CRYPT_OK);

	free(tom_crypto);
}


#pragma warning(pop)
