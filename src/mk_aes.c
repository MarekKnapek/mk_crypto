#include "mk_aes.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <string.h> /* memcpy memmove */


#define mk_aes_config_small 1
#define mk_aes_config_fast 2
#if !defined(mk_aes_config)
#define mk_aes_config mk_aes_config_fast
#endif


static unsigned char const mk_aes_detail_sbox[] =
{
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16,
};

static unsigned char const mk_aes_detail_inv_sbox[] =
{
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d,
};

static unsigned char const mk_aes_detail_rcon[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };


static mk_inline unsigned char mk_aes_detail_mul_2(unsigned char x)
{
	return (x << 1) ^ (((x >> 7) & 0x01) * 0x1b);
}

static mk_inline unsigned char mk_aes_detail_mul_3(unsigned char x)
{
	return mk_aes_detail_mul_2(x) ^ x;
}

static mk_inline void mk_aes_detail_mix_columns(unsigned char state[16])
{
	unsigned char orig[16];
	int i;

	mk_assert(state);

	memcpy(orig, state, 16);
	for(i = 0; i != 4; ++i)
	{
		state[i * 4 + 0] = mk_aes_detail_mul_2(orig[i * 4 + 0]) ^ mk_aes_detail_mul_3(orig[i * 4 + 1]) ^ orig[i * 4 + 2] ^ orig[i * 4 + 3];
		state[i * 4 + 1] = orig[i * 4 + 0] ^ mk_aes_detail_mul_2(orig[i * 4 + 1]) ^ mk_aes_detail_mul_3(orig[i * 4 + 2]) ^ orig[i * 4 + 3];
		state[i * 4 + 2] = orig[i * 4 + 0] ^ orig[i * 4 + 1] ^ mk_aes_detail_mul_2(orig[i * 4 + 2]) ^ mk_aes_detail_mul_3(orig[i * 4 + 3]);
		state[i * 4 + 3] = mk_aes_detail_mul_3(orig[i * 4 + 0]) ^ orig[i * 4 + 1] ^ orig[i * 4 + 2] ^ mk_aes_detail_mul_2(orig[i * 4 + 3]);
	}
}

static mk_inline unsigned char mk_aes_detail_mul_4(unsigned char x)
{
	return mk_aes_detail_mul_2(mk_aes_detail_mul_2(x));
}

static mk_inline unsigned char mk_aes_detail_mul_8(unsigned char x)
{
	return mk_aes_detail_mul_2(mk_aes_detail_mul_2(mk_aes_detail_mul_2(x)));
}

static mk_inline unsigned char mk_aes_detail_mul_9(unsigned char x)
{
	return mk_aes_detail_mul_8(x) ^ x;
}

static mk_inline unsigned char mk_aes_detail_mul_b(unsigned char x)
{
	return mk_aes_detail_mul_8(x) ^ mk_aes_detail_mul_2(x) ^ x;
}

static mk_inline unsigned char mk_aes_detail_mul_d(unsigned char x)
{
	return mk_aes_detail_mul_8(x) ^ mk_aes_detail_mul_4(x) ^ x;
}

static mk_inline unsigned char mk_aes_detail_mul_e(unsigned char x)
{
	return mk_aes_detail_mul_8(x) ^ mk_aes_detail_mul_4(x) ^ mk_aes_detail_mul_2(x);
}

static mk_inline void mk_aes_detail_inv_mix_columns(unsigned char state[16])
{
	unsigned char orig[16];
	int i;

	mk_assert(state);

	memcpy(orig, state, 16);
	for(i = 0; i != 4; ++i)
	{
		state[i * 4 + 0] = mk_aes_detail_mul_e(orig[i * 4 + 0]) ^ mk_aes_detail_mul_b(orig[i * 4 + 1]) ^ mk_aes_detail_mul_d(orig[i * 4 + 2]) ^ mk_aes_detail_mul_9(orig[i * 4 + 3]);
		state[i * 4 + 1] = mk_aes_detail_mul_9(orig[i * 4 + 0]) ^ mk_aes_detail_mul_e(orig[i * 4 + 1]) ^ mk_aes_detail_mul_b(orig[i * 4 + 2]) ^ mk_aes_detail_mul_d(orig[i * 4 + 3]);
		state[i * 4 + 2] = mk_aes_detail_mul_d(orig[i * 4 + 0]) ^ mk_aes_detail_mul_9(orig[i * 4 + 1]) ^ mk_aes_detail_mul_e(orig[i * 4 + 2]) ^ mk_aes_detail_mul_b(orig[i * 4 + 3]);
		state[i * 4 + 3] = mk_aes_detail_mul_b(orig[i * 4 + 0]) ^ mk_aes_detail_mul_d(orig[i * 4 + 1]) ^ mk_aes_detail_mul_9(orig[i * 4 + 2]) ^ mk_aes_detail_mul_e(orig[i * 4 + 3]);
	}
}

