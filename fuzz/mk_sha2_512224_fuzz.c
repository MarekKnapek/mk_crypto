#include "mk_sha2_512224_fuzz.h"

#include "../src/mk_sha2_512224.h"

#include "../utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static int mk_sha2_512224_fuzz_detail_baseline_checked = 0;


static mk_inline void mk_sha2_512224_fuzz_detail_check_baseline(void)
{
	static char const s_input_0[] = "abc";
	static char const s_input_1[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

	static unsigned char const s_output_0[] = {0x46, 0x34, 0x27, 0x0F, 0x70, 0x7B, 0x6A, 0x54, 0xDA, 0xAE, 0x75, 0x30, 0x46, 0x08, 0x42, 0xE2, 0x0E, 0x37, 0xED, 0x26, 0x5C, 0xEE, 0xE9, 0xA4, 0x3E, 0x89, 0x24, 0xAA};
	static unsigned char const s_output_1[] = {0x23, 0xFE, 0xC5, 0xBB, 0x94, 0xD6, 0x0B, 0x23, 0x30, 0x81, 0x92, 0x64, 0x0B, 0x0C, 0x45, 0x33, 0x35, 0xD6, 0x64, 0x73, 0x4F, 0xE4, 0x0E, 0x72, 0x68, 0x67, 0x4A, 0xF9};

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

		struct mk_sha2_512224_state_s mk_sha2_512224_state;
		unsigned char mk_sha2_512224_digest[28];

		mk_sha2_512224_init(&mk_sha2_512224_state);
		mk_sha2_512224_append(&mk_sha2_512224_state, input, input_len);
		mk_sha2_512224_finish(&mk_sha2_512224_state, &mk_sha2_512224_digest);

		test(memcmp(mk_sha2_512224_digest, output, 28) == 0);
	}
}


void mk_sha2_512224_fuzz(unsigned char const* data, size_t size)
{
	(void)data;
	(void)size;

	if(!mk_sha2_512224_fuzz_detail_baseline_checked)
	{
		mk_sha2_512224_fuzz_detail_check_baseline();
		mk_sha2_512224_fuzz_detail_baseline_checked = 1;
	}
}


#undef test
