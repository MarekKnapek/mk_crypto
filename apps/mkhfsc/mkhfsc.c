#include "../../src/mk_hash.h"
#include "../../src/mk_hash_function.h"
#include "../../src/utils/mk_assert.h"
#include "../../src/utils/mk_try.h"

#include <string.h> /* strlen */
#include <stddef.h> /* size_t */
#include <stdio.h> /* fopen fread fclose sprintf printf */

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4701) /* warning C4701: potentially uninitialized local variable 'xxx' used */
#endif


static enum mk_hash_e const hashes[] =
{
	mk_hash_md2,
	mk_hash_md4,
	mk_hash_md5,
	mk_hash_sha1,
	mk_hash_sha2_224,
	mk_hash_sha2_256,
	mk_hash_sha2_384,
	mk_hash_sha2_512,
	mk_hash_sha2_512224,
	mk_hash_sha2_512256,
	mk_hash_sha3_224,
	mk_hash_sha3_256,
	mk_hash_sha3_384,
	mk_hash_sha3_512,
};
static int const nhashses = sizeof(hashes) / sizeof(hashes[0]);


static mk_inline int mkhfsc_help(void)
{
	int i;

	printf("mkhfsc by Marek Knapek https://github.com/MarekKnapek\n");
	printf("Usage: mkhfsc <hash> <file>\n");
	printf("Example: mkhfsc MD5 explorer.exe\n");
	printf("Example: mkhfsc SHA-1 explorer.exe\n");
	printf("Example: mkhfsc SHA-512 explorer.exe\n");
	printf("Example: mkhfsc SHA3-512 explorer.exe\n");
	printf("Possible hashes are: ");
	for(i = 0; i != nhashses; ++i)
	{
		printf("%s ", mk_hash_get_name(hashes[i]));
	}
	printf("\n");
	return 0;
}

static mk_inline int mkhfsc_bussiness(int argc, char const* const* argv)
{
	char const* hash_name;
	int hash_name_len;
	int i;
	enum mk_hash_e h;
	char const* hn;
	int hnl;
	mk_hash_function_h hf;
	char const* file_name;
	FILE* file;
	size_t read;
	unsigned char buff[512];
	int closed;
	int digest_len;
	unsigned char digest[64];
	char digest_str[64 * 2 + 1];
	int sprinted;
	int printed;

	mk_check(argc == 3);
	hash_name = argv[1];
	mk_check(hash_name);
	hash_name_len = (int)strlen(hash_name);
	for(i = 0; i != nhashses; ++i)
	{
		h = hashes[i];
		hn = mk_hash_get_name(h);
		hnl = mk_hash_get_name_len(h);
		if(hash_name_len == hnl && memcmp(hash_name, hn, hnl) == 0)
		{
			break;
		}
	}
	mk_check(i != nhashses);
	hf = mk_hash_function_create((enum mk_hash_function_e)h);
	mk_check(mk_hash_function_is_good(hf));
	file_name = argv[2];
	file = fopen(file_name, "rb");
	mk_check(file);
	for(;;)
	{
		read = fread(buff, 1, sizeof(buff), file);
		if(read == 0)
		{
			break;
		}
		mk_hash_function_append(hf, buff, (int)read);
	}
	closed = fclose(file);
	mk_check(closed == 0);
	digest_len = mk_hash_get_digest_len(h);
	mk_assert((int)sizeof(digest) >= digest_len);
	mk_assert((int)sizeof(digest_str) >= digest_len * 2 + 1);
	mk_hash_function_finish(hf, digest);
	mk_hash_function_destroy(hf);
	for(i = 0; i != digest_len; ++i)
	{
		sprinted = sprintf(digest_str + i * 2, "%02x", (unsigned)(digest[i]));
		mk_check(sprinted == 2);
	}
	printed = printf("%s\n", digest_str);
	mk_check(printed >= digest_len * 2 + 1);

	return 0;
}

static mk_inline int mkhfsc(int argc, char const* const* argv)
{
	if(argc == 1)
	{
		return mkhfsc_help();
	}
	else
	{
		return mkhfsc_bussiness(argc, argv);
	}
}


int main(int argc, char const** argv)
{
	return mkhfsc(argc, argv);
}


#ifdef _MSC_VER
#pragma warning(pop)
#endif
