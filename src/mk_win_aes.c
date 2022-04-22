#include "mk_win_aes.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <string.h> /* memcpy */

#include <windows.h>
#include <wincrypt.h>

#if 0
void mk_win_aes128_encrypt_block(void const* msg, void const* key, void* out)
{
	struct mk_win_aes128_blob_s
	{
		BLOBHEADER m_header;
		DWORD m_key_len;
		unsigned char m_key[16];
	};

	BOOL csp_created;
	HCRYPTPROV csp;
	struct mk_win_aes128_blob_s key_blob;
	BOOL ck_created;
	HCRYPTKEY ck;
	DWORD data_len;
	BOOL encrypted;
	BOOL ck_destroyed;
	BOOL csp_freed;

	mk_assert(msg);
	mk_assert(key);
	mk_assert(out);

	csp_created = CryptAcquireContextW(&csp, NULL, MS_ENH_RSA_AES_PROV_W, PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);
	
	key_blob.m_header.bType = PLAINTEXTKEYBLOB;
	key_blob.m_header.bVersion = CUR_BLOB_VERSION;
	key_blob.m_header.reserved = 0;
	key_blob.m_header.aiKeyAlg = CALG_AES_128;
	key_blob.m_key_len = 16;
	memcpy(key_blob.m_key, key, 16);
	ck_created = CryptImportKey(csp, (BYTE const*)&key_blob, sizeof(key_blob), 0, 0, &ck);
	mk_assert(ck_created != 0);

	memcpy(out, msg, 16);
	data_len = 16;
	encrypted = CryptEncrypt(ck, 0, FALSE, 0, out, &data_len, 16);
	mk_assert(encrypted != 0);
	mk_assert(data_len == 16);

	ck_destroyed = CryptDestroyKey(ck);
	mk_assert(ck_destroyed != 0);

	csp_freed = CryptReleaseContext(csp, 0);
	mk_assert(csp_freed != FALSE);
}

void mk_win_aes128_decrypt_block(void const* msg, void const* key, void* out)
{
	struct mk_win_aes128_blob_s
	{
		BLOBHEADER m_header;
		DWORD m_key_len;
		unsigned char m_key[16];
	};

	BOOL csp_created;
	HCRYPTPROV csp;
	struct mk_win_aes128_blob_s key_blob;
	BOOL ck_created;
	HCRYPTKEY ck;
	DWORD data_len;
	BOOL decrypted;
	BOOL ck_destroyed;
	BOOL csp_freed;

	mk_assert(msg);
	mk_assert(key);
	mk_assert(out);

	csp_created = CryptAcquireContextW(&csp, NULL, MS_ENH_RSA_AES_PROV_W, PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);
	
	key_blob.m_header.bType = PLAINTEXTKEYBLOB;
	key_blob.m_header.bVersion = CUR_BLOB_VERSION;
	key_blob.m_header.reserved = 0;
	key_blob.m_header.aiKeyAlg = CALG_AES_128;
	key_blob.m_key_len = 16;
	memcpy(key_blob.m_key, key, 16);
	ck_created = CryptImportKey(csp, (BYTE const*)&key_blob, sizeof(key_blob), 0, 0, &ck);
	mk_assert(ck_created != 0);

	memcpy(out, msg, 16);
	data_len = 16;
	decrypted = CryptDecrypt(ck, 0, FALSE, 0, out, &data_len);
	mk_assert(decrypted != 0);
	mk_assert(data_len == 16);

	ck_destroyed = CryptDestroyKey(ck);
	mk_assert(ck_destroyed != 0);

	csp_freed = CryptReleaseContext(csp, 0);
	mk_assert(csp_freed != FALSE);
}


