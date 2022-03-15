#include "mk_test_utils.h"

#include "../mk_assert.h"

#include <assert.h> /* static_assert */ /* C11 */


int hex_symbol_to_int(char const hs)
{
	static char const s_hex_alphabet_lc[] = "0123456789abcdef";
	static char const s_hex_alphabet_uc[] = "0123456789ABCDEF";

	static_assert(sizeof(s_hex_alphabet_lc) == sizeof(s_hex_alphabet_uc), "");

	int ret = -1;
	for(int i = 0; i != sizeof(s_hex_alphabet_lc) - 1; ++i)
	{
		if(hs == s_hex_alphabet_lc[i])
		{
			ret = i;
			break;
		}
		if(hs == s_hex_alphabet_uc[i])
		{
			ret = i;
			break;
		}
	}
	mk_assert(ret != -1);
	return ret;
}

void hex_string_to_binary(char const* in, int len, void* out)
{
	mk_assert(in);
	mk_assert(out);
	mk_assert(len % 2 == 0);

	unsigned char* output = (unsigned char*)out;
	
	for(int i = 0; i != len / 2; ++i)
	{
		int hi = hex_symbol_to_int(in[2 * i + 0]);
		int lo = hex_symbol_to_int(in[2 * i + 1]);
		output[i] = (unsigned char)((hi << 4) | (lo << 0));
	}
}
