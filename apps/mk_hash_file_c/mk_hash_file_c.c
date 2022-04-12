#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4464) /* warning C4464: relative include path contains '..' */
#endif

#include "../mk_hash_file_lib/mk_hash_file.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <stddef.h> /* offsetof */
#include <stdio.h> /* printf fprintf stderr fflush */
#include <stdlib.h> /* EXIT_SUCCESS EXIT_FAILURE malloc free */
#include <string.h> /* memcpy */


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err_ = (x); if(err_ != 0){ return err_; } }while(0)


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4710) /* warning C4710: 'xxx': function not inlined */
#pragma warning(disable:4711) /* warning C4711: function 'xxx' selected for automatic inline expansion */
#pragma warning(disable:4820) /* warning C4820: 'xxx': 'xxx' bytes padding added after data member 'xxx' */
#endif


static mk_inline void mk_bytes_to_string(void const* input, int count, void* output)
{
	static char const s_alphabet[] = "0123456789abcdef";

	unsigned char const* in;
	char* out;
	int i;

	mk_assert(input);
	mk_assert(output);

	in = (unsigned char const*)input;
	out = (char*)output;
	for(i = 0; i != count; ++i)
	{
		out[i * 2 + 0] = s_alphabet[(in[i] >> 4) & 0x0f];
		out[i * 2 + 1] = s_alphabet[(in[i] >> 0) & 0x0f];
	}
}

static mk_inline int mk_hash_file_c_make_text(struct mk_hash_file_digests_s const* digests, char** text)
{
	struct alg_descr_s
	{
		char const* m_name;
		int m_name_len;
		int m_digest_len;
		int m_digest_offset;
	};

	static char const s_alg_name_00[] = "MD2";
	static char const s_alg_name_01[] = "MD4";
	static char const s_alg_name_02[] = "MD5";
	static char const s_alg_name_03[] = "SHA-1";
	static char const s_alg_name_04[] = "SHA-224";
	static char const s_alg_name_05[] = "SHA-256";
	static char const s_alg_name_06[] = "SHA-384";
	static char const s_alg_name_07[] = "SHA-512";
	static char const s_alg_name_08[] = "SHA-512/224";
	static char const s_alg_name_09[] = "SHA-512/256";
	static char const s_alg_name_10[] = "SHA3-224";
	static char const s_alg_name_11[] = "SHA3-256";
	static char const s_alg_name_12[] = "SHA3-384";
	static char const s_alg_name_13[] = "SHA3-512";

	static struct alg_descr_s const s_alg_descrs[] =
	{
		{s_alg_name_00, sizeof(s_alg_name_00) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_md2),         offsetof(struct mk_hash_file_digests_s, m_md2)         },
		{s_alg_name_01, sizeof(s_alg_name_01) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_md4),         offsetof(struct mk_hash_file_digests_s, m_md4)         },
		{s_alg_name_02, sizeof(s_alg_name_02) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_md5),         offsetof(struct mk_hash_file_digests_s, m_md5)         },
		{s_alg_name_03, sizeof(s_alg_name_03) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha1),        offsetof(struct mk_hash_file_digests_s, m_sha1)        },
		{s_alg_name_04, sizeof(s_alg_name_04) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_224),    offsetof(struct mk_hash_file_digests_s, m_sha2_224)    },
		{s_alg_name_05, sizeof(s_alg_name_05) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_256),    offsetof(struct mk_hash_file_digests_s, m_sha2_256)    },
		{s_alg_name_06, sizeof(s_alg_name_06) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_384),    offsetof(struct mk_hash_file_digests_s, m_sha2_384)    },
		{s_alg_name_07, sizeof(s_alg_name_07) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_512),    offsetof(struct mk_hash_file_digests_s, m_sha2_512)    },
		{s_alg_name_08, sizeof(s_alg_name_08) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_512224), offsetof(struct mk_hash_file_digests_s, m_sha2_512224) },
		{s_alg_name_09, sizeof(s_alg_name_09) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_512256), offsetof(struct mk_hash_file_digests_s, m_sha2_512256) },
		{s_alg_name_10, sizeof(s_alg_name_10) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_224),    offsetof(struct mk_hash_file_digests_s, m_sha3_224)    },
		{s_alg_name_11, sizeof(s_alg_name_11) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_256),    offsetof(struct mk_hash_file_digests_s, m_sha3_256)    },
		{s_alg_name_12, sizeof(s_alg_name_12) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_384),    offsetof(struct mk_hash_file_digests_s, m_sha3_384)    },
		{s_alg_name_13, sizeof(s_alg_name_13) - 1, sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_512),    offsetof(struct mk_hash_file_digests_s, m_sha3_512)    },
	};

	int alg_count;
	int longest_name;
	int i;
	int string_len;
	char* string;
	char* ptr;
	int j;

	mk_assert(digests);
	mk_assert(text);

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	longest_name = 0;
	for(i = 0; i != alg_count; ++i)
	{
		longest_name = s_alg_descrs[i].m_name_len > longest_name ? s_alg_descrs[i].m_name_len : longest_name;
	}

	string_len = 0;
	string_len += alg_count * (longest_name + 2);
	for(i = 0; i != alg_count; ++i)
	{
		string_len += s_alg_descrs[i].m_digest_len * 2;
	}

	string = malloc(string_len);
	mk_check(string);

	ptr = string;
	for(i = 0; i != alg_count; ++i)
	{
		memcpy(ptr, s_alg_descrs[i].m_name, s_alg_descrs[i].m_name_len);
		ptr += s_alg_descrs[i].m_name_len;
		for(j = 0; j != longest_name - s_alg_descrs[i].m_name_len + 1; ++j)
		{
			*ptr = ' ';
			++ptr;
		}
		mk_bytes_to_string((unsigned char const*)digests + s_alg_descrs[i].m_digest_offset, s_alg_descrs[i].m_digest_len, ptr);
		ptr += s_alg_descrs[i].m_digest_len * 2;
		*ptr = '\n';
		++ptr;
	}
	--ptr;
	*ptr = '\0';

	*text = string;
	return 0;
}

