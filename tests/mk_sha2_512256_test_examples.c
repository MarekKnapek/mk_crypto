#include "mk_sha2_512256_test_examples.h"

#include "mk_test_utils.h"

#include "../src/utils/mk_assert.h"

#include "../src/hash/mk_sha2_512256.h"

#include <string.h> /* memcmp */


/*

https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA512_256.pdf

*/


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)


int mk_sha2_512256_test_examples(void)
{
	static char const s_msg_0[] = "abc";
	static char const s_msg_1[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

	static char const s_sha2_512256_0[] = "53048E2681941EF99B2E29B76B4C7DABE4C2D0C634FC6D46E0E2F13107E7AF23";
	static char const s_sha2_512256_1[] = "3928E184FB8690F840DA3988121D31BE65CB9D3EF83EE6146FEAC861E19B563A";

	struct task_s
	{
		char const* m_msg;
		int m_msg_len;
		char const* m_digest;
		int m_digest_len;
	};

	static struct task_s const s_tasks[] =
	{
		{s_msg_0, sizeof(s_msg_0) - 1, s_sha2_512256_0, sizeof(s_sha2_512256_0) - 1},
		{s_msg_1, sizeof(s_msg_1) - 1, s_sha2_512256_1, sizeof(s_sha2_512256_1) - 1},
	};

	int i;
	struct task_s const* task;
	char const* msg;
	int msg_len;
	char const* digest;
	int digest_len;
	unsigned char digest_bin[32];
	struct mk_sha2_512256_s mk_sha2_512256;
	unsigned char computed[sizeof(digest_bin)];

	for(i = 0; i != sizeof(s_tasks) / sizeof(s_tasks[0]); ++i)
	{
		task = &s_tasks[i];
		msg = task->m_msg;
		msg_len = task->m_msg_len;
		digest = task->m_digest;
		digest_len = task->m_digest_len;
		mk_string_hex_to_bytes(digest, digest_len, digest_bin, sizeof(digest_bin));
		mk_sha2_512256_init(&mk_sha2_512256);
		mk_sha2_512256_append(&mk_sha2_512256, msg, msg_len);
		mk_sha2_512256_finish(&mk_sha2_512256, &computed);
		mk_check(memcmp(computed, digest_bin, sizeof(computed)) == 0);
	}
	return 0;
}


#undef mk_check
