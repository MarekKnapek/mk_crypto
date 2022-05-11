#include "mk_operation_mode.h"

#include "mk_operation_mode_cbc.h"
#include "mk_operation_mode_cfb.h"
#include "mk_operation_mode_ecb.h"

#include "../../utils/mk_assert.h"

#include <string.h> /* memcpy */


#define mk_assert_operation_mode(operation_mode) mk_assert \
	( \
		(operation_mode) == mk_operation_mode_cbc || \
		(operation_mode) == mk_operation_mode_cfb || \
		(operation_mode) == mk_operation_mode_ctr || \
		(operation_mode) == mk_operation_mode_ecb || \
		(operation_mode) == mk_operation_mode_gcm || \
		(operation_mode) == mk_operation_mode_ofb || \
		0 \
	)


void mk_operation_mode_init(struct mk_operation_mode_s* operation_mode, enum mk_operation_mode_e type, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(type);

	operation_mode->m_type = type;
	switch(type)
	{
		case mk_operation_mode_cbc: mk_operation_mode_init_cbc(&operation_mode->m_mode.m_cbc, block_cipher, padding, key, key_len); break;
		case mk_operation_mode_cfb: mk_operation_mode_init_cfb(&operation_mode->m_mode.m_cfb, block_cipher, padding, key, key_len); break;
		case mk_operation_mode_ctr: mk_operation_mode_init_ctr(&operation_mode->m_mode.m_ctr, block_cipher, padding, key, key_len); break;
		case mk_operation_mode_ecb: mk_operation_mode_init_ecb(&operation_mode->m_mode.m_ecb, block_cipher, padding, key, key_len); break;
		case mk_operation_mode_gcm: mk_operation_mode_init_gcm(&operation_mode->m_mode.m_gcm, block_cipher, padding, key, key_len); break;
		case mk_operation_mode_ofb: mk_operation_mode_init_ofb(&operation_mode->m_mode.m_ofb, block_cipher, padding, key, key_len); break;
	}
}

enum mk_block_cipher_e mk_operation_mode_get_block_cipher(struct mk_operation_mode_s* operation_mode)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(operation_mode->m_type);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_cbc: return mk_operation_mode_get_block_cipher_cbc(&operation_mode->m_mode.m_cbc); break;
		case mk_operation_mode_cfb: return mk_operation_mode_get_block_cipher_cfb(&operation_mode->m_mode.m_cfb); break;
		case mk_operation_mode_ctr: return mk_operation_mode_get_block_cipher_ctr(&operation_mode->m_mode.m_ctr); break;
		case mk_operation_mode_ecb: return mk_operation_mode_get_block_cipher_ecb(&operation_mode->m_mode.m_ecb); break;
		case mk_operation_mode_gcm: return mk_operation_mode_get_block_cipher_gcm(&operation_mode->m_mode.m_gcm); break;
		case mk_operation_mode_ofb: return mk_operation_mode_get_block_cipher_ofb(&operation_mode->m_mode.m_ofb); break;
	}

	return 0;
}

void mk_operation_mode_set_param_iv(struct mk_operation_mode_s* operation_mode, void const* iv, int iv_len)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(operation_mode->m_type);
	mk_assert(iv || iv_len == 0);
	mk_assert(iv_len >= 0);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_cbc: mk_operation_mode_set_param_iv_cbc(&operation_mode->m_mode.m_cbc, iv, iv_len); break;
		case mk_operation_mode_cfb: mk_operation_mode_set_param_iv_cfb(&operation_mode->m_mode.m_cfb, iv, iv_len); break;
		case mk_operation_mode_ctr: mk_operation_mode_set_param_iv_ctr(&operation_mode->m_mode.m_ctr, iv, iv_len); break;
		case mk_operation_mode_ecb: mk_operation_mode_set_param_iv_ecb(&operation_mode->m_mode.m_ecb, iv, iv_len); break;
		case mk_operation_mode_gcm: mk_operation_mode_set_param_iv_gcm(&operation_mode->m_mode.m_gcm, iv, iv_len); break;
		case mk_operation_mode_ofb: mk_operation_mode_set_param_iv_ofb(&operation_mode->m_mode.m_ofb, iv, iv_len); break;
	}
}

void mk_operation_mode_set_param_aad_append(struct mk_operation_mode_s* operation_mode, void const* aad, int aad_len)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(operation_mode->m_type);
	mk_assert(aad || aad_len == 0);
	mk_assert(aad_len >= 0);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_gcm: mk_operation_mode_set_param_aad_append_gcm(&operation_mode->m_mode.m_gcm, aad, aad_len); break;
		default: mk_assert(0); break;
	}
}

void mk_operation_mode_set_param_aad_finish(struct mk_operation_mode_s* operation_mode, void const* aad, int aad_len)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(operation_mode->m_type);
	mk_assert(aad || aad_len == 0);
	mk_assert(aad_len >= 0);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_gcm: mk_operation_mode_set_param_aad_finish_gcm(&operation_mode->m_mode.m_gcm, aad, aad_len); break;
		default: mk_assert(0); break;
	}
}

