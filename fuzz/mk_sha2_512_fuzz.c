#include "mk_sha2_512_fuzz.h"

#include "../src/hash/mk_hash_sha2_512.h"
#include "../src/hash/mk_win_sha2_512.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_sha2_512_fuzz_basic(void const* data, int size)
{
	struct mk_win_sha2_512_s win_sha2_512;
	unsigned char win_sha2_512_digest[64];

	struct mk_sha2_512_s sha2_512;
	unsigned char sha2_512_digest[64];

	mk_win_sha2_512_init(&win_sha2_512);
	mk_win_sha2_512_append(&win_sha2_512, data, size);
	mk_win_sha2_512_finish(&win_sha2_512, &win_sha2_512_digest);

	mk_hash_sha2_512_init(&sha2_512);
	mk_hash_sha2_512_append(&sha2_512, data, size);
	mk_hash_sha2_512_finish(&sha2_512, &sha2_512_digest);

	test(memcmp(&sha2_512_digest, &win_sha2_512_digest, sizeof(win_sha2_512_digest)) == 0);
}

static mk_inline void mk_sha2_512_fuzz_complex(unsigned char const* data, int size)
{
	struct mk_win_sha2_512_s win_sha2_512;
	unsigned char win_sha2_512_digest[64];

	struct mk_sha2_512_s sha2_512;
	unsigned char sha2_512_digest[64];

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
	mk_win_sha2_512_init(&win_sha2_512);
	mk_hash_sha2_512_init(&sha2_512);
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
		mk_win_sha2_512_append(&win_sha2_512, data, part_len);
		mk_hash_sha2_512_append(&sha2_512, data, part_len);
		data += part_len;
		size -= part_len;
	}
	mk_win_sha2_512_finish(&win_sha2_512, &win_sha2_512_digest);
	mk_hash_sha2_512_finish(&sha2_512, &sha2_512_digest);
	test(memcmp(&sha2_512_digest, &win_sha2_512_digest, sizeof(win_sha2_512_digest)) == 0);
}


void mk_sha2_512_fuzz(unsigned char const* data, int size)
{
	mk_sha2_512_fuzz_basic(data, size);
	mk_sha2_512_fuzz_complex(data, size);
}


#undef test
