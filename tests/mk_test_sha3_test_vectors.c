#include "../mk_sha3.h"

#include "../mk_assert.h"
#include "mk_test_utils.h"

#include <limits.h> /* CHAR_BIT */
#include <stdbool.h> /* bool true false */
#include <stddef.h> /* NULL */
#include <stdio.h> /* printf fopen fclose fgets feof sscanf */
#include <stdlib.h> /* EXIT_SUCCESS EXIT_FAILURE */
#include <stdlib.h> /* malloc free */
#include <string.h> /* strlen memcmp */


static char const* const s_file_names[] =
{
	"SHA3_224LongMsg.rsp",
	"SHA3_224Monte.rsp",
	"SHA3_224ShortMsg.rsp",
	"SHA3_256LongMsg.rsp",
	"SHA3_256Monte.rsp",
	"SHA3_256ShortMsg.rsp",
	"SHA3_384LongMsg.rsp",
	"SHA3_384Monte.rsp",
	"SHA3_384ShortMsg.rsp",
	"SHA3_512LongMsg.rsp",
	"SHA3_512Monte.rsp",
	"SHA3_512ShortMsg.rsp",
};


struct context_s
{
	int m_digest_len_bits;
	bool m_has_seed;
	unsigned char m_seed[64];
	int m_msg_len_bits;
	char* m_msg;
	bool m_has_md;
	unsigned char m_md[64];
	int m_count;
	unsigned char m_prev_hash[64];
};


#define mk_try(x) do{ int err = (x); if(err != 0){ return err; } }while(0)
#define mk_check(x) do{ if(!(x)){ __debugbreak(); return __LINE__; } }while(0)


