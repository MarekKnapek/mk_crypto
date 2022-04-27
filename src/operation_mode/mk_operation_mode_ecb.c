#include "mk_operation_mode_ecb.h"

#include "mk_operation_mode_impl.h"
#include "../mk_block_cipher.h"

#include "../../utils/mk_assert.h"


void mk_operation_mode_encrypt_blocks_ecb(enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output)
{
	int block_len;
	int i;

	(void)iv;
	mk_assert(key);
	mk_assert(n >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(block_cipher);
	mk_assert(block_len <= mk_operation_mode_detail_max_block_len);

	for(i = 0; i != n; ++i)
	{
		mk_block_cipher_encrypt_block(block_cipher, key, input, output);
		input += block_len;
		output += block_len;
	}
}

void mk_operation_mode_decrypt_blocks_ecb(enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output)
{
	int block_len;
	int i;

	(void)iv;
	mk_assert(key);
	mk_assert(n >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(block_cipher);
	mk_assert(block_len <= mk_operation_mode_detail_max_block_len);

	for(i = 0; i != n; ++i)
	{
		mk_block_cipher_decrypt_block(block_cipher, key, input, output);
		input += block_len;
		output += block_len;
	}
}
