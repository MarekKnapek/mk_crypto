#include "mk_md5_fuzz.h"

#include "../src/hash/mk_md5.h"
#include "../src/hash/mk_win_md5.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_md5_fuzz_basic(void const* data, int size)
{
	struct mk_win_md5_state_s mk_win_md5_state;
	unsigned char mk_win_md5_digest[16];

	struct mk_md5_s mk_md5_state;
	unsigned char mk_md5_digest[16];

	mk_win_md5_init(&mk_win_md5_state);
	mk_win_md5_append(&mk_win_md5_state, data, size);
	mk_win_md5_finish(&mk_win_md5_state, &mk_win_md5_digest);

	mk_md5_init(&mk_md5_state);
	mk_md5_append(&mk_md5_state, data, size);
	mk_md5_finish(&mk_md5_state, &mk_md5_digest);

	test(memcmp(&mk_md5_digest, &mk_win_md5_digest, sizeof(mk_win_md5_digest)) == 0);
}

static mk_inline void mk_md5_fuzz_complex(unsigned char const* data, int size)
{
	struct mk_win_md5_state_s mk_win_md5_state;
	unsigned char mk_win_md5_digest[16];

	struct mk_md5_s mk_md5_state;
	unsigned char mk_md5_digest[16];

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
	mk_win_md5_init(&mk_win_md5_state);
	mk_md5_init(&mk_md5_state);
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
		mk_win_md5_append(&mk_win_md5_state, data, part_len);
		mk_md5_append(&mk_md5_state, data, part_len);
		data += part_len;
		size -= part_len;
	}
	mk_win_md5_finish(&mk_win_md5_state, &mk_win_md5_digest);
	mk_md5_finish(&mk_md5_state, &mk_md5_digest);
	test(memcmp(&mk_md5_digest, &mk_win_md5_digest, sizeof(mk_win_md5_digest)) == 0);
}


void mk_md5_fuzz(unsigned char const* data, int size)
{
	mk_md5_fuzz_basic(data, size);
	mk_md5_fuzz_complex(data, size);
}


#undef test
