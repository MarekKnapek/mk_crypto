#include "mk_fuzz_hash.h"

#include "../src/mk_hash.h"
#include "../src/mk_hash_function.h"
#include "../win/mk_win_hash.h"

#include "../src/utils/mk_assert.h"
#include "../src/utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline void mk_fuzz_hash_simple(unsigned char const* data, int size)
{
	static enum mk_hash_e const hashes1[] =
	{
		mk_hash_e_md2,
		mk_hash_e_md4,
		mk_hash_e_md5,
		mk_hash_e_sha1,
		mk_hash_e_sha2_256,
		mk_hash_e_sha2_384,
		mk_hash_e_sha2_512,
	};
	static enum mk_win_hash_e const hashes2[] =
	{
		mk_win_hash_e_md2,
		mk_win_hash_e_md4,
		mk_win_hash_e_md5,
		mk_win_hash_e_sha1,
		mk_win_hash_e_sha2_256,
		mk_win_hash_e_sha2_384,
		mk_win_hash_e_sha2_512,
	};

	int n;
	int i;
	mk_hash_function_h hasher1;
	mk_win_hash_h hasher2;
	unsigned char digest1[512 / 8];
	unsigned char digest2[512 / 8];

	mk_assert(sizeof(hashes1) == sizeof(hashes2));
	mk_assert(sizeof(digest1) == sizeof(digest2));
	n = sizeof(hashes1) / sizeof(hashes1[0]);
	for(i = 0; i != n; ++i)
	{
		mk_assert(sizeof(digest1) >= mk_hash_get_digest_len(hashes1[i]));

		hasher1 = mk_hash_function_create(hashes1[i]);
		test(mk_hash_function_is_good(hasher1));
		mk_hash_function_append(hasher1, data, size);
		mk_hash_function_finish(hasher1, digest1);
		mk_hash_function_destroy(hasher1);

		mk_win_hash_init(&hasher2, hashes2[i]);
		mk_win_hash_append(hasher2, data, size);
		mk_win_hash_finish(hasher2, digest2);

		test(memcmp(digest1, digest2, mk_hash_get_digest_len(hashes1[i])) == 0);
	}
}

static mk_inline void mk_fuzz_hash_complex(unsigned char const* data, int size)
{
	static enum mk_hash_e const hashes1[] =
	{
		mk_hash_e_md2,
		mk_hash_e_md4,
		mk_hash_e_md5,
		mk_hash_e_sha1,
		mk_hash_e_sha2_256,
		mk_hash_e_sha2_384,
		mk_hash_e_sha2_512,
	};
	static enum mk_win_hash_e const hashes2[] =
	{
		mk_win_hash_e_md2,
		mk_win_hash_e_md4,
		mk_win_hash_e_md5,
		mk_win_hash_e_sha1,
		mk_win_hash_e_sha2_256,
		mk_win_hash_e_sha2_384,
		mk_win_hash_e_sha2_512,
	};

	int n;
	int i;
	unsigned char const* dt;
	int sz;
	int nparts;
	int ipart;
	mk_hash_function_h hasher1;
	mk_win_hash_h hasher2;
	int part_len;
	unsigned char digest1[512 / 8];
	unsigned char digest2[512 / 8];

	mk_assert(sizeof(hashes1) == sizeof(hashes2));
	mk_assert(sizeof(digest1) == sizeof(digest2));
	n = sizeof(hashes1) / sizeof(hashes1[0]);
	for(i = 0; i != n; ++i)
	{
		dt = data;
		sz = size;

		mk_assert(sizeof(digest1) >= mk_hash_get_digest_len(hashes1[i]));

		hasher1 = mk_hash_function_create(hashes1[i]);
		test(mk_hash_function_is_good(hasher1));
		mk_win_hash_init(&hasher2, hashes2[i]);

		if(!(sz >= 1))
		{
			break;
		}
		nparts = *dt;
		dt++;
		sz--;
		for(ipart = 0; ipart != nparts; ++ipart)
		{
			if(!(sz >= 1))
			{
				break;
			}
			part_len = *dt;
			dt++;
			sz--;
			if(!(sz >= part_len))
			{
				break;
			}

			mk_hash_function_append(hasher1, dt, part_len);
			mk_win_hash_append(hasher2, dt, part_len);
			dt += part_len;
			sz -= part_len;
		}

		mk_hash_function_finish(hasher1, digest1);
		mk_hash_function_destroy(hasher1);
		mk_win_hash_finish(hasher2, digest2);

		test(memcmp(digest1, digest2, mk_hash_get_digest_len(hashes1[i])) == 0);
	}
}


void mk_fuzz_hash(unsigned char const* data, int size)
{
	mk_fuzz_hash_simple(data, size);
	mk_fuzz_hash_complex(data, size);
}


#undef test
