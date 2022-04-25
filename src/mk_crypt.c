#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <string.h> /* memcpy memset */


#define mk_aes_jumbo 1
#include "mk_aes.c"
#undef mk_aes_jumbo


#if defined(mk_crypt_jumbo) && mk_crypt_jumbo == 1
#define mk_jumbo static mk_inline
#else
#define mk_jumbo
#endif


/* concept of crypt algorithm */

enum mk_crypt_algorithm_e
{
	mk_crypt_algorithm_aes128,
	mk_crypt_algorithm_aes192,
	mk_crypt_algorithm_aes256,
};

/* concept of crypt algorithm end */

#define mk_assert_algorithm(algorithm) mk_assert \
	( \
		(algorithm) == mk_crypt_algorithm_aes128 || \
		(algorithm) == mk_crypt_algorithm_aes192 || \
		(algorithm) == mk_crypt_algorithm_aes256 || \
		0 \
	)

/* concept of crypt key */
/* depends on crypt algorithm */

enum mk_crypt_key_len_e
{
	mk_crypt_key_len_aes128 = 16,
	mk_crypt_key_len_aes192 = 24,
	mk_crypt_key_len_aes256 = 32,
};

struct mk_crypt_key_aes128_s
{
	unsigned char m_key[mk_crypt_key_len_aes128];
};

struct mk_crypt_key_aes192_s
{
	unsigned char m_key[mk_crypt_key_len_aes192];
};

struct mk_crypt_key_aes256_s
{
	unsigned char m_key[mk_crypt_key_len_aes256];
};

union mk_crypt_key_u
{
	struct mk_crypt_key_aes128_s m_aes128;
	struct mk_crypt_key_aes192_s m_aes192;
	struct mk_crypt_key_aes256_s m_aes256;
};

/* concept of crypt key end */

/* concept of crypt key init */
/* depends on crypt algorithm */
/* depends on crypt key */

static mk_inline void mk_crypt_key_init_aes128(struct mk_crypt_key_aes128_s* key, void const* input)
{
	mk_assert(key);
	mk_assert(input);

	memcpy(key->m_key, input, mk_crypt_key_len_aes128);
}

static mk_inline void mk_crypt_key_init_aes192(struct mk_crypt_key_aes192_s* key, void const* input)
{
	mk_assert(key);
	mk_assert(input);

	memcpy(key->m_key, input, mk_crypt_key_len_aes192);
}

static mk_inline void mk_crypt_key_init_aes256(struct mk_crypt_key_aes256_s* key, void const* input)
{
	mk_assert(key);
	mk_assert(input);

	memcpy(key->m_key, input, mk_crypt_key_len_aes256);
}

static mk_inline void mk_crypt_key_init(enum mk_crypt_algorithm_e algorithm, union mk_crypt_key_u* key, void const* input)
{
	mk_assert(key);
	mk_assert(input);

	switch(algorithm)
	{
		case mk_crypt_algorithm_aes128: mk_crypt_key_init_aes128(&key->m_aes128, input); break;
		case mk_crypt_algorithm_aes192: mk_crypt_key_init_aes192(&key->m_aes192, input); break;
		case mk_crypt_algorithm_aes256: mk_crypt_key_init_aes256(&key->m_aes256, input); break;
	}
}

/* concept of crypt key init end */

/* concept of crypt block */

enum mk_crypt_block_len_e
{
	mk_crypt_block_len_aes128 = 16,
	mk_crypt_block_len_aes192 = 16,
	mk_crypt_block_len_aes256 = 16,
	mk_crypt_block_len_max = 16,
};

/* concept of crypt block end */

/* concept of crypt block get len */
/* depends on crypt block */
/* depends on crypt algorithm */

static mk_inline enum mk_crypt_block_len_e mk_crypt_block_get_len(enum mk_crypt_algorithm_e algorithm)
{
	mk_assert_algorithm(algorithm);

	switch(algorithm)
	{
		case mk_crypt_algorithm_aes128: return mk_crypt_block_len_aes128; break;
		case mk_crypt_algorithm_aes192: return mk_crypt_block_len_aes192; break;
		case mk_crypt_algorithm_aes256: return mk_crypt_block_len_aes256; break;
	}

	return 0;
}

/* concept of crypt block get len end */

