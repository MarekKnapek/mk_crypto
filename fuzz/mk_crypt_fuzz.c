#include "mk_crypt_fuzz.h"

#include "../src/mk_crypto.h"
#include "../src/mk_win_crypto.h"
#include "../src/mk_win_cryptong.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <stdlib.h> /* malloc free */
#include <string.h> /* memset memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_crypto_fuzz_1(unsigned char const* data, size_t size)
{
	enum mk_crypto_operation_mode_e om_mk;
	enum mk_win_crypto_operation_mode_e om_win;
	enum mk_crypto_algorithm_e alg_mk;
	enum mk_win_crypto_algorithm_e alg_win;
	int key_len;
	unsigned char const* iv;
	unsigned char const* key;
	int chunks;
	int good;
	int i;
	int blocks;
	mk_crypto_h crypto_mk;
	mk_win_crypto_h crypto_win;
	unsigned char const* msg;
	int msg_len;
	int out_len;
	unsigned char* out_mk;
	unsigned char* out_win;

	mk_assert(data);

	if(!(size >= 1))
	{
		return;
	}
	om_mk = 0, om_win = 0;
	switch(*data % 3)
	{
		case 0: om_mk = mk_crypto_operation_mode_cbc; om_win = mk_win_crypto_operation_mode_cbc; break;
		case 1: om_mk = mk_crypto_operation_mode_ecb; om_win = mk_win_crypto_operation_mode_ecb; break;
		case 2: om_mk = mk_crypto_operation_mode_cfb; om_win = mk_win_crypto_operation_mode_cfb; break;
	}
	++data;
	--size;

	if(!(size >= 1))
	{
		return;
	}
	alg_mk = 0, alg_win = 0;
	key_len = 0;
	switch(*data % 3)
	{
		case 0: alg_mk = mk_crypto_algorithm_aes128; alg_win = mk_win_crypto_algorithm_aes128; key_len = 16; break;
		case 1: alg_mk = mk_crypto_algorithm_aes192; alg_win = mk_win_crypto_algorithm_aes192; key_len = 24; break;
		case 2: alg_mk = mk_crypto_algorithm_aes256; alg_win = mk_win_crypto_algorithm_aes256; key_len = 32; break;
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
	crypto_win = mk_win_crypto_create(om_win, alg_win, iv, key);
	mk_assert(crypto_mk);
	mk_assert(crypto_win);

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
		mk_assert(out_mk);
		mk_crypto_encrypt(crypto_mk, 0, data, blocks * 16, out_mk);

		out_win = malloc(blocks * 16);
		mk_assert(out_win);
		mk_win_crypto_encrypt(crypto_win, 0, data, blocks * 16, out_win);

		mk_assert(memcmp(out_mk, out_win, blocks * 16) == 0);

		free(out_mk);
		free(out_win);

		data += blocks * 16;
		size -= blocks * 16;
	}
	if(!good)
	{
		mk_crypto_destroy(crypto_mk);
		mk_win_crypto_destroy(crypto_win);
		return;
	}

	msg = data;
	msg_len = (int)size;
	
	out_len = (msg_len / 16 + 1) * 16;
	out_mk = (unsigned char*)malloc(out_len);
	out_win = (unsigned char*)malloc(out_len);
	mk_assert(out_mk);
	mk_assert(out_win);
	memset(out_mk, 0, out_len);
	memset(out_win, 0, out_len);

	mk_crypto_encrypt(crypto_mk, 1, msg, msg_len, out_mk);
	mk_win_crypto_encrypt(crypto_win, 1, msg, msg_len, out_win);

	test(memcmp(out_mk, out_win, out_len) == 0);

	mk_crypto_destroy(crypto_mk);
	mk_win_crypto_destroy(crypto_win);

	free(out_mk);
	free(out_win);
}

static mk_inline void mk_crypto_fuzz_2(unsigned char const* data, size_t size)
{
	enum mk_crypto_operation_mode_e om_mk;
	enum mk_win_cryptong_operation_mode_e om_winng;
	enum mk_crypto_algorithm_e alg_mk;
	enum mk_win_cryptong_algorithm_e alg_winng;
	int key_len;
	unsigned char const* iv;
	unsigned char const* key;
	int chunks;
	int good;
	int i;
	int blocks;
	mk_crypto_h crypto_mk;
	mk_win_cryptong_h crypto_winng;
	unsigned char const* msg;
	int msg_len;
	int out_len;
	unsigned char* out_mk;
	unsigned char* out_winng;

	mk_assert(data);

	if(!(size >= 1))
	{
		return;
	}
	om_mk = 0, om_winng = 0;
	switch(*data % 3)
	{
		case 0: om_mk = mk_crypto_operation_mode_cbc; om_winng = mk_win_cryptong_operation_mode_cbc; break;
		case 1: om_mk = mk_crypto_operation_mode_ecb; om_winng = mk_win_cryptong_operation_mode_ecb; break;
		case 2: om_mk = mk_crypto_operation_mode_cfb; om_winng = mk_win_cryptong_operation_mode_cfb; break;
	}
	++data;
	--size;

	if(!(size >= 1))
	{
		return;
	}
	alg_mk = 0, alg_winng = 0;
	key_len = 0;
	switch(*data % 3)
	{
		case 0: alg_mk = mk_crypto_algorithm_aes128; alg_winng = mk_win_cryptong_algorithm_aes128; key_len = 16; break;
		case 1: alg_mk = mk_crypto_algorithm_aes192; alg_winng = mk_win_cryptong_algorithm_aes192; key_len = 24; break;
		case 2: alg_mk = mk_crypto_algorithm_aes256; alg_winng = mk_win_cryptong_algorithm_aes256; key_len = 32; break;
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
	crypto_winng = mk_win_cryptong_create(om_winng, alg_winng, iv, key);
	mk_assert(crypto_mk);
	mk_assert(crypto_winng);

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
		mk_assert(out_mk);
		mk_crypto_encrypt(crypto_mk, 0, data, blocks * 16, out_mk);

		out_winng = malloc(blocks * 16);
		mk_assert(out_winng);
		mk_win_cryptong_encrypt(crypto_winng, 0, data, blocks * 16, out_winng);

		mk_assert(memcmp(out_mk, out_winng, blocks * 16) == 0);

		free(out_mk);
		free(out_winng);

		data += blocks * 16;
		size -= blocks * 16;
	}
	if(!good)
	{
		mk_crypto_destroy(crypto_mk);
		mk_win_cryptong_destroy(crypto_winng);
		return;
	}

	msg = data;
	msg_len = (int)size;
	
	out_len = (msg_len / 16 + 1) * 16;
	out_mk = (unsigned char*)malloc(out_len);
	out_winng = (unsigned char*)malloc(out_len);
	mk_assert(out_mk);
	mk_assert(out_winng);
	memset(out_mk, 0, out_len);
	memset(out_winng, 0, out_len);

	mk_crypto_encrypt(crypto_mk, 1, msg, msg_len, out_mk);
	mk_win_cryptong_encrypt(crypto_winng, 1, msg, msg_len, out_winng);

	test(memcmp(out_mk, out_winng, out_len) == 0);

	mk_crypto_destroy(crypto_mk);
	mk_win_cryptong_destroy(crypto_winng);

	free(out_mk);
	free(out_winng);
}


void mk_crypto_fuzz(unsigned char const* data, size_t size)
{
	mk_crypto_fuzz_1(data, size);
	mk_crypto_fuzz_2(data, size);
}


#undef test
