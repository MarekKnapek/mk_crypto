#include "mk_sha2_256_test_examples.h"

#include "mk_test_utils.h"

#include "../src/utils/mk_assert.h"

#include "../src/hash/mk_hash_sha2_256.h"

#include <string.h> /* memcmp */


/*

https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA256.pdf

*/


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)


int mk_sha2_256_test_examples(void)
{
	static char const s_msg_0[] = "abc";
	static char const s_msg_1[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

	static char const s_sha2_256_0[] = "BA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD";
	static char const s_sha2_256_1[] = "248D6A61D20638B8E5C026930C3E6039A33CE45964FF2167F6ECEDD419DB06C1";

	struct task_s
	{
		char const* m_msg;
		int m_msg_len;
		char const* m_digest;
		int m_digest_len;
	};

	static struct task_s const s_tasks[] =
	{
		{s_msg_0, sizeof(s_msg_0) - 1, s_sha2_256_0, sizeof(s_sha2_256_0) - 1},
		{s_msg_1, sizeof(s_msg_1) - 1, s_sha2_256_1, sizeof(s_sha2_256_1) - 1},
	};

	int i;
	struct task_s const* task;
	char const* msg;
	int msg_len;
	char const* digest;
	int digest_len;
	unsigned char digest_bin[32];
	struct mk_hash_sha2_256_s mk_sha2_256;
	unsigned char computed[sizeof(digest_bin)];

	for(i = 0; i != sizeof(s_tasks) / sizeof(s_tasks[0]); ++i)
	{
		task = &s_tasks[i];
		msg = task->m_msg;
		msg_len = task->m_msg_len;
		digest = task->m_digest;
		digest_len = task->m_digest_len;
		mk_string_hex_to_bytes(digest, digest_len, digest_bin, sizeof(digest_bin));
		mk_hash_sha2_256_init(&mk_sha2_256);
		mk_hash_sha2_256_append(&mk_sha2_256, msg, msg_len);
		mk_hash_sha2_256_finish(&mk_sha2_256, &computed);
		mk_check(memcmp(computed, digest_bin, sizeof(computed)) == 0);
	}
	return 0;
}


#undef mk_check