void mk_win_aes192_encrypt_block(void const* msg, void const* key, void* out)
{
	struct mk_win_aes192_blob_s
	{
		BLOBHEADER m_header;
		DWORD m_key_len;
		unsigned char m_key[24];
	};

	BOOL csp_created;
	HCRYPTPROV csp;
	struct mk_win_aes192_blob_s key_blob;
	BOOL ck_created;
	HCRYPTKEY ck;
	DWORD data_len;
	BOOL encrypted;
	BOOL ck_destroyed;
	BOOL csp_freed;

	mk_assert(msg);
	mk_assert(key);
	mk_assert(out);

	csp_created = CryptAcquireContextW(&csp, NULL, MS_ENH_RSA_AES_PROV_W, PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);
	
	key_blob.m_header.bType = PLAINTEXTKEYBLOB;
	key_blob.m_header.bVersion = CUR_BLOB_VERSION;
	key_blob.m_header.reserved = 0;
	key_blob.m_header.aiKeyAlg = CALG_AES_192;
	key_blob.m_key_len = 24;
	memcpy(key_blob.m_key, key, 24);
	ck_created = CryptImportKey(csp, (BYTE const*)&key_blob, sizeof(key_blob), 0, 0, &ck);
	mk_assert(ck_created != 0);

	memcpy(out, msg, 16);
	data_len = 16;
	encrypted = CryptEncrypt(ck, 0, FALSE, 0, out, &data_len, 16);
	mk_assert(encrypted != 0);
	mk_assert(data_len == 16);

	ck_destroyed = CryptDestroyKey(ck);
	mk_assert(ck_destroyed != 0);

	csp_freed = CryptReleaseContext(csp, 0);
	mk_assert(csp_freed != FALSE);
}

void mk_win_aes192_decrypt_block(void const* msg, void const* key, void* out)
{
	struct mk_win_aes192_blob_s
	{
		BLOBHEADER m_header;
		DWORD m_key_len;
		unsigned char m_key[24];
	};

	BOOL csp_created;
	HCRYPTPROV csp;
	struct mk_win_aes192_blob_s key_blob;
	BOOL ck_created;
	HCRYPTKEY ck;
	DWORD data_len;
	BOOL decrypted;
	BOOL ck_destroyed;
	BOOL csp_freed;

	mk_assert(msg);
	mk_assert(key);
	mk_assert(out);

	csp_created = CryptAcquireContextW(&csp, NULL, MS_ENH_RSA_AES_PROV_W, PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);
	
	key_blob.m_header.bType = PLAINTEXTKEYBLOB;
	key_blob.m_header.bVersion = CUR_BLOB_VERSION;
	key_blob.m_header.reserved = 0;
	key_blob.m_header.aiKeyAlg = CALG_AES_192;
	key_blob.m_key_len = 24;
	memcpy(key_blob.m_key, key, 24);
	ck_created = CryptImportKey(csp, (BYTE const*)&key_blob, sizeof(key_blob), 0, 0, &ck);
	mk_assert(ck_created != 0);

	memcpy(out, msg, 16);
	data_len = 16;
	decrypted = CryptDecrypt(ck, 0, FALSE, 0, out, &data_len);
	mk_assert(decrypted != 0);
	mk_assert(data_len == 16);

	ck_destroyed = CryptDestroyKey(ck);
	mk_assert(ck_destroyed != 0);

	csp_freed = CryptReleaseContext(csp, 0);
	mk_assert(csp_freed != FALSE);
}


