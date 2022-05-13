#include "../../../src/hash/mk_md2.h"
#include "../../../src/hash/mk_md4.h"
#include "../../../src/hash/mk_md5.h"
#include "../../../src/hash/mk_sha1.h"
#include "../../../src/hash/mk_sha2_224.h"
#include "../../../src/hash/mk_sha2_256.h"
#include "../../../src/hash/mk_sha2_384.h"
#include "../../../src/hash/mk_sha2_512.h"
#include "../../../src/hash/mk_sha2_512224.h"
#include "../../../src/hash/mk_sha2_512256.h"
#include "../../../src/utils/mk_inline.h"

#include <stddef.h> /* size_t offsetof */
#include <stdio.h> /* printf fprintf stderr fopen fclose fread feof */
#include <stdlib.h> /* EXIT_SUCCESS EXIT_FAILURE */


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err = (x); if(err != 0){ return err; } }while(0)


struct alg_descr_s
{
	char const* m_name;
	int m_name_len;
	int m_digest_len_bytes;
	int m_offset;
	void(*m_init)(void* state);
	void(*m_append_bytes)(void* state, void const* msg, size_t msg_len_bytes);
	void(*m_finish)(void* state, void* digest);
};

struct hash_states_s
{
	struct mk_md2_s m_state_md2;
	struct mk_md4_s m_state_md4;
	struct mk_md5_state_s m_state_md5;
	struct mk_sha1_state_s m_state_sha1;
	struct mk_sha2_224_state_s m_state_sha2_224;
	struct mk_sha2_256_state_s m_state_sha2_256;
	struct mk_sha2_384_state_s m_state_sha2_384;
	struct mk_sha2_512_state_s m_state_sha2_512;
	struct mk_sha2_512224_state_s m_state_sha2_512224;
	struct mk_sha2_512256_state_s m_state_sha2_512256;
};


static char const s_alg_name_00[] = "MD2";
static char const s_alg_name_01[] = "MD4";
static char const s_alg_name_02[] = "MD5";
static char const s_alg_name_03[] = "SHA-1";
static char const s_alg_name_04[] = "SHA-224";
static char const s_alg_name_05[] = "SHA-256";
static char const s_alg_name_06[] = "SHA-384";
static char const s_alg_name_07[] = "SHA-512";
static char const s_alg_name_08[] = "SHA-512/224";
static char const s_alg_name_09[] = "SHA-512/256";

static struct alg_descr_s const s_alg_descrs[] =
{
	{s_alg_name_00, sizeof(s_alg_name_00) - 1, 16, offsetof(struct hash_states_s, m_state_md2),         (void(*)(void*))&mk_md2_init,         (void(*)(void*, void const*, size_t))&mk_md2_append,         (void(*)(void*, void*))&mk_md2_finish},
	{s_alg_name_01, sizeof(s_alg_name_01) - 1, 16, offsetof(struct hash_states_s, m_state_md4),         (void(*)(void*))&mk_md4_init,         (void(*)(void*, void const*, size_t))&mk_md4_append,         (void(*)(void*, void*))&mk_md4_finish},
	{s_alg_name_02, sizeof(s_alg_name_02) - 1, 16, offsetof(struct hash_states_s, m_state_md5),         (void(*)(void*))&mk_md5_init,         (void(*)(void*, void const*, size_t))&mk_md5_append,         (void(*)(void*, void*))&mk_md5_finish},
	{s_alg_name_03, sizeof(s_alg_name_03) - 1, 20, offsetof(struct hash_states_s, m_state_sha1),        (void(*)(void*))&mk_sha1_init,        (void(*)(void*, void const*, size_t))&mk_sha1_append,        (void(*)(void*, void*))&mk_sha1_finish},
	{s_alg_name_04, sizeof(s_alg_name_04) - 1, 28, offsetof(struct hash_states_s, m_state_sha2_224),    (void(*)(void*))&mk_sha2_224_init,    (void(*)(void*, void const*, size_t))&mk_sha2_224_append,    (void(*)(void*, void*))&mk_sha2_224_finish},
	{s_alg_name_05, sizeof(s_alg_name_05) - 1, 32, offsetof(struct hash_states_s, m_state_sha2_256),    (void(*)(void*))&mk_sha2_256_init,    (void(*)(void*, void const*, size_t))&mk_sha2_256_append,    (void(*)(void*, void*))&mk_sha2_256_finish},
	{s_alg_name_06, sizeof(s_alg_name_06) - 1, 48, offsetof(struct hash_states_s, m_state_sha2_384),    (void(*)(void*))&mk_sha2_384_init,    (void(*)(void*, void const*, size_t))&mk_sha2_384_append,    (void(*)(void*, void*))&mk_sha2_384_finish},
	{s_alg_name_07, sizeof(s_alg_name_07) - 1, 64, offsetof(struct hash_states_s, m_state_sha2_512),    (void(*)(void*))&mk_sha2_512_init,    (void(*)(void*, void const*, size_t))&mk_sha2_512_append,    (void(*)(void*, void*))&mk_sha2_512_finish},
	{s_alg_name_08, sizeof(s_alg_name_08) - 1, 28, offsetof(struct hash_states_s, m_state_sha2_512224), (void(*)(void*))&mk_sha2_512224_init, (void(*)(void*, void const*, size_t))&mk_sha2_512224_append, (void(*)(void*, void*))&mk_sha2_512224_finish},
	{s_alg_name_09, sizeof(s_alg_name_09) - 1, 32, offsetof(struct hash_states_s, m_state_sha2_512256), (void(*)(void*))&mk_sha2_512256_init, (void(*)(void*, void const*, size_t))&mk_sha2_512256_append, (void(*)(void*, void*))&mk_sha2_512256_finish},
};


