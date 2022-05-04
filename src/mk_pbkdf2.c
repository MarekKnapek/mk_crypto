#include "mk_pbkdf2.h"

#include "mk_hash_fn.h"
#include "mk_hmac.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <string.h> /* memcpy memset */


static mk_inline void mk_pbkdf2_detail_inc(unsigned char* counter_be)
{
	int i;

	mk_assert(counter_be);

	i = 4 - 1;
	do
	{
		counter_be[i] += 1;
	}while(counter_be[i--] == 0 && i >= 0);
}

static mk_inline void mk_pbkdf2_detail_xor(int count, unsigned char const* src1, unsigned char const* src2, unsigned char* dst)
{
	int i;

	mk_assert(count >= 0);
	mk_assert(src1);
	mk_assert(src2);
	mk_assert(dst);

	for(i = 0; i != count; ++i)
	{
		dst[i] = src1[i] ^ src2[i];
	}
}


void mk_pbkdf2(enum mk_pbkdf2_hash_e hash_id, void const* password, int password_len, void const* salt, int salt_len, int iterations, int key_len, void* key)
{
	int digest_len;
	int blocks;
	int rest;
	unsigned char* output;
	int remaining;
	int i;
	unsigned char counter_be[4];
	struct mk_hmac_s hash;
	unsigned char digest_1[mk_hash_fn_max_digest_len];
	int j;
	unsigned char digest_2[mk_hash_fn_max_digest_len];

	mk_assert(password || password_len == 0);
	mk_assert(password_len >= 0);
	mk_assert(salt || salt_len == 0);
	mk_assert(salt_len >= 0);
	mk_assert(iterations > 0);
	mk_assert(key_len > 0);
	mk_assert(key);

	digest_len = mk_hash_fn_get_digest_len((enum mk_hash_fn_e)hash_id);
	blocks = (key_len - 1) / digest_len + 1;
	rest = key_len - (blocks - 1) * digest_len;
	output = (unsigned char*)key;
	remaining = key_len;

	memset(&counter_be, 0, 4);
	for(i = 0; i != blocks; ++i)
	{
		mk_pbkdf2_detail_inc(counter_be);
		mk_hmac_init(&hash, hash_id, password, password_len);
		mk_hmac_append(&hash, salt, salt_len);
		mk_hmac_append(&hash, counter_be, 4);
		mk_hmac_finish(&hash, digest_1);
		memcpy(digest_2, digest_1, digest_len);
		for(j = 1; j != iterations; ++j)
		{
			mk_hmac_init(&hash, hash_id, password, password_len);
			mk_hmac_append(&hash, digest_2, digest_len);
			mk_hmac_finish(&hash, digest_2);
			mk_pbkdf2_detail_xor(digest_len, digest_1, digest_2, digest_1);
		}
		memcpy(output, digest_1, i == blocks - 1 ? rest : digest_len);
		output += digest_len;
		remaining -= digest_len;
	}
}
