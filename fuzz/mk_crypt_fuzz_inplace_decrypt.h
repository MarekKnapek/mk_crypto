#include "../src/mk_crypto.h"

#include "../utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <stdlib.h> /* malloc free */
#include <string.h> /* memcpy memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_crypt_fuzz_inplace_decrypt(unsigned char const* data, size_t size)
{
	struct pointer_and_lenght_s
	{
		void const* m_pointer;
		int m_lenght;
	};

	enum mk_crypto_operation_mode_e om;
	int want_cfb_s_bytes;
	int want_ctr_big_endian;
	enum mk_crypto_block_cipher_e bc;
	enum mk_crypto_padding_e padding;
	int key_len;
	unsigned char const* iv;
	unsigned char const* key;
	int out_len;
	unsigned char* out1;
	unsigned char* out2;
	unsigned char* out3;
	mk_crypto_h crypto1;
	mk_crypto_h crypto2;
	mk_crypto_h crypto3;
	struct pointer_and_lenght_s ivs;
	int cfb_s_bytes;
	int ctr_endian;
	int encrypted;
	int decrypted;

	test(data);

	if(!(size >= 1))
	{
		return;
	}
	om = 0;
	switch(*data % 5)
	{
		case 0: om = mk_crypto_operation_mode_cbc; break;
		case 1: om = mk_crypto_operation_mode_cfb; break;
		case 2: om = mk_crypto_operation_mode_ctr; break;
		case 3: om = mk_crypto_operation_mode_ecb; break;
		case 4: om = mk_crypto_operation_mode_ofb; break;
	}
	++data;
	--size;

	if(!(size >= 1))
	{
		return;
	}
	want_cfb_s_bytes = *data % 2;
	++data;
	--size;

	if(!(size >= 1))
	{
		return;
	}
	want_ctr_big_endian = *data % 2;
	++data;
	--size;

	if(!(size >= 1))
	{
		return;
	}
	bc = 0;
	key_len = 0;
	switch(*data % 3)
	{
		case 0: bc = mk_crypto_block_cipher_aes128; key_len = 16; break;
		case 1: bc = mk_crypto_block_cipher_aes192; key_len = 24; break;
		case 2: bc = mk_crypto_block_cipher_aes256; key_len = 32; break;
	}
	++data;
	--size;

	if(!(size >= 1))
	{
		return;
	}
	padding = 0;
	switch(*data % 5)
	{
		case 0: padding = mk_crypto_padding_pkcs7; break;
		case 1: padding = mk_crypto_padding_10s; break;
		case 2: padding = mk_crypto_padding_10s1; break;
		case 3: padding = mk_crypto_padding_zero; break;
		case 4: padding = mk_crypto_padding_none; break;
	}
	++data;
	--size;

	if(!(size >= 16))
	{
		return;
	}
	iv = data;
	data += 16;
	size -= 16;

	if(!((int)size >= key_len))
	{
		return;
	}
	key = data;
	data += key_len;
	size -= key_len;

	out_len = ((int)size / 16 + 1) * 16;
	out1 = (unsigned char*)malloc(out_len);
	out2 = (unsigned char*)malloc(out_len);
	out3 = (unsigned char*)malloc(out_len);
	test(out1);
	test(out2);
	test(out3);

	crypto1 = mk_crypto_create(om, bc, padding, key, key_len);
	crypto2 = mk_crypto_create(om, bc, padding, key, key_len);
	crypto3 = mk_crypto_create(om, bc, padding, key, key_len);
	test(crypto1);
	test(crypto2);
	test(crypto3);

	if(om != mk_crypto_operation_mode_ecb)
	{
		ivs.m_pointer = iv;
		ivs.m_lenght = 16;
		mk_crypto_set_param(crypto1, mk_crypto_param_iv, &ivs);
		mk_crypto_set_param(crypto2, mk_crypto_param_iv, &ivs);
		mk_crypto_set_param(crypto3, mk_crypto_param_iv, &ivs);
	}
	if(om == mk_crypto_operation_mode_cfb && want_cfb_s_bytes == 0)
	{
		cfb_s_bytes = 16;
		mk_crypto_set_param(crypto1, mk_crypto_param_cfb_s_bytes, &cfb_s_bytes);
		mk_crypto_set_param(crypto2, mk_crypto_param_cfb_s_bytes, &cfb_s_bytes);
		mk_crypto_set_param(crypto3, mk_crypto_param_cfb_s_bytes, &cfb_s_bytes);
	}
	if(om == mk_crypto_operation_mode_ctr && want_ctr_big_endian == 0)
	{
		ctr_endian = 1;
		mk_crypto_set_param(crypto1, mk_crypto_param_ctr_endian, &ctr_endian);
		mk_crypto_set_param(crypto2, mk_crypto_param_ctr_endian, &ctr_endian);
		mk_crypto_set_param(crypto3, mk_crypto_param_ctr_endian, &ctr_endian);
	}

	encrypted = mk_crypto_encrypt(crypto1, 1, data, (int)size, out1, out_len);
	test(encrypted == out_len);

	decrypted = mk_crypto_decrypt(crypto2, 1, out1, out_len, out2, out_len);
	test(decrypted == (int)size);
	test(memcmp(out2, data, size) == 0);

	memcpy(out3, out1, out_len);
	decrypted = mk_crypto_decrypt(crypto3, 1, out3, out_len, out3, out_len);
	test(decrypted == (int)size);
	test(memcmp(out3, data, size) == 0);

	mk_crypto_destroy(crypto3);
	mk_crypto_destroy(crypto2);
	mk_crypto_destroy(crypto1);
	free(out3);
	free(out2);
	free(out1);
}


#undef test
