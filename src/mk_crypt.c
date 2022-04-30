#include "mk_crypt.h"

#include "../utils/mk_assert.h"

#include <string.h> /* memcpy memset */


void mk_crypt_init(struct mk_crypt_s* crypt, enum mk_operation_mode_e operation_mode, enum mk_block_cipher_e block_cipher, void const* key)
{
	mk_assert(crypt);

	mk_operation_mode_init(&crypt->m_operation_mode, operation_mode, block_cipher, key);
	crypt->m_idx = 0;
}

void mk_crypt_set_param_iv(struct mk_crypt_s* crypt, unsigned char const* iv)
{
	mk_assert(crypt);

	mk_operation_mode_set_param_iv(&crypt->m_operation_mode, iv);
}

void mk_crypt_set_param_cfb_s_bytes(struct mk_crypt_s* crypt, int cfb_s_bytes)
{
	mk_assert(crypt);

	mk_operation_mode_set_param_cfb_s_bytes(&crypt->m_operation_mode, cfb_s_bytes);
}

void mk_crypt_set_param_ctr_endian(struct mk_crypt_s* crypt, int ctr_endian)
{
	mk_assert(crypt);

	mk_operation_mode_set_param_ctr_endian(&crypt->m_operation_mode, ctr_endian);
}

int mk_crypt_encrypt(struct mk_crypt_s* crypt, int final, void const* input, int input_len_bytes, void* output)
{
	unsigned char const* in;
	int len;
	unsigned char* out;
	int ret;

	int block_len;
	int capacity;
	int encrypted;
	int blocks;
	int padding;

	mk_assert(crypt);
	mk_assert(final == 0 || final == 1);
	mk_assert(input || input_len_bytes == 0);
	mk_assert(input_len_bytes >= 0);
	mk_assert(output || (!input && final == 0));

	in = (unsigned char const*)input;
	len = input_len_bytes;
	out = (unsigned char*)output;
	ret = 0;

	block_len = mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher(&crypt->m_operation_mode));
	capacity = block_len - crypt->m_idx;
	if(len >= capacity)
	{
		if(crypt->m_idx != 0)
		{
			memcpy(crypt->m_block + crypt->m_idx, in, capacity);
			crypt->m_idx = 0;
			encrypted = mk_crypt_encrypt(crypt, 0, crypt->m_block, block_len, out);
			mk_assert(encrypted == block_len);
			in += capacity;
			len -= capacity;
			out += block_len;
			ret += block_len;
		}
		blocks = len / block_len;
		mk_operation_mode_encrypt_blocks(&crypt->m_operation_mode, blocks, in, out);
		in += blocks * block_len;
		len -= blocks * block_len;
		out += blocks * block_len;
		ret += blocks * block_len;
	}
	mk_assert(len < block_len);
	mk_assert(crypt->m_idx + len < block_len);
	memcpy(crypt->m_block + crypt->m_idx, in, len);
	crypt->m_idx += len;

	if(final == 1)
	{
		padding = block_len - crypt->m_idx;
		memset(crypt->m_block + crypt->m_idx, padding, padding);
		crypt->m_idx = 0;
		encrypted = mk_crypt_encrypt(crypt, 0, crypt->m_block, block_len, out);
		mk_assert(encrypted == block_len);
		ret += block_len;
	}

	return ret;
}

int mk_crypt_decrypt(struct mk_crypt_s* crypt, int final, void const* input, int input_len_bytes, void* output)
{
	unsigned char const* in;
	int len;
	unsigned char* out;
	int ret;

	int block_len;
	int capacity;
	int decrypted;
	int blocks;
	int padding;
	int i;

	mk_assert(crypt);
	mk_assert(final == 0 || final == 1);
	mk_assert(input || input_len_bytes == 0);
	mk_assert(input_len_bytes >= 0);
	mk_assert(output || (!input && final == 0));

	in = (unsigned char const*)input;
	len = input_len_bytes;
	out = (unsigned char*)output;
	ret = 0;

	block_len = mk_block_cipher_get_block_len(mk_operation_mode_get_block_cipher(&crypt->m_operation_mode));
	mk_assert(final == 0 || len % block_len == 0);
	if(final == 1 && len >= block_len)
	{
		len -= block_len;
	}
	capacity = block_len - crypt->m_idx;
	if(len >= block_len)
	{
		if(crypt->m_idx != 0)
		{
			memcpy(crypt->m_block + crypt->m_idx, in, capacity);
			crypt->m_idx = 0;
			decrypted = mk_crypt_decrypt(crypt, final, crypt->m_block, block_len, out);
			mk_assert(decrypted == block_len);
			in += capacity;
			len -= capacity;
			out += block_len;
			ret += block_len;
		}
		blocks = len / block_len;
		mk_operation_mode_decrypt_blocks(&crypt->m_operation_mode, blocks, in, out);
		in += blocks * block_len;
		len -= blocks * block_len;
		out += blocks * block_len;
		ret += blocks * block_len;
	}
	mk_assert(len < block_len);
	mk_assert(crypt->m_idx + len < block_len);
	memcpy(crypt->m_block + crypt->m_idx, in, len);
	crypt->m_idx += len;

	if(final == 1)
	{
		#define decrypt_check(x) do{ if(!(x)){ return -1; } }while(0)
		mk_assert(crypt->m_idx == 0);
		mk_assert(len == 0);
		decrypted = mk_crypt_decrypt(crypt, 0, in, block_len, crypt->m_block);
		mk_assert(decrypted == block_len);
		padding = crypt->m_block[block_len - 1];
		decrypt_check(padding <= block_len);
		for(i = 1; i != padding; ++i)
		{
			decrypt_check(crypt->m_block[block_len - 1 - i] == padding);
		}
		ret += block_len - padding;
		memcpy(out, crypt->m_block, block_len - padding);
		#undef decrypt_check
	}

	return ret;
}
