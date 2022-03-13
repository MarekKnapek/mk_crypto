#include "mk_sha1.h"
#include "mk_win_sha1.h"

#include <stddef.h> /* size_t */
#include <string.h> /* memcmp */


/*extern "C" int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size)
{
	mk_sha1_state_s mk_sha1_state;
	unsigned char mk_sha1_digest[20];

	mk_sha1_init(&mk_sha1_state);
	mk_sha1_append(&mk_sha1_state, data, size);
	mk_sha1_finish(&mk_sha1_state, &mk_sha1_digest);

	mk_win_sha1_state_s mk_win_sha1_state;
	unsigned char mk_win_sha1_digest[20];

	mk_win_sha1_init(&mk_win_sha1_state);
	mk_win_sha1_append(&mk_win_sha1_state, data, size);
	mk_win_sha1_finish(&mk_win_sha1_state, &mk_win_sha1_digest);

	if(memcmp(mk_sha1_digest, mk_win_sha1_digest, 20) != 0)
	{
		//int volatile* volatile ptr = NULL;
		//*ptr = 0;
		__debugbreak();
	}

	return 0;
}*/