static mk_inline void mk_aes_detail_shift_rows(unsigned char state[16])
{
	unsigned char tmp1;
	unsigned char tmp2;

	mk_assert(state);

	tmp1 = state[0 * 4 + 1];
	state[0 * 4 + 1] = state[1 * 4 + 1];
	state[1 * 4 + 1] = state[2 * 4 + 1];
	state[2 * 4 + 1] = state[3 * 4 + 1];
	state[3 * 4 + 1] = tmp1;

	tmp1 = state[0 * 4 + 2];
	tmp2 = state[1 * 4 + 2];
	state[0 * 4 + 2] = state[2 * 4 + 2];
	state[1 * 4 + 2] = state[3 * 4 + 2];
	state[2 * 4 + 2] = tmp1;
	state[3 * 4 + 2] = tmp2;

	tmp1 = state[1 * 4 + 3];
	state[1 * 4 + 3] = state[0 * 4 + 3];
	state[0 * 4 + 3] = state[3 * 4 + 3];
	state[3 * 4 + 3] = state[2 * 4 + 3];
	state[2 * 4 + 3] = tmp1;
}

static mk_inline void mk_aes_detail_inv_shift_rows(unsigned char state[16])
{
	unsigned char tmp1;
	unsigned char tmp2;

	mk_assert(state);

	tmp1 = state[1 * 4 + 1];
	state[1 * 4 + 1] = state[0 * 4 + 1];
	state[0 * 4 + 1] = state[3 * 4 + 1];
	state[3 * 4 + 1] = state[2 * 4 + 1];
	state[2 * 4 + 1] = tmp1;

	tmp1 = state[0 * 4 + 2];
	tmp2 = state[1 * 4 + 2];
	state[0 * 4 + 2] = state[2 * 4 + 2];
	state[1 * 4 + 2] = state[3 * 4 + 2];
	state[2 * 4 + 2] = tmp1;
	state[3 * 4 + 2] = tmp2;

	tmp1 = state[0 * 4 + 3];
	state[0 * 4 + 3] = state[1 * 4 + 3];
	state[1 * 4 + 3] = state[2 * 4 + 3];
	state[2 * 4 + 3] = state[3 * 4 + 3];
	state[3 * 4 + 3] = tmp1;
}

static mk_inline void mk_aes_detail_sub_byte(unsigned char* byte)
{
	mk_assert(byte);

	*byte = mk_aes_detail_sbox[*byte];
}

static mk_inline void mk_aes_detail_inv_sub_byte(unsigned char* byte)
{
	mk_assert(byte);

	*byte = mk_aes_detail_inv_sbox[*byte];
}

static mk_inline void mk_aes_detail_sub_bytes(unsigned char state[16])
{
	int i;

	mk_assert(state);

	for(i = 0; i != 16; ++i)
	{
		mk_aes_detail_sub_byte(state + i);
	}
}

static mk_inline void mk_aes_detail_inv_sub_bytes(unsigned char state[16])
{
	int i;

	mk_assert(state);

	for(i = 0; i != 16; ++i)
	{
		mk_aes_detail_inv_sub_byte(state + i);
	}
}

static mk_inline void mk_aes_detail_xor_word(unsigned char word[4], unsigned char rcon)
{
	mk_assert(word);

	word[0] ^= rcon;
}

static mk_inline void mk_aes_detail_sub_word(unsigned char word[4])
{
	mk_assert(word);

	mk_aes_detail_sub_byte(word + 0);
	mk_aes_detail_sub_byte(word + 1);
	mk_aes_detail_sub_byte(word + 2);
	mk_aes_detail_sub_byte(word + 3);
}

static mk_inline void mk_aes_detail_rot_word(unsigned char word[4])
{
	unsigned char tmp;

	mk_assert(word);

	tmp = word[0];
	word[0] = word[1];
	word[1] = word[2];
	word[2] = word[3];
	word[3] = tmp;
}

static mk_inline void mk_aes_detail_add_round_key(unsigned char state[16], unsigned char const round_key[16])
{
	int i;

	mk_assert(state);
	mk_assert(round_key);

	for(i = 0; i != 16; ++i)
	{
		state[i] ^= round_key[i];
	}
}

#if mk_aes_config == mk_aes_config_small

#elif mk_aes_config == mk_aes_config_fast

static mk_inline void mk_aes_detail_key_expansion_128(int i, unsigned char round_keys[(4 + 1) * 4])
{
	unsigned char temp[4];

	mk_assert(round_keys);

	temp[0] = round_keys[(4 - 1) * 4 + 0];
	temp[1] = round_keys[(4 - 1) * 4 + 1];
	temp[2] = round_keys[(4 - 1) * 4 + 2];
	temp[3] = round_keys[(4 - 1) * 4 + 3];
	if(i % 4 == 0)
	{
		mk_aes_detail_rot_word(temp);
		mk_aes_detail_sub_word(temp);
		mk_aes_detail_xor_word(temp, mk_aes_detail_rcon[i / 4 - 1]);
	}
	round_keys[4 * 4 + 0] = round_keys[(4 - 4) * 4 + 0] ^ temp[0];
	round_keys[4 * 4 + 1] = round_keys[(4 - 4) * 4 + 1] ^ temp[1];
	round_keys[4 * 4 + 2] = round_keys[(4 - 4) * 4 + 2] ^ temp[2];
	round_keys[4 * 4 + 3] = round_keys[(4 - 4) * 4 + 3] ^ temp[3];
}

