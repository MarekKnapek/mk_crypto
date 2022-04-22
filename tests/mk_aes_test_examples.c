#include "mk_aes_test_examples.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <string.h> /* memcmp */


#include "../src/mk_aes.h"
#include "../src/mk_aes.c"


/* https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.197.pdf */


static char const s_aes_key_128[] = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";
static char const s_aes_key_192[] = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";
static char const s_aes_key_256[] = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";

static char const s_aes_128_msg_0[] = "3243f6a8885a308d313198a2e0370734";
static char const s_aes_128_key_0[] = "2b7e151628aed2a6abf7158809cf4f3c";
static char const s_aes_128_out_0[] = "3925841d02dc09fbdc118597196a0b32";

static char const s_aes_128_msg_1[] = "00112233445566778899aabbccddeeff";
static char const s_aes_128_key_1[] = "000102030405060708090a0b0c0d0e0f";
static char const s_aes_128_out_1[] = "69c4e0d86a7b0430d8cdb78070b4c55a";

static char const s_aes_192_msg_0[] = "00112233445566778899aabbccddeeff";
static char const s_aes_192_key_0[] = "000102030405060708090a0b0c0d0e0f1011121314151617";
static char const s_aes_192_out_0[] = "dda97ca4864cdfe06eaf70a0ec0d7191";

static char const s_aes_256_msg_0[] = "00112233445566778899aabbccddeeff";
static char const s_aes_256_key_0[] = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
static char const s_aes_256_out_0[] = "8ea2b7ca516745bfeafc49904b496089";


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err; err = (x); if(err != 0){ return err; } }while(0)


static mk_inline void mk_string_hex_to_bytes(void const* in, int len, void* out);


static mk_inline int mk_aes_test_128(void const* msg_str, void const* key_str, void const* out_str)
{
	unsigned char msg[16];
	unsigned char key[16];
	unsigned char out[16];
	unsigned char buff1[16];
	unsigned char buff2[16];

	mk_string_hex_to_bytes(msg_str, 16 * 2, msg);
	mk_string_hex_to_bytes(key_str, 16 * 2, key);
	mk_string_hex_to_bytes(out_str, 16 * 2, out);

	mk_aes_detail_encrypt_block_128(msg, key, buff1);
	mk_check(memcmp(buff1, out, 16) == 0);

	mk_aes_detail_decrypt_block_128(buff1, key, buff2);
	mk_check(memcmp(buff2, msg, 16) == 0);

	return 0;
}

static mk_inline int mk_aes_test_192(void const* msg_str, void const* key_str, void const* out_str)
{
	unsigned char msg[16];
	unsigned char key[24];
	unsigned char out[16];
	unsigned char buff1[16];
	unsigned char buff2[16];

	mk_string_hex_to_bytes(msg_str, 16 * 2, msg);
	mk_string_hex_to_bytes(key_str, 24 * 2, key);
	mk_string_hex_to_bytes(out_str, 16 * 2, out);

	mk_aes_detail_encrypt_block_192(msg, key, buff1);
	mk_check(memcmp(buff1, out, 16) == 0);

	mk_aes_detail_decrypt_block_192(buff1, key, buff2);
	mk_check(memcmp(buff2, msg, 16) == 0);

	return 0;
}

static mk_inline int mk_aes_test_256(void const* msg_str, void const* key_str, void const* out_str)
{
	unsigned char msg[16];
	unsigned char key[32];
	unsigned char out[16];
	unsigned char buff1[16];
	unsigned char buff2[16];

	mk_string_hex_to_bytes(msg_str, 16 * 2, msg);
	mk_string_hex_to_bytes(key_str, 32 * 2, key);
	mk_string_hex_to_bytes(out_str, 16 * 2, out);

	mk_aes_detail_encrypt_block_256(msg, key, buff1);
	mk_check(memcmp(buff1, out, 16) == 0);

	mk_aes_detail_decrypt_block_256(buff1, key, buff2);
	mk_check(memcmp(buff2, msg, 16) == 0);

	return 0;
}


int mk_aes_test_examples(void)
{
	mk_try(mk_aes_test_128(s_aes_128_msg_0, s_aes_128_key_0, s_aes_128_out_0));
	mk_try(mk_aes_test_128(s_aes_128_msg_1, s_aes_128_key_1, s_aes_128_out_1));

	mk_try(mk_aes_test_192(s_aes_192_msg_0, s_aes_192_key_0, s_aes_192_out_0));

	mk_try(mk_aes_test_256(s_aes_256_msg_0, s_aes_256_key_0, s_aes_256_out_0));

	return 0;
}


#undef mk_check
#undef mk_try
