#include "mk_fuzz_mac_hmac.h"

#include "../src/mac/mk_mac_hmac.h"
#include "../src/mac/mk_mac_hmac_obj.h"
#include "../win/mk_win_mac_hmac.h"

#include "../src/utils/mk_assert.h"
#include "../src/utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcmp */


static enum mk_hash_e const s_algs1[] =
{
	mk_hash_e_md2,
	mk_hash_e_md4,
	mk_hash_e_md5,
	mk_hash_e_sha1,
	mk_hash_e_sha2_256,
	mk_hash_e_sha2_384,
	mk_hash_e_sha2_512,
};

static enum mk_hash_e const s_algs2[] =
{
	mk_hash_e_md2,
	mk_hash_e_md4,
	mk_hash_e_md5,
	mk_hash_e_sha1,
	mk_hash_e_sha2_256,
	mk_hash_e_sha2_384,
	mk_hash_e_sha2_512,
};

static enum mk_win_mac_hmac_e const s_algs3[] =
{
	mk_win_mac_hmac_e_md2,
	mk_win_mac_hmac_e_md4,
	mk_win_mac_hmac_e_md5,
	mk_win_mac_hmac_e_sha1,
	mk_win_mac_hmac_e_sha2_256,
	mk_win_mac_hmac_e_sha2_384,
	mk_win_mac_hmac_e_sha2_512,
};

static int const s_digest_lens[] =
{
	mk_hash_base_hash_md2_digest_len,
	mk_hash_base_hash_md4_digest_len,
	mk_hash_base_hash_md5_digest_len,
	mk_hash_base_hash_sha1_digest_len,
	mk_hash_base_hash_sha2_256_digest_len,
	mk_hash_base_hash_sha2_384_digest_len,
	mk_hash_base_hash_sha2_512_digest_len,
};


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static mk_inline int mk_fuzz_mac_hmac_data_gud(unsigned char const* data, int size, int* len1_out, int* len2_out, unsigned char const** data1_out, unsigned char const** data2_out)
{
	int len1;
	int len2;
	unsigned char const* data1;
	unsigned char const* data2;

	mk_assert(len1_out);
	mk_assert(len2_out);
	mk_assert(data1_out);
	mk_assert(data2_out);

	#define check(x) do{ if(!(x)) return 0; }while(0)

	check(data && size != 0);

	check(size >= 1);
	len1 = *data;
	check(len1 != 0 && len1 != 1);
	++data;
	--size;

	check(size >= 1);
	len2 = *data;
	++data;
	--size;

	check(size >= len1);
	data1 = data;
	data += len1;
	size -= len1;

	check(size >= len2);
	data2 = data;
	data += len2;
	size -= len2;

	check(size == 0);

	#undef check

	*len1_out = len1;
	*len2_out = len2;
	*data1_out = data1;
	*data2_out = data2;
	return 1;
}


void mk_fuzz_mac_hmac(unsigned char const* data, int size)
{
	int len1;
	int len2;
	unsigned char const* data1;
	unsigned char const* data2;
	union mk_mac_hmac_pu phmac1;
	union mk_mac_hmac_u hmac1;
	int n;
	int i;
	unsigned char digest1[512 / 8];
	mk_mac_hmac_obj_h hmac2;
	unsigned char digest2[512 / 8];
	mk_win_mac_hmac_h hmac3;
	unsigned char digest3[512 / 8];

	if(!mk_fuzz_mac_hmac_data_gud(data, size, &len1, &len2, &data1, &data2))
	{
		return;
	}
	phmac1.m_u = &hmac1;
	n = (int)(sizeof(s_algs1) / sizeof(s_algs1[0]));
	mk_assert((int)(sizeof(s_algs2) / sizeof(s_algs2[0])) == n);
	mk_assert((int)(sizeof(s_algs3) / sizeof(s_algs3[0])) == n);
	mk_assert((int)(sizeof(s_digest_lens) / sizeof(s_digest_lens[0])) == n);
	for(i = 0; i != n; ++i)
	{
		mk_mac_hmac_init(s_algs1[i], phmac1, data1, len1);
		mk_mac_hmac_append(s_algs1[i], phmac1, data2, len2);
		mk_mac_hmac_finish(s_algs1[i], phmac1, digest1);

		hmac2 = mk_mac_hmac_obj_create(s_algs2[i], data1, len1);
		test(mk_mac_hmac_obj_is_good(hmac2));
		mk_mac_hmac_obj_append(hmac2, data2, len2);
		mk_mac_hmac_obj_finish(hmac2, digest2);
		mk_mac_hmac_obj_destroy(hmac2);

		mk_win_mac_hmac_init(&hmac3, s_algs3[i], data1, len1);
		mk_win_mac_hmac_append(hmac3, data2, len2);
		mk_win_mac_hmac_finish(hmac3, digest3);

		test
		(
			(memcmp(digest1, digest2, s_digest_lens[i]) == 0) &&
			(memcmp(digest1, digest3, s_digest_lens[i]) == 0)
		);
	}
}


#undef test
