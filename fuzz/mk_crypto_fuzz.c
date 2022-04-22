#include "mk_aes_fuzz.h"
#include "mk_md2_fuzz.h"
#include "mk_md4_fuzz.h"
#include "mk_md5_fuzz.h"
#include "mk_sha1_fuzz.h"
#include "mk_sha2_224_fuzz.h"
#include "mk_sha2_256_fuzz.h"
#include "mk_sha2_384_fuzz.h"
#include "mk_sha2_512_fuzz.h"
#include "mk_sha2_512224_fuzz.h"
#include "mk_sha2_512256_fuzz.h"

#include <stddef.h> /* size_t */


int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size)
{
	mk_aes_fuzz(data, size);
	//mk_md2_fuzz(data, size);
	//mk_md4_fuzz(data, size);
	//mk_md5_fuzz(data, size);
	//mk_sha1_fuzz(data, size);
	//mk_sha2_224_fuzz(data, size);
	//mk_sha2_256_fuzz(data, size);
	//mk_sha2_384_fuzz(data, size);
	//mk_sha2_512_fuzz(data, size);
	//mk_sha2_512224_fuzz(data, size);
	//mk_sha2_512256_fuzz(data, size);

	return 0;
}
