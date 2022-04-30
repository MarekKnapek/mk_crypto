#include "mk_aes_fuzz.h"
#include "mk_crypt_fuzz.h"
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



#include "../src/hw/mk_cpuid.h"


int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size)
{
	struct mk_cpuid_registers_s registers;
	mk_cpuid(0, &registers);
	if(registers.m_eax >= 1)
	{
		mk_cpuid(1, &registers);
		if
		(
			((registers.m_ecx & (1u <<  1)) != 0) &&
			((registers.m_ecx & (1u << 25)) != 0)
		)
		{
		}
	}

	mk_crypto_fuzz(data, size);
	//mk_aes_fuzz(data, size);
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