void mk_win_aes256_encrypt_block(void const* msg, void const* key, void* out)
{
	struct mk_win_aes256_blob_s
	{
		BLOBHEADER m_header;
		DWORD m_key_len;
		unsigned char m_key[32];
	};

	BOOL csp_created;
	HCRYPTPROV csp;
	struct mk_win_aes256_blob_s key_blob;
	BOOL ck_created;
	HCRYPTKEY ck;
	DWORD data_len;
	BOOL encrypted;
	BOOL ck_destroyed;
	BOOL csp_freed;

	mk_assert(msg);
	mk_assert(key);
	mk_assert(out);

	csp_created = CryptAcquireContextW(&csp, NULL, MS_ENH_RSA_AES_PROV_W, PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);
	
	key_blob.m_header.bType = PLAINTEXTKEYBLOB;
	key_blob.m_header.bVersion = CUR_BLOB_VERSION;
	key_blob.m_header.reserved = 0;
	key_blob.m_header.aiKeyAlg = CALG_AES_256;
	key_blob.m_key_len = 32;
	memcpy(key_blob.m_key, key, 32);
	ck_created = CryptImportKey(csp, (BYTE const*)&key_blob, sizeof(key_blob), 0, 0, &ck);
	mk_assert(ck_created != 0);

	memcpy(out, msg, 16);
	data_len = 16;
	encrypted = CryptEncrypt(ck, 0, FALSE, 0, out, &data_len, 16);
	mk_assert(encrypted != 0);
	mk_assert(data_len == 16);

	ck_destroyed = CryptDestroyKey(ck);
	mk_assert(ck_destroyed != 0);

	csp_freed = CryptReleaseContext(csp, 0);
	mk_assert(csp_freed != FALSE);
}

void mk_win_aes256_decrypt_block(void const* msg, void const* key, void* out)
{
	struct mk_win_aes256_blob_s
	{
		BLOBHEADER m_header;
		DWORD m_key_len;
		unsigned char m_key[32];
	};

	BOOL csp_created;
	HCRYPTPROV csp;
	struct mk_win_aes256_blob_s key_blob;
	BOOL ck_created;
	HCRYPTKEY ck;
	DWORD data_len;
	BOOL decrypted;
	BOOL ck_destroyed;
	BOOL csp_freed;

	mk_assert(msg);
	mk_assert(key);
	mk_assert(out);

	csp_created = CryptAcquireContextW(&csp, NULL, MS_ENH_RSA_AES_PROV_W, PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);
	
	key_blob.m_header.bType = PLAINTEXTKEYBLOB;
	key_blob.m_header.bVersion = CUR_BLOB_VERSION;
	key_blob.m_header.reserved = 0;
	key_blob.m_header.aiKeyAlg = CALG_AES_256;
	key_blob.m_key_len = 32;
	memcpy(key_blob.m_key, key, 32);
	ck_created = CryptImportKey(csp, (BYTE const*)&key_blob, sizeof(key_blob), 0, 0, &ck);
	mk_assert(ck_created != 0);

	memcpy(out, msg, 16);
	data_len = 16;
	decrypted = CryptDecrypt(ck, 0, FALSE, 0, out, &data_len);
	mk_assert(decrypted != 0);
	mk_assert(data_len == 16);

	ck_destroyed = CryptDestroyKey(ck);
	mk_assert(ck_destroyed != 0);

	csp_freed = CryptReleaseContext(csp, 0);
	mk_assert(csp_freed != FALSE);
}


