#include "mk_operation_mode_ecb.h"

#include "../../utils/mk_assert.h"

#include <string.h> /* memcpy */


void mk_operation_mode_init_ecb(struct mk_operation_mode_ecb_s* ecb, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len)
{
	mk_assert(ecb);
	mk_assert(key);

	mk_operation_mode_init_base(&ecb->m_base, block_cipher, padding, key, key_len);
}

enum mk_block_cipher_e mk_operation_mode_get_block_cipher_ecb(struct mk_operation_mode_ecb_s* ecb)
{
	mk_assert(ecb);

	return mk_operation_mode_get_block_cipher_base(&ecb->m_base);
}

unsigned char const* mk_operation_mode_get_key_ecb(struct mk_operation_mode_ecb_s* ecb)
{
	mk_assert(ecb);

	return mk_operation_mode_get_key_base(&ecb->m_base);
}

void mk_operation_mode_set_param_iv_ecb(struct mk_operation_mode_ecb_s* ecb, void const* iv, int iv_len)
{
	mk_assert(0);

	(void)ecb;
	(void)iv;
	(void)iv_len;
}

void mk_operation_mode_encrypt_blocks_ecb(struct mk_operation_mode_ecb_s* ecb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	int i;

	mk_assert(ecb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(ecb->m_base.m_block_cipher);
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_encrypt_block(ecb->m_base.m_block_cipher, ecb->m_base.m_key, input, output);
		input += block_len;
		output += block_len;
	}
}

void mk_operation_mode_decrypt_blocks_ecb(struct mk_operation_mode_ecb_s* ecb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	int i;

	mk_assert(ecb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(ecb->m_base.m_block_cipher);
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_decrypt_block(ecb->m_base.m_block_cipher, ecb->m_base.m_key, input, output);
		input += block_len;
		output += block_len;
	}
}

int mk_operation_mode_encrypt_finish_ecb(struct mk_operation_mode_ecb_s* ecb, void const* input, int input_len, void* output, int output_len)
{
	int block_len;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int padded_len;

	mk_assert(ecb);
	mk_assert(input || input_len == 0);
	mk_assert(input_len >= 0 && input_len < mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher_base(&ecb->m_base)));
	mk_assert(output || output_len == 0);
	mk_assert(output_len >= 0 && output_len >= input_len);

	block_len = mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher_base(&ecb->m_base));
	memcpy(tmp, input, input_len);
	padded_len = mk_padding_add(ecb->m_padding, block_len, tmp, input_len);
	mk_assert(padded_len == 0 || padded_len == block_len);
	if(padded_len == 0)
	{
		return 0;
	}
	mk_assert(output_len >= block_len);
	mk_operation_mode_encrypt_blocks_ecb(ecb, 1, tmp, output);
	return block_len;
}