static mk_inline void mk_bytes_to_string(void const* input, int count, void* output)
{
	static char const s_alphabet[] = "0123456789abcdef";
	
	unsigned char const* in;
	char* out;
	int i;

	in = (unsigned char const*)input;
	out = (char*)output;
	for(i = 0; i != count; ++i)
	{
		out[i * 2 + 0] = s_alphabet[(in[i] >> 4) & 0x0f];
		out[i * 2 + 1] = s_alphabet[(in[i] >> 0) & 0x0f];
	}
}

static mk_inline int mk_hash_file(int argc, char const* const* argv)
{
	int alg_count;
	struct hash_states_s hash_states;
	int i;
	char const* file_name;
	FILE* file;
	unsigned char buff[1024];
	int offset;
	void* hash_state;
	int longest_name;
	unsigned char digest_bytes[64];
	char digest_string[2 * 64 + 1];
	int digest_len_bytes;

	mk_check(argc == 2);

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	for(i = 0; i != alg_count; ++i)
	{
		offset = s_alg_descrs[i].m_offset;
		hash_state = (unsigned char*)&hash_states + offset;
		s_alg_descrs[i].m_init(hash_state);
	}

	file_name = argv[1];
	file = fopen(file_name, "rb");
	mk_check(file);

	for(;;)
	{
		size_t read = fread(buff, 1, sizeof(buff), file);
		if(read == 0)
		{
			mk_check(feof(file) != 0);
			break;
		}
		for(i = 0; i != alg_count; ++i)
		{
			offset = s_alg_descrs[i].m_offset;
			hash_state = (unsigned char*)&hash_states + offset;
			s_alg_descrs[i].m_append_bytes(hash_state, buff, read);
		}
	}
	
	mk_check(fclose(file) == 0);

	longest_name = 0;
	for(i = 0; i != alg_count; ++i)
	{
		longest_name = s_alg_descrs[i].m_name_len > longest_name ? s_alg_descrs[i].m_name_len : longest_name;
	}

	for(i = 0; i != alg_count; ++i)
	{
		offset = s_alg_descrs[i].m_offset;
		hash_state = (unsigned char*)&hash_states + offset;
		s_alg_descrs[i].m_finish(hash_state, &digest_bytes);
		digest_len_bytes = s_alg_descrs[i].m_digest_len_bytes;
		mk_bytes_to_string(&digest_bytes, digest_len_bytes, &digest_string);
		digest_string[digest_len_bytes * 2] = '\0';
		printf("%-*s %s\n", longest_name, s_alg_descrs[i].m_name, digest_string);
	}

	return 0;
}


int main(int argc, char const* const* argv)
{
	int err = mk_hash_file(argc, argv);
	if(err != 0)
	{
		fprintf(stderr, "Error at line %d.\n", err);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


#undef mk_check
#undef mk_try


#include "../../../src/hash/mk_md2.c"
#include "../../../src/hash/mk_md4.c"
#include "../../../src/hash/mk_md5.c"
#include "../../../src/hash/mk_sha1.c"
#include "../../../src/hash/mk_sha2_224.c"
#include "../../../src/hash/mk_sha2_256.c"
#include "../../../src/hash/mk_sha2_384.c"
#include "../../../src/hash/mk_sha2_512.c"
#include "../../../src/hash/mk_sha2_512224.c"
#include "../../../src/hash/mk_sha2_512256.c"

#include "../../../src/hash/base/mk_md2_base.c"
#include "../../../src/hash/base/mk_md4_base.c"

#include "../../../src/hash/mk_sha2_detail_256.c"
#include "../../../src/hash/mk_sha2_detail_512.c"

#include "../../../../mk_int/src/base/mk_uint_base_char.c"
#include "../../../../mk_int/src/base/mk_uint_base_short.c"
#include "../../../../mk_int/src/base/mk_uint_base_int.c"
#include "../../../../mk_int/src/base/mk_uint_base_long.c"
#include "../../../../mk_int/src/base/mk_uint_base_llong.c"
#include "../../../../mk_int/src/base/mk_uint_base_128.c"

#include "../../../../mk_int/src/exact/mk_uint_8.c"
#include "../../../../mk_int/src/exact/mk_uint_16.c"
#include "../../../../mk_int/src/exact/mk_uint_32.c"
#include "../../../../mk_int/src/exact/mk_uint_64.c"
#include "../../../../mk_int/src/exact/mk_uint_128.c"
