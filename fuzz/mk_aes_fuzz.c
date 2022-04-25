#include "mk_aes_fuzz.h"

#include "../src/mk_aes.h"
#include "../src/mk_win_aes.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <stdlib.h> /* malloc free */
#include <string.h> /* memset memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


void mk_aes_fuzz(unsigned char const* data, size_t size)
{
	(void)data;
	(void)size;
#if 0
	int direction;
	enum mk_aes_key_len_e mk_key_len;
	enum mk_win_aes_key_len_e win_key_len;
	int key_len;
	enum mk_aes_operation_mode_e mk_om;
	enum mk_win_aes_operation_mode_e win_om;
	unsigned char const* iv;
	unsigned char const* key;
	unsigned char const* msg;
	int msg_len;
	int out_len;
	unsigned char* mk_out;
	unsigned char* win_out;
	int m;

	mk_assert(data);

	if(!(size >= 1))
	{
		return;
	}
	direction = *data % 2;
	++data;
	--size;

	if(!(size >= 1))
	{
		return;
	}
	switch(*data % 3)
	{
		case 0: mk_key_len = mk_aes_key_len_128; win_key_len = mk_win_aes_key_len_128; key_len = 16; break;
		case 1: mk_key_len = mk_aes_key_len_192; win_key_len = mk_win_aes_key_len_192; key_len = 24; break;
		case 2: mk_key_len = mk_aes_key_len_256; win_key_len = mk_win_aes_key_len_256; key_len = 32; break;
		default: return; break;
	}
	++data;
	--size;

	if(!(size >= 1))
	{
		return;
	}
	switch(*data % 5)
	{
		case 0: mk_om = mk_aes_operation_mode_cbc; win_om = mk_win_aes_operation_mode_cbc; break;
		case 1: mk_om = mk_aes_operation_mode_ecb; win_om = mk_win_aes_operation_mode_ecb; break;
		case 2: mk_om = mk_aes_operation_mode_ofb; win_om = mk_win_aes_operation_mode_ofb; break;
		case 3: mk_om = mk_aes_operation_mode_cfb; win_om = mk_win_aes_operation_mode_cfb; break;
		case 4: mk_om = mk_aes_operation_mode_cts; win_om = mk_win_aes_operation_mode_cts; break;
		default: return; break;
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

	msg = data;
	msg_len = (int)size;
	
	m = msg_len % 16;
	if(direction == 1 && m != 0)
	{
		direction = 0;
	}
	if(direction == 1 && msg_len == 0)
	{
		direction = 0;
	}
	if(direction == 1 && (mk_om == mk_aes_operation_mode_ecb || mk_om == mk_aes_operation_mode_cbc || mk_om == mk_aes_operation_mode_ofb || mk_om == mk_aes_operation_mode_cts || mk_om == mk_aes_operation_mode_cfb))
	{
		direction = 0;
	}
	
	out_len = (msg_len / 16 + (direction == 0 ? 1 : 0)) * 16;
	mk_out = (unsigned char*)malloc(out_len);
	win_out = (unsigned char*)malloc(out_len);
	memset(mk_out, 0, out_len);
	memset(win_out, 0, out_len);

	if(direction == 0)
	{
		mk_aes_encrypt_msg(mk_key_len, mk_om, mk_aes_padding_pkcs7, iv, key, msg, msg_len, mk_out);
		mk_win_aes_encrypt_msg(win_key_len, win_om, mk_win_aes_padding_pkcs7, iv, key, msg, msg_len, win_out);
	}
	else
	{
		mk_aes_decrypt_msg(mk_key_len, mk_om, mk_aes_padding_pkcs7, iv, key, msg, msg_len, mk_out);
		mk_win_aes_decrypt_msg(win_key_len, win_om, mk_win_aes_padding_pkcs7, iv, key, msg, msg_len, win_out);
	}

	test(memcmp(mk_out, win_out, out_len) == 0);

	free(win_out);
	free(mk_out);
#endif
}


#undef test
