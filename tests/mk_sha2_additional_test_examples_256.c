#include "mk_sha2_additional_test_examples.h"

#include "mk_test_utils.h"

#include "../src/hash/hash/mk_hash_hash_sha2_256.h"

#include "../src/utils/mk_assert.h"

#include <stdlib.h> /* malloc free */
#include <string.h> /* memset memcmp */


/*

https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA2_Additional.pdf

*/


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err_ = (x); if(err_ != 0){ return err_; } }while(0)


int mk_sha2_additional_test_examples_256(void)
{
	static char const s_pattern_0[] = "bd";
	static char const s_pattern_1[] = "c98c8e55";
	static char const s_pattern_2[] = "00";
	static char const s_pattern_3[] = "00";
	static char const s_pattern_4[] = "00";
	static char const s_pattern_5[] = "00";
	static char const s_pattern_6[] = "00";
	static char const s_pattern_7[] = "41";
	static char const s_pattern_8[] = "55";
	static char const s_pattern_9[] = "00";
	static char const s_pattern_a[] = "5a";
	static char const s_pattern_b[] = "00";
	static char const s_pattern_c[] = "42";

	#define s_repeat_0 1
	#define s_repeat_1 1
	#define s_repeat_2 55
	#define s_repeat_3 56
	#define s_repeat_4 57
	#define s_repeat_5 64
	#define s_repeat_6 1000
	#define s_repeat_7 1000
	#define s_repeat_8 1005
	#define s_repeat_9 1000000
	#define s_repeat_a 0x20000000
	#define s_repeat_b 0x41000000
	#define s_repeat_c 0x6000003e

	static char const s_digest_0[] = "68325720aabd7c82f30f554b313d0570c95accbb7dc4b5aae11204c08ffe732b";
	static char const s_digest_1[] = "7abc22c0ae5af26ce93dbb94433a0e0b2e119d014f8e7f65bd56c61ccccd9504";
	static char const s_digest_2[] = "02779466cdec163811d078815c633f21901413081449002f24aa3e80f0b88ef7";
	static char const s_digest_3[] = "d4817aa5497628e7c77e6b606107042bbba3130888c5f47a375e6179be789fbb";
	static char const s_digest_4[] = "65a16cb7861335d5ace3c60718b5052e44660726da4cd13bb745381b235a1785";
	static char const s_digest_5[] = "f5a5fd42d16a20302798ef6ed309979b43003d2320d9f0e8ea9831a92759fb4b";
	static char const s_digest_6[] = "541b3e9daa09b20bf85fa273e5cbd3e80185aa4ec298e765db87742b70138a53";
	static char const s_digest_7[] = "c2e686823489ced2017f6059b8b239318b6364f6dcd835d0a519105a1eadd6e4";
	static char const s_digest_8[] = "f4d62ddec0f3dd90ea1380fa16a5ff8dc4c54b21740650f24afc4120903552b0";
	static char const s_digest_9[] = "d29751f2649b32ff572b5e0a9f541ea660a50f94ff0beedfb0b692b924cc8025";
	static char const s_digest_a[] = "15a1868c12cc53951e182344277447cd0979536badcc512ad24c67e9b2d4f3dd";
	static char const s_digest_b[] = "461c19a93bd4344f9215f5ec64357090342bc66b15a148317d276e31cbc20b53";
	static char const s_digest_c[] = "c23ce8a7895f4b21ec0daf37920ac0a262a220045a03eb2dfed48ef9b05aabea";

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
		{s_pattern_a, sizeof(s_pattern_a) - 1, s_repeat_a, s_digest_a, sizeof(s_digest_a) - 1},
		{s_pattern_b, sizeof(s_pattern_b) - 1, s_repeat_b, s_digest_b, sizeof(s_digest_b) - 1},
		{s_pattern_c, sizeof(s_pattern_c) - 1, s_repeat_c, s_digest_c, sizeof(s_digest_c) - 1},
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
	#undef s_repeat_a
	#undef s_repeat_b
	#undef s_repeat_c

	int i;
	struct task_s const* task;
	char const* pattern;
	int pattern_len;
	long repeat;
	char const* digest;
	int digest_len;
	unsigned char pattern_bin[4];
	unsigned char digest_bin[32];
	struct mk_hash_hash_sha2_256_s sha2_256;
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
		mk_hash_hash_sha2_256_init(&sha2_256);
		if(pattern_len / 2 == 1 && repeat >= 1024)
		{
			block_len = 16 * 1024;
			block = malloc(block_len);
			mk_check(block);
			memset(block, pattern_bin[0], block_len);
			blocks = repeat / block_len;
			for(j = 0; j != blocks; ++j)
			{
				mk_hash_hash_sha2_256_append(&sha2_256, block, block_len);
			}
			mk_hash_hash_sha2_256_append(&sha2_256, block, repeat - blocks * block_len);
			free(block);
		}
		else
		{
			for(j = 0; j != repeat; ++j)
			{
				mk_hash_hash_sha2_256_append(&sha2_256, pattern_bin, pattern_len / 2);
			}
		}
		mk_hash_hash_sha2_256_finish(&sha2_256, &computed);
		mk_check(memcmp(computed, digest_bin, sizeof(computed)) == 0);
	}
	return 0;
}


#undef mk_check
#undef mk_try
