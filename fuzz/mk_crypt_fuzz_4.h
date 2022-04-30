#include "../src/mk_crypto.h"

#include "../utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <stdlib.h> /* malloc free */
#include <string.h> /* memcpy memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_crypto_fuzz_4(unsigned char const* data, size_t size)
{
	enum mk_crypto_operation_mode_e om_mk;
	int want_cfb_s_bytes;
	int want_ctr_big_endian;
	enum mk_crypto_algorithm_e alg_mk;
	int key_len;
	unsigned char const* iv;
	unsigned char const* key;
	unsigned char const* data_start;
	size_t size_start;
	int chunks;
	int sum;
	int i;
	int chunk_len;
	mk_crypto_h crypto1;
	mk_crypto_h crypto2;
	int cfb_s_bytes;
	int ctr_endian;
	int out_len;
	unsigned char* input;
	unsigned char* output_1;
	unsigned char* output_2;
	unsigned char* in;
	unsigned char* out_1;
	int encrypted_sum;
	int encrypted;

	test(data);

	if(!(size >= 1))
	{
		return;
	}
	om_mk = 0;
	switch(*data % 5)
	{
		case 0: om_mk = mk_crypto_operation_mode_cbc; break;
		case 1: om_mk = mk_crypto_operation_mode_cfb; break;
		case 2: om_mk = mk_crypto_operation_mode_ctr; break;
		case 3: om_mk = mk_crypto_operation_mode_ecb; break;
		case 4: om_mk = mk_crypto_operation_mode_ofb; break;
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
	alg_mk = 0;
	key_len = 0;
	switch(*data % 3)
	{
		case 0: alg_mk = mk_crypto_block_cipher_aes128; key_len = 16; break;
		case 1: alg_mk = mk_crypto_block_cipher_aes192; key_len = 24; break;
		case 2: alg_mk = mk_crypto_block_cipher_aes256; key_len = 32; break;
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
	chunks = *data;
	++data;
	--size;
	if(chunks == 0)
	{
		return;
	}

	data_start = data;
	size_start = size;
	sum = 0;
	for(i = 0; i != chunks; ++i)
	{
		if(!(size >= 1))
		{
			return;
		}
		chunk_len = *data;
		++data;
		--size;

		if(!((int)size >= chunk_len))
		{
			return;
		}
		data += chunk_len;
		size -= chunk_len;

		sum += chunk_len;
	}

	crypto1 = mk_crypto_create(om_mk, alg_mk, iv, key);
	crypto2 = mk_crypto_create(om_mk, alg_mk, iv, key);
	test(crypto1);
	test(crypto2);

	if(om_mk == mk_crypto_operation_mode_cfb && want_cfb_s_bytes == 0)
	{
		cfb_s_bytes = 16;
		mk_crypto_set_param(crypto1, mk_crypto_param_cfb_s_bytes, &cfb_s_bytes);
		mk_crypto_set_param(crypto2, mk_crypto_param_cfb_s_bytes, &cfb_s_bytes);
	}

	if(om_mk == mk_crypto_operation_mode_ctr && want_ctr_big_endian == 0)
	{
		ctr_endian = 1;
		mk_crypto_set_param(crypto1, mk_crypto_param_ctr_endian, &ctr_endian);
		mk_crypto_set_param(crypto2, mk_crypto_param_ctr_endian, &ctr_endian);
	}

	out_len = (sum / 16 + 1) * 16;
	input = (unsigned char*)malloc(sum);
	output_1 = (unsigned char*)malloc(out_len);
	output_2 = (unsigned char*)malloc(out_len);
	test(input);
	test(output_1);
	test(output_2);
	in = input;
	out_1 = output_1;

	encrypted_sum = 0;
	data = data_start;
	size = size_start;
	for(i = 0; i != chunks; ++i)
	{
		chunk_len = *data;
		++data;
		--size;

		encrypted = mk_crypto_encrypt(crypto1, i == chunks - 1, data, chunk_len, out_1);
		out_1 += encrypted;
		encrypted_sum += encrypted;

		memcpy(in, data, chunk_len);
		in += chunk_len;

		data += chunk_len;
		size -= chunk_len;
	}

	encrypted = mk_crypto_encrypt(crypto2, 1, input, sum, output_2);
	test(encrypted_sum == encrypted);

	test(memcmp(output_1, output_2, encrypted_sum) == 0);

	mk_crypto_destroy(crypto1);
	mk_crypto_destroy(crypto2);
	free(input);
	free(output_1);
	free(output_2);
}


#undef test
