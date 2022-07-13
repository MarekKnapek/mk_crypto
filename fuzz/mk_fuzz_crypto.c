#include "mk_fuzz_hash.h"
#include "mk_fuzz_mac_hmac.h"
#include "mk_fuzz_kdf_pbkdf2.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* size_t */


static mk_inline void mk_fuzz(unsigned char const* data, int size)
{
	mk_fuzz_hash(data, size);
	mk_fuzz_mac_hmac(data, size);
	mk_fuzz_kdf_pbkdf2(data, size);
}

int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size)
{
	mk_fuzz(data, (int)size);
	return 0;
}