static mk_inline void mk_aes_detail_key_expansion_192(int i, unsigned char round_keys[(6 + 1) * 4])
{
	unsigned char temp[4];

	mk_assert(round_keys);

	temp[0] = round_keys[(6 - 1) * 4 + 0];
	temp[1] = round_keys[(6 - 1) * 4 + 1];
	temp[2] = round_keys[(6 - 1) * 4 + 2];
	temp[3] = round_keys[(6 - 1) * 4 + 3];
	if(i % 6 == 0)
	{
		mk_aes_detail_rot_word(temp);
		mk_aes_detail_sub_word(temp);
		mk_aes_detail_xor_word(temp, mk_aes_detail_rcon[i / 6 - 1]);
	}
	round_keys[6 * 4 + 0] = round_keys[(6 - 6) * 4 + 0] ^ temp[0];
	round_keys[6 * 4 + 1] = round_keys[(6 - 6) * 4 + 1] ^ temp[1];
	round_keys[6 * 4 + 2] = round_keys[(6 - 6) * 4 + 2] ^ temp[2];
	round_keys[6 * 4 + 3] = round_keys[(6 - 6) * 4 + 3] ^ temp[3];
}

static mk_inline void mk_aes_detail_key_expansion_256(int i, unsigned char round_keys[(8 + 1) * 4])
{
	unsigned char temp[4];

	mk_assert(round_keys);

	temp[0] = round_keys[(8 - 1) * 4 + 0];
	temp[1] = round_keys[(8 - 1) * 4 + 1];
	temp[2] = round_keys[(8 - 1) * 4 + 2];
	temp[3] = round_keys[(8 - 1) * 4 + 3];
	if(i % 8 == 0)
	{
		mk_aes_detail_rot_word(temp);
		mk_aes_detail_sub_word(temp);
		mk_aes_detail_xor_word(temp, mk_aes_detail_rcon[i / 8 - 1]);
	}
	else if(i % 4 == 0)
	{
		mk_aes_detail_sub_word(temp);
	}
	round_keys[8 * 4 + 0] = round_keys[(8 - 8) * 4 + 0] ^ temp[0];
	round_keys[8 * 4 + 1] = round_keys[(8 - 8) * 4 + 1] ^ temp[1];
	round_keys[8 * 4 + 2] = round_keys[(8 - 8) * 4 + 2] ^ temp[2];
	round_keys[8 * 4 + 3] = round_keys[(8 - 8) * 4 + 3] ^ temp[3];
}

#endif

#if mk_aes_config == mk_aes_config_small

static mk_inline void mk_aes_detail_encrypt_block(enum mk_aes_key_len_e key_len, unsigned char const input[16], unsigned char const* key, unsigned char output[16])
{
}

#elif mk_aes_config == mk_aes_config_fast

static mk_inline void mk_aes_detail_encrypt_block_128(unsigned char const input[16], unsigned char const key[16], unsigned char output[16])
{
	unsigned char state[16];
	unsigned char round_keys[(4 + 4) * 4];
	int i;
	int r;

	mk_assert(input);
	mk_assert(key);
	mk_assert(output);

	memcpy(state, input, 16);
	memcpy(round_keys, key, 16);
	mk_aes_detail_add_round_key(state, round_keys + 0 * 4);

	i = 4;
	for(r = 0; r != 10 - 1; ++r)
	{
		mk_aes_detail_sub_bytes(state);
		mk_aes_detail_shift_rows(state);
		mk_aes_detail_mix_columns(state);
		mk_aes_detail_key_expansion_128(i + 0, round_keys + 0 * 4);
		mk_aes_detail_key_expansion_128(i + 1, round_keys + 1 * 4);
		mk_aes_detail_key_expansion_128(i + 2, round_keys + 2 * 4);
		mk_aes_detail_key_expansion_128(i + 3, round_keys + 3 * 4);
		mk_aes_detail_add_round_key(state, round_keys + 4 * 4);
		memcpy(round_keys + 0 * 4, round_keys + 4 * 4, 4 * 4);
		i += 4;
	}
	mk_aes_detail_sub_bytes(state);
	mk_aes_detail_shift_rows(state);
	mk_aes_detail_key_expansion_128(i + 0, round_keys + 0 * 4);
	mk_aes_detail_key_expansion_128(i + 1, round_keys + 1 * 4);
	mk_aes_detail_key_expansion_128(i + 2, round_keys + 2 * 4);
	mk_aes_detail_key_expansion_128(i + 3, round_keys + 3 * 4);
	mk_aes_detail_add_round_key(state, round_keys + 4 * 4);

	memcpy(output, state, 16);
}

