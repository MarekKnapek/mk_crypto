#include "mk_crypt_fuzz.h"

#include "mk_crypt_fuzz_inplace_decrypt.h"
#include "mk_crypt_fuzz_inplace_encrypt.h"
#include "mk_crypt_fuzz_piecewise_decrypt.h"
#include "mk_crypt_fuzz_piecewise_encrypt.h"
#include "mk_crypt_fuzz_tom.h"
#include "mk_crypt_fuzz_win.h"
#include "mk_crypt_fuzz_winng.h"


void mk_crypto_fuzz(unsigned char const* data, size_t size)
{
	mk_crypt_fuzz_inplace_decrypt(data, size);
	mk_crypt_fuzz_inplace_encrypt(data, size);
	mk_crypt_fuzz_piecewise_decrypt(data, size);
	mk_crypt_fuzz_piecewise_encrypt(data, size);
	mk_crypto_fuzz_tom(data, size);
	mk_crypto_fuzz_win(data, size);
	mk_crypto_fuzz_winng(data, size);
}
