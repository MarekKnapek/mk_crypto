#include "mk_hmac.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <string.h> /* memcpy memset */


static mk_inline void mk_hmac_detail_xor(unsigned char pad, void const* src, int count, void* dst)
{
	unsigned char const* input;
	unsigned char* output;
	int i;

	mk_assert(pad == 0x36 || pad == 0x5c);
	mk_assert(src);
	mk_assert(count >= 0);
	mk_assert(dst);

	input = (unsigned char const*)src;
	output = (unsigned char*)dst;
	for(i = 0; i != count; ++i)
	{
		output[i] = input[i] ^ pad;
	}
}


void mk_hmac_init(struct mk_hmac_s* hmac, enum mk_hmac_e id, void const* key, int key_len)
{
	int block_len;
	int digest_len;
	unsigned char ipad[mk_hash_fn_max_block_len];

	block_len = mk_hash_fn_get_block_len((enum mk_hash_fn_e)id);
	digest_len = mk_hash_fn_get_digest_len((enum mk_hash_fn_e)id);

	if(key_len < digest_len)
	{
		/* warning */
	}
	if(key_len > block_len)
	{
		mk_hash_fn_init(&hmac->m_hash_fn, (enum mk_hash_fn_e)id);
		mk_hash_fn_append(&hmac->m_hash_fn, key, key_len);
		mk_hash_fn_finish(&hmac->m_hash_fn, &ipad);
		key_len = digest_len;
	}
	else
	{
		memcpy(ipad, key, key_len);
	}
	memset(ipad + key_len, 0, block_len - key_len);
	mk_hmac_detail_xor(0x5c, &ipad, block_len, &hmac->m_opad);
	mk_hmac_detail_xor(0x36, &ipad, block_len, &ipad);

	mk_hash_fn_init(&hmac->m_hash_fn, (enum mk_hash_fn_e)id);
	mk_hash_fn_append(&hmac->m_hash_fn, ipad, block_len);
}

void mk_hmac_append(struct mk_hmac_s* hmac, void const* msg, size_t msg_len_bytes)
{
	mk_hash_fn_append(&hmac->m_hash_fn, msg, msg_len_bytes);
}

void mk_hmac_finish(struct mk_hmac_s* hmac, void* digest)
{
	enum mk_hash_fn_e hash_id;
	int block_len;
	int digest_len;
	unsigned char inner_digest[mk_hash_fn_max_digest_len];

	hash_id = mk_hash_fn_get_id(&hmac->m_hash_fn);
	block_len = mk_hash_fn_get_block_len(hash_id);
	digest_len = mk_hash_fn_get_digest_len(hash_id);

	mk_hash_fn_finish(&hmac->m_hash_fn, inner_digest);

	mk_hash_fn_init(&hmac->m_hash_fn, hash_id);
	mk_hash_fn_append(&hmac->m_hash_fn, hmac->m_opad, block_len);
	mk_hash_fn_append(&hmac->m_hash_fn, inner_digest, digest_len);
	mk_hash_fn_finish(&hmac->m_hash_fn, digest);
}
