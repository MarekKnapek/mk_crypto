#include "mk_md2_fuzz.h"

#include "../src/hash/mk_hash_md2.h"
#include "../src/hash/mk_win_md2.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_md2_fuzz_basic(void const* data, int size)
{
	struct mk_win_md2_s win_md2;
	unsigned char win_md2_digest[16];

	struct mk_md2_s md2;
	unsigned char md2_digest[16];

	mk_win_md2_init(&win_md2);
	mk_win_md2_append(&win_md2, data, size);
	mk_win_md2_finish(&win_md2, &win_md2_digest);

	mk_hash_md2_init(&md2);
	mk_hash_md2_append(&md2, data, size);
	mk_hash_md2_finish(&md2, &md2_digest);

	test(memcmp(&md2_digest, &win_md2_digest, sizeof(win_md2_digest)) == 0);
}

static mk_inline void mk_md2_fuzz_complex(unsigned char const* data, int size)
{
	struct mk_win_md2_s win_md2;
	unsigned char win_md2_digest[16];

	struct mk_md2_s md2;
	unsigned char md2_digest[16];

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
	mk_win_md2_init(&win_md2);
	mk_hash_md2_init(&md2);
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
		mk_win_md2_append(&win_md2, data, part_len);
		mk_hash_md2_append(&md2, data, part_len);
		data += part_len;
		size -= part_len;
	}
	mk_win_md2_finish(&win_md2, &win_md2_digest);
	mk_hash_md2_finish(&md2, &md2_digest);
	test(memcmp(&md2_digest, &win_md2_digest, sizeof(win_md2_digest)) == 0);
}


void mk_md2_fuzz(unsigned char const* data, int size)
{
	mk_md2_fuzz_basic(data, size);
	mk_md2_fuzz_complex(data, size);
}


#undef test
