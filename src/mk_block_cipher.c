#include "mk_block_cipher.h"

#include "mk_aes.h"

#include "../utils/mk_assert.h"

#include <string.h> /* memcpy */


#define mk_assert_block_cipher(block_cipher) mk_assert \
	( \
		(block_cipher) == mk_block_cipher_aes128 || \
		(block_cipher) == mk_block_cipher_aes192 || \
		(block_cipher) == mk_block_cipher_aes256 || \
		0 \
	)


int mk_block_cipher_get_block_len(enum mk_block_cipher_e block_cipher)
{
	mk_assert_block_cipher(block_cipher);

	switch(block_cipher)
	{
		case mk_block_cipher_aes128: return 16; break;
		case mk_block_cipher_aes192: return 16; break;
		case mk_block_cipher_aes256: return 16; break;
	}

	return 0;
}

int mk_block_cipher_get_key_len(enum mk_block_cipher_e block_cipher)
{
	mk_assert_block_cipher(block_cipher);

	switch(block_cipher)
	{
		case mk_block_cipher_aes128: return 16; break;
		case mk_block_cipher_aes192: return 24; break;
		case mk_block_cipher_aes256: return 32; break;
	}

	return 0;
}

void mk_block_cipher_init_key(enum mk_block_cipher_e block_cipher, unsigned char const* input, unsigned char* output, int output_len)
{
	int key_len;

	mk_assert_block_cipher(block_cipher);

	key_len = mk_block_cipher_get_key_len(block_cipher);
	mk_assert(output_len >= key_len);

	memcpy(output, input, key_len);
}

void mk_block_cipher_encrypt_block(enum mk_block_cipher_e block_cipher, unsigned char const* key, unsigned char const* input, unsigned char* output)
{
	mk_assert_block_cipher(block_cipher);

	switch(block_cipher)
	{
		case mk_block_cipher_aes128: mk_aes_encrypt_block_128(input, key, output); break;
		case mk_block_cipher_aes192: mk_aes_encrypt_block_192(input, key, output); break;
		case mk_block_cipher_aes256: mk_aes_encrypt_block_256(input, key, output); break;
	}
}

void mk_block_cipher_decrypt_block(enum mk_block_cipher_e block_cipher, unsigned char const* key, unsigned char const* input, unsigned char* output)
{
	mk_assert_block_cipher(block_cipher);

	switch(block_cipher)
	{
		case mk_block_cipher_aes128: mk_aes_decrypt_block_128(input, key, output); break;
		case mk_block_cipher_aes192: mk_aes_decrypt_block_192(input, key, output); break;
		case mk_block_cipher_aes256: mk_aes_decrypt_block_256(input, key, output); break;
	}
}


#undef mk_assert_block_cipher