/* concept of crypt block encrypt */
/* depends on crypt algorithm */
/* depends on crypt key */
/* depends on crypt block */

static mk_inline void mk_crypt_block_encrypt_aes128(struct mk_crypt_key_aes128_s const* key, unsigned char const input[mk_crypt_block_len_aes128], unsigned char output[mk_crypt_block_len_aes128])
{
	mk_aes_detail_encrypt_block_128(input, key->m_key, output);
}

static mk_inline void mk_crypt_block_encrypt_aes192(struct mk_crypt_key_aes192_s const* key, unsigned char const input[mk_crypt_block_len_aes192], unsigned char output[mk_crypt_block_len_aes192])
{
	mk_aes_detail_encrypt_block_192(input, key->m_key, output);
}

static mk_inline void mk_crypt_block_encrypt_aes256(struct mk_crypt_key_aes256_s const* key, unsigned char const input[mk_crypt_block_len_aes256], unsigned char output[mk_crypt_block_len_aes256])
{
	mk_aes_detail_encrypt_block_256(input, key->m_key, output);
}

static mk_inline void mk_crypt_block_encrypt(enum mk_crypt_algorithm_e algorithm, union mk_crypt_key_u const* key, unsigned char const* input, unsigned char* output)
{
	mk_assert(key);
	mk_assert(input);
	mk_assert(output);

	switch(algorithm)
	{
		case mk_crypt_algorithm_aes128: mk_crypt_block_encrypt_aes128(&key->m_aes128, input, output); break;
		case mk_crypt_algorithm_aes192: mk_crypt_block_encrypt_aes192(&key->m_aes192, input, output); break;
		case mk_crypt_algorithm_aes256: mk_crypt_block_encrypt_aes256(&key->m_aes256, input, output); break;
	}
}

/* concept of crypt block encrypt end */

/* concept of crypt block decrypt */
/* depends on crypt algorithm */
/* depends on crypt key */
/* depends on crypt block */

static mk_inline void mk_crypt_block_decrypt_aes128(struct mk_crypt_key_aes128_s const* key, unsigned char const input[mk_crypt_block_len_aes128], unsigned char output[mk_crypt_block_len_aes128])
{
	mk_aes_detail_decrypt_block_128(input, key->m_key, output);
}

static mk_inline void mk_crypt_block_decrypt_aes192(struct mk_crypt_key_aes192_s const* key, unsigned char const input[mk_crypt_block_len_aes192], unsigned char output[mk_crypt_block_len_aes192])
{
	mk_aes_detail_decrypt_block_192(input, key->m_key, output);
}

static mk_inline void mk_crypt_block_decrypt_aes256(struct mk_crypt_key_aes256_s const* key, unsigned char const input[mk_crypt_block_len_aes256], unsigned char output[mk_crypt_block_len_aes256])
{
	mk_aes_detail_decrypt_block_256(input, key->m_key, output);
}

static mk_inline void mk_crypt_block_decrypt(enum mk_crypt_algorithm_e algorithm, union mk_crypt_key_u const* key, unsigned char const* input, unsigned char* output)
{
	mk_assert(key);
	mk_assert(input);
	mk_assert(output);

	switch(algorithm)
	{
		case mk_crypt_algorithm_aes128: mk_crypt_block_decrypt_aes128(&key->m_aes128, input, output); break;
		case mk_crypt_algorithm_aes192: mk_crypt_block_decrypt_aes192(&key->m_aes192, input, output); break;
		case mk_crypt_algorithm_aes256: mk_crypt_block_decrypt_aes256(&key->m_aes256, input, output); break;
	}
}

/* concept of crypt block decrypt end */

/* concept of crypt operation mode */

enum mk_crypt_operation_mode_e
{
	mk_crypt_operation_mode_cbc,
	mk_crypt_operation_mode_cfb,
	mk_crypt_operation_mode_ctr,
	mk_crypt_operation_mode_cts,
	mk_crypt_operation_mode_ecb,
	mk_crypt_operation_mode_ofb,
	mk_crypt_operation_mode_pcbc,
};

/* concept of crypt operation mode end */

