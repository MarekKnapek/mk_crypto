#include "mk_sha2_224_test_examples.h"

#include "mk_test_utils.h"

#include "../src/utils/mk_assert.h"
#include "../src/utils/mk_try.h"

#include "../src/hash/hash/mk_hash_hash.h"

#include <string.h> /* memcmp */


/*

https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA224.pdf

*/


int mk_sha2_224_test_examples(void)
{
	static char const s_msg_0[] = "abc";
	static char const s_msg_1[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

	static char const s_sha2_224_0[] = "23097D223405D8228642A477BDA255B32AADBCE4BDA0B3F7E36C9DA7";
	static char const s_sha2_224_1[] = "75388B16512776CC5DBA5DA1FD890150B0C6455CB4F58B1952522525";

	struct task_s
	{
		char const* m_msg;
		int m_msg_len;
		char const* m_digest;
		int m_digest_len;
	};

	static struct task_s const s_tasks[] =
	{
		{s_msg_0, sizeof(s_msg_0) - 1, s_sha2_224_0, sizeof(s_sha2_224_0) - 1},
		{s_msg_1, sizeof(s_msg_1) - 1, s_sha2_224_1, sizeof(s_sha2_224_1) - 1},
	};

	int i;
	struct task_s const* task;
	char const* msg;
	int msg_len;
	char const* digest;
	int digest_len;
	unsigned char digest_bin[28];
	struct mk_hash_hash_sha2_224_s mk_sha2_224;
	unsigned char computed[sizeof(digest_bin)];

	for(i = 0; i != sizeof(s_tasks) / sizeof(s_tasks[0]); ++i)
	{
		task = &s_tasks[i];
		msg = task->m_msg;
		msg_len = task->m_msg_len;
		digest = task->m_digest;
		digest_len = task->m_digest_len;
		mk_string_hex_to_bytes(digest, digest_len, digest_bin, sizeof(digest_bin));
		mk_hash_hash_sha2_224_init(&mk_sha2_224);
		mk_hash_hash_sha2_224_append(&mk_sha2_224, msg, msg_len);
		mk_hash_hash_sha2_224_finish(&mk_sha2_224, &computed);
		mk_check(memcmp(computed, digest_bin, sizeof(computed)) == 0);
	}
	return 0;
}
