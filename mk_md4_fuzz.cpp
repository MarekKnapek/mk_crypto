#include "mk_md4.h"
#include "md4.h"

#include <string.h>


extern "C" int LLVMFuzzerTestOneInput(uint8_t const* data, size_t size)
{
	mk_md4_state_s mk_md4_state;
	mk_md4_digest_s mk_md4_digest;

	mk_md4_init(&mk_md4_state);
	mk_md4_append(&mk_md4_state, data, size);
	mk_md4_finish(&mk_md4_state, &mk_md4_digest);

	MD4_CTX md4_state;
	unsigned char md4_digest[16];

	MD4Init(&md4_state);
	MD4Update(&md4_state, (unsigned char*)data, (unsigned int)size);
	MD4Final(md4_digest, &md4_state);

	if(memcmp(mk_md4_digest.m_data.m_bytes, md4_digest, 16) != 0)
	{
		//int volatile* volatile ptr = NULL;
		//*ptr = 0;
		__debugbreak();
	}

	return 0;
}
