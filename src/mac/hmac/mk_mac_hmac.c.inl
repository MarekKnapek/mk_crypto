#include "../../hash/hash/mk_hash_hash.h"

#include "../../utils/mk_jumbo.h"
#include "../../utils/mk_assert.h"

#include <string.h> /* memcpy memset */


#include "../../hash/base/mk_hash_base_alg_name_def.h"


#define concat_(a, b) a ## b
#define concat(a, b) concat_(a, b)


#define block_len concat(concat(mk_hash_base_hash_, alg_name), _block_len)
#define digest_len concat(concat(mk_hash_base_hash_, alg_name), _digest_len)
#define hash_s concat(concat(struct mk_hash_hash_, alg_name), _s)
#define hash_init concat(concat(mk_hash_hash_, alg_name), _init)
#define hash_append concat(concat(mk_hash_hash_, alg_name), _append)
#define hash_finish concat(concat(mk_hash_hash_, alg_name), _finish)
#define hmac_s concat(concat(struct mk_mac_hmac_, alg_name), _s)
#define hmac_init concat(concat(mk_mac_hmac_, alg_name), _init)
#define hmac_append concat(concat(mk_mac_hmac_, alg_name), _append)
#define hmac_finish concat(concat(mk_mac_hmac_, alg_name), _finish)


/* rfc 2104 */


mk_jumbo void hmac_init(hmac_s* hmac, void const* key, int key_len)
{
	unsigned char ipad[block_len];
	int i;

	mk_assert(hmac);
	mk_assert(key || key_len == 0);
	mk_assert(key_len >= 0);
	mk_assert((int)digest_len <= (int)block_len);

	if(key_len < digest_len)
	{
		/* warning */
	}

	if(key_len > block_len)
	{
		hash_init(&hmac->m_hash);
		hash_append(&hmac->m_hash, key, key_len);
		hash_finish(&hmac->m_hash, ipad);
		memset(ipad + digest_len, 0x00, block_len - digest_len);
	}
	else
	{
		memcpy(ipad, key, key_len);
		memset(ipad + key_len, 0x00, block_len - key_len);
	}
	for(i = 0; i != block_len; ++i){ hmac->m_opad[i] = ipad[i] ^ 0x5c; }
	for(i = 0; i != block_len; ++i){ ipad[i] ^= 0x36; }

	hash_init(&hmac->m_hash);
	hash_append(&hmac->m_hash, ipad, block_len);
}

mk_jumbo void hmac_append(hmac_s* hmac, void const* msg, int msg_len)
{
	mk_assert(hmac);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	hash_append(&hmac->m_hash, msg, msg_len);
}

mk_jumbo void hmac_finish(hmac_s* hmac, void* digest)
{
	unsigned char dgst[digest_len];

	mk_assert(hmac);
	mk_assert(digest);

	hash_finish(&hmac->m_hash, dgst);

	hash_init(&hmac->m_hash);
	hash_append(&hmac->m_hash, hmac->m_opad, block_len);
	hash_append(&hmac->m_hash, dgst, digest_len);
	hash_finish(&hmac->m_hash, digest);
}


#undef block_len
#undef digest_len
#undef hash_s
#undef hash_init
#undef hash_append
#undef hash_finish
#undef hmac_s
#undef hmac_init
#undef hmac_append
#undef hmac_finish


#undef concat_
#undef concat


#include "../../hash/base/mk_hash_base_alg_name_undef.h"
