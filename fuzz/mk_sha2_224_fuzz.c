#include "mk_sha2_224_fuzz.h"

#include "../src/mk_sha2_224.h"

#include "../utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


static int mk_sha2_224_fuzz_detail_baseline_checked = 0;


static mk_inline void mk_sha2_224_fuzz_detail_check_baseline(void)
{
	static char const s_input_0[] = "abc";
	static char const s_input_1[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

	static unsigned char const s_output_0[] = {0x23, 0x09, 0x7D, 0x22, 0x34, 0x05, 0xD8, 0x22, 0x86, 0x42, 0xA4, 0x77, 0xBD, 0xA2, 0x55, 0xB3, 0x2A, 0xAD, 0xBC, 0xE4, 0xBD, 0xA0, 0xB3, 0xF7, 0xE3, 0x6C, 0x9D, 0xA7};
	static unsigned char const s_output_1[] = {0x75, 0x38, 0x8B, 0x16, 0x51, 0x27, 0x76, 0xCC, 0x5D, 0xBA, 0x5D, 0xA1, 0xFD, 0x89, 0x01, 0x50, 0xB0, 0xC6, 0x45, 0x5C, 0xB4, 0xF5, 0x8B, 0x19, 0x52, 0x52, 0x25, 0x25};

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

		struct mk_sha2_224_state_s mk_sha2_224_state;
		unsigned char mk_sha2_224_digest[28];

		mk_sha2_224_init(&mk_sha2_224_state);
		mk_sha2_224_append(&mk_sha2_224_state, input, input_len);
		mk_sha2_224_finish(&mk_sha2_224_state, &mk_sha2_224_digest);

		test(memcmp(mk_sha2_224_digest, output, 28) == 0);
	}
}


void mk_sha2_224_fuzz(unsigned char const* data, size_t size)
{
	(void)data;
	(void)size;

	if(!mk_sha2_224_fuzz_detail_baseline_checked)
	{
		mk_sha2_224_fuzz_detail_check_baseline();
		mk_sha2_224_fuzz_detail_baseline_checked = 1;
	}
}


#undef test
