#include "mk_operation_mode_gcm.h"

#include "mk_operation_mode_impl.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

#include "../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../mk_int/src/exact/mk_uint_128.h"

#include <stdlib.h> /* NULL */
#include <string.h> /* memcpy memset */


static mk_inline void mk_gcm_xor2(unsigned char dst[16], unsigned char const src[16])
{
	int i;

	mk_assert(dst);
	mk_assert(src);

	for(i = 0; i != 16; ++i)
	{
		dst[i] ^= src[i];
	}
}

static mk_inline void mk_gcm_xor3(unsigned char dst[16], unsigned char const src1[16], unsigned char const src2[16])
{
	int i;

	mk_assert(dst);
	mk_assert(src1);
	mk_assert(src2);

	for(i = 0; i != 16; ++i)
	{
		dst[i] = src1[i] ^ src2[i];
	}
}

static mk_inline void mk_gcm_mul(unsigned char const x[16], unsigned char const y[16], unsigned char out_z[16])
{
	static unsigned char const r = 0xe1;

	unsigned char z[16];
	unsigned char v[16];
	int i;
	int j;

	memset(z, 0, 16);
	memcpy(v, x, 16);
	for(i = 0; i != 128; ++i)
	{
		if(((y[i / 8] >> (8 - i % 8)) & 1) == 1)
		{
			for(j = 0; j != 16; ++j) z[i] ^= v[i];
		}
		if(((v[15] >> 7) & 1) == 0)
		{
			for(j = 0; j != 15; ++j) v[15 - j] = (v[15 - j] >> 1) & ((v[15 - j - 1] & 1) << 7); v[0] >>= 1;
		}
		else
		{
			for(j = 0; j != 15; ++j) v[15 - j] = (v[15 - j] >> 1) & ((v[15 - j - 1] & 1) << 7); v[0] >>= 1;
			v[0] ^= r;
		}
	}
	memcpy(out_z, z, 16);
}

static mk_inline void mk_gcm_ghash_continue(void const* h, void const* x, int m, void* output_block)
{
	unsigned char const* input;
	int i;

	mk_assert(h);
	mk_assert(x);
	mk_assert(m >= 0);
	mk_assert(output_block);

	input = (unsigned char const*)x;
	for(i = 0; i != m; ++i, input += 16)
	{
		mk_gcm_xor2(output_block, input);
		mk_gcm_mul(output_block, h, output_block);
	}
}

static mk_inline void mk_gcm_ghash_start(void const* h, void const* x, int m, void* output_block)
{
	mk_assert(h);
	mk_assert(m > 0);
	mk_assert(output_block);

	mk_gcm_mul(x, h, output_block);
	mk_gcm_ghash_continue(h, (unsigned char const*)x + 16, m - 1, output_block);
}

static mk_inline void mk_gcm_inc32(void* ctr)
{
	unsigned char* input;
	int i;

	mk_assert(ctr);

	input = (unsigned char*)ctr + 12;

	i = 4 - 1;
	do
	{
		input[i] += 1;
	}while(input[i--] == 0 && i >= 0);
}

static mk_inline void mk_gcm_gctr_ghash_overlap0(enum mk_block_cipher_e block_cipher, void const* key, void* icb, void const* x, int x_len, void* out_y, void const* h, void* tag)
{
	unsigned char const* input;
	unsigned char* output;
	int n;
	int i;

	mk_assert(mk_block_cipher_get_block_len(block_cipher) == 16);
	mk_assert(key);
	mk_assert(icb);
	mk_assert(x || x_len == 0);
	mk_assert(x_len >= 0);
	mk_assert(out_y);
	mk_assert((h && tag) || (!h && !tag));

	mk_assert(x_len % 16 == 0);

	input = (unsigned char const*)x;
	output = (unsigned char*)out_y;

	n = x_len / 16;
	for(i = 0; i != n; ++i, input += 16, output += 16)
	{
		mk_block_cipher_encrypt_block(block_cipher, key, icb, output);
		mk_gcm_xor2(output, input);
		mk_gcm_inc32(icb);
		if(h)
		{
			mk_gcm_ghash_continue(h, output, 1, tag);
		}
	}
}