static mk_inline void mk_aes_detail_decrypt_block_128(unsigned char const input[16], unsigned char const key[16], unsigned char output[16])
{
	unsigned char state[16];
	unsigned char round_keys[(10 + 1) * 16];
	int r;
	int i;

	mk_assert(input);
	mk_assert(key);
	mk_assert(output);

	memcpy(state, input, 16);
	memcpy(round_keys, key, 16);
	i = 4;
	for(r = 0; r != 10; ++r)
	{
		mk_aes_detail_key_expansion_128(i + 0, round_keys + r * 16 + 0 * 4);
		mk_aes_detail_key_expansion_128(i + 1, round_keys + r * 16 + 1 * 4);
		mk_aes_detail_key_expansion_128(i + 2, round_keys + r * 16 + 2 * 4);
		mk_aes_detail_key_expansion_128(i + 3, round_keys + r * 16 + 3 * 4);
		i += 4;
	}
	mk_aes_detail_add_round_key(state, round_keys + 10 * 16);
	for(r = 0; r != 10 - 1; ++r)
	{
		mk_aes_detail_inv_shift_rows(state);
		mk_aes_detail_inv_sub_bytes(state);
		mk_aes_detail_add_round_key(state, round_keys + (10 - 1 - r) * 16);
		mk_aes_detail_inv_mix_columns(state);
	}
	mk_aes_detail_inv_shift_rows(state);
	mk_aes_detail_inv_sub_bytes(state);
	mk_aes_detail_add_round_key(state, round_keys + 0 * 16);
	memcpy(output, state, 16);
}

static mk_inline void mk_aes_detail_decrypt2_block_128(unsigned char const input[16], unsigned char const key[16], unsigned char output[16])
{
	unsigned char state[16];
	unsigned char round_keys[(10 + 1) * 16];
	int r;

	mk_assert(input);
	mk_assert(key);
	mk_assert(output);

	memcpy(state, input, 16);
	memcpy(round_keys, key, 16);
	for(r = 0; r != 10; ++r)
	{
		mk_aes_detail_key_expansion_128(r, round_keys + r * 16);
	}
	mk_aes_detail_add_round_key(state, round_keys + 10 * 16);
	for(r = 0; r != 10 - 1; ++r)
	{
		mk_aes_detail_inv_shift_rows(state);
		mk_aes_detail_inv_sub_bytes(state);
		mk_aes_detail_add_round_key(state, round_keys + (10 - 1 - r) * 16);
		mk_aes_detail_inv_mix_columns(state);
	}
	mk_aes_detail_inv_shift_rows(state);
	mk_aes_detail_inv_sub_bytes(state);
	mk_aes_detail_add_round_key(state, round_keys + 0 * 16);
	memcpy(output, state, 16);
}

static mk_inline void mk_aes_detail_encrypt_block_192(unsigned char const input[16], unsigned char const key[24], unsigned char output[16])
{
	unsigned char state[16];
	unsigned char round_keys[(6 + 4) * 4];
	int i;
	int r;

	mk_assert(input);
	mk_assert(key);
	mk_assert(output);

	memcpy(state, input, 16);
	memcpy(round_keys, key, 24);
	mk_aes_detail_add_round_key(state, round_keys + 0 * 4);

	i = 6;
	mk_aes_detail_sub_bytes(state);
	mk_aes_detail_shift_rows(state);
	mk_aes_detail_mix_columns(state);
	mk_aes_detail_key_expansion_192(i + 0, round_keys + 0 * 4);
	mk_aes_detail_key_expansion_192(i + 1, round_keys + 1 * 4);
	mk_aes_detail_add_round_key(state, round_keys + 4 * 4);
	memmove(round_keys + 0 * 4, round_keys + 2 * 4, 6 * 4);
	i += 2;

	for(r = 0; r != 12 - 1 - 1; ++r)
	{
		mk_aes_detail_sub_bytes(state);
		mk_aes_detail_shift_rows(state);
		mk_aes_detail_mix_columns(state);
		mk_aes_detail_key_expansion_192(i + 0, round_keys + 0 * 4);
		mk_aes_detail_key_expansion_192(i + 1, round_keys + 1 * 4);
		mk_aes_detail_key_expansion_192(i + 2, round_keys + 2 * 4);
		mk_aes_detail_key_expansion_192(i + 3, round_keys + 3 * 4);
		mk_aes_detail_add_round_key(state, round_keys + 6 * 4);
		memmove(round_keys + 0 * 4, round_keys + 4 * 4, 6 * 4);
		i += 4;
	}
	mk_aes_detail_sub_bytes(state);
	mk_aes_detail_shift_rows(state);
	mk_aes_detail_key_expansion_192(i + 0, round_keys + 0 * 4);
	mk_aes_detail_key_expansion_192(i + 1, round_keys + 1 * 4);
	mk_aes_detail_key_expansion_192(i + 2, round_keys + 2 * 4);
	mk_aes_detail_key_expansion_192(i + 3, round_keys + 3 * 4);
	mk_aes_detail_add_round_key(state, round_keys + 6 * 4);

	memcpy(output, state, 16);
}

