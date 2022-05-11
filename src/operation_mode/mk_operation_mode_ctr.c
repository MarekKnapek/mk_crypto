#include "mk_operation_mode_ctr.h"

#include "mk_operation_mode_impl.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#include <string.h> /* memcpy */


static mk_inline void mk_operation_mode_ctr_detail_inc_little(int count, unsigned char const* src, unsigned char* dst)
{
	int i;

	mk_assert(count >= 0);
	mk_assert(src);
	mk_assert(dst);

	i = 0;
	do
	{
		dst[i] = src[i] + 1;
	}while(dst[i++] == 0 && i < count);
}

static mk_inline void mk_operation_mode_ctr_detail_inc_big(int count, unsigned char const* src, unsigned char* dst)
{
	int i;

	mk_assert(count >= 0);
	mk_assert(src);
	mk_assert(dst);

	i = count - 1;
	do
	{
		dst[i] = src[i] + 1;
	}while(dst[i--] == 0 && i >= 0);
}

static mk_inline void mk_operation_mode_ctr_detail_inc(int endian, int count, unsigned char const* src, unsigned char* dst)
{
	mk_assert(endian == 0 || endian == 1);
	
	if(endian == 0)
	{
		mk_operation_mode_ctr_detail_inc_little(count, src, dst);
	}
	else
	{
		mk_operation_mode_ctr_detail_inc_big(count, src, dst);
	}
}

static mk_inline void mk_operation_mode_process_blocks_ctr(struct mk_operation_mode_ctr_s* ctr, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int i;

	mk_assert(ctr);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(ctr->m_base.m_block_cipher);
	mk_assert(block_len <= mk_block_cipher_block_len_max);

	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_encrypt_block(ctr->m_base.m_block_cipher, ctr->m_base.m_key, ctr->m_iv, tmp);
		mk_operation_mode_detail_xor(block_len, tmp, input, output);
		mk_operation_mode_ctr_detail_inc(ctr->m_endian, block_len, ctr->m_iv, ctr->m_iv);
		input += block_len;
		output += block_len;
	}
}


void mk_operation_mode_init_ctr(struct mk_operation_mode_ctr_s* ctr, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len)
{
	mk_assert(ctr);
	mk_assert(key);

	mk_operation_mode_init_base(&ctr->m_base, block_cipher, padding, key, key_len);
	ctr->m_endian = 0;
}

enum mk_block_cipher_e mk_operation_mode_get_block_cipher_ctr(struct mk_operation_mode_ctr_s* ctr)
{
	mk_assert(ctr);

	return mk_operation_mode_get_block_cipher_base(&ctr->m_base);
}

unsigned char const* mk_operation_mode_get_key_ctr(struct mk_operation_mode_ctr_s* ctr)
{
	mk_assert(ctr);

	return mk_operation_mode_get_key_base(&ctr->m_base);
}

void mk_operation_mode_set_param_iv_ctr(struct mk_operation_mode_ctr_s* ctr, void const* iv, int iv_len)
{
	mk_assert(ctr);
	mk_assert(iv || iv_len == 0);
	mk_assert(iv_len >= 0);

	mk_assert(iv_len == mk_block_cipher_get_block_len(ctr->m_base.m_block_cipher));

	memcpy(ctr->m_iv, iv, iv_len);
}

void mk_operation_mode_set_param_ctr_endian_ctr(struct mk_operation_mode_ctr_s* ctr, int endian)
{
	mk_assert(ctr);
	mk_assert(endian == 0 || endian == 1);

	ctr->m_endian = endian;
}

void mk_operation_mode_encrypt_blocks_ctr(struct mk_operation_mode_ctr_s* ctr, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_operation_mode_process_blocks_ctr(ctr, blocks, input, output);
}

void mk_operation_mode_decrypt_blocks_ctr(struct mk_operation_mode_ctr_s* ctr, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_operation_mode_process_blocks_ctr(ctr, blocks, input, output);
}

int mk_operation_mode_encrypt_finish_ctr(struct mk_operation_mode_ctr_s* ctr, void const* input, int input_len, void* output, int output_len)
{
	int block_len;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int padded_len;

	mk_assert(ctr);
	mk_assert(input || input_len == 0);
	mk_assert(input_len >= 0 && input_len < mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher_base(&ctr->m_base)));
	mk_assert(output || output_len == 0);
	mk_assert(output_len >= 0 && output_len >= input_len);

	block_len = mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher_base(&ctr->m_base));
	memcpy(tmp, input, input_len);
	padded_len = mk_padding_add(ctr->m_padding, block_len, tmp, input_len);
	if(padded_len == 0)
	{
		return 0;
	}
	mk_operation_mode_encrypt_blocks_ctr(ctr, 1, tmp, tmp);
	mk_assert(output_len >= padded_len);
	memcpy(output, tmp, padded_len);
	return padded_len;
}