#define mk_assert_operation_mode(operation_mode) mk_assert \
	( \
		(operation_mode) == mk_crypt_operation_mode_cbc  || \
		(operation_mode) == mk_crypt_operation_mode_cfb  || \
		(operation_mode) == mk_crypt_operation_mode_ctr  || \
		(operation_mode) == mk_crypt_operation_mode_cts  || \
		(operation_mode) == mk_crypt_operation_mode_ecb  || \
		(operation_mode) == mk_crypt_operation_mode_ofb  || \
		(operation_mode) == mk_crypt_operation_mode_pcbc || \
		0 \
	)

/* concept of crypt iv copy */
/* depends on crypt operation mode */
/* depends on crypt algorithm */
/* depends on crypt block */
/* depends on crypt block get len */

static mk_inline void mk_crypt_iv_copy(enum mk_crypt_operation_mode_e operation_mode, enum mk_crypt_algorithm_e algorithm, void* iv, void const* input)
{
	enum mk_crypt_block_len_e block_len;

	switch(operation_mode)
	{
		case mk_crypt_operation_mode_cbc:  mk_assert(iv); mk_assert(input); block_len = mk_crypt_block_get_len(algorithm); memcpy(iv, input, block_len); break;
		case mk_crypt_operation_mode_cfb:  mk_assert(iv); mk_assert(input); block_len = mk_crypt_block_get_len(algorithm); memcpy(iv, input, block_len); break;
		case mk_crypt_operation_mode_ctr:  mk_assert(iv); mk_assert(input); block_len = mk_crypt_block_get_len(algorithm); memcpy(iv, input, block_len); break;
		case mk_crypt_operation_mode_cts:  mk_assert(iv); mk_assert(input); block_len = mk_crypt_block_get_len(algorithm); memcpy(iv, input, block_len); break;
		case mk_crypt_operation_mode_ecb:                                                                                                                break;
		case mk_crypt_operation_mode_ofb:  mk_assert(iv); mk_assert(input); block_len = mk_crypt_block_get_len(algorithm); memcpy(iv, input, block_len); break;
		case mk_crypt_operation_mode_pcbc: mk_assert(iv); mk_assert(input); block_len = mk_crypt_block_get_len(algorithm); memcpy(iv, input, block_len); break;
	}
}

/* concept of crypt iv copy end */

/* concept of crypt operation mode encrypt blocks */
/* depends on crypt operation mode */
/* depends on crypt algorithm */
/* depends on crypt key */
/* depends on crypt block */
/* depends on crypt block encrypt */

static mk_inline void mk_crypt_xor(unsigned char const* src1, unsigned char const* src2, unsigned char* dst, int n)
{
	int i;

	mk_assert(src1);
	mk_assert(src2);
	mk_assert(dst);
	mk_assert(n >= 0);

	for(i = 0; i != n; ++i)
	{
		dst[i] = src1[i] ^ src2[i];
	}
}

static mk_inline void mk_crypt_inc(unsigned char* ctr, int n)
{
	int overflow;
	int i;

	mk_assert(n >= 1);

	i = n - 1;
	++ctr[i];
	overflow = ctr[i] == 0;
	while(overflow && i != 0)
	{
		--i;
		++ctr[i];
		overflow = ctr[i] == 0;
	}
}

static mk_inline void mk_crypt_operation_mode_encrypt_cbc (enum mk_crypt_algorithm_e algorithm, int n, unsigned char* iv, union mk_crypt_key_u const* key, unsigned char const* input, unsigned char* output)
{
	enum mk_crypt_block_len_e block_len;
	unsigned char tmp[mk_crypt_block_len_max];
	int i;

	mk_assert(n >= 1);

	block_len = mk_crypt_block_get_len(algorithm);
	
	mk_crypt_xor(input, iv, tmp, block_len);
	mk_crypt_block_encrypt(algorithm, key, tmp, output);
	for(i = 1; i != n; ++i)
	{
		input += block_len;
		mk_crypt_xor(input, output, tmp, block_len);
		output += block_len;
		mk_crypt_block_encrypt(algorithm, key, tmp, output);
	}
	memcpy(iv, output, block_len);
}

