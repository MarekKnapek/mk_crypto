#include "mk_operation_mode_ofb.h"

#include "mk_operation_mode_impl.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#include <string.h> /* memcpy */


static mk_inline void mk_operation_mode_process_blocks_ofb(struct mk_operation_mode_ofb_s* ofb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	int i;

	mk_assert(ofb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(ofb->m_base.m_block_cipher);
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_encrypt_block(ofb->m_base.m_block_cipher, ofb->m_base.m_key, ofb->m_iv, ofb->m_iv);
		mk_operation_mode_detail_xor(block_len, ofb->m_iv, input, output);
		input += block_len;
		output += block_len;
	}
}


void mk_operation_mode_init_ofb(struct mk_operation_mode_ofb_s* ofb, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len)
{
	mk_assert(ofb);
	mk_assert(key);

	mk_operation_mode_init_base(&ofb->m_base, block_cipher, padding, key, key_len);
}

enum mk_block_cipher_e mk_operation_mode_get_block_cipher_ofb(struct mk_operation_mode_ofb_s* ofb)
{
	mk_assert(ofb);

	return mk_operation_mode_get_block_cipher_base(&ofb->m_base);
}

unsigned char const* mk_operation_mode_get_key_ofb(struct mk_operation_mode_ofb_s* ofb)
{
	mk_assert(ofb);

	return mk_operation_mode_get_key_base(&ofb->m_base);
}

void mk_operation_mode_set_param_iv_ofb(struct mk_operation_mode_ofb_s* ofb, void const* iv, int iv_len)
{
	mk_assert(ofb);
	mk_assert(iv || iv_len == 0);
	mk_assert(iv_len >= 0);

	mk_assert(iv_len == mk_block_cipher_get_block_len(ofb->m_base.m_block_cipher));

	memcpy(ofb->m_iv, iv, iv_len);
}

void mk_operation_mode_encrypt_blocks_ofb(struct mk_operation_mode_ofb_s* ofb, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_operation_mode_process_blocks_ofb(ofb, blocks, input, output);
}

void mk_operation_mode_decrypt_blocks_ofb(struct mk_operation_mode_ofb_s* ofb, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_operation_mode_process_blocks_ofb(ofb, blocks, input, output);
}

int mk_operation_mode_encrypt_finish_ofb(struct mk_operation_mode_ofb_s* ofb, void const* input, int input_len, void* output, int output_len)
{
	int block_len;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int padded_len;

	mk_assert(ofb);
	mk_assert(input || input_len == 0);
	mk_assert(input_len >= 0 && input_len < mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher_base(&ofb->m_base)));
	mk_assert(output || output_len == 0);
	mk_assert(output_len >= 0 && output_len >= input_len);

	block_len = mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher_base(&ofb->m_base));
	memcpy(tmp, input, input_len);
	padded_len = mk_padding_add(ofb->m_padding, block_len, tmp, input_len);
	if(padded_len == 0)
	{
		return 0;
	}
	mk_operation_mode_encrypt_blocks_ofb(ofb, 1, tmp, tmp);
	mk_assert(output_len >= padded_len);
	memcpy(output, tmp, padded_len);
	return padded_len;
}