void mk_win_aes_encrypt_msg(enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key, void const* msg, size_t msg_len, void* out)
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

	BOOL csp_created;
	HCRYPTPROV csp;
	union mk_win_aes_blob_u key_blob;
	int key_blob_size;
	BOOL ck_created;
	HCRYPTKEY ck;
	DWORD kp_mode;
	BOOL mode_set;
	BOOL iv_set;
	DWORD data_len;
	BOOL encrypted;
	BOOL ck_destroyed;
	BOOL csp_freed;

	mk_assert(key_len == mk_win_aes_key_len_128 || key_len == mk_win_aes_key_len_192 || key_len == mk_win_aes_key_len_256);
	mk_assert(om == mk_win_aes_operation_mode_cbc || om == mk_win_aes_operation_mode_ecb || om == mk_win_aes_operation_mode_ofb || om == mk_win_aes_operation_mode_cfb || om == mk_win_aes_operation_mode_cts);
	mk_assert(padding == mk_win_aes_padding_pkcs7);
	mk_assert(iv);
	mk_assert(key);
	mk_assert(msg);
	mk_assert(out);

	csp_created = CryptAcquireContextW(&csp, NULL, MS_ENH_RSA_AES_PROV_W, PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);
	
	switch(key_len)
	{
		case mk_win_aes_key_len_128:
			key_blob.m_128.m_header.bType = PLAINTEXTKEYBLOB;
			key_blob.m_128.m_header.bVersion = CUR_BLOB_VERSION;
			key_blob.m_128.m_header.reserved = 0;
			key_blob.m_128.m_header.aiKeyAlg = CALG_AES_128;
			key_blob.m_128.m_key_len = 16;
			memcpy(key_blob.m_128.m_key, key, 16);
			key_blob_size = sizeof(key_blob.m_128);
		break;
		case mk_win_aes_key_len_192:
			key_blob.m_192.m_header.bType = PLAINTEXTKEYBLOB;
			key_blob.m_192.m_header.bVersion = CUR_BLOB_VERSION;
			key_blob.m_192.m_header.reserved = 0;
			key_blob.m_192.m_header.aiKeyAlg = CALG_AES_192;
			key_blob.m_192.m_key_len = 24;
			memcpy(key_blob.m_192.m_key, key, 24);
			key_blob_size = sizeof(key_blob.m_192);
		break;
		case mk_win_aes_key_len_256:
			key_blob.m_256.m_header.bType = PLAINTEXTKEYBLOB;
			key_blob.m_256.m_header.bVersion = CUR_BLOB_VERSION;
			key_blob.m_256.m_header.reserved = 0;
			key_blob.m_256.m_header.aiKeyAlg = CALG_AES_256;
			key_blob.m_256.m_key_len = 32;
			memcpy(key_blob.m_256.m_key, key, 32);
			key_blob_size = sizeof(key_blob.m_256);
		break;
	}
	ck_created = CryptImportKey(csp, (BYTE const*)&key_blob, key_blob_size, 0, 0, &ck);
	mk_assert(ck_created != 0);

	switch(om)
	{
		case mk_win_aes_operation_mode_cbc: kp_mode = CRYPT_MODE_CBC; break;
		case mk_win_aes_operation_mode_ecb: kp_mode = CRYPT_MODE_ECB; break;
		case mk_win_aes_operation_mode_ofb: kp_mode = CRYPT_MODE_OFB; break;
		case mk_win_aes_operation_mode_cfb: kp_mode = CRYPT_MODE_CFB; break;
		case mk_win_aes_operation_mode_cts: kp_mode = CRYPT_MODE_CTS; break;
	}
	mode_set = CryptSetKeyParam(ck, KP_MODE, (BYTE const*)&kp_mode, 0);
	mk_assert(mode_set != 0);

	iv_set = CryptSetKeyParam(ck, KP_IV, (BYTE const*)iv, 0);
	mk_assert(iv_set != 0);

	if(msg != out)
	{
		memcpy(out, msg, msg_len);
	}
	data_len = (DWORD)msg_len;
	encrypted = CryptEncrypt(ck, 0, TRUE, 0, out, &data_len, (msg_len / 16 + 1) * 16);/*cast?*/
	mk_assert(encrypted != 0);
	mk_assert((data_len == (msg_len / 16 + 0) * 16) || (data_len == (msg_len / 16 + 1) * 16));/*cast?*/

	ck_destroyed = CryptDestroyKey(ck);
	mk_assert(ck_destroyed != 0);

	csp_freed = CryptReleaseContext(csp, 0);
	mk_assert(csp_freed != FALSE);
}

void mk_win_aes_decrypt_msg(enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key, void const* msg, size_t msg_len, void* out)
{
}
#endif






