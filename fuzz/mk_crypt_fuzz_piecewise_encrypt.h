#include "../src/mk_crypto.h"

#include "../utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <stdlib.h> /* malloc free */
#include <string.h> /* memcpy memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_crypt_fuzz_piecewise_encrypt(unsigned char const* data, size_t size)
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
	int nchunks;
	int sum;
	int i;
	int chunk;
	unsigned char chunks[0xff];
	int out_len;
	unsigned char* out1;
	unsigned char* out2;
	mk_crypto_h crypto1;
	mk_crypto_h crypto2;
	struct pointer_and_lenght_s ivs;
	int cfb_s_bytes;
	int ctr_endian;
	unsigned char const* input;
	int encrypted;
	unsigned char* out2p;

	if(!data || size == 0)
	{
		return;
	}

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

	if(!(size >= 1))
	{
		return;
	}
	nchunks = *data;
	++data;
	--size;
	if(!(nchunks >= 2))
	{
		return;
	}

	sum = 0;
	for(i = 0; i != nchunks; ++i)
	{
		if(!(size >= 1))
		{
			return;
		}
		chunk = *data;
		++data;
		--size;

		chunks[i] = (unsigned char)chunk;
		sum += chunk;
	}

	if(!(sum == (int)size))
	{
		return;
	}

	out_len = ((int)size / 16 + 1) * 16;
	out1 = (unsigned char*)malloc(out_len);
	out2 = (unsigned char*)malloc(out_len);
	test(out1);
	test(out2);

	crypto1 = mk_crypto_create(om, bc, padding, key, key_len);
	crypto2 = mk_crypto_create(om, bc, padding, key, key_len);
	test(crypto1);
	test(crypto2);

	if(om != mk_crypto_operation_mode_ecb)
	{
		ivs.m_pointer = iv;
		ivs.m_lenght = 16;
		mk_crypto_set_param(crypto1, mk_crypto_param_iv, &ivs);
		mk_crypto_set_param(crypto2, mk_crypto_param_iv, &ivs);
	}
	if(om == mk_crypto_operation_mode_cfb && want_cfb_s_bytes == 0)
	{
		cfb_s_bytes = 16;
		mk_crypto_set_param(crypto1, mk_crypto_param_cfb_s_bytes, &cfb_s_bytes);
		mk_crypto_set_param(crypto2, mk_crypto_param_cfb_s_bytes, &cfb_s_bytes);
	}
	if(om == mk_crypto_operation_mode_ctr && want_ctr_big_endian == 0)
	{
		ctr_endian = 1;
		mk_crypto_set_param(crypto1, mk_crypto_param_ctr_endian, &ctr_endian);
		mk_crypto_set_param(crypto2, mk_crypto_param_ctr_endian, &ctr_endian);
	}

	input = data;

	encrypted = mk_crypto_encrypt(crypto1, 1, input, (int)size, out1, out_len);
	test(encrypted == out_len);

	out2p = out2;
	sum = 0;
	for(i = 0; i != nchunks - 1; ++i)
	{
		chunk = chunks[i];
		encrypted = mk_crypto_encrypt(crypto2, 0, input, chunk, out2p, out_len - (int)(out2p - out2));
		test(encrypted != -1);
		out2p += encrypted;
		sum += encrypted;
		input += chunk;
	}
	chunk = chunks[i];
	encrypted = mk_crypto_encrypt(crypto2, 1, input, chunk, out2p, out_len - (int)(out2p - out2));
	test(encrypted != -1);
	out2p += encrypted;
	sum += encrypted;
	input += chunk;
	test(sum == out_len);
	test(out2p == out2 + out_len);

	test(memcmp(out1, out2, out_len) == 0);

	mk_crypto_destroy(crypto2);
	mk_crypto_destroy(crypto1);
	free(out2);
	free(out1);
}


#undef test
