#include "mk_operation_mode_cfb.h"

#include "mk_operation_mode_impl.h"
#include "../mk_block_cipher.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#include <string.h> /* memcpy */


void mk_operation_mode_encrypt_blocks_cfb(enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output)
{
	int block_len;
	unsigned char tmp[mk_operation_mode_detail_max_block_len];
	int i;
	int j;
	int k;

	mk_assert(iv);
	mk_assert(key);
	mk_assert(n >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(block_cipher);
	mk_assert(block_len <= mk_operation_mode_detail_max_block_len);

	for(i = 0; i != n; ++i)
	{
		for(j = 0; j != block_len; ++j)
		{
			mk_block_cipher_encrypt_block(block_cipher, key, iv, tmp);
			output[j] = input[j] ^ tmp[0];
			for(k = 0; k != block_len - 1; ++k)
			{
				iv[k] = iv[k + 1];
			}
			iv[block_len - 1] = output[j];
		}
		input += block_len;
		output += block_len;
	}
}

void mk_operation_mode_decrypt_blocks_cfb(enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output)
{
	enum mk_crypt_block_len_e block_len;
	unsigned char tmp[mk_operation_mode_detail_max_block_len];
	int i;
	int j;
	int k;

	mk_assert(iv);
	mk_assert(key);
	mk_assert(n >= 0);
	mk_assert(input);
	mk_assert(output);

	block_len = mk_block_cipher_get_block_len(block_cipher);
	mk_assert(block_len <= mk_operation_mode_detail_max_block_len);
	
	for(i = 0; i != n; ++i)
	{
		for(j = 0; j != block_len; ++j)
		{
			mk_block_cipher_encrypt_block(block_cipher, key, iv, tmp);
			output[j] = input[j] ^ tmp[0];
			for(k = 0; k != block_len - 1; ++k)
			{
				iv[k] = iv[k + 1];
			}
			iv[block_len - 1] = input[j];
		}
		input += block_len;
		output += block_len;
	}
}
