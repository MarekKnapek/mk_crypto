#include "mk_md4_fuzz.h"

#include "../src/mk_md4.h"
#include "../src/mk_win_md4.h"

#include "../utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_md4_fuzz_basic(unsigned char const* data, size_t size)
{
	struct mk_win_md4_state_s mk_win_md4_state;
	unsigned char mk_win_md4_digest[16];

	struct mk_md4_state_s mk_md4_state;
	unsigned char mk_md4_digest[16];

	mk_win_md4_init(&mk_win_md4_state);
	mk_win_md4_append(&mk_win_md4_state, data, size);
	mk_win_md4_finish(&mk_win_md4_state, &mk_win_md4_digest);

	mk_md4_init(&mk_md4_state);
	mk_md4_append(&mk_md4_state, data, size);
	mk_md4_finish(&mk_md4_state, &mk_md4_digest);

	test(memcmp(&mk_md4_digest, &mk_win_md4_digest, sizeof(mk_win_md4_digest)) == 0);
}

static mk_inline void mk_md4_fuzz_complex(unsigned char const* data, size_t size)
{
	struct mk_win_md4_state_s mk_win_md4_state;
	unsigned char mk_win_md4_digest[16];

	struct mk_md4_state_s mk_md4_state;
	unsigned char mk_md4_digest[16];

	unsigned parts;
	unsigned i;
	unsigned part_len;

	if(size < 2)
	{
		return;
	}
	parts = ((unsigned)(data[0]) << CHAR_BIT) | ((unsigned)(data[1]));
	data += 2;
	size -= 2;
	mk_win_md4_init(&mk_win_md4_state);
	mk_md4_init(&mk_md4_state);
	for(i = 0; i != parts; ++i)
	{
		if(size < 2)
		{
			mk_win_md4_finish(&mk_win_md4_state, &mk_win_md4_digest);
			mk_md4_finish(&mk_md4_state, &mk_md4_digest);
			test(memcmp(&mk_md4_digest, &mk_win_md4_digest, sizeof(mk_win_md4_digest)) == 0);
			return;
		}
		part_len = ((unsigned)(data[0]) << CHAR_BIT) | ((unsigned)(data[1]));
		data += 2;
		size -= 2;
		if(size < part_len)
		{
			mk_win_md4_finish(&mk_win_md4_state, &mk_win_md4_digest);
			mk_md4_finish(&mk_md4_state, &mk_md4_digest);
			test(memcmp(&mk_md4_digest, &mk_win_md4_digest, sizeof(mk_win_md4_digest)) == 0);
			return;
		}
		mk_win_md4_append(&mk_win_md4_state, data, part_len);
		mk_md4_append(&mk_md4_state, data, part_len);
		data += part_len;
		size -= part_len;
	}
	mk_win_md4_finish(&mk_win_md4_state, &mk_win_md4_digest);
	mk_md4_finish(&mk_md4_state, &mk_md4_digest);
	test(memcmp(&mk_md4_digest, &mk_win_md4_digest, sizeof(mk_win_md4_digest)) == 0);
}


void mk_md4_fuzz(unsigned char const* data, size_t size)
{
	mk_md4_fuzz_basic(data, size);
	mk_md4_fuzz_complex(data, size);
}


#undef test
