#include "mk_win_cryptong.h"

#include "../utils/mk_assert.h"

#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc free NULL */

#include <windows.h>
#include <bcrypt.h>
#define STATUS_SUCCESS 0


struct mk_win_cryptong_s
{
	BCRYPT_ALG_HANDLE m_alg;
	BCRYPT_KEY_HANDLE m_key;
	unsigned char m_iv[16];
	int m_want_iv;
	void* m_key_obj;
};


mk_win_cryptong_h mk_win_cryptong_create(enum mk_win_cryptong_operation_mode_e operation_mode, enum mk_win_cryptong_algorithm_e algorithm, void const* iv, int iv_len, void const* key, int key_len)
{
	NTSTATUS alg_provider_opened;
	BCRYPT_ALG_HANDLE alg;
	PUCHAR chain_mode;
	int chain_mode_len;
	NTSTATUS set_chain_mode;
	NTSTATUS got_key_obj_len;
	DWORD key_obj_len;
	DWORD key_obj_len_len;
	void* key_obj;
	NTSTATUS got_key;
	BCRYPT_KEY_HANDLE hkey;
	struct mk_win_cryptong_s* win_cryptong;
	NTSTATUS key_destroyed;
	NTSTATUS alg_provider_closed;

	mk_assert
	(
		operation_mode == mk_win_cryptong_operation_mode_cbc ||
		operation_mode == mk_win_cryptong_operation_mode_ccm ||
		operation_mode == mk_win_cryptong_operation_mode_cfb ||
		operation_mode == mk_win_cryptong_operation_mode_ecb ||
		operation_mode == mk_win_cryptong_operation_mode_gcm ||
		0
	);
	mk_assert
	(
		algorithm == mk_win_cryptong_algorithm_aes128 ||
		algorithm == mk_win_cryptong_algorithm_aes192 ||
		algorithm == mk_win_cryptong_algorithm_aes256 ||
		0
	);
	mk_assert(key);

	alg_provider_opened = BCryptOpenAlgorithmProvider(&alg, BCRYPT_AES_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
	if(!(alg_provider_opened == STATUS_SUCCESS))
	{
		goto cleanup_null;
	}

	switch(operation_mode)
	{
		case mk_win_cryptong_operation_mode_cbc: chain_mode = (PUCHAR)BCRYPT_CHAIN_MODE_CBC; chain_mode_len = sizeof(BCRYPT_CHAIN_MODE_CBC); break;
		case mk_win_cryptong_operation_mode_ccm: chain_mode = (PUCHAR)BCRYPT_CHAIN_MODE_CCM; chain_mode_len = sizeof(BCRYPT_CHAIN_MODE_CCM); break;
		case mk_win_cryptong_operation_mode_cfb: chain_mode = (PUCHAR)BCRYPT_CHAIN_MODE_CFB; chain_mode_len = sizeof(BCRYPT_CHAIN_MODE_CFB); break;
		case mk_win_cryptong_operation_mode_ecb: chain_mode = (PUCHAR)BCRYPT_CHAIN_MODE_ECB; chain_mode_len = sizeof(BCRYPT_CHAIN_MODE_ECB); break;
		case mk_win_cryptong_operation_mode_gcm: chain_mode = (PUCHAR)BCRYPT_CHAIN_MODE_GCM; chain_mode_len = sizeof(BCRYPT_CHAIN_MODE_GCM); break;
		default: mk_assert((chain_mode = NULL, chain_mode_len = 0, 0)); break;
	}
	set_chain_mode = BCryptSetProperty(alg, BCRYPT_CHAINING_MODE, chain_mode, chain_mode_len, 0);
	if(!(set_chain_mode == STATUS_SUCCESS))
	{
		goto cleanup_provider;
	}

	got_key_obj_len = BCryptGetProperty(alg, BCRYPT_OBJECT_LENGTH, (PUCHAR)&key_obj_len, sizeof(key_obj_len), &key_obj_len_len, 0);
	if(!(got_key_obj_len == STATUS_SUCCESS))
	{
		goto cleanup_provider;
	}
	if(!(key_obj_len_len == sizeof(key_obj_len)))
	{
		goto cleanup_provider;
	}

	key_obj = malloc(key_obj_len);
	if(!key_obj)
	{
		goto cleanup_provider;
	}

	switch(algorithm)
	{
		case mk_win_cryptong_algorithm_aes128: mk_assert(key_len == 16); break;
		case mk_win_cryptong_algorithm_aes192: mk_assert(key_len == 24); break;
		case mk_win_cryptong_algorithm_aes256: mk_assert(key_len == 32); break;
	}
	got_key = BCryptGenerateSymmetricKey(alg, &hkey, (PUCHAR)key_obj, key_obj_len, (PUCHAR)key, key_len, 0);
	if(!(got_key == STATUS_SUCCESS))
	{
		goto cleanup_key_obj;
	}

	win_cryptong = (struct mk_win_cryptong_s*)malloc(sizeof (struct mk_win_cryptong_s));
	if(!win_cryptong)
	{
		goto cleanup_key;
	}

	win_cryptong->m_alg = alg;
	win_cryptong->m_key = hkey;
	if(operation_mode == mk_win_cryptong_operation_mode_ecb)
	{
		mk_assert(iv_len == 0);
		win_cryptong->m_want_iv = 0;
	}
	else
	{
		mk_assert(iv_len == 16);
		memcpy(win_cryptong->m_iv, iv, iv_len);
		win_cryptong->m_want_iv = 1;
	}
	win_cryptong->m_key_obj = key_obj;
	return (mk_win_cryptong_h)win_cryptong;

cleanup_key:
	key_destroyed = BCryptDestroyKey(hkey);
	mk_assert(key_destroyed == STATUS_SUCCESS);
cleanup_key_obj:
	free(key_obj);
cleanup_provider:
	alg_provider_closed = BCryptCloseAlgorithmProvider(alg, 0);
	mk_assert(alg_provider_closed == STATUS_SUCCESS);
cleanup_null:
	return NULL;
}

void mk_win_cryptong_set_param(mk_win_cryptong_h win_cryptong_h, enum mk_win_cryptong_param_e param, void const* value)
{
	struct mk_win_cryptong_s* win_cryptong;
	DWORD dw_value;
	PUCHAR p_value;
	DWORD value_len;
	NTSTATUS st;

	mk_assert(win_cryptong_h);

	mk_assert
	(
		param == mk_win_cryptong_param_cfb_s_bytes ||
		0
	);

	win_cryptong = (struct mk_win_cryptong_s*)win_cryptong_h;
	switch(param)
	{
		case mk_win_cryptong_param_cfb_s_bytes:
			dw_value = *(int const*)value;
			p_value = (PUCHAR)&dw_value;
			value_len = sizeof(dw_value);
			st = BCryptSetProperty(win_cryptong->m_key, BCRYPT_MESSAGE_BLOCK_LENGTH, p_value, value_len, 0);
			mk_assert(st == STATUS_SUCCESS);
		break;
	}
}

void mk_win_cryptong_encrypt(mk_win_cryptong_h win_cryptong_h, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes)
{
	struct mk_win_cryptong_s* win_cryptong;
	PUCHAR iv;
	ULONG iv_len;
	ULONG out_len;
	ULONG out_len_real;
	ULONG flags;
	NTSTATUS encrypted;

	mk_assert(win_cryptong_h);

	win_cryptong = (struct mk_win_cryptong_s*)win_cryptong_h;

	iv = win_cryptong->m_want_iv == 0 ? (PUCHAR)NULL : (PUCHAR)win_cryptong->m_iv;
	iv_len = win_cryptong->m_want_iv == 0 ? (ULONG)0 : (ULONG)16;
	out_len = output_len_bytes;
	flags = final == 0 ? (ULONG)0 : (ULONG)BCRYPT_BLOCK_PADDING;
	encrypted = BCryptEncrypt(win_cryptong->m_key, (PUCHAR)input, input_len_bytes, NULL, iv, iv_len, (PUCHAR)output, out_len, &out_len_real, flags);
	mk_assert(encrypted == STATUS_SUCCESS);
	mk_assert(out_len == out_len_real);
}

int mk_win_cryptong_decrypt(mk_win_cryptong_h win_cryptong_h, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes)
{
	struct mk_win_cryptong_s* win_cryptong;
	PUCHAR iv;
	ULONG iv_len;
	ULONG out_len;
	ULONG out_len_real;
	ULONG flags;
	NTSTATUS encrypted;

	mk_assert(win_cryptong_h);

	win_cryptong = (struct mk_win_cryptong_s*)win_cryptong_h;

	iv = win_cryptong->m_want_iv == 0 ? (PUCHAR)NULL : (PUCHAR)win_cryptong->m_iv;
	iv_len = win_cryptong->m_want_iv == 0 ? (ULONG)0 : (ULONG)16;
	out_len = output_len_bytes;
	flags = final == 0 ? (ULONG)0 : (ULONG)BCRYPT_BLOCK_PADDING;
	encrypted = BCryptDecrypt(win_cryptong->m_key, (PUCHAR)input, input_len_bytes, NULL, iv, iv_len, (PUCHAR)output, out_len, &out_len_real, flags);
	mk_assert(encrypted == STATUS_SUCCESS);
	return (int)out_len_real;
}

void mk_win_cryptong_destroy(mk_win_cryptong_h win_cryptong_h)
{
	struct mk_win_cryptong_s* win_cryptong;
	NTSTATUS alg_provider_closed;
	NTSTATUS key_destroyed;

	mk_assert(win_cryptong_h);
	
	win_cryptong = (struct mk_win_cryptong_s*)win_cryptong_h;

	key_destroyed = BCryptDestroyKey(win_cryptong->m_key);
	mk_assert(key_destroyed == STATUS_SUCCESS);
	alg_provider_closed = BCryptCloseAlgorithmProvider(win_cryptong->m_alg, 0);
	mk_assert(alg_provider_closed == STATUS_SUCCESS);
	free(win_cryptong->m_key_obj);

	free(win_cryptong);
}


#undef mk_jumbo
