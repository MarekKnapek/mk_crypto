#include "mk_md4_fuzz.h"

#include "../src/mk_md4.h"
#include "../src/mk_win_md4.h"

#include <stddef.h> /* size_t NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


void mk_md4_fuzz(unsigned char const* data, size_t size)
{
	struct mk_win_md4_state_s mk_win_md4_state;
	unsigned char mk_win_md4_digest[16];

	struct mk_md4_state_s mk_md4_state;
	unsigned char mk_md4_digest[16];

	mk_win_md4_init(&mk_win_md4_state);
	mk_win_md4_append(&mk_win_md4_state, data, size);
	mk_win_md4_finish(&mk_win_md4_state, &mk_win_md4_digest);

	mk_md4_init(&mk_md4_state);
	mk_md4_append(&mk_md4_state, data, size);
	mk_md4_finish(&mk_md4_state, &mk_md4_digest);

	test(memcmp(&mk_md4_digest, &mk_win_md4_digest, 16) == 0);
}


#undef test
