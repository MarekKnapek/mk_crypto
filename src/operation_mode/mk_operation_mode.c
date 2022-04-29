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
		(operation_mode) == mk_operation_mode_ecb || \
		0 \
	)


void mk_operation_mode_init(struct mk_operation_mode_s* operation_mode, enum mk_operation_mode_e type, enum mk_block_cipher_e block_cipher, unsigned char const* key)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(type);

	operation_mode->m_type = type;
	switch(type)
	{
		case mk_operation_mode_cbc: mk_operation_mode_init_cbc(&operation_mode->m_cbc, block_cipher, key); break;
		case mk_operation_mode_cfb: mk_operation_mode_init_cfb(&operation_mode->m_cfb, block_cipher, key); break;
		case mk_operation_mode_ecb: mk_operation_mode_init_ecb(&operation_mode->m_ecb, block_cipher, key); break;
	}
}

enum mk_block_cipher_e mk_operation_mode_get_block_cipher(struct mk_operation_mode_s* operation_mode)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(operation_mode->m_type);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_cbc: return mk_operation_mode_get_block_cipher_cbc(&operation_mode->m_cbc); break;
		case mk_operation_mode_cfb: return mk_operation_mode_get_block_cipher_cfb(&operation_mode->m_cfb); break;
		case mk_operation_mode_ecb: return mk_operation_mode_get_block_cipher_ecb(&operation_mode->m_ecb); break;
	}

	return 0;
}

void mk_operation_mode_set_param_iv(struct mk_operation_mode_s* operation_mode, unsigned char const* iv)
{
	mk_assert(operation_mode);
	mk_assert(operation_mode->m_type != mk_operation_mode_ecb);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_cbc: mk_operation_mode_set_param_iv_cbc(&operation_mode->m_cbc, iv); break;
		case mk_operation_mode_cfb: mk_operation_mode_set_param_iv_cfb(&operation_mode->m_cfb, iv); break;
	}
}

void mk_operation_mode_set_param_cfb_s_bytes(struct mk_operation_mode_s* operation_mode, int cfb_s_bytes)
{
	mk_assert(operation_mode);
	mk_assert(operation_mode->m_type == mk_operation_mode_cfb);


	mk_operation_mode_set_param_cfb_s_bytes_cfb(&operation_mode->m_cfb, cfb_s_bytes);
}

void mk_operation_mode_encrypt_blocks(struct mk_operation_mode_s* operation_mode, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(operation_mode->m_type);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_cbc: mk_operation_mode_encrypt_blocks_cbc(&operation_mode->m_cbc, blocks, input, output); break;
		case mk_operation_mode_cfb: mk_operation_mode_encrypt_blocks_cfb(&operation_mode->m_cfb, blocks, input, output); break;
		case mk_operation_mode_ecb: mk_operation_mode_encrypt_blocks_ecb(&operation_mode->m_ecb, blocks, input, output); break;
	}
}

void mk_operation_mode_decrypt_blocks(struct mk_operation_mode_s* operation_mode, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_assert(operation_mode);
	mk_assert_operation_mode(operation_mode->m_type);

	switch(operation_mode->m_type)
	{
		case mk_operation_mode_cbc: mk_operation_mode_decrypt_blocks_cbc(&operation_mode->m_cbc, blocks, input, output); break;
		case mk_operation_mode_cfb: mk_operation_mode_decrypt_blocks_cfb(&operation_mode->m_cfb, blocks, input, output); break;
		case mk_operation_mode_ecb: mk_operation_mode_decrypt_blocks_ecb(&operation_mode->m_ecb, blocks, input, output); break;
	}
}


#undef mk_assert_operation_mode