static inline int process_monte(struct context_s* context)
{
	MK_ASSERT(context);

	switch(context->m_digest_len_bits)
	{
		case 224:
		{
			unsigned char data[28];
			unsigned char* prev_hash = context->m_count == 0 ? context->m_seed : context->m_prev_hash;
			memcpy(&data, prev_hash, sizeof(data));

			struct mk_sha3_224_state_s sha3;
			for(int i = 0; i != 1'000; ++i)
			{
				mk_sha3_224_init  (&sha3);
				mk_sha3_224_append(&sha3, &data, sizeof(data) * CHAR_BIT);
				mk_sha3_224_finish(&sha3, &data);
			}
			memcpy(&context->m_prev_hash, &data, sizeof(data));

			mk_check(memcmp(&data, context->m_md, sizeof(data)) == 0);
		}
		break;
		case 256:
		{
			unsigned char data[32];
			unsigned char* prev_hash = context->m_count == 0 ? context->m_seed : context->m_prev_hash;
			memcpy(&data, prev_hash, sizeof(data));

			struct mk_sha3_256_state_s sha3;
			for(int i = 0; i != 1'000; ++i)
			{
				mk_sha3_256_init  (&sha3);
				mk_sha3_256_append(&sha3, &data, sizeof(data) * CHAR_BIT);
				mk_sha3_256_finish(&sha3, &data);
			}
			memcpy(&context->m_prev_hash, &data, sizeof(data));

			mk_check(memcmp(&data, context->m_md, sizeof(data)) == 0);
		}
		break;
		case 384:
		{
			unsigned char data[48];
			unsigned char* prev_hash = context->m_count == 0 ? context->m_seed : context->m_prev_hash;
			memcpy(&data, prev_hash, sizeof(data));

			struct mk_sha3_384_state_s sha3;
			for(int i = 0; i != 1'000; ++i)
			{
				mk_sha3_384_init  (&sha3);
				mk_sha3_384_append(&sha3, &data, sizeof(data) * CHAR_BIT);
				mk_sha3_384_finish(&sha3, &data);
			}
			memcpy(&context->m_prev_hash, &data, sizeof(data));

			mk_check(memcmp(&data, context->m_md, sizeof(data)) == 0);
		}
		break;
		case 512:
		{
			unsigned char data[64];
			unsigned char* prev_hash = context->m_count == 0 ? context->m_seed : context->m_prev_hash;
			memcpy(&data, prev_hash, sizeof(data));

			struct mk_sha3_512_state_s sha3;
			for(int i = 0; i != 1'000; ++i)
			{
				mk_sha3_512_init  (&sha3);
				mk_sha3_512_append(&sha3, &data, sizeof(data) * CHAR_BIT);
				mk_sha3_512_finish(&sha3, &data);
			}
			memcpy(&context->m_prev_hash, &data, sizeof(data));

			mk_check(memcmp(&data, context->m_md, sizeof(data)) == 0);
		}
		break;
		default:
		{
			MK_ASSERT(0);
		}
		break;
	}

	context->m_has_md = false;
	context->m_count = -1;

	return 0;
}

static inline int process_task(struct context_s* context)
{
	MK_ASSERT(context);

	int msg_len_bytes = (context->m_msg_len_bits + (CHAR_BIT - 1)) / CHAR_BIT;
	void* msg = malloc(msg_len_bytes);
	mk_check(msg);
	hex_string_to_binary(context->m_msg, msg_len_bytes * 2, msg);
	free(context->m_msg);
	context->m_msg = NULL;

	switch(context->m_digest_len_bits)
	{
		case 224:
		{
			unsigned char digest[28];
			struct mk_sha3_224_state_s sha3;
			mk_sha3_224_init(&sha3);
			mk_sha3_224_append(&sha3, msg, context->m_msg_len_bits);
			mk_sha3_224_finish(&sha3, &digest);

			mk_check(memcmp(digest, context->m_md, sizeof(digest)) == 0);
		}
		break;
		case 256:
		{
			unsigned char digest[32];
			struct mk_sha3_256_state_s sha3;
			mk_sha3_256_init(&sha3);
			mk_sha3_256_append(&sha3, msg, context->m_msg_len_bits);
			mk_sha3_256_finish(&sha3, &digest);

			mk_check(memcmp(digest, context->m_md, sizeof(digest)) == 0);
		}
		break;
		case 384:
		{
			unsigned char digest[48];
			struct mk_sha3_384_state_s sha3;
			mk_sha3_384_init(&sha3);
			mk_sha3_384_append(&sha3, msg, context->m_msg_len_bits);
			mk_sha3_384_finish(&sha3, &digest);

			mk_check(memcmp(digest, context->m_md, sizeof(digest)) == 0);
		}
		break;
		case 512:
		{
			unsigned char digest[64];
			struct mk_sha3_512_state_s sha3;
			mk_sha3_512_init(&sha3);
			mk_sha3_512_append(&sha3, msg, context->m_msg_len_bits);
			mk_sha3_512_finish(&sha3, &digest);

			mk_check(memcmp(digest, context->m_md, sizeof(digest)) == 0);
		}
		break;
		default:
		{
			MK_ASSERT(0);
		}
		break;
	}

	free(msg);
	context->m_msg_len_bits = -1;
	context->m_has_md = false;

	return 0;
}

static inline int expect_count(struct context_s* context, char const* line)
{
	MK_ASSERT(context);
	MK_ASSERT(line);

	int count;
	int scanned = sscanf(line, "COUNT = %d\n", &count);
	mk_check(scanned == 1);

	context->m_count = count;

	return 0;
}

static inline int expect_md(struct context_s* context, char const* line)
{
	MK_ASSERT(context);
	MK_ASSERT(line);

	char buff[64 * 2 + 1];

	int md_len_bytes = context->m_digest_len_bits / CHAR_BIT;
	int scanned = sscanf(line, "MD = %s\n", buff);
	mk_check(scanned == 1);

	hex_string_to_binary(buff, md_len_bytes * 2, context->m_md);

	context->m_has_md = true;

	return 0;
}

static inline int expect_msg(struct context_s* context, char const* line)
{
	MK_ASSERT(context);
	MK_ASSERT(line);

	int msg_len_bytes = (context->m_msg_len_bits + (CHAR_BIT - 1)) / CHAR_BIT;
	int buff_len = 2 * msg_len_bytes + 1;
	char* msg = (char*)malloc(buff_len);
	mk_check(msg);

	int scanned = sscanf(line, "Msg = %s\n", msg);
	mk_check(scanned == 1);

	context->m_msg = msg;

	return 0;
}

static inline int expect_msg_len(struct context_s* context, char const* line)
{
	MK_ASSERT(context);
	MK_ASSERT(line);

	int msg_len_bits;
	int scanned = sscanf(line, "Len = %d\n", &msg_len_bits);
	mk_check(scanned == 1);
	mk_check(msg_len_bits >= 0);
	mk_check(msg_len_bits <= 16 * 1024 * CHAR_BIT);

	context->m_msg_len_bits = msg_len_bits;

	return 0;
}

static inline int expect_monte(struct context_s* context, char const* line)
{
	MK_ASSERT(context);
	MK_ASSERT(line);

	bool have_count = context->m_count != -1 ? true : false;
	if(!have_count)
	{
		mk_try(expect_count(context, line));
	}
	else
	{
		mk_try(expect_md(context, line));
	}

	return 0;
}

static inline int expect_task(struct context_s* context, char const* line)
{
	MK_ASSERT(context);
	MK_ASSERT(line);

	if(context->m_msg_len_bits == -1)
	{
		mk_try(expect_msg_len(context, line));
	}
	else if(context->m_msg == NULL)
	{
		mk_try(expect_msg(context, line));
	}
	else
	{
		MK_ASSERT(!context->m_has_md);
		mk_try(expect_md(context, line));
	}

	return 0;
}

static inline int expect_seed(struct context_s* context, char const* line)
{
	MK_ASSERT(context);
	MK_ASSERT(line);
	MK_ASSERT(context->m_digest_len_bits != -1);
	
	char buff[64 * 2 + 1];

	int md_len_bytes = context->m_digest_len_bits / CHAR_BIT;
	int scanned = sscanf(line, "Seed = %s\n", buff);
	if(scanned == 0)
	{
		return 0;
	}
	mk_check(scanned == 1);

	hex_string_to_binary(buff, md_len_bytes * 2, context->m_seed);

	context->m_has_seed = true;

	return 0;
}

static inline int expect_digest_len(struct context_s* context, char const* line)
{
	MK_ASSERT(context);
	MK_ASSERT(line);

	int digest_len;
	int scanned = sscanf(line, "[L = %d ]\n", &digest_len);
	mk_check(scanned == 1);

	switch(digest_len)
	{
		case 224:
		case 256:
		case 384:
		case 512:
		{
			context->m_digest_len_bits = digest_len;
		}
		break;
		default:
		{
			mk_check(0);
		}
		break;
	}

	return 0;
}

static inline int process_line(struct context_s* context, char const* line)
{
	MK_ASSERT(context);
	MK_ASSERT(line);

	int len = (int)strlen(line);
	
	if(len == 0)
	{
		return 0;
	}
	if(line[0] == '#')
	{
		return 0;
	}
	if(line[0] == '\n')
	{
		return 0;
	}

	bool have_digest_len = context->m_digest_len_bits != 0 ? true : false;
	if(!have_digest_len)
	{
		mk_try(expect_digest_len(context, line));
		return 0;
	}

	bool has_seed = context->m_has_seed;
	if(!has_seed)
	{
		mk_try(expect_seed(context, line));
		has_seed = context->m_has_seed;
		if(has_seed)
		{
			return 0;
		}
	}

	has_seed = context->m_has_seed;
	if(!has_seed)
	{
		bool have_task = context->m_has_md;
		MK_ASSERT(!have_task);
		mk_try(expect_task(context, line));
	}
	else
	{
		mk_try(expect_monte(context, line));
	}

	return 0;
}

static inline int test_file(char const* file_name, int* msg_count)
{
	MK_ASSERT(file_name);
	MK_ASSERT(msg_count);

	FILE* file = fopen(file_name, "r");
	mk_check(file);

	struct context_s context;
	context.m_digest_len_bits = 0;
	context.m_has_seed = false;
	context.m_msg_len_bits = -1;
	context.m_msg = NULL;
	context.m_has_md = false;
	context.m_count = -1;

	int buffer_size = 32 * 1024;
	char* buffer = malloc(buffer_size);
	mk_check(buffer);
	
	for(;;)
	{
		bool has_msg = context.m_msg != NULL ? true : false;
		bool has_md = context.m_has_md;
		bool has_task = has_msg && has_md;
		if(has_task)
		{
			mk_try(process_task(&context));
			++*msg_count;
			continue;
		}

		bool has_count = context.m_count != -1 ? true : false;
		has_md = context.m_has_md;
		bool has_monte = has_count && has_md;
		if(has_monte)
		{
			mk_try(process_monte(&context));
			++*msg_count;
			continue;
		}

		char* read = fgets(buffer, buffer_size, file);
		if(!read)
		{
			if(feof(file) != 0)
			{
				break;
			}
			mk_check(0);
		}
		MK_ASSERT(read == buffer);

		mk_try(process_line(&context, buffer));
	}

	free(buffer);

	mk_check(fclose(file) == 0);

	return 0;
}

static inline int test_files(int* msg_count, int* file_count)
{
	MK_ASSERT(msg_count);
	MK_ASSERT(file_count);

	int n = sizeof(s_file_names) / sizeof(s_file_names[0]);
	for(int i = 0; i != n; ++i)
	{
		mk_try(test_file(s_file_names[i], msg_count));
		++*file_count;
	}

	return 0;
}


int main()
{
	int msg_count = 0;
	int file_count = 0;

	int err = test_files(&msg_count, &file_count);
	if(err != 0)
	{
		printf("Failure: %d.\n", err);
		return EXIT_FAILURE;
	}

	printf("Success, processed %d messages in %d files.\n", msg_count, file_count);
	return EXIT_SUCCESS;
}
