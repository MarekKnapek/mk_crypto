#include "mk_md4_fuzz.h"

#include "../src/hash/mk_hash_md4.h"
#include "../src/hash/mk_hash_win_md4.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_md4_fuzz_basic(void const* data, int size)
{
	struct mk_win_md4_s win_md4;
	unsigned char win_md4_digest[16];

	struct mk_md4_s md4;
	unsigned char md4_digest[16];

	mk_win_md4_init(&win_md4);
	mk_win_md4_append(&win_md4, data, size);
	mk_win_md4_finish(&win_md4, &win_md4_digest);

	mk_hash_md4_init(&md4);
	mk_hash_md4_append(&md4, data, size);
	mk_hash_md4_finish(&md4, &md4_digest);

	test(memcmp(&md4_digest, &win_md4_digest, sizeof(win_md4_digest)) == 0);
}

static mk_inline void mk_md4_fuzz_complex(unsigned char const* data, int size)
{
	struct mk_win_md4_s win_md4;
	unsigned char win_md4_digest[16];

	struct mk_md4_s md4;
	unsigned char md4_digest[16];

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
	mk_win_md4_init(&win_md4);
	mk_hash_md4_init(&md4);
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
		mk_win_md4_append(&win_md4, data, part_len);
		mk_hash_md4_append(&md4, data, part_len);
		data += part_len;
		size -= part_len;
	}
	mk_win_md4_finish(&win_md4, &win_md4_digest);
	mk_hash_md4_finish(&md4, &md4_digest);
	test(memcmp(&md4_digest, &win_md4_digest, sizeof(win_md4_digest)) == 0);
}


void mk_md4_fuzz(unsigned char const* data, int size)
{
	mk_md4_fuzz_basic(data, size);
	mk_md4_fuzz_complex(data, size);
}


#undef test