static mk_inline int mk_hash_file_c(int argc, char const* const* argv)
{
	static char const s_progress[] = "....................";

	char const* file_name;
	mk_hash_file_handle hf;
	int progress_last;
	int err;
	int progress_curr;
	int progress_delta;
	struct mk_hash_file_digests_s* digests;
	char* text;

	mk_check(argc == 2);

	file_name = argv[1];
	hf = mk_hash_file_create(file_name);
	mk_check(hf);
	progress_last = 0;
	for(;;)
	{
		err = mk_hash_file_step(hf);
		mk_check(err == 0 || err == 1);
		mk_try(mk_hash_file_get_progress(hf, &progress_curr));
		progress_delta = progress_curr - progress_last;
		progress_delta /= 500;
		if(progress_delta != 0)
		{
			fprintf(stderr, "%.*s", progress_delta, s_progress);
			mk_check(fflush(stderr) == 0);
			progress_last = progress_curr;
		}
		if(err == 1)
		{
			break;
		}
	}
	fprintf(stderr, "\n");
	mk_check(fflush(stderr) == 0);
	mk_try(mk_hash_file_get_result(hf, &digests));
	mk_try(mk_hash_file_c_make_text(digests, &text));
	printf("%s\n", text);
	free(text);
	mk_try(mk_hash_file_destroy(hf));
	return 0;
}


int main(int argc, char const* const* argv)
{
	int err = mk_hash_file_c(argc, argv);
	if(err != 0)
	{
		fprintf(stderr, "Error at line %d.\n", err);
		mk_check(fflush(stderr) == 0);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif


#undef mk_check
#undef mk_try
