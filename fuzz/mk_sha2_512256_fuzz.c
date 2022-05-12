#include "mk_sha2_512256_fuzz.h"

#include "../src/hash/mk_sha2_512256.h"

#include "../src/utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static int mk_sha2_512256_fuzz_detail_baseline_checked = 0;


static mk_inline void mk_sha2_512256_fuzz_detail_check_baseline(void)
{
	static char const s_input_0[] = "abc";
	static char const s_input_1[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

	static unsigned char const s_output_0[] = {0x53, 0x04, 0x8E, 0x26, 0x81, 0x94, 0x1E, 0xF9, 0x9B, 0x2E, 0x29, 0xB7, 0x6B, 0x4C, 0x7D, 0xAB, 0xE4, 0xC2, 0xD0, 0xC6, 0x34, 0xFC, 0x6D, 0x46, 0xE0, 0xE2, 0xF1, 0x31, 0x07, 0xE7, 0xAF, 0x23};
	static unsigned char const s_output_1[] = {0x39, 0x28, 0xE1, 0x84, 0xFB, 0x86, 0x90, 0xF8, 0x40, 0xDA, 0x39, 0x88, 0x12, 0x1D, 0x31, 0xBE, 0x65, 0xCB, 0x9D, 0x3E, 0xF8, 0x3E, 0xE6, 0x14, 0x6F, 0xEA, 0xC8, 0x61, 0xE1, 0x9B, 0x56, 0x3A};

	struct task_s
	{
		char const* m_input;
		int m_input_len;
		unsigned char const* m_output;
	};

	static struct task_s s_tasks[] =
	{
		{s_input_0, sizeof(s_input_0) - 1, s_output_0},
		{s_input_1, sizeof(s_input_1) - 1, s_output_1},
	};

	for(int i = 0; i != sizeof(s_tasks) / sizeof(s_tasks[0]); ++i)
	{
		char const* input = s_tasks[i].m_input;
		int input_len = s_tasks[i].m_input_len;
		unsigned char const* output = s_tasks[i].m_output;

		struct mk_sha2_512256_state_s mk_sha2_512256_state;
		unsigned char mk_sha2_512256_digest[32];

		mk_sha2_512256_init(&mk_sha2_512256_state);
		mk_sha2_512256_append(&mk_sha2_512256_state, input, input_len);
		mk_sha2_512256_finish(&mk_sha2_512256_state, &mk_sha2_512256_digest);

		test(memcmp(mk_sha2_512256_digest, output, 32) == 0);
	}
}


void mk_sha2_512256_fuzz(unsigned char const* data, size_t size)
{
	(void)data;
	(void)size;

	if(!mk_sha2_512256_fuzz_detail_baseline_checked)
	{
		mk_sha2_512256_fuzz_detail_check_baseline();
		mk_sha2_512256_fuzz_detail_baseline_checked = 1;
	}
}


#undef test
