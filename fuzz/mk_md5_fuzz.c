#include "mk_md5_fuzz.h"

#include "../src/hash/mk_hash_md5.h"
#include "../src/hash/mk_win_md5.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_md5_fuzz_basic(void const* data, int size)
{
	struct mk_win_md5_s win_md5;
	unsigned char win_md5_digest[16];

	struct mk_md5_s md5;
	unsigned char md5_digest[16];

	mk_win_md5_init(&win_md5);
	mk_win_md5_append(&win_md5, data, size);
	mk_win_md5_finish(&win_md5, &win_md5_digest);

	mk_hash_md5_init(&md5);
	mk_hash_md5_append(&md5, data, size);
	mk_hash_md5_finish(&md5, &md5_digest);

	test(memcmp(&md5_digest, &win_md5_digest, sizeof(win_md5_digest)) == 0);
}

static mk_inline void mk_md5_fuzz_complex(unsigned char const* data, int size)
{
	struct mk_win_md5_s win_md5;
	unsigned char win_md5_digest[16];

	struct mk_md5_s md5;
	unsigned char md5_digest[16];

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
	mk_win_md5_init(&win_md5);
	mk_hash_md5_init(&md5);
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
		mk_win_md5_append(&win_md5, data, part_len);
		mk_hash_md5_append(&md5, data, part_len);
		data += part_len;
		size -= part_len;
	}
	mk_win_md5_finish(&win_md5, &win_md5_digest);
	mk_hash_md5_finish(&md5, &md5_digest);
	test(memcmp(&md5_digest, &win_md5_digest, sizeof(win_md5_digest)) == 0);
}


void mk_md5_fuzz(unsigned char const* data, int size)
{
	mk_md5_fuzz_basic(data, size);
	mk_md5_fuzz_complex(data, size);
}


#undef test