void mk_operation_mode_set_param_cfb_s_bytes(struct mk_operation_mode_s* operation_mode, int cfb_s_bytes)
{
	mk_assert(operation_mode);
	mk_assert(operation_mode->m_type == mk_operation_mode_cfb);

	mk_operation_mode_set_param_cfb_s_bytes_cfb(&operation_mode->m_mode.m_cfb, cfb_s_bytes);
}

void mk_operation_mode_set_param_ctr_endian(struct mk_operation_mode_s* operation_mode, int ctr_endian)
{
	mk_assert(operation_mode);
	mk_assert(operation_mode->m_type == mk_operation_mode_ctr);

	mk_operation_mode_set_param_ctr_endian_ctr(&operation_mode->m_mode.m_ctr, ctr_endian);
}

void mk_operation_mode_encrypt_blocks(struct mk_operation_mode_s* operation_mode, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(operation_mode->m_type);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_cbc: mk_operation_mode_encrypt_blocks_cbc(&operation_mode->m_mode.m_cbc, blocks, input, output); break;
		case mk_operation_mode_cfb: mk_operation_mode_encrypt_blocks_cfb(&operation_mode->m_mode.m_cfb, blocks, input, output); break;
		case mk_operation_mode_ctr: mk_operation_mode_encrypt_blocks_ctr(&operation_mode->m_mode.m_ctr, blocks, input, output); break;
		case mk_operation_mode_ecb: mk_operation_mode_encrypt_blocks_ecb(&operation_mode->m_mode.m_ecb, blocks, input, output); break;
		case mk_operation_mode_gcm: mk_operation_mode_encrypt_blocks_gcm(&operation_mode->m_mode.m_gcm, blocks, input, output); break;
		case mk_operation_mode_ofb: mk_operation_mode_encrypt_blocks_ofb(&operation_mode->m_mode.m_ofb, blocks, input, output); break;
	}
}

void mk_operation_mode_decrypt_blocks(struct mk_operation_mode_s* operation_mode, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(operation_mode->m_type);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_cbc: mk_operation_mode_decrypt_blocks_cbc(&operation_mode->m_mode.m_cbc, blocks, input, output); break;
		case mk_operation_mode_cfb: mk_operation_mode_decrypt_blocks_cfb(&operation_mode->m_mode.m_cfb, blocks, input, output); break;
		case mk_operation_mode_ctr: mk_operation_mode_decrypt_blocks_ctr(&operation_mode->m_mode.m_ctr, blocks, input, output); break;
		case mk_operation_mode_ecb: mk_operation_mode_decrypt_blocks_ecb(&operation_mode->m_mode.m_ecb, blocks, input, output); break;
		case mk_operation_mode_gcm: mk_operation_mode_decrypt_blocks_gcm(&operation_mode->m_mode.m_gcm, blocks, input, output); break;
		case mk_operation_mode_ofb: mk_operation_mode_decrypt_blocks_ofb(&operation_mode->m_mode.m_ofb, blocks, input, output); break;
	}
}

int mk_operation_mode_encrypt_finish(struct mk_operation_mode_s* operation_mode, void const* input, int input_len, void* output, int output_len)
{
	int ret;

	mk_assert(operation_mode);
	mk_assert_operation_mode(operation_mode->m_type);
	mk_assert(input || input_len == 0);
	mk_assert(input_len >= 0 && input_len < mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher(operation_mode)));
	mk_assert(output || output_len == 0);
	mk_assert(output_len >= 0 && output_len >= input_len);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_cbc: ret = mk_operation_mode_encrypt_finish_cbc(&operation_mode->m_mode.m_cbc, input, input_len, output, output_len); break;
		case mk_operation_mode_cfb: ret = mk_operation_mode_encrypt_finish_cfb(&operation_mode->m_mode.m_cfb, input, input_len, output, output_len); break;
		case mk_operation_mode_ctr: ret = mk_operation_mode_encrypt_finish_ctr(&operation_mode->m_mode.m_ctr, input, input_len, output, output_len); break;
		case mk_operation_mode_ecb: ret = mk_operation_mode_encrypt_finish_ecb(&operation_mode->m_mode.m_ecb, input, input_len, output, output_len); break;
		case mk_operation_mode_gcm: ret = mk_operation_mode_encrypt_finish_gcm(&operation_mode->m_mode.m_gcm, input, input_len, output, output_len); break;
		case mk_operation_mode_ofb: ret = mk_operation_mode_encrypt_finish_ofb(&operation_mode->m_mode.m_ofb, input, input_len, output, output_len); break;
		default: mk_assert((ret = 0, 0)); break;
	}
	return ret;
}


#undef mk_assert_operation_mode
