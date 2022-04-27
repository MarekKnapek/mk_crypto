#include "mk_crypt.h"

#include "operation_mode/mk_operation_mode.h"
#include "mk_block_cipher.h"

#include "../utils/mk_assert.h"

#include <string.h> /* memcpy memset */


#define mk_assert_operation_mode(operation_mode) mk_assert \
	( \
		(operation_mode) == mk_crypt_operation_mode_cbc  || \
		(operation_mode) == mk_crypt_operation_mode_cfb  || \
		(operation_mode) == mk_crypt_operation_mode_ecb  || \
		0 \
	)


#define mk_assert_block_cipher(block_cipher) mk_assert \
	( \
		(block_cipher) == mk_crypt_block_cipher_aes128 || \
		(block_cipher) == mk_crypt_block_cipher_aes192 || \
		(block_cipher) == mk_crypt_block_cipher_aes256 || \
		0 \
	)


void mk_crypt_init(struct mk_crypt_s* crypt, enum mk_crypt_operation_mode_e operation_mode, enum mk_crypt_block_cipher_e block_cipher, void const* iv, void const* key)
{
	mk_assert(crypt);
	mk_assert_operation_mode(operation_mode);
	mk_assert_block_cipher(block_cipher);
	mk_assert(key);

	crypt->m_operation_mode = operation_mode;
	crypt->m_block_cipher = block_cipher;
	mk_operation_mode_init_iv(operation_mode, block_cipher, iv, crypt->m_iv, sizeof(crypt->m_iv));
	mk_block_cipher_init_key(block_cipher, key, crypt->m_key, sizeof(crypt->m_key));
}

void mk_crypt_encrypt(struct mk_crypt_s* crypt, int final, void const* input, int input_len_bytes, void* output)
{
	int block_len;
	int n;
	int m;
	unsigned char const* last_block_in;
	unsigned char* last_block_out;
	unsigned char last_block[16];

	mk_assert(crypt);
	mk_assert_operation_mode(crypt->m_operation_mode);
	mk_assert_block_cipher(crypt->m_block_cipher);
	mk_assert(final == 0 || final == 1);
	mk_assert(input || input_len_bytes == 0);
	mk_assert(input_len_bytes >= 0);
	mk_assert(output || (!input && final == 0));

	block_len = mk_block_cipher_get_block_len(crypt->m_block_cipher);
	mk_assert((final == 0 && input_len_bytes % block_len == 0) || final == 1);

	n = input_len_bytes / block_len;
	m = input_len_bytes % block_len;
	mk_operation_mode_encrypt_blocks(crypt->m_operation_mode, crypt->m_block_cipher, crypt->m_iv, crypt->m_key, n, input, output);

	if(final == 1)
	{
		mk_assert(sizeof(last_block) >= block_len);
		last_block_in = (unsigned char const*)input + n * block_len;
		last_block_out = (unsigned char*)output + n * block_len;
		memcpy(last_block, last_block_in, m);
		memset(last_block + m, block_len - m, block_len - m);
		mk_crypt_encrypt(crypt, 0, last_block, block_len, last_block_out);
	}
}

int mk_crypt_decrypt(struct mk_crypt_s* crypt, int final, void const* input, int input_len_bytes, void* output)
{
	#define decrypt_check(x) do{ if(!(x)){ return -1; } }while(0)

	int block_len;
	int n;
	int m;
	unsigned char const* last_block_in;
	unsigned char* last_block_out;
	unsigned char last_block[16];
	int decrypted;
	unsigned char padding;
	int i;

	mk_assert(crypt);
	mk_assert_operation_mode(crypt->m_operation_mode);
	mk_assert_block_cipher(crypt->m_block_cipher);
	mk_assert(final == 0 || final == 1);
	mk_assert(final == 1 && input || final == 0);
	mk_assert(input || input_len_bytes == 0);
	mk_assert(input_len_bytes >= 0);
	mk_assert(output || !input);

	block_len = mk_block_cipher_get_block_len(crypt->m_block_cipher);
	mk_assert(input_len_bytes % block_len == 0);

	n = input_len_bytes / block_len;
	m = final == 0 ? n : (n == 0 ? 0 : n - 1);
	mk_operation_mode_decrypt_blocks(crypt->m_operation_mode, crypt->m_block_cipher, crypt->m_iv, crypt->m_key, m, input, output);

	if(final == 1)
	{
		mk_assert(sizeof(last_block) >= block_len);
		last_block_in = (unsigned char const*)input + m * block_len;
		last_block_out = (unsigned char*)output + m * block_len;
		decrypted = mk_crypt_decrypt(crypt, 0, last_block_in, block_len, last_block);
		mk_assert(decrypted == block_len);
		padding = last_block[block_len - 1];
		decrypt_check(padding <= block_len);
		for(i = 1; i != padding; ++i)
		{
			decrypt_check(last_block[block_len - 1 - i] == padding);
		}
		memcpy(last_block_out, last_block, block_len - padding);
		return input_len_bytes - padding;
	}
	return input_len_bytes;

	#undef decrypt_check
}


#undef mk_assert_operation_mode
#undef mk_assert_block_cipher
