#include "mk_sha1_fuzz.h"

#include "../src/mk_sha1.h"
#include "../src/mk_win_sha1.h"

#include <stddef.h> /* size_t NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


void mk_sha1_fuzz(unsigned char const* data, size_t size)
{
	struct mk_win_sha1_state_s mk_win_sha1_state;
	unsigned char mk_win_sha1_digest[20];

	struct mk_sha1_state_s mk_sha1_state;
	unsigned char mk_sha1_digest[20];

	mk_win_sha1_init(&mk_win_sha1_state);
	mk_win_sha1_append(&mk_win_sha1_state, data, size);
	mk_win_sha1_finish(&mk_win_sha1_state, &mk_win_sha1_digest);

	mk_sha1_init(&mk_sha1_state);
	mk_sha1_append(&mk_sha1_state, data, size);
	mk_sha1_finish(&mk_sha1_state, &mk_sha1_digest);

	test(memcmp(&mk_sha1_digest, &mk_win_sha1_digest, 20) == 0);
}


#undef test
