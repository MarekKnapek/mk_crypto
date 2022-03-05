#include "mk_sha3.h"

#include <assert.h> /* assert static_assert */ /* C11 */
#include <limits.h> /* CHAR_BIT */
#include <string.h> /* memset memcmp NULL */


static char const s_msg_0[] = "";
static char const s_sha3_224_0[] = "6B4E03423667DBB73B6E15454F0EB1ABD4597F9A1B078E3F5B5A6BC7";
static char const s_sha3_256_0[] = "A7FFC6F8BF1ED76651C14756A061D662F580FF4DE43B49FA82D80A4B80F8434A";

static char const s_msg_1[] = "11001";
static char const s_sha3_224_1[] = "FFBAD5DA96BAD71789330206DC6768ECAEB1B32DCA6B3301489674AB";
static char const s_sha3_256_1[] = "7B0047CF5A456882363CBF0FB05322CF65F4B7059A46365E830132E3B5D957AF";

static char const s_msg_2[] = "110010100001101011011110100110";
static char const s_sha3_224_2[] = "D666A514CC9DBA25AC1BA69ED3930460DEAAC9851B5F0BAAB007DF3B";
static char const s_sha3_256_2[] = "C8242FEF409E5AE9D1F1C857AE4DC624B92B19809F62AA8C07411C54A078B1D0";

static char const s_msg_3[] =
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101";
static char const s_sha3_224_3[] = "9376816ABA503F72F96CE7EB65AC095DEEE3BE4BF9BBC2A1CB7E11E0";
static char const s_sha3_256_3[] = "79F38ADEC5C20307A98EF76E8324AFBFD46CFD81B22E3973C65FA1BD9DE31787";

static char const s_msg_4[] =
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000";
static char const s_sha3_224_4[] = "22D2F7BB0B173FD8C19686F9173166E3EE62738047D7EADD69EFB228";
static char const s_sha3_256_4[] = "81EE769BED0950862B1DDDED2E84AAA6AB7BFDD3CEAA471BE31163D40336363C";

static char const s_msg_5[] =
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"11000101110001011100010111000101"
	"110001011100010111000101110001";
static char const s_sha3_224_5[] = "4E907BB1057861F200A599E9D4F85B02D88453BF5B8ACE9AC589134C";
static char const s_sha3_256_5[] = "52860AA301214C610D922A6B6CAB981CCD06012E54EF689D744021E738B9ED20";


struct task_s
{
	char const* m_msg;
	int m_len;
	char const* m_sha3_224;
	char const* m_sha3_256;
};


static struct task_s const s_tasks[] =
{
	{s_msg_0, sizeof(s_msg_0) - 1, s_sha3_224_0, s_sha3_256_0},
	{s_msg_1, sizeof(s_msg_1) - 1, s_sha3_224_1, s_sha3_256_1},
	{s_msg_2, sizeof(s_msg_2) - 1, s_sha3_224_2, s_sha3_256_2},
	{s_msg_3, sizeof(s_msg_3) - 1, s_sha3_224_3, s_sha3_256_3},
	{s_msg_4, sizeof(s_msg_4) - 1, s_sha3_224_4, s_sha3_256_4},
	{s_msg_5, sizeof(s_msg_5) - 1, s_sha3_224_5, s_sha3_256_5},
};


static inline void bit_string_to_binary(char const* in, int len, void* out)
{
	assert(in);
	assert(out);

	unsigned char* output = (unsigned char*)out;
	for(int i = 0; i != len; ++i)
	{
		int byte = i / CHAR_BIT;
		int bit = i % CHAR_BIT;
		if(in[i] == '1')
		{
			output[byte] = (output[byte] & ~(1u << bit)) | (unsigned char)(1u << bit);
		}
		else
		{
			assert(in[i] == '0');
			output[byte] = (output[byte] & ~(1u << bit));
		}
	}
}

static inline int hex_symbol_to_int(char const hs)
{
	static char const s_hex_alphabet_lc[] = "0123456789abcdef";
	static char const s_hex_alphabet_uc[] = "0123456789ABCDEF";

	static_assert(sizeof(s_hex_alphabet_lc) == sizeof(s_hex_alphabet_uc), "");

	for(int i = 0; i != sizeof(s_hex_alphabet_lc) - 1; ++i)
	{
		if(hs == s_hex_alphabet_lc[i])
		{
			return i;
		}
		if(hs == s_hex_alphabet_uc[i])
		{
			return i;
		}
	}
	assert(0);
	return -1;
}

static inline void hex_string_to_binary(char const* in, int len, void* out)
{
	assert(in);
	assert(out);
	assert(len % 2 == 0);

	unsigned char* output = (unsigned char*)out;
	for(int i = 0; i != len / 2; ++i)
	{
		int v;

		v = hex_symbol_to_int(in[2 * i + 0]);
		output[i] = (unsigned char)(v << 4);

		v = hex_symbol_to_int(in[2 * i + 1]);
		output[i] |= (unsigned char)(v << 0);
	}
}

static inline void process_task(struct task_s const* task)
{
	assert(task);

	unsigned char msg_buff[256];
	bit_string_to_binary(task->m_msg, task->m_len, &msg_buff);


	unsigned char sha3_224_buff[28];
	hex_string_to_binary(task->m_sha3_224, 28 * 2, &sha3_224_buff);

	struct mk_sha3_224_state_s mk_sha3_224_state;
	unsigned char mk_sha3_224_digest[28];

	mk_sha3_224_init(&mk_sha3_224_state);
	mk_sha3_224_append(&mk_sha3_224_state, msg_buff, task->m_len);
	mk_sha3_224_finish(&mk_sha3_224_state, mk_sha3_224_digest);

	if(memcmp(&mk_sha3_224_digest, &sha3_224_buff, 28) != 0)
	{
		int volatile* volatile ptr = NULL;
		*ptr = 0;
	}


	unsigned char sha3_256_buff[32];
	hex_string_to_binary(task->m_sha3_256, 32 * 2, &sha3_256_buff);

	struct mk_sha3_256_state_s mk_sha3_256_state;
	unsigned char mk_sha3_256_digest[32];

	mk_sha3_256_init(&mk_sha3_256_state);
	mk_sha3_256_append(&mk_sha3_256_state, msg_buff, task->m_len);
	mk_sha3_256_finish(&mk_sha3_256_state, mk_sha3_256_digest);

	if(memcmp(&mk_sha3_256_digest, &sha3_256_buff, 32) != 0)
	{
		int volatile* volatile ptr = NULL;
		*ptr = 0;
	}
}


int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size)
{
	int ntasks = sizeof(s_tasks) / sizeof(s_tasks[0]);
	for(int i = 0; i != ntasks; ++i)
	{
		process_task(s_tasks + i);
	}

	return 0;
}
