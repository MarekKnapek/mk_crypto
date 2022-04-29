#include "../src/mk_crypto.h"
#include "../src/mk_tom_crypto.h"

#include "../utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <stdlib.h> /* malloc free */
#include <string.h> /* memset memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_crypto_fuzz_3(unsigned char const* data, size_t size)
{
	enum mk_crypto_operation_mode_e om_mk;
	enum mk_tom_crypto_operation_mode_e om_tom;
	enum mk_crypto_algorithm_e alg_mk;
	enum mk_tom_crypto_algorithm_e alg_tom;
	int key_len;
	unsigned char const* iv;
	unsigned char const* key;
	int chunks;
	int cfb_s_bytes;
	int good;
	int i;
	int blocks;
	mk_crypto_h crypto_mk;
	mk_tom_crypto_h crypto_tom;
	mk_crypto_h cryptod_mk;
	mk_tom_crypto_h cryptod_tom;
	unsigned char const* msg;
	int msg_len;
	int out_len;
	unsigned char* out_mk;
	unsigned char* out_tom;
	int out_lend_mk;
	int out_lend_tom;
	unsigned char* outd_mk;
	unsigned char* outd_tom;

	test(data);

	if(!(size >= 1))
	{
		return;
	}
	om_mk = 0, om_tom = 0;
	switch(*data % 3)
	{
		case 0: om_mk = mk_crypto_operation_mode_cbc; om_tom = mk_tom_crypto_operation_mode_cbc; break;
		case 1: om_mk = mk_crypto_operation_mode_ecb; om_tom = mk_tom_crypto_operation_mode_ecb; break;
		case 2: om_mk = mk_crypto_operation_mode_cfb; om_tom = mk_tom_crypto_operation_mode_cfb; break;
	}
	++data;
	--size;

	if(!(size >= 1))
	{
		return;
	}
	alg_mk = 0, alg_tom = 0;
	key_len = 0;
	switch(*data % 3)
	{
		case 0: alg_mk = mk_crypto_block_cipher_aes128; alg_tom = mk_tom_crypto_block_cipher_aes128; key_len = 16; break;
		case 1: alg_mk = mk_crypto_block_cipher_aes192; alg_tom = mk_tom_crypto_block_cipher_aes192; key_len = 24; break;
		case 2: alg_mk = mk_crypto_block_cipher_aes256; alg_tom = mk_tom_crypto_block_cipher_aes256; key_len = 32; break;
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

	crypto_mk = mk_crypto_create(om_mk, alg_mk, iv, key);
	crypto_tom = mk_tom_crypto_create(om_tom, alg_tom, iv, key);
	test(crypto_mk);
	test(crypto_tom);
	cryptod_mk = mk_crypto_create(om_mk, alg_mk, iv, key);
	cryptod_tom = mk_tom_crypto_create(om_tom, alg_tom, iv, key);
	test(cryptod_mk);
	test(cryptod_tom);

	if(om_mk == mk_crypto_operation_mode_cfb)
	{
		cfb_s_bytes = 16;
		mk_crypto_set_param(crypto_mk, mk_crypto_param_cfb_s_bytes, &cfb_s_bytes);
		mk_crypto_set_param(cryptod_mk, mk_crypto_param_cfb_s_bytes, &cfb_s_bytes);
	}

	good = 1;
	for(i = 0; i != chunks; ++i)
	{
		if(!(size >= 1))
		{
			good = 0;
			break;
		}
		blocks = *data;
		++data;
		--size;

		if(!((int)size >= blocks * 16))
		{
			good = 0;
			break;
		}
		
		out_mk = malloc(blocks * 16);
		test(out_mk);
		mk_crypto_encrypt(crypto_mk, 0, data, blocks * 16, out_mk);

		out_tom = malloc(blocks * 16);
		test(out_tom);
		mk_tom_crypto_encrypt(crypto_tom, 0, data, blocks * 16, out_tom);

		test(memcmp(out_mk, out_tom, blocks * 16) == 0);

		outd_mk = malloc(blocks * 16);
		test(outd_mk);
		out_lend_mk = mk_crypto_decrypt(cryptod_mk, 0, out_mk, blocks * 16, outd_mk);
		test(out_lend_mk == blocks * 16);
		test(memcmp(outd_mk, data, blocks * 16) == 0);

		outd_tom = malloc(blocks * 16);
		test(outd_tom);
		out_lend_tom = mk_tom_crypto_decrypt(cryptod_tom, 0, out_tom, blocks * 16, outd_tom);
		test(out_lend_mk == blocks * 16);
		test(memcmp(outd_tom, data, blocks * 16) == 0);

		free(out_mk);
		free(out_tom);
		free(outd_mk);
		free(outd_tom);

		data += blocks * 16;
		size -= blocks * 16;
	}
	if(!good)
	{
		mk_crypto_destroy(crypto_mk);
		mk_tom_crypto_destroy(crypto_tom);
		mk_crypto_destroy(cryptod_mk);
		mk_tom_crypto_destroy(cryptod_tom);
		return;
	}

	msg = data;
	msg_len = (int)size;
	
	out_len = (msg_len / 16 + 1) * 16;
	out_mk = (unsigned char*)malloc(out_len);
	out_tom = (unsigned char*)malloc(out_len);
	test(out_mk);
	test(out_tom);
	memset(out_mk, 0, out_len);
	memset(out_tom, 0, out_len);

	mk_crypto_encrypt(crypto_mk, 1, msg, msg_len, out_mk);
	mk_tom_crypto_encrypt(crypto_tom, 1, msg, msg_len, out_tom);

	test(memcmp(out_mk, out_tom, out_len) == 0);

	outd_mk = malloc(out_len);
	test(outd_mk);
	out_lend_mk = mk_crypto_decrypt(cryptod_mk, 1, out_mk, out_len, outd_mk);
	test(out_lend_mk == msg_len);
	test(memcmp(outd_mk, msg, msg_len) == 0);

	outd_tom = malloc(out_len);
	test(outd_tom);
	out_lend_tom = mk_tom_crypto_decrypt(cryptod_tom, 1, out_tom, out_len, outd_tom);
	test(out_lend_tom == msg_len);
	test(memcmp(outd_tom, msg, msg_len) == 0);

	mk_crypto_destroy(crypto_mk);
	mk_tom_crypto_destroy(crypto_tom);
	mk_crypto_destroy(cryptod_mk);
	mk_tom_crypto_destroy(cryptod_tom);

	free(out_mk);
	free(out_tom);
	free(outd_mk);
	free(outd_tom);
}


#undef test
