#include "mk_sha2.h"
#include "mk_win_sha2.h"

#include <stddef.h> /* size_t */
#include <string.h> /* memcmp */


static inline void mk_sha2_224_fuzz(unsigned char const* data, size_t size)
{
	static char const s_input_0[] = "abc";
	static char const s_input_1[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

	static int const s_input_len_0 = sizeof(s_input_0) - 1;
	static int const s_input_len_1 = sizeof(s_input_1) - 1;

	static unsigned char const s_output_0[] = {0x23, 0x09, 0x7D, 0x22,  0x34, 0x05, 0xD8, 0x22,  0x86, 0x42, 0xA4, 0x77,  0xBD, 0xA2, 0x55, 0xB3,  0x2A, 0xAD, 0xBC, 0xE4,  0xBD, 0xA0, 0xB3, 0xF7,  0xE3, 0x6C, 0x9D, 0xA7};
	static unsigned char const s_output_1[] = {0x75, 0x38, 0x8B, 0x16,  0x51, 0x27, 0x76, 0xCC,  0x5D, 0xBA, 0x5D, 0xA1,  0xFD, 0x89, 0x01, 0x50,  0xB0, 0xC6, 0x45, 0x5C,  0xB4, 0xF5, 0x8B, 0x19,  0x52, 0x52, 0x25, 0x25};

	struct task_s
	{
		char const* m_input;
		int m_input_len;
		unsigned char const* m_output;
	};

	static struct task_s s_tasks[] =
	{
		{s_input_0, s_input_len_0, s_output_0},
		{s_input_1, s_input_len_1, s_output_1},
	};


	(void)data;
	(void)size;

	for(int i = 0; i != sizeof(s_tasks) / sizeof(s_tasks[0]); ++i)
	{
		mk_sha2_224_state_s mk_sha2_224_state;
		unsigned char mk_sha2_224_digest[28];

		char const* input = s_tasks[i].m_input;
		int input_len = s_tasks[i].m_input_len;
		unsigned char const* output = s_tasks[i].m_output;

		mk_sha2_224_init(&mk_sha2_224_state);
		mk_sha2_224_append(&mk_sha2_224_state, input, input_len);
		mk_sha2_224_finish(&mk_sha2_224_state, &mk_sha2_224_digest);

		if(memcmp(mk_sha2_224_digest, output, 28) != 0)
		{
			/*int volatile* volatile ptr = NULL;
			*ptr = 0;*/
			__debugbreak();
		}
	}
}

static inline void mk_sha2_256_fuzz(unsigned char const* data, size_t size)
{
	mk_sha2_256_state_s mk_sha2_256_state;
	unsigned char mk_sha2_256_digest[32];

	mk_sha2_256_init(&mk_sha2_256_state);
	mk_sha2_256_append(&mk_sha2_256_state, data, size);
	mk_sha2_256_finish(&mk_sha2_256_state, &mk_sha2_256_digest);

	mk_win_sha2_256_state_s mk_win_sha2_256_state;
	unsigned char mk_win_sha2_256_digest[32];

	mk_win_sha2_256_init(&mk_win_sha2_256_state);
	mk_win_sha2_256_append(&mk_win_sha2_256_state, data, size);
	mk_win_sha2_256_finish(&mk_win_sha2_256_state, &mk_win_sha2_256_digest);

	if(memcmp(mk_sha2_256_digest, mk_win_sha2_256_digest, 32) != 0)
	{
		/*int volatile* volatile ptr = NULL;
		*ptr = 0;*/
		__debugbreak();
	}
}


extern "C" int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size)
{
	mk_sha2_224_fuzz(data, size);
	mk_sha2_256_fuzz(data, size);

	return 0;
}
