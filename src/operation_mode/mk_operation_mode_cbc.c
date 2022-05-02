#include "mk_operation_mode_cbc.h"

#include "mk_operation_mode_impl.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#include <string.h> /* memcpy */


static mk_inline void mk_operation_mode_cbc_swap_ptr(unsigned char const** a, unsigned char const** b)
{
	unsigned char const* t;

	mk_assert(a);
	mk_assert(b);

	t = *a;
	*a = *b;
	*b = t;
}

static mk_inline void mk_operation_mode_encrypt_blocks_cbc_overlap0(struct mk_operation_mode_cbc_s* cbc, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* iv;
	int i;

	mk_assert(cbc);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cbc->m_base.m_block_cipher);
	iv = cbc->m_iv;
	for(i = 0; i != blocks; ++i)
	{
		mk_operation_mode_detail_xor(block_len, iv, input, cbc->m_iv);
		mk_block_cipher_encrypt_block(cbc->m_base.m_block_cipher, cbc->m_base.m_key, cbc->m_iv, output);
		iv = output;
		input += block_len;
		output += block_len;
	}
	memcpy(cbc->m_iv, iv, block_len);
}

static mk_inline void mk_operation_mode_encrypt_blocks_cbc_overlap1(struct mk_operation_mode_cbc_s* cbc, int blocks, unsigned char const* input, unsigned char* output)
{
	mk_operation_mode_encrypt_blocks_cbc_overlap0(cbc, blocks, input, output);
}

static mk_inline void mk_operation_mode_decrypt_blocks_cbc_overlap0(struct mk_operation_mode_cbc_s* cbc, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* iv;
	int i;

	mk_assert(cbc);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cbc->m_base.m_block_cipher);
	iv = cbc->m_iv;
	for(i = 0; i != blocks; ++i)
	{
		mk_block_cipher_decrypt_block(cbc->m_base.m_block_cipher, cbc->m_base.m_key, input, output);
		mk_operation_mode_detail_xor(block_len, output, iv, output);
		iv = input;
		input += block_len;
		output += block_len;
	}
	memcpy(cbc->m_iv, iv, block_len);
}

static mk_inline void mk_operation_mode_decrypt_blocks_cbc_overlap1(struct mk_operation_mode_cbc_s* cbc, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char* tmp;
	unsigned char const* iv;
	unsigned char temporary[mk_block_cipher_block_len_max];
	int i;

	mk_assert(cbc);
	mk_assert(blocks >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(cbc->m_base.m_block_cipher);
	tmp = cbc->m_iv;
	iv = temporary;
	for(i = 0; i != blocks; ++i)
	{
		mk_operation_mode_cbc_swap_ptr(&tmp, &iv);
		memcpy(tmp, input, block_len);
		mk_block_cipher_decrypt_block(cbc->m_base.m_block_cipher, cbc->m_base.m_key, input, output);
		mk_operation_mode_detail_xor(block_len, output, iv, output);
		input += block_len;
		output += block_len;
	}
	memcpy(cbc->m_iv, tmp, block_len);
}


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
	int overlapping;

	block_len = mk_block_cipher_get_block_len(cbc->m_base.m_block_cipher);
	overlapping = !(output >= input + blocks * block_len || input >= output + blocks * block_len);
	if(overlapping)
	{
		mk_operation_mode_encrypt_blocks_cbc_overlap1(cbc, blocks, input, output);
	}
	else
	{
		mk_operation_mode_encrypt_blocks_cbc_overlap0(cbc, blocks, input, output);
	}
}

void mk_operation_mode_decrypt_blocks_cbc(struct mk_operation_mode_cbc_s* cbc, int blocks, unsigned char const* input, unsigned char* output)
{
	int block_len;
	int overlapping;

	block_len = mk_block_cipher_get_block_len(cbc->m_base.m_block_cipher);
	overlapping = !(output >= input + blocks * block_len || input >= output + blocks * block_len);
	if(overlapping)
	{
		mk_operation_mode_decrypt_blocks_cbc_overlap1(cbc, blocks, input, output);
	}
	else
	{
		mk_operation_mode_decrypt_blocks_cbc_overlap0(cbc, blocks, input, output);
	}
}
