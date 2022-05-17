#include "mk_sha2_additional_test_examples.h"

#include "mk_test_utils.h"

#include "../src/hash/mk_hash_sha2_384.h"

#include "../src/utils/mk_assert.h"

#include <stdlib.h> /* malloc free */
#include <string.h> /* memset memcmp */


/*

https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA2_Additional.pdf

*/


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err_ = (x); if(err_ != 0){ return err_; } }while(0)


int mk_sha2_additional_test_examples_384(void)
{
	static char const s_pattern_0[] = "00";
	static char const s_pattern_1[] = "00";
	static char const s_pattern_2[] = "00";
	static char const s_pattern_3[] = "00";
	static char const s_pattern_4[] = "00";
	static char const s_pattern_5[] = "00";
	static char const s_pattern_6[] = "41";
	static char const s_pattern_7[] = "55";
	static char const s_pattern_8[] = "00";
	static char const s_pattern_9[] = "5a";
	static char const s_pattern_a[] = "00";
	static char const s_pattern_b[] = "42";

	#define s_repeat_0 0
	#define s_repeat_1 111
	#define s_repeat_2 112
	#define s_repeat_3 113
	#define s_repeat_4 122
	#define s_repeat_5 1000
	#define s_repeat_6 1000
	#define s_repeat_7 1005
	#define s_repeat_8 1000000
	#define s_repeat_9 0x20000000
	#define s_repeat_a 0x41000000
	#define s_repeat_b 0x6000003e

	static char const s_digest_0[] = "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b";
	static char const s_digest_1[] = "435770712c611be7293a66dd0dc8d1450dc7ff7337bfe115bf058ef2eb9bed09cee85c26963a5bcc0905dc2df7cc6a76";
	static char const s_digest_2[] = "3e0cbf3aee0e3aa70415beae1bd12dd7db821efa446440f12132edffce76f635e53526a111491e75ee8e27b9700eec20";
	static char const s_digest_3[] = "6be9af2cf3cd5dd12c8d9399ec2b34e66034fbd699d4e0221d39074172a380656089caafe8f39963f94cc7c0a07e3d21";
	static char const s_digest_4[] = "12a72ae4972776b0db7d73d160a15ef0d19645ec96c7f816411ab780c794aa496a22909d941fe671ed3f3caee900bdd5";
	static char const s_digest_5[] = "aae017d4ae5b6346dd60a19d52130fb55194b6327dd40b89c11efc8222292de81e1a23c9b59f9f58b7f6ad463fa108ca";
	static char const s_digest_6[] = "7df01148677b7f18617eee3a23104f0eed6bb8c90a6046f715c9445ff43c30d69e9e7082de39c3452fd1d3afd9ba0689";
	static char const s_digest_7[] = "1bb8e256da4a0d1e87453528254f223b4cb7e49c4420dbfa766bba4adba44eeca392ff6a9f565bc347158cc970ce44ec";
	static char const s_digest_8[] = "8a1979f9049b3fff15ea3a43a4cf84c634fd14acad1c333fecb72c588b68868b66a994386dc0cd1687b9ee2e34983b81";
	static char const s_digest_9[] = "18aded227cc6b562cc7fb259e8f404549e52914531aa1c5d85167897c779cc4b25d0425fd1590e40bd763ec3f4311c1a";
	static char const s_digest_a[] = "83ab05ca483abe3faa597ad524d31291ae827c5be2b3efcb6391bfed31ccd937b6135e0378c6c7f598857a7c516f207a";
	static char const s_digest_b[] = "cf852304f8d80209351b37ce69ca7dcf34972b4edb7817028ec55ab67ad3bc96eecb8241734258a85d2afce65d4571e2";

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

	int i;
	struct task_s const* task;
	char const* pattern;
	int pattern_len;
	long repeat;
	char const* digest;
	int digest_len;
	unsigned char pattern_bin[4];
	unsigned char digest_bin[48];
	struct mk_sha2_384_s sha2_384;
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
		mk_sha2_384_init(&sha2_384);
		if(pattern_len / 2 == 1 && repeat >= 1024)
		{
			block_len = 16 * 1024;
			block = malloc(block_len);
			mk_check(block);
			memset(block, pattern_bin[0], block_len);
			blocks = repeat / block_len;
			for(j = 0; j != blocks; ++j)
			{
				mk_sha2_384_append(&sha2_384, block, block_len);
			}
			mk_sha2_384_append(&sha2_384, block, repeat - blocks * block_len);
			free(block);
		}
		else
		{
			for(j = 0; j != repeat; ++j)
			{
				mk_sha2_384_append(&sha2_384, pattern_bin, pattern_len / 2);
			}
		}
		mk_sha2_384_finish(&sha2_384, &computed);
		mk_check(memcmp(computed, digest_bin, sizeof(computed)) == 0);
	}
	return 0;
}


#undef mk_check
#undef mk_try
