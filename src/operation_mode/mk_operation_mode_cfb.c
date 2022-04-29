#include "mk_operation_mode_cfb.h"

#include "mk_operation_mode_impl.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcpy */


static mk_inline void mk_operation_mode_encrypt_blocks_cfb_s1(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int i;
	int j;
	int k;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	mk_assert(block_len <= mk_block_cipher_block_len_max);
	
	for(i = 0; i != blocks; ++i)
	{
		for(j = 0; j != block_len; ++j)
		{
			mk_block_cipher_encrypt_block(cfb->m_base.m_block_cipher, cfb->m_base.m_key, cfb->m_iv, tmp);
			output[j] = tmp[0] ^ input[j];
			for(k = 0; k != block_len - 1; ++k)
			{
				cfb->m_iv[k] = cfb->m_iv[k + 1];
			}
			cfb->m_iv[block_len - 1] = output[j];
		}
		input += block_len;
		output += block_len;
	}
}

static mk_inline void mk_operation_mode_decrypt_blocks_cfb_s1(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	enum mk_crypt_block_len_e block_len;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int i;
	int j;
	int k;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	mk_assert(block_len <= mk_block_cipher_block_len_max);
	
	for(i = 0; i != blocks; ++i)
	{
		for(j = 0; j != block_len; ++j)
		{
			mk_block_cipher_encrypt_block(cfb->m_base.m_block_cipher, cfb->m_base.m_key, cfb->m_iv, tmp);
			output[j] = tmp[0] ^ input[j];
			for(k = 0; k != block_len - 1; ++k)
			{
				cfb->m_iv[k] = cfb->m_iv[k + 1];
			}
			cfb->m_iv[block_len - 1] = input[j];
		}
		input += block_len;
		output += block_len;
	}
}

static mk_inline void mk_operation_mode_encrypt_blocks_cfb_sfull(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* ivp;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int i;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	mk_assert(block_len <= mk_block_cipher_block_len_max);

	ivp =  cfb->m_iv;
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_encrypt_block(cfb->m_base.m_block_cipher, cfb->m_base.m_key, ivp, tmp);
		mk_operation_mode_detail_xor(block_len, tmp, input, output);
		ivp = output;
		input += block_len;
		output += block_len;
	}
	memcpy(cfb->m_iv, ivp, block_len);
}

static mk_inline void mk_operation_mode_decrypt_blocks_cfb_sfull(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* ivp;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int i;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	mk_assert(block_len <= mk_block_cipher_block_len_max);

	ivp =  cfb->m_iv;
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_encrypt_block(cfb->m_base.m_block_cipher, cfb->m_base.m_key, ivp, tmp);
		mk_operation_mode_detail_xor(block_len, tmp, input, output);
		ivp = input;
		input += block_len;
		output += block_len;
	}
	memcpy(cfb->m_iv, ivp, block_len);
}


void mk_operation_mode_init_cfb(struct mk_operation_mode_cfb_s* cfb, enum mk_block_cipher_e block_cipher, unsigned char const* key)
{
	mk_assert(cfb);
	mk_assert(key);

	mk_operation_mode_init_base(&cfb->m_base, block_cipher, key);
	cfb->m_s_bytes = 1;
}

enum mk_block_cipher_e mk_operation_mode_get_block_cipher_cfb(struct mk_operation_mode_cfb_s* cfb)
{
	mk_assert(cfb);

	return mk_operation_mode_get_block_cipher_base(&cfb->m_base);
}

unsigned char const* mk_operation_mode_get_key_cfb(struct mk_operation_mode_cfb_s* cfb)
{
	mk_assert(cfb);

	return mk_operation_mode_get_key_base(&cfb->m_base);
}

void mk_operation_mode_set_param_iv_cfb(struct mk_operation_mode_cfb_s* cfb, unsigned char const* iv)
{
	mk_assert(cfb);
	mk_assert(iv);

	memcpy(cfb->m_iv, iv, mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher));
}

void mk_operation_mode_set_param_cfb_s_bytes_cfb(struct mk_operation_mode_cfb_s* cfb, int cfb_s_bytes)
{
	mk_assert(cfb);

	cfb->m_s_bytes = cfb_s_bytes;
}

void mk_operation_mode_encrypt_blocks_cfb(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	mk_assert(cfb->m_s_bytes == 1 || cfb->m_s_bytes == block_len);
	
	if(cfb->m_s_bytes == 1)
	{
		mk_operation_mode_encrypt_blocks_cfb_s1(cfb, blocks, input, output);
	}
	else
	{
		mk_operation_mode_encrypt_blocks_cfb_sfull(cfb, blocks, input, output);
	}
}

void mk_operation_mode_decrypt_blocks_cfb(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	mk_assert(cfb->m_s_bytes == 1 || cfb->m_s_bytes == 8 || cfb->m_s_bytes == block_len);
	
	if(cfb->m_s_bytes == 1)
	{
		mk_operation_mode_decrypt_blocks_cfb_s1(cfb, blocks, input, output);
	}
	else
	{
		mk_operation_mode_decrypt_blocks_cfb_sfull(cfb, blocks, input, output);
	}
}
