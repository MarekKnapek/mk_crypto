#include "mk_md2.h"
#include "md2.h"

#include <string.h>


extern "C" int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size)
{
	mk_md2_state_s mk_md2_state;
	mk_md2_digest_s mk_md2_digest;

	mk_md2_init(&mk_md2_state);
	mk_md2_append(&mk_md2_state, data, size);
	mk_md2_finish(&mk_md2_state, &mk_md2_digest);

	MD2_CTX md2_state;
	unsigned char md2_digest[16];

	MD2Init(&md2_state);
	MD2Update(&md2_state, (unsigned char*)data, (unsigned int)size);
	MD2Final(md2_digest, &md2_state);

	if(memcmp(mk_md2_digest.m_data, md2_digest, 16) != 0)
	{
		//int volatile* volatile ptr = NULL;
		//*ptr = 0;
		__debugbreak();
	}

	return 0;
}
