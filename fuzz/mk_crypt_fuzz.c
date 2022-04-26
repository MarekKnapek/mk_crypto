#include "mk_crypt_fuzz.h"

#include "mk_crypt_fuzz_1.h"
#include "mk_crypt_fuzz_2.h"


void mk_crypto_fuzz(unsigned char const* data, size_t size)
{
	mk_crypto_fuzz_1(data, size);
	mk_crypto_fuzz_2(data, size);
}