static mk_inline void mk_aes_detail_decrypt_block_192(unsigned char const input[16], unsigned char const key[24], unsigned char output[16])
{
	unsigned char state[16];
	unsigned char round_keys[(12 + 1) * 16];
	int r;
	int i;

	mk_assert(input);
	mk_assert(key);
	mk_assert(output);

	memcpy(state, input, 16);
	memcpy(round_keys, key, 24);
	i = 6;
	mk_aes_detail_key_expansion_192(i + 0, round_keys + 0 * 4);
	mk_aes_detail_key_expansion_192(i + 1, round_keys + 1 * 4);
	i += 2;
	for(r = 0; r != 12 - 1; ++r)
	{
		mk_aes_detail_key_expansion_192(i + 0, round_keys + 2 * 4 + r * 16 + 0 * 4);
		mk_aes_detail_key_expansion_192(i + 1, round_keys + 2 * 4 + r * 16 + 1 * 4);
		mk_aes_detail_key_expansion_192(i + 2, round_keys + 2 * 4 + r * 16 + 2 * 4);
		mk_aes_detail_key_expansion_192(i + 3, round_keys + 2 * 4 + r * 16 + 3 * 4);
		i += 4;
	}
	mk_aes_detail_add_round_key(state, round_keys + 12 * 16);
	for(r = 0; r != 12 - 1; ++r)
	{
		mk_aes_detail_inv_shift_rows(state);
		mk_aes_detail_inv_sub_bytes(state);
		mk_aes_detail_add_round_key(state, round_keys + (12 - 1 - r) * 16);
		mk_aes_detail_inv_mix_columns(state);
	}
	mk_aes_detail_inv_shift_rows(state);
	mk_aes_detail_inv_sub_bytes(state);
	mk_aes_detail_add_round_key(state, round_keys + 0 * 16);
	memcpy(output, state, 16);
}

static mk_inline void mk_aes_detail_encrypt_block_256(unsigned char const input[16], unsigned char const key[32], unsigned char output[16])
{
	unsigned char state[16];
	unsigned char round_keys[(8 + 4) * 4];
	int i;
	int r;

	mk_assert(input);
	mk_assert(key);
	mk_assert(output);

	memcpy(state, input, 16);
	memcpy(round_keys, key, 32);
	mk_aes_detail_add_round_key(state, round_keys + 0 * 4);

	mk_aes_detail_sub_bytes(state);
	mk_aes_detail_shift_rows(state);
	mk_aes_detail_mix_columns(state);
	mk_aes_detail_add_round_key(state, round_keys + 4 * 4);

	i = 8;
	for(r = 0; r != 14 - 1 - 1; ++r)
	{
		mk_aes_detail_sub_bytes(state);
		mk_aes_detail_shift_rows(state);
		mk_aes_detail_mix_columns(state);
		mk_aes_detail_key_expansion_256(i + 0, round_keys + 0 * 4);
		mk_aes_detail_key_expansion_256(i + 1, round_keys + 1 * 4);
		mk_aes_detail_key_expansion_256(i + 2, round_keys + 2 * 4);
		mk_aes_detail_key_expansion_256(i + 3, round_keys + 3 * 4);
		mk_aes_detail_add_round_key(state, round_keys + 8 * 4);
		memmove(round_keys + 0 * 4, round_keys + 4 * 4, 8 * 4);
		i += 4;
	}
	mk_aes_detail_sub_bytes(state);
	mk_aes_detail_shift_rows(state);
	mk_aes_detail_key_expansion_256(i + 0, round_keys + 0 * 4);
	mk_aes_detail_key_expansion_256(i + 1, round_keys + 1 * 4);
	mk_aes_detail_key_expansion_256(i + 2, round_keys + 2 * 4);
	mk_aes_detail_key_expansion_256(i + 3, round_keys + 3 * 4);
	mk_aes_detail_add_round_key(state, round_keys + 8 * 4);

	memcpy(output, state, 16);
}

static mk_inline void mk_aes_detail_decrypt_block_256(unsigned char const input[16], unsigned char const key[32], unsigned char output[16])
{
	unsigned char state[16];
	unsigned char round_keys[(14 + 1) * 16];
	int r;
	int i;

	mk_assert(input);
	mk_assert(key);
	mk_assert(output);

	memcpy(state, input, 16);
	memcpy(round_keys, key, 32);
	i = 8;
	for(r = 0; r != 14 - 1; ++r)
	{
		mk_aes_detail_key_expansion_256(i + 0, round_keys + r * 16 + 0 * 4);
		mk_aes_detail_key_expansion_256(i + 1, round_keys + r * 16 + 1 * 4);
		mk_aes_detail_key_expansion_256(i + 2, round_keys + r * 16 + 2 * 4);
		mk_aes_detail_key_expansion_256(i + 3, round_keys + r * 16 + 3 * 4);
		i += 4;
	}
	mk_aes_detail_add_round_key(state, round_keys + 14 * 16);
	for(r = 0; r != 14 - 1; ++r)
	{
		mk_aes_detail_inv_shift_rows(state);
		mk_aes_detail_inv_sub_bytes(state);
		mk_aes_detail_add_round_key(state, round_keys + (14 - 1 - r) * 16);
		mk_aes_detail_inv_mix_columns(state);
	}
	mk_aes_detail_inv_shift_rows(state);
	mk_aes_detail_inv_sub_bytes(state);
	mk_aes_detail_add_round_key(state, round_keys + 0 * 16);
	memcpy(output, state, 16);
}

