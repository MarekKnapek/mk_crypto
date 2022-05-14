#include "mk_test_utils.h"

#include "../src/utils/mk_assert.h"
#include "../src/utils/mk_inline.h"


static mk_inline int mk_hex_symbol_to_int(char const hs)
{
	static char const s_hex_alphabet_lc[] = "0123456789abcdef";
	static char const s_hex_alphabet_uc[] = "0123456789ABCDEF";

	int i;

	mk_assert(sizeof(s_hex_alphabet_lc) == sizeof(s_hex_alphabet_uc));

	for(i = 0; i != sizeof(s_hex_alphabet_lc) - 1; ++i)
	{
		if(hs == s_hex_alphabet_lc[i])
		{
			break;
		}
		if(hs == s_hex_alphabet_uc[i])
		{
			break;
		}
	}
	return i;
}


void mk_string_hex_to_bytes(void const* in, int in_len, void* out, int out_len)
{
	char const* input;
	unsigned char* output;
	int i;
	int hi;
	int lo;

	mk_assert(in || in_len == 0);
	mk_assert(in_len >= 0 && in_len % 2 == 0);
	mk_assert(out || out_len == 0);
	mk_assert(out_len >= 0 && out_len >= in_len / 2);

	input = (char const*)in;
	output = (unsigned char*)out;
	for(i = 0; i != in_len / 2; ++i)
	{
		hi = mk_hex_symbol_to_int(input[2 * i + 0]);
		lo = mk_hex_symbol_to_int(input[2 * i + 1]);
		output[i] = (unsigned char)((hi << 4) | (lo << 0));
	}
}

void mk_string_bin_to_bytes(void const* in, int in_len, void* out, int out_len)
{
	char const* input;
	unsigned char* output;
	int i;
	int byte;
	int bit;

	mk_assert(in || in_len == 0);
	mk_assert(in_len >= 0);
	mk_assert(out || out_len == 0);
	mk_assert(out_len >= 0 && out_len >= (in_len + (8 - 1)) / 8);

	if(in_len == 0)
	{
		return;
	}
	input = (char const*)in;
	output = (unsigned char*)out;
	output[(in_len + (8 - 1)) / 8 - 1] = 0;
	for(i = 0; i != in_len; ++i)
	{
		byte = i / 8;
		bit = i % 8;
		mk_assert(input[i] == '0' || input[i] == '1');
		if(input[i] == '1')
		{
			output[byte] = (output[byte] & ~(1u << bit)) | (unsigned char)(1u << bit);
		}
		else
		{
			output[byte] = (output[byte] & ~(1u << bit));
		}
	}
}
