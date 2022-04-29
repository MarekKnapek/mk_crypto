#include "mk_operation_mode_ecb.h"

#include "../../utils/mk_assert.h"


void mk_operation_mode_init_ecb(struct mk_operation_mode_ecb_s* ecb, enum mk_block_cipher_e block_cipher, unsigned char const* key)
{
	mk_assert(ecb);
	mk_assert(key);

	mk_operation_mode_init_base(&ecb->m_base, block_cipher, key);
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