#endif

static mk_inline void mk_aes_detail_mix(unsigned char iv[16], unsigned char const msg[16])
{
	int i;

	mk_assert(iv);
	mk_assert(msg);

	for(i = 0; i != 16; ++i)
	{
		iv[i] ^= msg[i];
	}
}

static mk_inline void mk_aes_detail_mix_iv_before(enum mk_aes_operation_mode_e om, unsigned char iv[16], unsigned char const msg[16])
{
	mk_assert(om == mk_aes_operation_mode_cbc || om == mk_aes_operation_mode_ecb || om == mk_aes_operation_mode_ofb || om == mk_aes_operation_mode_cfb || om == mk_aes_operation_mode_cts);
	mk_assert(iv);
	mk_assert(msg);

	switch(om)
	{
		case mk_aes_operation_mode_cbc: mk_aes_detail_mix(iv, msg); break;
		case mk_aes_operation_mode_ecb: break;
		case mk_aes_operation_mode_ofb: break;
		case mk_aes_operation_mode_cfb: break;
		case mk_aes_operation_mode_cts: break;
	}
}

static mk_inline void mk_aes_detail_mix_iv_after(enum mk_aes_operation_mode_e om, unsigned char iv[16], unsigned char const msg[16])
{
	mk_assert(om == mk_aes_operation_mode_cbc || om == mk_aes_operation_mode_ecb || om == mk_aes_operation_mode_ofb || om == mk_aes_operation_mode_cfb || om == mk_aes_operation_mode_cts);
	mk_assert(iv);
	mk_assert(msg);

	switch(om)
	{
		case mk_aes_operation_mode_cbc: break;
		case mk_aes_operation_mode_ecb: break;
		case mk_aes_operation_mode_ofb: break;
		case mk_aes_operation_mode_cfb: break;
		case mk_aes_operation_mode_cts: break;
	}
}


void mk_aes_128_encrypt_init(struct mk_aes_128_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key)
{
	mk_assert(self);
	mk_assert(om == mk_aes_operation_mode_cbc || om == mk_aes_operation_mode_ecb || om == mk_aes_operation_mode_ofb || om == mk_aes_operation_mode_cfb || om == mk_aes_operation_mode_cts);
	mk_assert(padding == mk_aes_padding_pkcs7);
	mk_assert(iv);
	mk_assert(key);

	self->m_om = om;
	memcpy(self->m_iv, iv, 16);
	memcpy(self->m_key, key, 16);
}

void mk_aes_128_encrypt_blocks(struct mk_aes_128_s* self, void const* msg, int n, void* out)
{
	int i;

	mk_assert(self);
	mk_assert(msg);
	mk_assert(n >= 0);
	mk_assert(out);

	for(i = 0; i != n; ++i)
	{
		#if mk_aes_config == mk_aes_config_small
		#elif mk_aes_config == mk_aes_config_fast
		mk_aes_detail_mix_iv_before(self->m_om, self->m_iv, msg);
		mk_aes_detail_encrypt_block_128(msg, self->m_key, out);
		mk_aes_detail_mix_iv_after(self->m_om, self->m_iv, msg);
		#endif
	}
}

void mk_aes_128_encrypt_finish(struct mk_aes_128_s* self, void const* msg, int msg_len, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(msg_len >= 0 && msg_len < 16);
	mk_assert(out);
}

void mk_aes_128_decrypt_init(struct mk_aes_128_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key)
{
	mk_assert(self);
	mk_assert(om == mk_aes_operation_mode_cbc || om == mk_aes_operation_mode_ecb || om == mk_aes_operation_mode_ofb || om == mk_aes_operation_mode_cfb || om == mk_aes_operation_mode_cts);
	mk_assert(padding == mk_aes_padding_pkcs7);
	mk_assert(iv);
	mk_assert(key);

	self->m_om = om;
	memcpy(self->m_iv, iv, 16);
	memcpy(self->m_key, key, 16);
}

void mk_aes_128_decrypt_blocks(struct mk_aes_128_s* self, void const* msg, int n, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(n >= 0);
	mk_assert(out);
}

void mk_aes_128_decrypt_finish(struct mk_aes_128_s* self, void const* msg, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(out);
}


