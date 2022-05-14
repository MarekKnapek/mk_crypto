#include "mk_sha2_256_fuzz.h"

#include "../src/hash/mk_sha2_256.h"
#include "../src/hash/mk_win_sha2_256.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_sha2_256_fuzz_basic(void const* data, int size)
{
	struct mk_win_sha2_256_state_s mk_win_sha2_256_state;
	unsigned char mk_win_sha2_256_digest[32];

	struct mk_sha2_256_s mk_sha2_256_state;
	unsigned char mk_sha2_256_digest[32];

	mk_win_sha2_256_init(&mk_win_sha2_256_state);
	mk_win_sha2_256_append(&mk_win_sha2_256_state, data, size);
	mk_win_sha2_256_finish(&mk_win_sha2_256_state, &mk_win_sha2_256_digest);

	mk_sha2_256_init(&mk_sha2_256_state);
	mk_sha2_256_append(&mk_sha2_256_state, data, size);
	mk_sha2_256_finish(&mk_sha2_256_state, &mk_sha2_256_digest);

	test(memcmp(&mk_sha2_256_digest, &mk_win_sha2_256_digest, sizeof(mk_win_sha2_256_digest)) == 0);
}

static mk_inline void mk_sha2_256_fuzz_complex(unsigned char const* data, int size)
{
	struct mk_win_sha2_256_state_s mk_win_sha2_256_state;
	unsigned char mk_win_sha2_256_digest[32];

	struct mk_sha2_256_s mk_sha2_256_state;
	unsigned char mk_sha2_256_digest[32];

	int parts;
	int i;
	int part_len;

	if(!(size >= 1))
	{
		return;
	}
	parts = *data;
	data++;
	size--;
	mk_win_sha2_256_init(&mk_win_sha2_256_state);
	mk_sha2_256_init(&mk_sha2_256_state);
	for(i = 0; i != parts; ++i)
	{
		if(!(size >= 1))
		{
			break;
		}
		part_len = *data;
		data++;
		size--;
		if(!(size >= part_len))
		{
			break;
		}
		mk_win_sha2_256_append(&mk_win_sha2_256_state, data, part_len);
		mk_sha2_256_append(&mk_sha2_256_state, data, part_len);
		data += part_len;
		size -= part_len;
	}
	mk_win_sha2_256_finish(&mk_win_sha2_256_state, &mk_win_sha2_256_digest);
	mk_sha2_256_finish(&mk_sha2_256_state, &mk_sha2_256_digest);
	test(memcmp(&mk_sha2_256_digest, &mk_win_sha2_256_digest, sizeof(mk_win_sha2_256_digest)) == 0);
}


void mk_sha2_256_fuzz(unsigned char const* data, int size)
{
	mk_sha2_256_fuzz_basic(data, size);
	mk_sha2_256_fuzz_complex(data, size);
}


#undef test