static mk_inline void mk_crypt_operation_mode_encrypt_cfb (enum mk_crypt_algorithm_e algorithm, int n, unsigned char* iv, union mk_crypt_key_u const* key, unsigned char const* input, unsigned char* output)
{
	enum mk_crypt_block_len_e block_len;
	unsigned char tmp[mk_crypt_block_len_max];
	int i;
	int j;
	int k;

	mk_assert(n >= 1);

	block_len = mk_crypt_block_get_len(algorithm);

	for(i = 0; i != n; ++i)
	{
		for(j = 0; j != block_len; ++j)
		{
			mk_crypt_block_encrypt(algorithm, key, iv, tmp);
			output[j] = input[j] ^ tmp[0];
			for(k = 0; k != block_len - 1; ++k)
			{
				iv[k] = iv[k + 1];
			}
			iv[block_len - 1] = output[j];
		}
		input += block_len;
		output += block_len;
	}
}

static mk_inline void mk_crypt_operation_mode_encrypt_ctr (enum mk_crypt_algorithm_e algorithm, int n, unsigned char* iv, union mk_crypt_key_u const* key, unsigned char const* input, unsigned char* output)
{
	enum mk_crypt_block_len_e block_len;
	unsigned char tmp[mk_crypt_block_len_max];
	unsigned char ctr[mk_crypt_block_len_max];
	int i;

	mk_assert(n >= 1);

	block_len = mk_crypt_block_get_len(algorithm);
	
	mk_crypt_block_encrypt(algorithm, key, iv, tmp);
	mk_crypt_xor(input, tmp, output, block_len);
	memcpy(ctr, iv, block_len);
	mk_crypt_inc(ctr, block_len);
	for(i = 1; i != n; ++i)
	{
		mk_crypt_block_encrypt(algorithm, key, ctr, tmp);
		input += block_len;
		output += block_len;
		mk_crypt_xor(input, tmp, output, block_len);
		mk_crypt_inc(ctr, block_len);
	}
	memcpy(iv, ctr, block_len);
}

static mk_inline void mk_crypt_operation_mode_encrypt_cts (enum mk_crypt_algorithm_e algorithm, int n, unsigned char* iv, union mk_crypt_key_u const* key, unsigned char const* input, unsigned char* output)
{
	/*TODO*/
	(void)algorithm;
	(void)n;
	(void)key;
	(void)iv;
	(void)input;
	(void)output;
}

static mk_inline void mk_crypt_operation_mode_encrypt_ecb (enum mk_crypt_algorithm_e algorithm, int n, unsigned char* iv, union mk_crypt_key_u const* key, unsigned char const* input, unsigned char* output)
{
	enum mk_crypt_block_len_e block_len;
	int i;

	mk_assert(n >= 1);
	(void)iv;
	
	block_len = mk_crypt_block_get_len(algorithm);

	for(i = 0; i != n; ++i)
	{
		mk_crypt_block_encrypt(algorithm, key, input, output);
		input += block_len;
		output += block_len;
	}
}

static mk_inline void mk_crypt_operation_mode_encrypt_ofb (enum mk_crypt_algorithm_e algorithm, int n, unsigned char* iv, union mk_crypt_key_u const* key, unsigned char const* input, unsigned char* output)
{
	enum mk_crypt_block_len_e block_len;
	unsigned char tmp[mk_crypt_block_len_max];
	int i;

	mk_assert(n >= 1);

	block_len = mk_crypt_block_get_len(algorithm);
	
	mk_crypt_block_encrypt(algorithm, key, iv, tmp);
	mk_crypt_xor(input, tmp, output, block_len);
	for(i = 1; i != n; ++i)
	{
		mk_crypt_block_encrypt(algorithm, key, tmp, tmp);
		input += block_len;
		output += block_len;
		mk_crypt_xor(input, tmp, output, block_len);
	}
	memcpy(iv, tmp, block_len);
}

static mk_inline void mk_crypt_operation_mode_encrypt_pcbc(enum mk_crypt_algorithm_e algorithm, int n, unsigned char* iv, union mk_crypt_key_u const* key, unsigned char const* input, unsigned char* output)
{
	enum mk_crypt_block_len_e block_len;
	unsigned char tmp[mk_crypt_block_len_max];
	int i;

	mk_assert(n >= 1);

	block_len = mk_crypt_block_get_len(algorithm);
	mk_crypt_xor(input, iv, tmp, block_len);
	mk_crypt_block_encrypt(algorithm, key, tmp, output);
	for(i = 1; i != n; ++i)
	{
		mk_crypt_xor(input, output, tmp, block_len);
		input += block_len;
		mk_crypt_xor(input, tmp, tmp, block_len);
		output += block_len;
		mk_crypt_block_encrypt(algorithm, key, tmp, output);
	}
	memcpy(iv, output, block_len);
}

