#include "mk_kdf_pbkdf2_fuzz.h"

#include "../src/kdf/mk_kdf_pbkdf2.h"
#include "../win/mk_win_kdf_pbkdf2.h"

#include "../src/utils/mk_assert.h"
#include "../src/utils/mk_inline.h"

#include <stddef.h> /* NULL */
#include <string.h> /* memcmp */


static mk_inline int mk_kdf_pbkdf2_fuzz_data_gud(unsigned char const* data, int size, int* len1_out, int* len2_out, unsigned char const** data1_out, unsigned char const** data2_out, long* len3_out, int* len4_out)
{
	int len1;
	int len2;
	unsigned char const* data1;
	unsigned char const* data2;
	long len3;
	int len4;

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

	check(size >= 1);
	len3 = *data;
	check(len3 > 0);
	++data;
	--size;

	check(size >= 1);
	len4 = *data;
	check(len4 > 0);
	++data;
	--size;

	check(size == 0);

	#undef check

	*len1_out = len1;
	*len2_out = len2;
	*data1_out = data1;
	*data2_out = data2;
	*len3_out = len3;
	*len4_out = len4;
	return 1;
}


void mk_kdf_pbkdf2_fuzz(unsigned char const* data, int size)
{
	static enum mk_kdf_pbkdf2_e const s_algs1[] =
	{
		mk_kdf_pbkdf2_e_md2,
		mk_kdf_pbkdf2_e_md4,
		mk_kdf_pbkdf2_e_md5,
		mk_kdf_pbkdf2_e_sha1,
		mk_kdf_pbkdf2_e_sha2_256,
		mk_kdf_pbkdf2_e_sha2_384,
		mk_kdf_pbkdf2_e_sha2_512
	};
	static enum mk_win_kdf_pbkdf2_e const s_algs2[] =
	{
		mk_win_kdf_pbkdf2_e_md2,
		mk_win_kdf_pbkdf2_e_md4,
		mk_win_kdf_pbkdf2_e_md5,
		mk_win_kdf_pbkdf2_e_sha1,
		mk_win_kdf_pbkdf2_e_sha2_256,
		mk_win_kdf_pbkdf2_e_sha2_384,
		mk_win_kdf_pbkdf2_e_sha2_512
	};

	int len1;
	int len2;
	unsigned char const* data1;
	unsigned char const* data2;
	long iterations;
	int key_len;
	int i;
	unsigned char key1[256];
	unsigned char key2[256];

	if(!mk_kdf_pbkdf2_fuzz_data_gud(data, size, &len1, &len2, &data1, &data2, &iterations, &key_len))
	{
		return;
	}
	for(i = 0; i != (int)(sizeof(s_algs2) / sizeof(s_algs2[i])); ++i)
	{
		mk_kdf_pbkdf2(s_algs1[i], data1, len1, data2, len2, iterations, key_len, key1);
		mk_win_kdf_pbkdf2(s_algs2[i], data1, len1, data2, len2, iterations, key_len, key2);
		if((memcmp(key1, key2, key_len) != 0))
		{
			int volatile* volatile ptr = NULL;
			*ptr = 0;
		}
	}
}
