#include "mk_sha1_fuzz.h"

#include "../src/hash/mk_sha1.h"
#include "../src/hash/mk_win_sha1.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_sha1_fuzz_basic(unsigned char const* data, size_t size)
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

	test(memcmp(&mk_sha1_digest, &mk_win_sha1_digest, sizeof(mk_sha1_digest)) == 0);
}

static mk_inline void mk_sha1_fuzz_complex(unsigned char const* data, size_t size)
{
	struct mk_win_sha1_state_s mk_win_sha1_state;
	unsigned char mk_win_sha1_digest[20];

	struct mk_sha1_state_s mk_sha1_state;
	unsigned char mk_sha1_digest[20];

	unsigned parts;
	unsigned i;
	unsigned part_len;

	if(size < 2)
	{
		return;
	}
	parts = (((unsigned)(data[0])) << 8) | ((unsigned)(data[1]));
	data += 2;
	size -= 2;
	mk_win_sha1_init(&mk_win_sha1_state);
	mk_sha1_init(&mk_sha1_state);
	for(i = 0; i != parts; ++i)
	{
		if(size < 2)
		{
			break;
		}
		part_len = (((unsigned)(data[0])) << 8) | ((unsigned)(data[1]));
		data += 2;
		size -= 2;
		if(size < part_len)
		{
			break;
		}
		mk_win_sha1_append(&mk_win_sha1_state, data, part_len);
		mk_sha1_append(&mk_sha1_state, data, part_len);
		data += part_len;
		size -= part_len;
	}
	mk_win_sha1_finish(&mk_win_sha1_state, &mk_win_sha1_digest);
	mk_sha1_finish(&mk_sha1_state, &mk_sha1_digest);
	test(memcmp(&mk_sha1_digest, &mk_win_sha1_digest, sizeof(mk_win_sha1_digest)) == 0);
}


void mk_sha1_fuzz(unsigned char const* data, size_t size)
{
	mk_sha1_fuzz_basic(data, size);
	mk_sha1_fuzz_complex(data, size);
}


#undef test
