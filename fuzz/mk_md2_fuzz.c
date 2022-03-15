#include "mk_md2_fuzz.h"

#include "../src/mk_md2.h"
#include "../src/mk_win_md2.h"

#include <stddef.h> /* size_t NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


void mk_md2_fuzz(unsigned char const* data, size_t size)
{
	struct mk_win_md2_state_s mk_win_md2_state;
	unsigned char mk_win_md2_digest[16];

	struct mk_md2_state_s mk_md2_state;
	unsigned char mk_md2_digest[16];

	mk_win_md2_init(&mk_win_md2_state);
	mk_win_md2_append(&mk_win_md2_state, data, size);
	mk_win_md2_finish(&mk_win_md2_state, &mk_win_md2_digest);

	mk_md2_init(&mk_md2_state);
	mk_md2_append(&mk_md2_state, data, size);
	mk_md2_finish(&mk_md2_state, &mk_md2_digest);

	test(memcmp(&mk_md2_digest, &mk_win_md2_digest, 16) == 0);
}


#undef test
