#include "mk_sha2_additional_test_examples.h"

#include "mk_test_utils.h"

#include "../src/hash/mk_hash_sha2_512.h"

#include "../src/utils/mk_assert.h"

#include <stdlib.h> /* malloc free */
#include <string.h> /* memset memcmp */


/*

https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA2_Additional.pdf

*/


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err_ = (x); if(err_ != 0){ return err_; } }while(0)


int mk_sha2_additional_test_examples_512(void)
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

	static char const s_digest_0[] = "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e";
	static char const s_digest_1[] = "77ddd3a542e530fd047b8977c657ba6ce72f1492e360b2b2212cd264e75ec03882e4ff0525517ab4207d14c70c2259ba88d4d335ee0e7e20543d22102ab1788c";
	static char const s_digest_2[] = "2be2e788c8a8adeaa9c89a7f78904cacea6e39297d75e0573a73c756234534d6627ab4156b48a6657b29ab8beb73334040ad39ead81446bb09c70704ec707952";
	static char const s_digest_3[] = "0e67910bcf0f9ccde5464c63b9c850a12a759227d16b040d98986d54253f9f34322318e56b8feb86c5fb2270ed87f31252f7f68493ee759743909bd75e4bb544";
	static char const s_digest_4[] = "4f3f095d015be4a7a7cc0b8c04da4aa09e74351e3a97651f744c23716ebd9b3e822e5077a01baa5cc0ed45b9249e88ab343d4333539df21ed229da6f4a514e0f";
	static char const s_digest_5[] = "ca3dff61bb23477aa6087b27508264a6f9126ee3a004f53cb8db942ed345f2f2d229b4b59c859220a1cf1913f34248e3803bab650e849a3d9a709edc09ae4a76";
	static char const s_digest_6[] = "329c52ac62d1fe731151f2b895a00475445ef74f50b979c6f7bb7cae349328c1d4cb4f7261a0ab43f936a24b000651d4a824fcdd577f211aef8f806b16afe8af";
	static char const s_digest_7[] = "59f5e54fe299c6a8764c6b199e44924a37f59e2b56c3ebad939b7289210dc8e4c21b9720165b0f4d4374c90f1bf4fb4a5ace17a1161798015052893a48c3d161";
	static char const s_digest_8[] = "ce044bc9fd43269d5bbc946cbebc3bb711341115cc4abdf2edbc3ff2c57ad4b15deb699bda257fea5aef9c6e55fcf4cf9dc25a8c3ce25f2efe90908379bff7ed";
	static char const s_digest_9[] = "da172279f3ebbda95f6b6e1e5f0ebec682c25d3d93561a1624c2fa9009d64c7e9923f3b46bcaf11d39a531f43297992ba4155c7e827bd0f1e194ae7ed6de4cac";
	static char const s_digest_a[] = "14b1be901cb43549b4d831e61e5f9df1c791c85b50e85f9d6bc64135804ad43ce8402750edbe4e5c0fc170b99cf78b9f4ecb9c7e02a157911d1bd1832d76784f";
	static char const s_digest_b[] = "fd05e13eb771f05190bd97d62647157ea8f1f6949a52bb6daaedbad5f578ec59b1b8d6c4a7ecb2feca6892b4dc138771670a0f3bd577eea326aed40ab7dd58b1";

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
	unsigned char digest_bin[64];
	struct mk_sha2_512_s sha2_512;
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
		mk_hash_sha2_512_init(&sha2_512);
		if(pattern_len / 2 == 1 && repeat >= 1024)
		{
			block_len = 16 * 1024;
			block = malloc(block_len);
			mk_check(block);
			memset(block, pattern_bin[0], block_len);
			blocks = repeat / block_len;
			for(j = 0; j != blocks; ++j)
			{
				mk_hash_sha2_512_append(&sha2_512, block, block_len);
			}
			mk_hash_sha2_512_append(&sha2_512, block, repeat - blocks * block_len);
			free(block);
		}
		else
		{
			for(j = 0; j != repeat; ++j)
			{
				mk_hash_sha2_512_append(&sha2_512, pattern_bin, pattern_len / 2);
			}
		}
		mk_hash_sha2_512_finish(&sha2_512, &computed);
		mk_check(memcmp(computed, digest_bin, sizeof(computed)) == 0);
	}
	return 0;
}


#undef mk_check
#undef mk_try