void mk_aes_192_encrypt_init(struct mk_aes_192_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key)
{
	mk_assert(self);
	mk_assert(om == mk_aes_operation_mode_cbc || om == mk_aes_operation_mode_ecb || om == mk_aes_operation_mode_ofb || om == mk_aes_operation_mode_cfb || om == mk_aes_operation_mode_cts);
	mk_assert(padding == mk_aes_padding_pkcs7);
	mk_assert(iv);
	mk_assert(key);

	self->m_om = om;
	memcpy(self->m_iv, iv, 16);
	memcpy(self->m_key, key, 24);
}

void mk_aes_192_encrypt_blocks(struct mk_aes_192_s* self, void const* msg, int n, void* out)
{
	int i;

	mk_assert(self);
	mk_assert(msg);
	mk_assert(n >= 0);
	mk_assert(out);

	for(i = 0; i != n; ++i)
	{
		#if mk_aes_config == mk_aes_config_small
		#elif mk_aes_config == mk_aes_config_fast
		mk_aes_detail_encrypt_block_192(msg, self->m_key, out);
		#endif
	}
}

void mk_aes_192_encrypt_finish(struct mk_aes_192_s* self, void const* msg, int msg_len, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(msg_len >= 0 && msg_len < 16);
	mk_assert(out);
}

void mk_aes_192_decrypt_init(struct mk_aes_192_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key)
{
	mk_assert(self);
	mk_assert(om == mk_aes_operation_mode_cbc || om == mk_aes_operation_mode_ecb || om == mk_aes_operation_mode_ofb || om == mk_aes_operation_mode_cfb || om == mk_aes_operation_mode_cts);
	mk_assert(padding == mk_aes_padding_pkcs7);
	mk_assert(iv);
	mk_assert(key);

	self->m_om = om;
	memcpy(self->m_iv, iv, 16);
	memcpy(self->m_key, key, 24);
}

void mk_aes_192_decrypt_blocks(struct mk_aes_192_s* self, void const* msg, int n, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(n >= 0);
	mk_assert(out);
}

void mk_aes_192_decrypt_finish(struct mk_aes_192_s* self, void const* msg, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(out);
}


void mk_aes_256_encrypt_init(struct mk_aes_256_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key)
{
	mk_assert(self);
	mk_assert(om == mk_aes_operation_mode_cbc || om == mk_aes_operation_mode_ecb || om == mk_aes_operation_mode_ofb || om == mk_aes_operation_mode_cfb || om == mk_aes_operation_mode_cts);
	mk_assert(padding == mk_aes_padding_pkcs7);
	mk_assert(iv);
	mk_assert(key);

	self->m_om = om;
	memcpy(self->m_iv, iv, 16);
	memcpy(self->m_key, key, 32);
}

void mk_aes_256_encrypt_blocks(struct mk_aes_256_s* self, void const* msg, int n, void* out)
{
	int i;

	mk_assert(self);
	mk_assert(msg);
	mk_assert(n >= 0);
	mk_assert(out);

	for(i = 0; i != n; ++i)
	{
		#if mk_aes_config == mk_aes_config_small
		#elif mk_aes_config == mk_aes_config_fast
		mk_aes_detail_encrypt_block_256(msg, self->m_key, out);
		#endif
	}
}

void mk_aes_256_encrypt_finish(struct mk_aes_256_s* self, void const* msg, int msg_len, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(msg_len >= 0 && msg_len < 16);
	mk_assert(out);
}

void mk_aes_256_decrypt_init(struct mk_aes_256_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key)
{
	mk_assert(self);
	mk_assert(om == mk_aes_operation_mode_cbc || om == mk_aes_operation_mode_ecb || om == mk_aes_operation_mode_ofb || om == mk_aes_operation_mode_cfb || om == mk_aes_operation_mode_cts);
	mk_assert(padding == mk_aes_padding_pkcs7);
	mk_assert(iv);
	mk_assert(key);

	self->m_om = om;
	memcpy(self->m_iv, iv, 16);
	memcpy(self->m_key, key, 32);
}

void mk_aes_256_decrypt_blocks(struct mk_aes_256_s* self, void const* msg, int n, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(n >= 0);
	mk_assert(out);
}

void mk_aes_256_decrypt_finish(struct mk_aes_256_s* self, void const* msg, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(out);
}


void mk_aes_encrypt_init(struct mk_aes_s* self, enum mk_aes_key_len_e key_len, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key)
{
	mk_assert(self);
	mk_assert(key_len == mk_aes_key_len_128 || key_len == mk_aes_key_len_192 || key_len == mk_aes_key_len_256);
	mk_assert(om == mk_aes_operation_mode_cbc || om == mk_aes_operation_mode_ecb || om == mk_aes_operation_mode_ofb || om == mk_aes_operation_mode_cfb || om == mk_aes_operation_mode_cts);
	mk_assert(padding == mk_aes_padding_pkcs7);
	mk_assert(iv);
	mk_assert(key);

	self->m_key_len = key_len;
	switch(key_len)
	{
		case mk_aes_key_len_128: mk_aes_128_encrypt_init(&self->m_aes_128, om, padding, iv, key); break;
		case mk_aes_key_len_192: mk_aes_192_encrypt_init(&self->m_aes_192, om, padding, iv, key); break;
		case mk_aes_key_len_256: mk_aes_256_encrypt_init(&self->m_aes_256, om, padding, iv, key); break;
	}
}

