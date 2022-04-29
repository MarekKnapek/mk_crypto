#include "mk_operation_mode_ofb.h"

#include "mk_operation_mode_impl.h"
#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#include <string.h> /* memcpy */


static mk_inline void mk_operation_mode_process_blocks_ofb(struct mk_operation_mode_ofb_s* ofb, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* ivp;
	unsigned char tmp[mk_block_cipher_block_len_max];
	int i;

	mk_assert(ofb);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(ofb->m_base.m_block_cipher);
	mk_assert(block_len <= mk_block_cipher_block_len_max);

	ivp = ofb->m_iv;
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_encrypt_block(ofb->m_base.m_block_cipher, ofb->m_base.m_key, ivp, tmp);
		mk_operation_mode_detail_xor(block_len, tmp, input, output);
		ivp = tmp;
		input += block_len;
		output += block_len;
	}
	memcpy(ofb->m_iv, ivp, block_len);
}


void mk_operation_mode_init_ofb(struct mk_operation_mode_ofb_s* ofb, enum mk_block_cipher_e block_cipher, unsigned char const* key)
{
	mk_assert(ofb);
	mk_assert(key);

	mk_operation_mode_init_base(&ofb->m_base, block_cipher, key);
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

void mk_operation_mode_set_param_iv_ofb(struct mk_operation_mode_ofb_s* ofb, unsigned char const* iv)
{
	mk_assert(ofb);
	mk_assert(iv);

	memcpy(ofb->m_iv, iv, mk_block_cipher_get_block_len(ofb->m_base.m_block_cipher));
}

void mk_operation_mode_encrypt_blocks_ofb(struct mk_operation_mode_ofb_s* ofb, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_operation_mode_process_blocks_ofb(ofb, blocks, input, output);
}

void mk_operation_mode_decrypt_blocks_ofb(struct mk_operation_mode_ofb_s* ofb, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_operation_mode_process_blocks_ofb(ofb, blocks, input, output);
}
