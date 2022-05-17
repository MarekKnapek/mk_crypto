#include "mk_sha2_512_test_examples.h"

#include "mk_test_utils.h"

#include "../src/utils/mk_assert.h"

#include "../src/hash/mk_hash_sha2_512.h"

#include <string.h> /* memcmp */


/*

https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA512.pdf

*/


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)


int mk_sha2_512_test_examples(void)
{
	static char const s_msg_0[] = "abc";
	static char const s_msg_1[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

	static char const s_sha2_512_0[] = "DDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F";
	static char const s_sha2_512_1[] = "8E959B75DAE313DA8CF4F72814FC143F8F7779C6EB9F7FA17299AEADB6889018501D289E4900F7E4331B99DEC4B5433AC7D329EEB6DD26545E96E55B874BE909";

	struct task_s
	{
		char const* m_msg;
		int m_msg_len;
		char const* m_digest;
		int m_digest_len;
	};

	static struct task_s const s_tasks[] =
	{
		{s_msg_0, sizeof(s_msg_0) - 1, s_sha2_512_0, sizeof(s_sha2_512_0) - 1},
		{s_msg_1, sizeof(s_msg_1) - 1, s_sha2_512_1, sizeof(s_sha2_512_1) - 1},
	};

	int i;
	struct task_s const* task;
	char const* msg;
	int msg_len;
	char const* digest;
	int digest_len;
	unsigned char digest_bin[64];
	struct mk_sha2_512_s mk_sha2_512;
	unsigned char computed[sizeof(digest_bin)];

	for(i = 0; i != sizeof(s_tasks) / sizeof(s_tasks[0]); ++i)
	{
		task = &s_tasks[i];
		msg = task->m_msg;
		msg_len = task->m_msg_len;
		digest = task->m_digest;
		digest_len = task->m_digest_len;
		mk_string_hex_to_bytes(digest, digest_len, digest_bin, sizeof(digest_bin));
		mk_hash_sha2_512_init(&mk_sha2_512);
		mk_hash_sha2_512_append(&mk_sha2_512, msg, msg_len);
		mk_hash_sha2_512_finish(&mk_sha2_512, &computed);
		mk_check(memcmp(computed, digest_bin, sizeof(computed)) == 0);
	}
	return 0;
}


#undef mk_check
