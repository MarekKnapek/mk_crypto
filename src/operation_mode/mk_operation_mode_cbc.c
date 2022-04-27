#include "mk_operation_mode_cbc.h"

#include "mk_operation_mode_impl.h"
#include "../mk_block_cipher.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#include <string.h> /* memcpy */


void mk_operation_mode_encrypt_blocks_cbc(enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* ivp;
	unsigned char tmp[mk_operation_mode_detail_max_block_len];
	int i;

	mk_assert(iv);
	mk_assert(key);
	mk_assert(n >= 1);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(block_cipher);
	mk_assert(block_len <= mk_operation_mode_detail_max_block_len);

	ivp = iv;
	for(i = 0; i != n; ++i)
	{
		mk_operation_mode_detail_xor(block_len, input, ivp, tmp);
		mk_block_cipher_encrypt_block(block_cipher, key, tmp, output);
		ivp = output;
		input += block_len;
		output += block_len;
	}
	memcpy(iv, output - block_len, block_len);
}

void mk_operation_mode_decrypt_blocks_cbc(enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char const* ivp;
	unsigned char tmp[mk_operation_mode_detail_max_block_len];
	int i;

	mk_assert(iv);
	mk_assert(key);
	mk_assert(n >= 1);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(block_cipher);
	mk_assert(block_len <= mk_operation_mode_detail_max_block_len);
	
	ivp = iv;
	for(i = 0; i != n; ++i)
	{
		mk_block_cipher_decrypt_block(block_cipher, key, input, tmp);
		mk_operation_mode_detail_xor(block_len, tmp, ivp, output);
		ivp = input;
		input += block_len;
		output += block_len;
	}
	memcpy(iv, input - block_len, block_len);
}
