#include "mk_sha2_additional_test_examples.h"

#include "mk_test_utils.h"

#include "../src/hash/mk_hash_sha2_224.h"

#include "../src/utils/mk_assert.h"

#include <stdlib.h> /* malloc free */
#include <string.h> /* memset memcmp */


/*

https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA2_Additional.pdf

*/


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err_ = (x); if(err_ != 0){ return err_; } }while(0)


int mk_sha2_additional_test_examples_224(void)
{
	static char const s_pattern_0[] = "ff";
	static char const s_pattern_1[] = "e5e09924";
	static char const s_pattern_2[] = "00";
	static char const s_pattern_3[] = "51";
	static char const s_pattern_4[] = "41";
	static char const s_pattern_5[] = "99";
	static char const s_pattern_6[] = "00";
	static char const s_pattern_7[] = "41";
	static char const s_pattern_8[] = "00";
	static char const s_pattern_9[] = "84";

	#define s_repeat_0 1
	#define s_repeat_1 1
	#define s_repeat_2 56
	#define s_repeat_3 1000
	#define s_repeat_4 1000
	#define s_repeat_5 1005
	#define s_repeat_6 1000000
	#define s_repeat_7 0x20000000
	#define s_repeat_8 0x41000000
	#define s_repeat_9 0x6000003f

	static char const s_digest_0[] = "e33f9d75e6ae1369dbabf81b96b4591ae46bba30b591a6b6c62542b5";
	static char const s_digest_1[] = "fd19e74690d291467ce59f077df311638f1c3a46e510d0e49a67062d";
	static char const s_digest_2[] = "5c3e25b69d0ea26f260cfae87e23759e1eca9d1ecc9fbf3c62266804";
	static char const s_digest_3[] = "3706197f66890a41779dc8791670522e136fafa24874685715bd0a8a";
	static char const s_digest_4[] = "a8d0c66b5c6fdfd836eb3c6d04d32dfe66c3b1f168b488bf4c9c66ce";
	static char const s_digest_5[] = "cb00ecd03788bf6c0908401e0eb053ac61f35e7e20a2cfd7bd96d640";
	static char const s_digest_6[] = "3a5d74b68f14f3a4b2be9289b8d370672d0b3d2f53bc303c59032df3";
	static char const s_digest_7[] = "c4250083cf8230bf21065b3014baaaf9f76fecefc21f91cf237dedc9";
	static char const s_digest_8[] = "014674abc5cb980199935695af22fab683748f4261d4c6492b77c543";
	static char const s_digest_9[] = "a654b50b767a8323c5b519f467d8669837142881dc7ad368a7d5ef8f";

	struct task_s
	{
		char const* m_pattern;
		int m_pattern_len;
		long m_repeat;
		char const* m_digest;
		int m_digest_len;
	};

	static struct task_s const s_tasks[] =
	{
		{s_pattern_0, sizeof(s_pattern_0) - 1, s_repeat_0, s_digest_0, sizeof(s_digest_0) - 1},
		{s_pattern_1, sizeof(s_pattern_1) - 1, s_repeat_1, s_digest_1, sizeof(s_digest_1) - 1},
		{s_pattern_2, sizeof(s_pattern_2) - 1, s_repeat_2, s_digest_2, sizeof(s_digest_2) - 1},
		{s_pattern_3, sizeof(s_pattern_3) - 1, s_repeat_3, s_digest_3, sizeof(s_digest_3) - 1},
		{s_pattern_4, sizeof(s_pattern_4) - 1, s_repeat_4, s_digest_4, sizeof(s_digest_4) - 1},
		{s_pattern_5, sizeof(s_pattern_5) - 1, s_repeat_5, s_digest_5, sizeof(s_digest_5) - 1},
		{s_pattern_6, sizeof(s_pattern_6) - 1, s_repeat_6, s_digest_6, sizeof(s_digest_6) - 1},
		{s_pattern_7, sizeof(s_pattern_7) - 1, s_repeat_7, s_digest_7, sizeof(s_digest_7) - 1},
		{s_pattern_8, sizeof(s_pattern_8) - 1, s_repeat_8, s_digest_8, sizeof(s_digest_8) - 1},
		{s_pattern_9, sizeof(s_pattern_9) - 1, s_repeat_9, s_digest_9, sizeof(s_digest_9) - 1},
	};

	#undef s_repeat_0
	#undef s_repeat_1
	#undef s_repeat_2
	#undef s_repeat_3
	#undef s_repeat_4
	#undef s_repeat_5
	#undef s_repeat_6
	#undef s_repeat_7
	#undef s_repeat_8
	#undef s_repeat_9

	int i;
	struct task_s const* task;
	char const* pattern;
	int pattern_len;
	long repeat;
	char const* digest;
	int digest_len;
	unsigned char pattern_bin[4];
	unsigned char digest_bin[28];
	struct mk_hash_sha2_224_s sha2_224;
	int block_len;
	void* block;
	long blocks;
	long j;
	unsigned char computed[sizeof(digest_bin)];

	for(i = 0; i != sizeof(s_tasks) / sizeof(s_tasks[0]); ++i)
	{
		task = &s_tasks[i];
		pattern = task->m_pattern;
		pattern_len = task->m_pattern_len;
		repeat = task->m_repeat;
		digest = task->m_digest;
		digest_len = task->m_digest_len;
		mk_string_hex_to_bytes(pattern, pattern_len, pattern_bin, sizeof(pattern_bin));
		mk_string_hex_to_bytes(digest, digest_len, digest_bin, sizeof(digest_bin));
		mk_hash_sha2_224_init(&sha2_224);
		if(pattern_len / 2 == 1 && repeat >= 1024)
		{
			block_len = 16 * 1024;
			block = malloc(block_len);
			mk_check(block);
			memset(block, pattern_bin[0], block_len);
			blocks = repeat / block_len;
			for(j = 0; j != blocks; ++j)
			{
				mk_hash_sha2_224_append(&sha2_224, block, block_len);
			}
			mk_hash_sha2_224_append(&sha2_224, block, repeat - blocks * block_len);
			free(block);
		}
		else
		{
			for(j = 0; j != repeat; ++j)
			{
				mk_hash_sha2_224_append(&sha2_224, pattern_bin, pattern_len / 2);
			}
		}
		mk_hash_sha2_224_finish(&sha2_224, &computed);
		mk_check(memcmp(computed, digest_bin, sizeof(computed)) == 0);
	}
	return 0;
}


#undef mk_check
#undef mk_try
