#include "mk_sha2_384_fuzz.h"

#include "../src/hash/mk_sha2_384.h"
#include "../src/hash/mk_win_sha2_384.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_sha2_384_fuzz_basic(unsigned char const* data, size_t size)
{
	struct mk_win_sha2_384_state_s mk_win_sha2_384_state;
	unsigned char mk_win_sha2_384_digest[48];

	struct mk_sha2_384_state_s mk_sha2_384_state;
	unsigned char mk_sha2_384_digest[48];

	mk_win_sha2_384_init(&mk_win_sha2_384_state);
	mk_win_sha2_384_append(&mk_win_sha2_384_state, data, size);
	mk_win_sha2_384_finish(&mk_win_sha2_384_state, &mk_win_sha2_384_digest);

	mk_sha2_384_init(&mk_sha2_384_state);
	mk_sha2_384_append(&mk_sha2_384_state, data, size);
	mk_sha2_384_finish(&mk_sha2_384_state, &mk_sha2_384_digest);

	test(memcmp(&mk_sha2_384_digest, &mk_win_sha2_384_digest, sizeof(mk_win_sha2_384_digest)) == 0);
}

static mk_inline void mk_sha2_384_fuzz_complex(unsigned char const* data, size_t size)
{
	struct mk_win_sha2_384_state_s mk_win_sha2_384_state;
	unsigned char mk_win_sha2_384_digest[48];

	struct mk_sha2_384_state_s mk_sha2_384_state;
	unsigned char mk_sha2_384_digest[48];

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
	mk_win_sha2_384_init(&mk_win_sha2_384_state);
	mk_sha2_384_init(&mk_sha2_384_state);
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
		mk_win_sha2_384_append(&mk_win_sha2_384_state, data, part_len);
		mk_sha2_384_append(&mk_sha2_384_state, data, part_len);
		data += part_len;
		size -= part_len;
	}
	mk_win_sha2_384_finish(&mk_win_sha2_384_state, &mk_win_sha2_384_digest);
	mk_sha2_384_finish(&mk_sha2_384_state, &mk_sha2_384_digest);
	test(memcmp(&mk_sha2_384_digest, &mk_win_sha2_384_digest, sizeof(mk_win_sha2_384_digest)) == 0);
}


void mk_sha2_384_fuzz(unsigned char const* data, size_t size)
{
	mk_sha2_384_fuzz_basic(data, size);
	mk_sha2_384_fuzz_complex(data, size);
}


#undef test