void mk_aes_encrypt_blocks(struct mk_aes_s* self, void const* msg, int n, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(out);

	switch(self->m_key_len)
	{
		case mk_aes_key_len_128: mk_aes_128_encrypt_blocks(&self->m_aes_128, msg, n, out); break;
		case mk_aes_key_len_192: mk_aes_192_encrypt_blocks(&self->m_aes_192, msg, n, out); break;
		case mk_aes_key_len_256: mk_aes_256_encrypt_blocks(&self->m_aes_256, msg, n, out); break;
	}
}

void mk_aes_encrypt_finish(struct mk_aes_s* self, void const* msg, int msg_len, void* out)
{
	mk_assert(self);
	mk_assert((!msg && !msg_len) || msg);
	mk_assert(msg_len >= 0 && msg_len <= 16);
	mk_assert(out);

	switch(self->m_key_len)
	{
		case mk_aes_key_len_128: mk_aes_128_encrypt_finish(&self->m_aes_128, msg, msg_len, out); break;
		case mk_aes_key_len_192: mk_aes_192_encrypt_finish(&self->m_aes_192, msg, msg_len, out); break;
		case mk_aes_key_len_256: mk_aes_256_encrypt_finish(&self->m_aes_256, msg, msg_len, out); break;
	}
}

void mk_aes_decrypt_init(struct mk_aes_s* self, enum mk_aes_key_len_e key_len, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key)
{
	mk_assert(self);
	mk_assert(key_len == mk_aes_key_len_128 || key_len == mk_aes_key_len_192 || key_len == mk_aes_key_len_256);
	mk_assert(om == mk_aes_operation_mode_cbc || om == mk_aes_operation_mode_ecb || om == mk_aes_operation_mode_ofb || om == mk_aes_operation_mode_cfb || om == mk_aes_operation_mode_cts);
	mk_assert(padding == mk_aes_padding_pkcs7);
	mk_assert(iv);
	mk_assert(key);

	self->m_key_len = key_len;
	switch(key_len)
	{
		case mk_aes_key_len_128: mk_aes_128_decrypt_init(&self->m_aes_128, om, padding, iv, key); break;
		case mk_aes_key_len_192: mk_aes_192_decrypt_init(&self->m_aes_192, om, padding, iv, key); break;
		case mk_aes_key_len_256: mk_aes_256_decrypt_init(&self->m_aes_256, om, padding, iv, key); break;
	}
}

void mk_aes_decrypt_blocks(struct mk_aes_s* self, void const* msg, int n, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(out);

	switch(self->m_key_len)
	{
		case mk_aes_key_len_128: mk_aes_128_decrypt_blocks(&self->m_aes_128, msg, n, out); break;
		case mk_aes_key_len_192: mk_aes_192_decrypt_blocks(&self->m_aes_192, msg, n, out); break;
		case mk_aes_key_len_256: mk_aes_256_decrypt_blocks(&self->m_aes_256, msg, n, out); break;
	}
}

void mk_aes_decrypt_finish(struct mk_aes_s* self, void const* msg, void* out)
{
	mk_assert(self);
	mk_assert(msg);
	mk_assert(out);

	switch(self->m_key_len)
	{
		case mk_aes_key_len_128: mk_aes_128_decrypt_finish(&self->m_aes_128, msg, out); break;
		case mk_aes_key_len_192: mk_aes_192_decrypt_finish(&self->m_aes_192, msg, out); break;
		case mk_aes_key_len_256: mk_aes_256_decrypt_finish(&self->m_aes_256, msg, out); break;
	}
}


void mk_aes_encrypt_msg(enum mk_aes_key_len_e key_len, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key, void const* msg, size_t msg_len, void* out)
{
	struct mk_aes_s mk_aes;
	int n;
	int m;

	n = msg_len / 16;
	m = msg_len % 16;
	mk_aes_encrypt_init(&mk_aes, key_len, om, padding, iv, key);
	mk_aes_encrypt_blocks(&mk_aes, msg, n, out);
	mk_aes_encrypt_finish(&mk_aes, (unsigned char*)msg + n * 16, m, (unsigned char*)out + n * 16);
}

void mk_aes_decrypt_msg(enum mk_aes_key_len_e key_len, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key, void const* msg, size_t msg_len, void* out)
{
	struct mk_aes_s mk_aes;
	int n;

	n = msg_len / 16;
	mk_assert(msg_len % 16 == 0);
	mk_aes_decrypt_init(&mk_aes, key_len, om, padding, iv, key);
	mk_aes_decrypt_blocks(&mk_aes, msg, n - 1, out);
	mk_aes_decrypt_finish(&mk_aes, (unsigned char*)msg + (n - 1) * 16, (unsigned char*)out + (n - 1) * 16);
}


#undef mk_aes_config_small
#undef mk_aes_config_fast
