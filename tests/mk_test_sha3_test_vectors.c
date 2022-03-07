#include "../mk_sha3.h"

#include "mk_test_utils.h"

#include <assert.h> /* assert */
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
	int m_msg_len_bits;
	char const* m_msg;
	char const* m_md;
};


#define try(x) do{ int err = (x); if(err != 0){ return err; } }while(0)
#define check(x) do{ if(!(x)){ return __LINE__; } }while(0)


static inline void context_init(struct context_s* context)
{
	assert(context);

	context->m_digest_len_bits = 0;
	context->m_msg_len_bits = 0;
	context->m_msg = NULL;
	context->m_md = NULL;
}

static inline void context_close(struct context_s* context)
{
	assert(context);

	free((void*)context->m_msg);
	free((void*)context->m_md);

	context->m_msg_len_bits = 0;
	context->m_msg = NULL;
	context->m_md = NULL;
}

static inline bool context_has_digest_len(struct context_s* context)
{
	assert(context);

	return context->m_digest_len_bits != 0 ? true : false;
}

static inline bool context_has_task(struct context_s* context)
{
	assert(context);

	return context->m_md != NULL ? true : false;
}


static inline int process_task(struct context_s* context)
{
	assert(context);

	int msg_len_bytes = (context->m_msg_len_bits + (CHAR_BIT - 1)) / CHAR_BIT;
	void* msg = malloc(msg_len_bytes);
	check(msg);
	hex_string_to_binary(context->m_msg, msg_len_bytes * 2, msg);

	switch(context->m_digest_len_bits)
	{
		case 224:
		{
			unsigned char baseline_digest[28];
			hex_string_to_binary(context->m_md, sizeof(baseline_digest) * 2, &baseline_digest);

			unsigned char digest[sizeof(baseline_digest)];
			struct mk_sha3_224_state_s sha3;
			mk_sha3_224_init(&sha3);
			mk_sha3_224_append(&sha3, msg, context->m_msg_len_bits);
			mk_sha3_224_finish(&sha3, &digest);

			check(memcmp(digest, baseline_digest, sizeof(baseline_digest)) == 0);
		}
		break;
		case 256:
		{
			check(0);
		}
		break;
		case 387:
		{
			check(0);
		}
		break;
		case 512:
		{
			check(0);
		}
		break;
		default:
		{
			check(0);
		}
		break;
	}

	free(msg);
	context_close(context);

	return 0;
}

static inline int expect_md(struct context_s* context, char const* line)
{
	assert(context);
	assert(line);

	int md_len_bytes = context->m_digest_len_bits / CHAR_BIT;
	int buff_len = 2 * md_len_bytes + 1;
	char* md = (char*)malloc(buff_len);
	check(md);

	int scanned = sscanf(line, "MD = %s\n", md);
	check(scanned == 1);

	context->m_md = md;

	return 0;
}

static inline int expect_msg(struct context_s* context, char const* line)
{
	assert(context);
	assert(line);

	int msg_len_bytes = (context->m_msg_len_bits + (CHAR_BIT - 1)) / CHAR_BIT;
	int buff_len = 2 * msg_len_bytes + 1;
	char* msg = (char*)malloc(buff_len);
	check(msg);

	int scanned = sscanf(line, "Msg = %s\n", msg);
	check(scanned == 1);

	context->m_msg = msg;

	return 0;
}

static inline int expect_msg_len(struct context_s* context, char const* line)
{
	assert(context);
	assert(line);

	int msg_len;
	int scanned = sscanf(line, "Len = %d\n", &msg_len);
	if(scanned != 1)
	{
		return __LINE__;
	}
	if(msg_len < 0)
	{
		return __LINE__;
	}
	if(msg_len > 16 * 1024 * CHAR_BIT)
	{
		return __LINE__;
	}

	context->m_msg_len_bits = msg_len;

	return 0;
}

static inline int expect_task(struct context_s* context, char const* line)
{
	assert(context);
	assert(line);

	if(context->m_msg_len_bits == 0)
	{
		try(expect_msg_len(context, line));
	}
	else if(context->m_msg == NULL)
	{
		try(expect_msg(context, line));
	}
	else
	{
		assert(context->m_md == NULL);
		try(expect_md(context, line));
	}

	return 0;
}

static inline int expect_digest_len(struct context_s* context, char const* line, int len)
{
	assert(context);
	assert(line);
	assert(len > 0);

	int digest_len;
	int scanned = sscanf(line, "[L = %d ]\n", &digest_len);
	check(scanned == 1);

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
			return __LINE__;
		}
		break;
	}

	return 0;
}

static inline int process_line(struct context_s* context, char const* line)
{
	assert(context);
	assert(line);

	int len = strlen(line);
	
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

	bool have_digest_len = context->m_digest_len_bits == 0 ? true : false;
	if(have_digest_len)
	{
		try(expect_digest_len(context, line, len));
	}
	else
	{
		bool have_task = context->m_md != NULL;
		assert(!have_task);
		try(expect_task(context, line));
	}

	return 0;
}

static inline int test_file(char const* file_name)
{
	assert(file_name);

	FILE* file = fopen(file_name, "r");
	if(!file)
	{
		return __LINE__;
	}

	struct context_s context;
	context_init(&context);

	int buffer_size = 32 * 1024;
	char* buffer = malloc(buffer_size);
	
	for(;;)
	{
		bool has_task = context_has_task(&context);
		if(has_task)
		{
			try(process_task(&context));
			continue;
		}

		char* read = fgets(buffer, buffer_size, file);
		if(!read)
		{
			if(feof(file) != 0)
			{
				break;
			}
			return __LINE__;
		}
		assert(read == buffer);

		try(process_line(&context, buffer));
	}
	free(buffer);

	check(fclose(file) == 0);

	return 0;
}

static inline int test_files()
{
	int file_count = sizeof(s_file_names) / sizeof(s_file_names[0]);
	for(int i = 0; i != file_count; ++i)
	{
		try(test_file(s_file_names[i]));
	}
	return 0;
}


int main()
{
	int err = test_files();
	if(err != 0)
	{
		printf("Failure: %d.\n", err);
		return EXIT_FAILURE;
	}

	printf("Success.\n");
	return EXIT_SUCCESS;
}
