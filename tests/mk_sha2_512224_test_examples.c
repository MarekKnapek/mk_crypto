#include "mk_sha2_512224_test_examples.h"

#include "mk_test_utils.h"

#include "../src/utils/mk_assert.h"

#include "../src/hash/mk_sha2_512224.h"

#include <string.h> /* memcmp */


/*

https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA512_224.pdf

*/


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)


int mk_sha2_512224_test_examples(void)
{
	static char const s_msg_0[] = "abc";
	static char const s_msg_1[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

	static char const s_sha2_512224_0[] = "4634270F707B6A54DAAE7530460842E20E37ED265CEEE9A43E8924AA";
	static char const s_sha2_512224_1[] = "23FEC5BB94D60B23308192640B0C453335D664734FE40E7268674AF9";

	struct task_s
	{
		char const* m_msg;
		int m_msg_len;
		char const* m_digest;
		int m_digest_len;
	};

	static struct task_s const s_tasks[] =
	{
		{s_msg_0, sizeof(s_msg_0) - 1, s_sha2_512224_0, sizeof(s_sha2_512224_0) - 1},
		{s_msg_1, sizeof(s_msg_1) - 1, s_sha2_512224_1, sizeof(s_sha2_512224_1) - 1},
	};

	int i;
	struct task_s const* task;
	char const* msg;
	int msg_len;
	char const* digest;
	int digest_len;
	unsigned char digest_bin[28];
	struct mk_sha2_512224_s mk_sha2_512224;
	unsigned char computed[sizeof(digest_bin)];

	for(i = 0; i != sizeof(s_tasks) / sizeof(s_tasks[0]); ++i)
	{
		task = &s_tasks[i];
		msg = task->m_msg;
		msg_len = task->m_msg_len;
		digest = task->m_digest;
		digest_len = task->m_digest_len;
		mk_string_hex_to_bytes(digest, digest_len, digest_bin, sizeof(digest_bin));
		mk_sha2_512224_init(&mk_sha2_512224);
		mk_sha2_512224_append(&mk_sha2_512224, msg, msg_len);
		mk_sha2_512224_finish(&mk_sha2_512224, &computed);
		mk_check(memcmp(computed, digest_bin, sizeof(computed)) == 0);
	}
	return 0;
}


#undef mk_check
