#include "mk_pbkdf2_fuzz.h"

#include "../src/mk_pbkdf2.h"
#include "../src/mk_win_pbkdf2.h"

#include "../utils/mk_inline.h"

#include <stddef.h> /* size_t NULL */
#include <stdlib.h> /* malloc free */
#include <string.h> /* memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


void mk_pbkdf2_fuzz(unsigned char const* data, size_t size)
{
	int alg;
	int password_len;
	void const* password;
	int salt_len;
	void const* salt;
	int iterations;
	int key_len;

	enum mk_pbkdf2_hash_e mk_alg;
	enum mk_win_pbkdf2_hash_e win_alg;
	void* mk_key;
	void* win_key;

	if(!(data && size != 0))
	{
		return;
	}

	if(!(size >= 1))
	{
		return;
	}
	alg = *data;
	++data;
	--size;

	if(!(size >= 1))
	{
		return;
	}
	password_len = *data;
	++data;
	--size;

	if(!((int)size >= password_len))
	{
		return;
	}
	password = data;
	data += password_len;
	size -= password_len;

	if(!(size >= 1))
	{
		return;
	}
	salt_len = *data;
	++data;
	--size;

	if(!((int)size >= salt_len))
	{
		return;
	}
	salt = data;
	data += salt_len;
	size -= salt_len;

	if(!(size >= 1))
	{
		return;
	}
	iterations = *data;
	++data;
	--size;
	if(!(iterations != 0))
	{
		return;
	}

	if(!(size >= 1))
	{
		return;
	}
	key_len = *data;
	++data;
	--size;
	if(!(key_len != 0))
	{
		return;
	}

	if(!(size == 0))
	{
		return;
	}

	win_alg = alg % 7;
	mk_alg = 0;
	switch(win_alg)
	{
		case mk_win_pbkdf2_hash_md2: mk_alg = mk_pbkdf2_hash_md2; break;
		case mk_win_pbkdf2_hash_md4: mk_alg = mk_pbkdf2_hash_md4; break;
		case mk_win_pbkdf2_hash_md5: mk_alg = mk_pbkdf2_hash_md5; break;
		case mk_win_pbkdf2_hash_sha1: mk_alg = mk_pbkdf2_hash_sha1; break;
		case mk_win_pbkdf2_hash_sha2_256: mk_alg = mk_pbkdf2_hash_sha2_256; break;
		case mk_win_pbkdf2_hash_sha2_384: mk_alg = mk_pbkdf2_hash_sha2_384; break;
		case mk_win_pbkdf2_hash_sha2_512: mk_alg = mk_pbkdf2_hash_sha2_512; break;
	}

	mk_key = malloc(key_len);
	win_key = malloc(key_len);

	mk_pbkdf2(mk_alg, password, password_len, salt, salt_len, iterations, key_len, mk_key);
	mk_win_pbkdf2(win_alg, password, password_len, salt, salt_len, iterations, key_len, win_key);

	test(memcmp(mk_key, win_key, key_len) == 0);

	free(win_key);
	free(mk_key);
}


#undef test
