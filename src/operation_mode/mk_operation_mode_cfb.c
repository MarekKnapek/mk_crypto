#include "mk_operation_mode_cfb.h"

#include "mk_operation_mode_impl.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#include <string.h> /* memcpy */


static mk_inline void mk_operation_mode_encrypt_blocks_cfb_s1(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	int i;
	int j;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int k;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	for(i = 0; i != blocks; ++i)
	{
		for(j = 0; j != block_len; ++j)
		{
			mk_block_cipher_encrypt_block(cfb->m_base.m_block_cipher, cfb->m_base.m_key, cfb->m_iv, tmp);
			output[0] = tmp[0] ^ input[0];
			for(k = 0; k != block_len - 1; ++k)
			{
				cfb->m_iv[k] = cfb->m_iv[k + 1];
			}
			cfb->m_iv[k] = output[0];
			++input;
			++output;
		}
	}
}

static mk_inline void mk_operation_mode_decrypt_blocks_cfb_s1(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	int i;
	int j;
	unsigned char tmp[mk_block_cipher_block_len_max];
	unsigned char in;
	int k;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	for(i = 0; i != blocks; ++i)
	{
		for(j = 0; j != block_len; ++j)
		{
			mk_block_cipher_encrypt_block(cfb->m_base.m_block_cipher, cfb->m_base.m_key, cfb->m_iv, tmp);
			in = input[0];
			output[0] = tmp[0] ^ in;
			for(k = 0; k != block_len - 1; ++k)
			{
				cfb->m_iv[k] = cfb->m_iv[k + 1];
			}
			cfb->m_iv[k] = in;
			++input;
			++output;
		}
	}
}

static mk_inline void mk_operation_mode_encrypt_blocks_cfb_sfull_overlap0(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* iv;
	int i;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	iv =  cfb->m_iv;
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_encrypt_block(cfb->m_base.m_block_cipher, cfb->m_base.m_key, iv, output);
		mk_operation_mode_detail_xor(block_len, output, input, output);
		iv = output;
		input += block_len;
		output += block_len;
	}
	memcpy(cfb->m_iv, iv, block_len);
}

static mk_inline void mk_operation_mode_encrypt_blocks_cfb_sfull_overlap1(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* iv;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int i;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	iv =  cfb->m_iv;
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_encrypt_block(cfb->m_base.m_block_cipher, cfb->m_base.m_key, iv, tmp);
		mk_operation_mode_detail_xor(block_len, tmp, input, output);
		iv = output;
		input += block_len;
		output += block_len;
	}
	memcpy(cfb->m_iv, iv, block_len);
}

static mk_inline void mk_operation_mode_encrypt_blocks_cfb_sfull(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	int overlapping;

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	overlapping = !(output >= input + blocks * block_len || input >= output + blocks * block_len);
	if(overlapping)
	{
		mk_operation_mode_encrypt_blocks_cfb_sfull_overlap1(cfb, blocks, input, output);
	}
	else
	{
		mk_operation_mode_encrypt_blocks_cfb_sfull_overlap0(cfb, blocks, input, output);
	}
}

static mk_inline void mk_operation_mode_decrypt_blocks_cfb_sfull_overlap0(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* iv;
	int i;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	iv = cfb->m_iv;
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_encrypt_block(cfb->m_base.m_block_cipher, cfb->m_base.m_key, iv, output);
		mk_operation_mode_detail_xor(block_len, output, input, output);
		iv = input;
		input += block_len;
		output += block_len;
	}
	memcpy(cfb->m_iv, iv, block_len);
}

static mk_inline void mk_operation_mode_decrypt_blocks_cfb_sfull_overlap1(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int i;

	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_encrypt_block(cfb->m_base.m_block_cipher, cfb->m_base.m_key, cfb->m_iv, tmp);
		memcpy(cfb->m_iv, input, block_len);
		mk_operation_mode_detail_xor(block_len, tmp, input, output);
		input += block_len;
		output += block_len;
	}
}

static mk_inline void mk_operation_mode_decrypt_blocks_cfb_sfull(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	int overlapping;

	block_len = mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher);
	overlapping = !(output >= input + blocks * block_len || input >= output + blocks * block_len);
	if(overlapping)
	{
		mk_operation_mode_decrypt_blocks_cfb_sfull_overlap1(cfb, blocks, input, output);
	}
	else
	{
		mk_operation_mode_decrypt_blocks_cfb_sfull_overlap0(cfb, blocks, input, output);
	}
}


void mk_operation_mode_init_cfb(struct mk_operation_mode_cfb_s* cfb, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len)
{
	mk_assert(cfb);
	mk_assert(key);

	mk_operation_mode_init_base(&cfb->m_base, block_cipher, padding, key, key_len);
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

void mk_operation_mode_set_param_iv_cfb(struct mk_operation_mode_cfb_s* cfb, void const* iv, int iv_len)
{
	mk_assert(cfb);
	mk_assert(iv || iv_len == 0);
	mk_assert(iv_len >= 0);

	mk_assert(iv_len == mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher));

	memcpy(cfb->m_iv, iv, iv_len);
}

void mk_operation_mode_set_param_cfb_s_bytes_cfb(struct mk_operation_mode_cfb_s* cfb, int cfb_s_bytes)
{
	mk_assert(cfb);
	mk_assert(cfb_s_bytes == 1 || cfb_s_bytes == mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher));

	cfb->m_s_bytes = cfb_s_bytes;
}

void mk_operation_mode_encrypt_blocks_cfb(struct mk_operation_mode_cfb_s* cfb, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	mk_assert(cfb->m_s_bytes == 1 || cfb->m_s_bytes == mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher));
	
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
	mk_assert(cfb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	mk_assert(cfb->m_s_bytes == 1 || cfb->m_s_bytes == mk_block_cipher_get_block_len(cfb->m_base.m_block_cipher));

	if(cfb->m_s_bytes == 1)
	{
		mk_operation_mode_decrypt_blocks_cfb_s1(cfb, blocks, input, output);
	}
	else
	{
		mk_operation_mode_decrypt_blocks_cfb_sfull(cfb, blocks, input, output);
	}
}

int mk_operation_mode_encrypt_finish_cfb(struct mk_operation_mode_cfb_s* cfb, void const* input, int input_len, void* output, int output_len)
{
	int block_len;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int padded_len;

	mk_assert(cfb);
	mk_assert(input || input_len == 0);
	mk_assert(input_len >= 0 && input_len < mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher_base(&cfb->m_base)));
	mk_assert(output || output_len == 0);
	mk_assert(output_len >= 0 && output_len >= input_len);

	block_len = mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher_base(&cfb->m_base));
	memcpy(tmp, input, input_len);
	padded_len = mk_padding_add(cfb->m_padding, block_len, tmp, input_len);
	if(padded_len == 0)
	{
		return 0;
	}
	mk_operation_mode_encrypt_blocks_cfb(cfb, 1, tmp, tmp);
	mk_assert(output_len >= padded_len);
	memcpy(output, tmp, padded_len);
	return padded_len;
}