static mk_inline void mk_gcm_gctr_ghash_overlap1(enum mk_block_cipher_e block_cipher, void const* key, void* icb, void const* x, int x_len, void* out_y, void const* h, void* tag)
{
	unsigned char const* input;
	unsigned char* output;
	int n;
	int i;
	unsigned char tmp[16];

	mk_assert(mk_block_cipher_get_block_len(block_cipher) == 16);
	mk_assert(key);
	mk_assert(icb);
	mk_assert(x || x_len == 0);
	mk_assert(x_len >= 0);
	mk_assert(out_y);
	mk_assert((h && tag) || (!h && !tag));

	mk_assert(x_len % 16 == 0);

	input = (unsigned char const*)x;
	output = (unsigned char*)out_y;

	n = x_len / 16;
	for(i = 0; i != n; ++i, input += 16, output += 16)
	{
		mk_block_cipher_encrypt_block(block_cipher, key, icb, tmp);
		mk_gcm_xor3(output, tmp, input);
		mk_gcm_inc32(icb);
		if(h)
		{
			mk_gcm_ghash_continue(h, output, 1, tag);
		}
	}
}

static mk_inline void mk_gcm_gctr_ghash(enum mk_block_cipher_e block_cipher, void const* key, void* icb, void const* x, int x_len, void* out_y, void const* h, void* tag)
{
	unsigned char const* input;
	unsigned char* output;
	int overlap;

	mk_assert(mk_block_cipher_get_block_len(block_cipher) == 16);
	mk_assert(key);
	mk_assert(icb);
	mk_assert(x || x_len == 0);
	mk_assert(x_len >= 0);
	mk_assert(out_y);
	mk_assert((h && tag) || (!h && !tag));

	mk_assert(x_len % 16 == 0);

	input = (unsigned char const*)x;
	output = (unsigned char*)out_y;
	overlap = !(output >= input + x_len || input >= output + 16);
	if(overlap == 0)
	{
		mk_gcm_gctr_ghash_overlap0(block_cipher, key, icb, x, x_len, out_y, h, tag);
	}
	else
	{
		mk_gcm_gctr_ghash_overlap1(block_cipher, key, icb, x, x_len, out_y, h, tag);
	}
}

static mk_inline void mk_gcm_gctr_ghash_finish(enum mk_block_cipher_e block_cipher, void const* key, void* icb, void const* x, int x_len, void* out_y, void const* h, void* tag)
{
	unsigned char const* input;
	unsigned char* output;
	int n;
	int r;
	int i;
	unsigned char tmp[16];

	mk_assert(mk_block_cipher_get_block_len(block_cipher) == 16);
	mk_assert(key);
	mk_assert(icb);
	mk_assert(x || x_len == 0);
	mk_assert(x_len >= 0);
	mk_assert(out_y);
	mk_assert((h && tag) || (!h && !tag));

	input = (unsigned char const*)x;
	output = (unsigned char*)out_y;

	n = x_len / 16;
	r = x_len % 16;
	mk_gcm_gctr_ghash(block_cipher, key, icb, input, x_len, output, h, tag);
	if(r != 0)
	{
		input += n * 16;
		output += n * 16;
		mk_block_cipher_encrypt_block(block_cipher, key, icb, tmp);
		for(i = 0; i != r; ++i) output[i] = tmp[i] ^= input[i];
		if(h)
		{
			memset(tmp + r, 0, 16 - r);
			mk_gcm_ghash_continue(h, tmp, 1, tag);
		}
	}
}