static mk_inline void mk_crypt_operation_mode_encrypt(enum mk_crypt_operation_mode_e operation_mode, enum mk_crypt_algorithm_e algorithm, int n, unsigned char* iv, union mk_crypt_key_u const* key, unsigned char const* input, unsigned char* output)
{
	mk_assert(n >= 0);
	mk_assert(key);
	mk_assert(input);
	mk_assert(output);

	if(n == 0)
	{
		return;
	}

	switch(operation_mode)
	{
		case mk_crypt_operation_mode_cbc:  mk_crypt_operation_mode_encrypt_cbc (algorithm, n, iv, key, input, output); break;
		case mk_crypt_operation_mode_cfb:  mk_crypt_operation_mode_encrypt_cfb (algorithm, n, iv, key, input, output); break;
		case mk_crypt_operation_mode_ctr:  mk_crypt_operation_mode_encrypt_ctr (algorithm, n, iv, key, input, output); break;
		case mk_crypt_operation_mode_cts:  mk_crypt_operation_mode_encrypt_cts (algorithm, n, iv, key, input, output); break;
		case mk_crypt_operation_mode_ecb:  mk_crypt_operation_mode_encrypt_ecb (algorithm, n, iv, key, input, output); break;
		case mk_crypt_operation_mode_ofb:  mk_crypt_operation_mode_encrypt_ofb (algorithm, n, iv, key, input, output); break;
		case mk_crypt_operation_mode_pcbc: mk_crypt_operation_mode_encrypt_pcbc(algorithm, n, iv, key, input, output); break;
	}
}

/* concept of crypt operation mode encrypt blocks end */


struct mk_crypt_s
{
	enum mk_crypt_operation_mode_e m_operation_mode;
	enum mk_crypt_algorithm_e m_algorithm;
	unsigned char m_iv[mk_crypt_block_len_max];
	union mk_crypt_key_u m_key;
};


mk_jumbo void mk_crypt_init(struct mk_crypt_s* crypt, enum mk_crypt_operation_mode_e operation_mode, enum mk_crypt_algorithm_e algorithm, void const* iv, void const* key)
{
	mk_assert(crypt);
	mk_assert_operation_mode(operation_mode);
	mk_assert_algorithm(algorithm);
	mk_assert(key);

	crypt->m_operation_mode = operation_mode;
	crypt->m_algorithm = algorithm;
	mk_crypt_iv_copy(operation_mode, algorithm, crypt->m_iv, iv);
	mk_crypt_key_init(algorithm, &crypt->m_key, key);
}

mk_jumbo void mk_crypt_encrypt(struct mk_crypt_s* crypt, int final, void const* input, int input_len_bytes, void* output)
{
	enum mk_crypt_block_len_e block_len;
	int n;
	int m;
	unsigned char const* last_block_in;
	unsigned char* last_block_out;
	unsigned char padding[mk_crypt_block_len_max];

	mk_assert(crypt);
	mk_assert_operation_mode(crypt->m_operation_mode);
	mk_assert_algorithm(crypt->m_algorithm);
	mk_assert(final == 0 || final == 1);
	mk_assert(input || input_len_bytes == 0);
	mk_assert(input_len_bytes >= 0);
	mk_assert(output || (!input && final == 0));

	block_len = mk_crypt_block_get_len(crypt->m_algorithm);
	mk_assert(final == 1 || input_len_bytes % block_len == 0);
	n = input_len_bytes / block_len;
	m = input_len_bytes % block_len;
	mk_crypt_operation_mode_encrypt(crypt->m_operation_mode, crypt->m_algorithm, n, crypt->m_iv, &crypt->m_key, input, output);

	if(final == 1)
	{
		last_block_in = (unsigned char const*)input + n * block_len;
		last_block_out = (unsigned char*)output + n * block_len;
		memcpy(padding, last_block_in, m);
		memset(padding + m, block_len - m, block_len - m);
		mk_crypt_operation_mode_encrypt(crypt->m_operation_mode, crypt->m_algorithm, 1, crypt->m_iv, &crypt->m_key, padding, last_block_out);
	}
}


#undef mk_assert_algorithm
#undef mk_assert_operation_mode
#undef mk_jumbo
