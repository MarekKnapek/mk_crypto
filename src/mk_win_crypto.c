#include "mk_win_crypto.h"

#include "../utils/mk_assert.h"

#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc free NULL */

#include <windows.h>
#include <wincrypt.h>


#if defined(mk_win_crypto_jumbo) && mk_win_crypto_jumbo == 1
#define mk_jumbo static mk_inline
#else
#define mk_jumbo
#endif


struct mk_win_crypto_s
{
	HCRYPTPROV m_csp;
	HCRYPTKEY m_ck;
};


mk_jumbo mk_win_crypto_h mk_win_crypto_create(enum mk_win_crypto_operation_mode_e operation_mode, enum mk_win_crypto_algorithm_e algorithm, void const* iv, void const* key)
{
	struct mk_win_aes128_blob_s
	{
		BLOBHEADER m_header;
		DWORD m_key_len;
		unsigned char m_key[16];
	};
	struct mk_win_aes192_blob_s
	{
		BLOBHEADER m_header;
		DWORD m_key_len;
		unsigned char m_key[24];
	};
	struct mk_win_aes256_blob_s
	{
		BLOBHEADER m_header;
		DWORD m_key_len;
		unsigned char m_key[32];
	};
	union mk_win_aes_blob_u
	{
		struct mk_win_aes128_blob_s m_128;
		struct mk_win_aes192_blob_s m_192;
		struct mk_win_aes256_blob_s m_256;
	};

	BOOL csp_acquired;
	HCRYPTPROV csp;
	union mk_win_aes_blob_u key_blob;
	int key_blob_size;
	BOOL ck_created;
	HCRYPTKEY ck;
	DWORD kp_mode;
	BOOL mode_set;
	BOOL csp_released;
	BOOL key_destroyed;
	BOOL iv_set;

	mk_assert
	(
		algorithm == mk_win_crypto_algorithm_aes128 ||
		algorithm == mk_win_crypto_algorithm_aes192 ||
		algorithm == mk_win_crypto_algorithm_aes256 ||
		0
	);
	mk_assert(key);

	csp_acquired = CryptAcquireContextW(&csp, NULL, MS_ENH_RSA_AES_PROV_W, PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	if(!(csp_acquired != 0))
	{
		return NULL;
	}

	key_blob_size = 0;
	switch(algorithm)
	{
		case mk_win_crypto_algorithm_aes128:
		{
			key_blob.m_128.m_header.bType = PLAINTEXTKEYBLOB;
			key_blob.m_128.m_header.bVersion = CUR_BLOB_VERSION;
			key_blob.m_128.m_header.reserved = 0;
			key_blob.m_128.m_header.aiKeyAlg = CALG_AES_128;
			key_blob.m_128.m_key_len = 16;
			memcpy(key_blob.m_128.m_key, key, 16);
			key_blob_size = sizeof(key_blob.m_128);
		}
		break;
		case mk_win_crypto_algorithm_aes192:
		{
			key_blob.m_192.m_header.bType = PLAINTEXTKEYBLOB;
			key_blob.m_192.m_header.bVersion = CUR_BLOB_VERSION;
			key_blob.m_192.m_header.reserved = 0;
			key_blob.m_192.m_header.aiKeyAlg = CALG_AES_192;
			key_blob.m_192.m_key_len = 24;
			memcpy(key_blob.m_192.m_key, key, 24);
			key_blob_size = sizeof(key_blob.m_192);
		}
		break;
		case mk_win_crypto_algorithm_aes256:
		{
			key_blob.m_256.m_header.bType = PLAINTEXTKEYBLOB;
			key_blob.m_256.m_header.bVersion = CUR_BLOB_VERSION;
			key_blob.m_256.m_header.reserved = 0;
			key_blob.m_256.m_header.aiKeyAlg = CALG_AES_256;
			key_blob.m_256.m_key_len = 32;
			memcpy(key_blob.m_256.m_key, key, 32);
			key_blob_size = sizeof(key_blob.m_256);
		}
		break;
	}
	ck_created = CryptImportKey(csp, (BYTE const*)&key_blob, key_blob_size, 0, 0, &ck);
	if(!(ck_created != 0))
	{
		csp_released = CryptReleaseContext(csp, 0);
		mk_assert(csp_released != 0);
		return NULL;
	}

	switch(operation_mode)
	{
		case mk_win_crypto_operation_mode_cbc: kp_mode = CRYPT_MODE_CBC; break;
		case mk_win_crypto_operation_mode_cfb: kp_mode = CRYPT_MODE_CFB; break;
		case mk_win_crypto_operation_mode_ecb: kp_mode = CRYPT_MODE_ECB; break;
	}
	mode_set = CryptSetKeyParam(ck, KP_MODE, (BYTE const*)&kp_mode, 0);
	if(!(mode_set != 0))
	{
		key_destroyed = CryptDestroyKey(ck);
		mk_assert(key_destroyed != 0);
		csp_released = CryptReleaseContext(csp, 0);
		mk_assert(csp_released != 0);
		return NULL;
	}

	if(iv)
	{
		iv_set = CryptSetKeyParam(ck, KP_IV, (BYTE const*)iv, 0);
		if(!(iv_set != 0))
		{
			key_destroyed = CryptDestroyKey(ck);
			mk_assert(key_destroyed != 0);
			csp_released = CryptReleaseContext(csp, 0);
			mk_assert(csp_released != 0);
			return NULL;
		}
	}

	struct mk_win_crypto_s* win_crypto = (struct mk_win_crypto_s*)malloc(sizeof (struct mk_win_crypto_s));
	if(!win_crypto)
	{
		key_destroyed = CryptDestroyKey(ck);
		mk_assert(key_destroyed != 0);
		csp_released = CryptReleaseContext(csp, 0);
		mk_assert(csp_released != 0);
		return NULL;
	}

	win_crypto->m_csp = csp;
	win_crypto->m_ck = ck;
	return (mk_win_crypto_h)win_crypto;
}

mk_jumbo void mk_win_crypto_encrypt(mk_win_crypto_h win_crypto_h, int final, void const* input, int input_len_bytes, void* output)
{
	struct mk_win_crypto_s* win_crypto;
	DWORD data_len;
	BOOL encrypted;
	DWORD out_len;

	mk_assert(win_crypto_h);
	mk_assert(final == 0 || final == 1);

	win_crypto = (struct mk_win_crypto_s*)win_crypto_h;

	if(input != output)
	{
		memcpy(output, input, input_len_bytes);
	}
	data_len = input_len_bytes;
	out_len = (input_len_bytes / 16 + final) * 16;
	encrypted = CryptEncrypt(win_crypto->m_ck, 0, final == 0 ? FALSE : TRUE, 0, output, &data_len, out_len);
	mk_assert(encrypted != 0);
	mk_assert(data_len == out_len);
}

mk_jumbo void mk_win_crypto_destroy(mk_win_crypto_h win_crypto_h)
{
	struct mk_win_crypto_s* win_crypto;
	BOOL key_destroyed;
	BOOL csp_released;

	mk_assert(win_crypto_h);
	
	win_crypto = (struct mk_win_crypto_s*)win_crypto_h;

	key_destroyed = CryptDestroyKey(win_crypto->m_ck);
	mk_assert(key_destroyed != 0);
	csp_released = CryptReleaseContext(win_crypto->m_csp, 0);
	mk_assert(csp_released != 0);

	free(win_crypto);
}


#undef mk_jumbo
