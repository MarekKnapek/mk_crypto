#include "../mk_hash_file_lib/mk_hash_file.h"

#include "../../src/utils/mk_assert.h"
#include "../../src/utils/mk_inline.h"

#include <stddef.h> /* offsetof */
#include <stdio.h> /* printf fprintf stderr fflush */
#include <stdlib.h> /* EXIT_SUCCESS malloc free */
#include <string.h> /* memcpy */


#ifdef NDEBUG
#define mk_check(x) do{ if(!(x)){ return 1; } }while(0)
#else
#define mk_check(x) do{ if(!(x)){ return (int)__LINE__; } }while(0)
#endif
#define mk_try(x) do{ int err_ = (x); if(err_ != 0){ return err_; } }while(0)


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

static mk_inline int mk_hash_file_c_text_create(char** text, struct mk_hash_file_digests_s const* digests)
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
	
	static struct alg_descr_s const s_alg_descriptions[] =
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

	mk_assert(text);
	mk_assert(digests);

	alg_count = sizeof(s_alg_descriptions) / sizeof(s_alg_descriptions[0]);
	longest_name = 0;
	for(i = 0; i != alg_count; ++i)
	{
		longest_name = s_alg_descriptions[i].m_name_len > longest_name ? s_alg_descriptions[i].m_name_len : longest_name;
	}

	string_len = 0;
	string_len += alg_count * (longest_name + 2);
	for(i = 0; i != alg_count; ++i)
	{
		string_len += s_alg_descriptions[i].m_digest_len * 2;
	}

	string = (char*)malloc(string_len);
	mk_check(string);

	ptr = string;
	for(i = 0; i != alg_count; ++i)
	{
		memcpy(ptr, s_alg_descriptions[i].m_name, s_alg_descriptions[i].m_name_len);
		ptr += s_alg_descriptions[i].m_name_len;
		for(j = 0; j != longest_name - s_alg_descriptions[i].m_name_len + 1; ++j)
		{
			*ptr = ' ';
			++ptr;
		}
		mk_bytes_to_string((unsigned char const*)digests + s_alg_descriptions[i].m_digest_offset, s_alg_descriptions[i].m_digest_len, ptr);
		ptr += s_alg_descriptions[i].m_digest_len * 2;
		*ptr = '\n';
		++ptr;
	}
	--ptr;
	*ptr = '\0';

	*text = string;
	return 0;
}

static mk_inline int mk_hash_file_c_text_destroy(char* text)
{
	mk_assert(text);
	
	free(text);
	
	return 0;
}

static mk_inline int mk_hash_file_c_process(mk_hash_file_handle hf)
{
	static char const s_progress[] = "....................";

	int progress_last;
	int progress_curr;
	int progress_delta;

	mk_assert(hf);

	progress_last = 0;
	do
	{
		mk_try(mk_hash_file_step(hf));
		progress_curr = mk_hash_file_get_progress(hf);
		mk_assert(progress_curr >= progress_last);
		progress_delta = progress_curr - progress_last;
		progress_delta /= 500;
		if(progress_delta != 0)
		{
			fprintf(stderr, "%.*s", progress_delta, s_progress);
			mk_check(fflush(stderr) == 0);
			progress_last = progress_curr;
		}
	}while(mk_hash_file_is_done(hf) == 0);
	fprintf(stderr, "\n");
	mk_check(fflush(stderr) == 0);
	return 0;
}

static mk_inline int mk_hash_file_c(int argc, char const* const* argv)
{
	char const* file_name;
	mk_hash_file_handle hf;
	struct mk_hash_file_digests_s* digests;
	char* text;

	mk_check(argc == 2);

	file_name = argv[1];
	mk_try(mk_hash_file_create(&hf, file_name));
	mk_try(mk_hash_file_c_process(hf));
	mk_try(mk_hash_file_get_result(hf, &digests));
	mk_try(mk_hash_file_c_text_create(&text, digests));
	printf("%s\n", text);
	mk_try(mk_hash_file_c_text_destroy(text));
	mk_try(mk_hash_file_destroy(hf));
	return 0;
}


int main(int argc, char const* const* argv)
{
	int err = mk_hash_file_c(argc, argv);
	if(err != 0)
	{
		fprintf(stderr, "Failed!\n");
		mk_check(fflush(stderr) == 0);
		return err;
	}
	return EXIT_SUCCESS;
}


#undef mk_check
#undef mk_try