static mk_inline void mk_gcm_init_h(enum mk_block_cipher_e block_cipher, void const* key, void* out_h)
{
	static unsigned char const s_zeros[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	mk_assert(mk_block_cipher_get_block_len(block_cipher) == 16);
	mk_assert(key);
	mk_assert(out_h);

	mk_block_cipher_encrypt_block(block_cipher, key, s_zeros, out_h);
}

static mk_inline void mk_gcm_init_j0(enum mk_block_cipher_e block_cipher, void const* key, void const* h, void const* iv, int iv_len, void* out_j0)
{
	unsigned char* output;
	int n;
	int s;
	unsigned char tmp[16];
	struct mk_uint64_s iv_len_tmp;

	mk_assert(mk_block_cipher_get_block_len(block_cipher) == 16);
	mk_assert(key);
	mk_assert(h);
	mk_assert(iv || iv_len == 0);
	mk_assert(iv_len >= 0);
	mk_assert(out_j0);

	output = (unsigned char*)out_j0;
	if(iv_len == 12)
	{
		memcpy(output, iv, 12);
		memset(output + 12, 0, 3);
		output[15] = 1;
	}
	else
	{
		n = iv_len / 16;
		s = iv_len % 16;
		if(n != 0)
		{
			mk_gcm_ghash_start(h, iv, n, output);
			memcpy(tmp, (unsigned char const*)iv + n * 16, s);
			memset(tmp + s, 0, 16 - s);
			mk_gcm_ghash_continue(h, tmp, 1, output);
		}
		else
		{
			memcpy(tmp, (unsigned char const*)iv + n * 16, s);
			memset(tmp + s, 0, 16 - s);
			mk_gcm_ghash_start(h, tmp, 1, output);
		}
		memset(tmp, 0, 8);
		mk_uint64_from_int(&iv_len_tmp, iv_len);
		mk_uint64_to_buff_be(&iv_len_tmp, tmp + 8);
		mk_gcm_ghash_continue(h, tmp, 1, output);
	}
}

static mk_inline void mk_gcm_init_cb(void const* j0, void* out_cb)
{
	mk_assert(j0);
	mk_assert(out_cb);

	memcpy(out_cb, j0, 16);
	mk_gcm_inc32(out_cb);
}

static mk_inline void mk_gcm_aad_append(void const* h, void* aad_block, int* aad_block_idx, struct mk_uint64_s* aad_ctr, void* tag, void const* aad, int aad_len)
{
	unsigned char const* input;
	int remaining;
	int capacity;
	int n;
	struct mk_uint64_s tmp_len;

	mk_assert(h);
	mk_assert(aad_block);
	mk_assert(aad_block_idx);
	mk_assert(aad_ctr);
	mk_assert(tag);
	mk_assert(aad || aad_len == 0);
	mk_assert(aad_len >= 0);

	input = (unsigned char const*)aad;
	remaining = aad_len;

	mk_assert(*aad_block_idx >= 0 && *aad_block_idx < 16);
	capacity = 16 - *aad_block_idx;
	if(remaining >= capacity)
	{
		if(*aad_block_idx != 0)
		{
			memcpy((unsigned char*)aad_block + *aad_block_idx, input, capacity);
			mk_gcm_ghash_continue(h, aad_block, 1, tag);
			input += capacity;
			remaining -= capacity;
			*aad_block_idx = 0;
		}
		n = remaining / 16;
		mk_gcm_ghash_continue(h, input, n, tag);
		input += n * 16;
		remaining -= n * 16;
	}
	mk_assert(*aad_block_idx >= 0 && *aad_block_idx < 16);
	mk_assert(remaining >= 0 && remaining + *aad_block_idx < 16);
	memcpy((unsigned char*)aad_block + *aad_block_idx, input, remaining);
	mk_uint64_from_int(&tmp_len, aad_len);
	mk_uint64_add(aad_ctr, aad_ctr, &tmp_len);
}

static mk_inline void mk_gcm_aad_finish(void const* h, void* aad_block, int* aad_block_idx, struct mk_uint64_s* aad_ctr, void* tag, void const* aad, int aad_len)
{
	int capacity;

	mk_assert(h);
	mk_assert(aad_block);
	mk_assert(aad_block_idx);
	mk_assert(aad_ctr);
	mk_assert(tag);
	mk_assert(aad || aad_len == 0);
	mk_assert(aad_len >= 0);

	mk_gcm_aad_append(h, aad_block, aad_block_idx, aad_ctr, tag, aad, aad_len);
	
	mk_assert(*aad_block_idx >= 0 && *aad_block_idx < 16);
	capacity = 16 - *aad_block_idx;
	memset((unsigned char*)aad_block + *aad_block_idx, 0, capacity);
	mk_gcm_ghash_continue(h, aad_block, 1, tag);
}


void mk_operation_mode_init_gcm(struct mk_operation_mode_gcm_s* gcm, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len)
{
	mk_assert(gcm);
	mk_assert(mk_block_cipher_get_block_len(block_cipher) == 16);
	mk_assert(key);

	mk_operation_mode_init_base(&gcm->m_base, block_cipher, padding, key, key_len);

	memset(gcm->m_tag, 0, 16);
	gcm->m_aad_idx = 0;
	mk_uint64_zero(&gcm->m_aad_len);
	mk_uint64_zero(&gcm->m_msg_len);
}

enum mk_block_cipher_e mk_operation_mode_get_block_cipher_gcm(struct mk_operation_mode_gcm_s* gcm)
{
	mk_assert(gcm);

	return mk_operation_mode_get_block_cipher_base(&gcm->m_base);
}

unsigned char const* mk_operation_mode_get_key_gcm(struct mk_operation_mode_gcm_s* gcm)
{
	mk_assert(gcm);

	return mk_operation_mode_get_key_base(&gcm->m_base);
}

void mk_operation_mode_set_param_iv_gcm(struct mk_operation_mode_gcm_s* gcm, unsigned char const* iv, int iv_len)
{
	enum mk_block_cipher_e block_cipher;
	unsigned char const* key;

	mk_assert(gcm);
	mk_assert(iv || iv_len == 0);
	mk_assert(iv_len >= 0);

	block_cipher = mk_operation_mode_get_block_cipher_base(&gcm->m_base);
	key = mk_operation_mode_get_key_base(&gcm->m_base);

	mk_gcm_init_h(block_cipher, key, gcm->m_h);
	mk_gcm_init_j0(block_cipher, key, gcm->m_h, iv, iv_len, gcm->m_j0);
	mk_gcm_init_cb(gcm->m_j0, gcm->m_cb);
}

void mk_operation_mode_set_param_aad_append_gcm(struct mk_operation_mode_gcm_s* gcm, void const* aad, int aad_len)
{
	mk_assert(gcm);
	mk_assert(aad || aad_len == 0);
	mk_assert(aad_len >= 0);

	mk_gcm_aad_append(gcm->m_h, gcm->m_aad_block, &gcm->m_aad_idx, &gcm->m_aad_len, gcm->m_tag, aad, aad_len);
}

void mk_operation_mode_set_param_aad_finish_gcm(struct mk_operation_mode_gcm_s* gcm, void const* aad, int aad_len)
{
	mk_assert(gcm);
	mk_assert(aad || aad_len == 0);
	mk_assert(aad_len >= 0);

	mk_gcm_aad_finish(gcm->m_h, gcm->m_aad_block, &gcm->m_aad_idx, &gcm->m_aad_len, gcm->m_tag, aad, aad_len);
}

void mk_operation_mode_encrypt_blocks_gcm(struct mk_operation_mode_gcm_s* gcm, int blocks, unsigned char const* input, unsigned char* output)
{
	enum mk_block_cipher_e block_cipher;
	unsigned char const* key;
	struct mk_uint64_s tmp_len;

	mk_assert(gcm);
	mk_assert(blocks >= 0);
	mk_assert(input || blocks == 0);
	mk_assert(output || blocks == 0);

	block_cipher = mk_operation_mode_get_block_cipher_base(&gcm->m_base);
	key = mk_operation_mode_get_key_base(&gcm->m_base);

	mk_gcm_gctr_ghash(block_cipher, key, gcm->m_cb, input, blocks * 16, output, gcm->m_h, gcm->m_tag);

	mk_uint64_from_int(&tmp_len, blocks * 16);
	mk_uint64_add(&gcm->m_msg_len, &gcm->m_msg_len, &tmp_len);
}

void mk_operation_mode_decrypt_blocks_gcm(struct mk_operation_mode_gcm_s* gcm, int blocks, unsigned char const* input, unsigned char* output)
{
	(void)gcm;
	(void)blocks;
	(void)input;
	(void)output;
}

int mk_operation_mode_encrypt_finish_gcm(struct mk_operation_mode_gcm_s* gcm, unsigned char const* input, int input_len, unsigned char* output, int output_len)
{
	enum mk_block_cipher_e block_cipher;
	unsigned char const* key;
	struct mk_uint64_s tmp_len;
	unsigned char lengths[16];

	mk_assert(gcm);
	mk_assert(input || input_len == 0);
	mk_assert(input_len >= 0);
	mk_assert(output || output_len == 0);
	mk_assert(output_len >= 0 && output_len >= input_len);

	block_cipher = mk_operation_mode_get_block_cipher_base(&gcm->m_base);
	key = mk_operation_mode_get_key_base(&gcm->m_base);

	mk_gcm_gctr_ghash_finish(block_cipher, key, gcm->m_cb, input, input_len, output, gcm->m_h, gcm->m_tag);

	mk_uint64_from_int(&tmp_len, input_len);
	mk_uint64_add(&gcm->m_msg_len, &gcm->m_msg_len, &tmp_len);

	mk_uint64_to_buff_be(&gcm->m_aad_len, lengths + 0);
	mk_uint64_to_buff_be(&gcm->m_msg_len, lengths + 8);
	mk_gcm_ghash_continue(gcm->m_h, lengths, 1, gcm->m_tag);

	mk_gcm_gctr_ghash_finish(block_cipher, key, gcm->m_j0, gcm->m_tag, 16, gcm->m_tag, NULL, NULL);

	return input_len;
}

/*void mk_operation_mode_decrypt_finish_gcm(struct mk_operation_mode_gcm_s* gcm, unsigned char const* input, int input_len, unsigned char* output, int* output_len)
{
}*/