static mk_inline void mk_win_aes_detail_init(struct mk_win_aes_s* self, enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key)
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

	BOOL csp_created;
	HCRYPTPROV csp;
	union mk_win_aes_blob_u key_blob;
	int key_blob_size;
	BOOL ck_created;
	HCRYPTKEY ck;
	DWORD kp_mode;
	BOOL mode_set;
	BOOL iv_set;

	mk_assert(self);
	mk_assert(key_len == mk_win_aes_key_len_128 || key_len == mk_win_aes_key_len_192 || key_len == mk_win_aes_key_len_256);
	mk_assert(om == mk_win_aes_operation_mode_cbc || om == mk_win_aes_operation_mode_ecb || om == mk_win_aes_operation_mode_ofb || om == mk_win_aes_operation_mode_cfb || om == mk_win_aes_operation_mode_cts);
	mk_assert(padding == mk_win_aes_padding_pkcs7);
	mk_assert(iv);
	mk_assert(key);

	csp_created = CryptAcquireContextW(&csp, NULL, MS_ENH_RSA_AES_PROV_W, PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);

	key_blob_size = 0;
	switch(key_len)
	{
		case mk_win_aes_key_len_128:
			key_blob.m_128.m_header.bType = PLAINTEXTKEYBLOB;
			key_blob.m_128.m_header.bVersion = CUR_BLOB_VERSION;
			key_blob.m_128.m_header.reserved = 0;
			key_blob.m_128.m_header.aiKeyAlg = CALG_AES_128;
			key_blob.m_128.m_key_len = 16;
			memcpy(key_blob.m_128.m_key, key, 16);
			key_blob_size = sizeof(key_blob.m_128);
		break;
		case mk_win_aes_key_len_192:
			key_blob.m_192.m_header.bType = PLAINTEXTKEYBLOB;
			key_blob.m_192.m_header.bVersion = CUR_BLOB_VERSION;
			key_blob.m_192.m_header.reserved = 0;
			key_blob.m_192.m_header.aiKeyAlg = CALG_AES_192;
			key_blob.m_192.m_key_len = 24;
			memcpy(key_blob.m_192.m_key, key, 24);
			key_blob_size = sizeof(key_blob.m_192);
		break;
		case mk_win_aes_key_len_256:
			key_blob.m_256.m_header.bType = PLAINTEXTKEYBLOB;
			key_blob.m_256.m_header.bVersion = CUR_BLOB_VERSION;
			key_blob.m_256.m_header.reserved = 0;
			key_blob.m_256.m_header.aiKeyAlg = CALG_AES_256;
			key_blob.m_256.m_key_len = 32;
			memcpy(key_blob.m_256.m_key, key, 32);
			key_blob_size = sizeof(key_blob.m_256);
		break;
	}
	ck_created = CryptImportKey(csp, (BYTE const*)&key_blob, key_blob_size, 0, 0, &ck);
	mk_assert(ck_created != 0);

	kp_mode = 0;
	switch(om)
	{
		case mk_win_aes_operation_mode_cbc: kp_mode = CRYPT_MODE_CBC; break;
		case mk_win_aes_operation_mode_ecb: kp_mode = CRYPT_MODE_ECB; break;
		case mk_win_aes_operation_mode_ofb: kp_mode = CRYPT_MODE_OFB; break;/**/
		case mk_win_aes_operation_mode_cfb: kp_mode = CRYPT_MODE_CFB; break;
		case mk_win_aes_operation_mode_cts: kp_mode = CRYPT_MODE_CTS; break;/**/
	}
	if(kp_mode == CRYPT_MODE_OFB) --kp_mode;
	if(kp_mode == CRYPT_MODE_CTS) --kp_mode;
	mode_set = CryptSetKeyParam(ck, KP_MODE, (BYTE const*)&kp_mode, 0);
	mk_assert(mode_set != 0);

	iv_set = CryptSetKeyParam(ck, KP_IV, (BYTE const*)iv, 0);
	mk_assert(iv_set != 0);

	self->m_csp = csp;
	self->m_ck = ck;
}


void mk_win_aes_encrypt_init(struct mk_win_aes_s* self, enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key)
{
	mk_win_aes_detail_init(self, key_len, om, padding, iv, key);
}

void mk_win_aes_encrypt_blocks(struct mk_win_aes_s* self, void const* msg, int n, void* out)
{
	DWORD data_len;
	BOOL encrypted;

	mk_assert(self);
	mk_assert(msg);
	mk_assert(n >= 0);
	mk_assert(out);

	if(msg != out)
	{
		memcpy(out, msg, n * 16);
	}
	data_len = n * 16;
	encrypted = CryptEncrypt(self->m_ck, 0, FALSE, 0, out, &data_len, n * 16);
	mk_assert(encrypted != 0);
	mk_assert(data_len == (DWORD)n * 16);
}

