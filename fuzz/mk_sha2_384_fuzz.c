#include "mk_sha2_384_fuzz.h"

#include "../src/hash/mk_hash_sha2_384.h"
#include "../src/hash/mk_hash_win_sha2_384.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_sha2_384_fuzz_basic(void const* data, int size)
{
	struct mk_win_sha2_384_s win_sha2_384;
	unsigned char win_sha2_384_digest[48];

	struct mk_sha2_384_s sha2_384;
	unsigned char sha2_384_digest[48];

	mk_win_sha2_384_init(&win_sha2_384);
	mk_win_sha2_384_append(&win_sha2_384, data, size);
	mk_win_sha2_384_finish(&win_sha2_384, &win_sha2_384_digest);

	mk_hash_sha2_384_init(&sha2_384);
	mk_hash_sha2_384_append(&sha2_384, data, size);
	mk_hash_sha2_384_finish(&sha2_384, &sha2_384_digest);

	test(memcmp(&sha2_384_digest, &win_sha2_384_digest, sizeof(win_sha2_384_digest)) == 0);
}

static mk_inline void mk_sha2_384_fuzz_complex(unsigned char const* data, int size)
{
	struct mk_win_sha2_384_s win_sha2_384;
	unsigned char win_sha2_384_digest[48];

	struct mk_sha2_384_s sha2_384;
	unsigned char sha2_384_digest[48];

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
	mk_win_sha2_384_init(&win_sha2_384);
	mk_hash_sha2_384_init(&sha2_384);
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
		mk_win_sha2_384_append(&win_sha2_384, data, part_len);
		mk_hash_sha2_384_append(&sha2_384, data, part_len);
		data += part_len;
		size -= part_len;
	}
	mk_win_sha2_384_finish(&win_sha2_384, &win_sha2_384_digest);
	mk_hash_sha2_384_finish(&sha2_384, &sha2_384_digest);
	test(memcmp(&sha2_384_digest, &win_sha2_384_digest, sizeof(win_sha2_384_digest)) == 0);
}


void mk_sha2_384_fuzz(unsigned char const* data, int size)
{
	mk_sha2_384_fuzz_basic(data, size);
	mk_sha2_384_fuzz_complex(data, size);
}


#undef test
