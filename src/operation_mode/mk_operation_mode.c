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


void mk_operation_mode_init_iv(enum mk_operation_mode_e operation_mode, enum mk_block_cipher_e block_cipher, unsigned char const* input, unsigned char* output, int output_len)
{
	int block_len;

	mk_assert_operation_mode(operation_mode);

	if(operation_mode == mk_operation_mode_ecb)
	{
		return;
	}

	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(block_cipher);
	mk_assert(output_len >= block_len);
	
	memcpy(output, input, block_len);
}

void mk_operation_mode_encrypt_blocks(enum mk_operation_mode_e operation_mode, enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output)
{
	mk_assert_operation_mode(operation_mode);

	if(n == 0)
	{
		return;
	}

	switch(operation_mode)
	{
		case mk_operation_mode_cbc: mk_operation_mode_encrypt_blocks_cbc(block_cipher, iv, key, n, input, output); break;
		case mk_operation_mode_cfb: mk_operation_mode_encrypt_blocks_cfb(block_cipher, iv, key, n, input, output); break;
		case mk_operation_mode_ecb: mk_operation_mode_encrypt_blocks_ecb(block_cipher, iv, key, n, input, output); break;
	}
}

void mk_operation_mode_decrypt_blocks(enum mk_operation_mode_e operation_mode, enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output)
{
	mk_assert_operation_mode(operation_mode);

	if(n == 0)
	{
		return;
	}

	switch(operation_mode)
	{
		case mk_operation_mode_cbc: mk_operation_mode_decrypt_blocks_cbc(block_cipher, iv, key, n, input, output); break;
		case mk_operation_mode_cfb: mk_operation_mode_decrypt_blocks_cfb(block_cipher, iv, key, n, input, output); break;
		case mk_operation_mode_ecb: mk_operation_mode_decrypt_blocks_ecb(block_cipher, iv, key, n, input, output); break;
	}
}


#undef mk_assert_operation_mode