void mk_win_aes_encrypt_finish(struct mk_win_aes_s* self, void const* msg, int msg_len, void* out)
{
	DWORD data_len;
	BOOL encrypted;
	BOOL ck_destroyed;
	BOOL csp_freed;

	mk_assert(self);
	mk_assert(msg);
	mk_assert(msg_len >= 0 && msg_len < 16);
	mk_assert(out);

	if(msg != out)
	{
		memcpy(out, msg, msg_len);
	}
	data_len = msg_len;
	encrypted = CryptEncrypt(self->m_ck, 0, TRUE, 0, out, &data_len, 16);
	mk_assert(encrypted != 0);
	mk_assert(data_len == 16);

	ck_destroyed = CryptDestroyKey(self->m_ck);
	mk_assert(ck_destroyed != 0);

	csp_freed = CryptReleaseContext(self->m_csp, 0);
	mk_assert(csp_freed != FALSE);
}


void mk_win_aes_decrypt_init(struct mk_win_aes_s* self, enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key)
{
	mk_win_aes_detail_init(self, key_len, om, padding, iv, key);
}

void mk_win_aes_decrypt_blocks(struct mk_win_aes_s* self, void const* msg, int n, void* out)
{
	DWORD data_len;
	BOOL decrypted;

	mk_assert(self);
	mk_assert(msg);
	mk_assert(n >= 0);
	mk_assert(out);

	if(msg != out)
	{
		memcpy(out, msg, n * 16);
	}
	data_len = n * 16;
	decrypted = CryptDecrypt(self->m_ck, 0, FALSE, 0, out, &data_len);
	mk_assert(decrypted != 0);
	mk_assert(data_len == (DWORD)n * 16);
}

void mk_win_aes_decrypt_finish(struct mk_win_aes_s* self, void const* msg, void* out)
{
	DWORD data_len;
	BOOL encrypted;
	BOOL ck_destroyed;
	BOOL csp_freed;

	mk_assert(self);
	mk_assert(msg);
	mk_assert(out);

	if(msg != out)
	{
		memcpy(out, msg, 16);
	}
	data_len = 16;
	encrypted = CryptDecrypt(self->m_ck, 0, TRUE, 0, out, &data_len);
	mk_assert(encrypted != 0);
	mk_assert(data_len == 16);

	ck_destroyed = CryptDestroyKey(self->m_ck);
	mk_assert(ck_destroyed != 0);

	csp_freed = CryptReleaseContext(self->m_csp, 0);
	mk_assert(csp_freed != FALSE);
}


void mk_win_aes_encrypt_msg(enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key, void const* msg, size_t msg_len, void* out)
{
	struct mk_win_aes_s mk_win_aes;
	int n;
	int m;

	n = msg_len / 16;
	m = msg_len % 16;
	mk_win_aes_encrypt_init(&mk_win_aes, key_len, om, padding, iv, key);
	mk_win_aes_encrypt_blocks(&mk_win_aes, msg, n, out);
	mk_win_aes_encrypt_finish(&mk_win_aes, (unsigned char*)msg + n * 16, m, (unsigned char*)out + n * 16);
}

void mk_win_aes_decrypt_msg(enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key, void const* msg, size_t msg_len, void* out)
{
	struct mk_win_aes_s mk_win_aes;
	int n;

	n = msg_len / 16;
	mk_assert(msg_len % 16 == 0);
	mk_win_aes_decrypt_init(&mk_win_aes, key_len, om, padding, iv, key);
	mk_win_aes_decrypt_blocks(&mk_win_aes, msg, n - 1, out);
	mk_win_aes_decrypt_finish(&mk_win_aes, (unsigned char*)msg + (n - 1) * 16, (unsigned char*)out + (n - 1) * 16);
}
