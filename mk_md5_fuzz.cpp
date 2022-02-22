#include "mk_md5.h"
#include "md5.h"

#include <string.h>


extern "C" int LLVMFuzzerTestOneInput(uint8_t const* data, size_t size)
{
	mk_md5_state_s mk_md5_state;
	mk_md5_digest_s mk_md5_digest;

	mk_md5_init(&mk_md5_state);
	mk_md5_append(&mk_md5_state, data, size);
	mk_md5_finish(&mk_md5_state, &mk_md5_digest);

	MD5_CTX md5_state;
	unsigned char md5_digest[16];

	MD5Init(&md5_state);
	MD5Update(&md5_state, (unsigned char*)data, (unsigned int)size);
	MD5Final(md5_digest, &md5_state);

	if(memcmp(mk_md5_digest.m_data.m_bytes, md5_digest, 16) != 0)
	{
		//int volatile* volatile ptr = NULL;
		//*ptr = 0;
		__debugbreak();
	}

	return 0;
}
