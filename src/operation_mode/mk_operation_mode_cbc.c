#include "mk_operation_mode_cbc.h"

#include "mk_operation_mode_impl.h"
#include "../../utils/mk_assert.h"

#include <string.h> /* memcpy */


void mk_operation_mode_init_cbc(struct mk_operation_mode_cbc_s* cbc, enum mk_block_cipher_e block_cipher, unsigned char const* key)
{
	mk_assert(cbc);
	mk_assert(key);

	mk_operation_mode_init_base(&cbc->m_base, block_cipher, key);
}

enum mk_block_cipher_e mk_operation_mode_get_block_cipher_cbc(struct mk_operation_mode_cbc_s* cbc)
{
	mk_assert(cbc);

	return mk_operation_mode_get_block_cipher_base(&cbc->m_base);
}

unsigned char const* mk_operation_mode_get_key_cbc(struct mk_operation_mode_cbc_s* cbc)
{
	mk_assert(cbc);

	return mk_operation_mode_get_key_base(&cbc->m_base);
}

void mk_operation_mode_set_param_iv_cbc(struct mk_operation_mode_cbc_s* cbc, unsigned char const* iv)
{
	mk_assert(cbc);
	mk_assert(iv);

	memcpy(cbc->m_iv, iv, mk_block_cipher_get_block_len(cbc->m_base.m_block_cipher));
}

void mk_operation_mode_encrypt_blocks_cbc(struct mk_operation_mode_cbc_s* cbc, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* ivp;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int i;

	mk_assert(cbc);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cbc->m_base.m_block_cipher);
	mk_assert(block_len <= mk_block_cipher_block_len_max);

	ivp = cbc->m_iv;
	for(i = 0; i != blocks; ++i)
	{
		mk_operation_mode_detail_xor(block_len, input, ivp, tmp);
		mk_block_cipher_encrypt_block(cbc->m_base.m_block_cipher, cbc->m_base.m_key, tmp, output);
		ivp = output;
		input += block_len;
		output += block_len;
	}
	memcpy(cbc->m_iv, ivp, block_len);
}

void mk_operation_mode_decrypt_blocks_cbc(struct mk_operation_mode_cbc_s* cbc, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* ivp;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int i;

	mk_assert(cbc);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cbc->m_base.m_block_cipher);
	mk_assert(block_len <= mk_block_cipher_block_len_max);
	
	ivp = cbc->m_iv;
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_decrypt_block(cbc->m_base.m_block_cipher, cbc->m_base.m_key, input, tmp);
		mk_operation_mode_detail_xor(block_len, tmp, ivp, output);
		ivp = input;
		input += block_len;
		output += block_len;
	}
	memcpy(cbc->m_iv, ivp, block_len);
}
