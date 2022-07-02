#include "../../hash/hash/mk_hash_hash.h"

#include "../../utils/mk_jumbo.h"


#include "../../hash/base/mk_hash_base_alg_name_def.h"


#define concat_(a, b) a ## b
#define concat(a, b) concat_(a, b)


#define block_len concat(concat(mk_hash_base_hash_, alg_name), _block_len)
#define hash_s concat(concat(struct mk_hash_hash_, alg_name), _s)
#define hmac_s concat(concat(struct mk_mac_hmac_, alg_name), _s)
#define hmac_init concat(concat(mk_mac_hmac_, alg_name), _init)
#define hmac_append concat(concat(mk_mac_hmac_, alg_name), _append)
#define hmac_finish concat(concat(mk_mac_hmac_, alg_name), _finish)


/* rfc 2104 */


hmac_s
{
	hash_s m_hash;
	unsigned char m_opad[block_len];
};


mk_jumbo void hmac_init(hmac_s* hmac, void const* key, int key_len);
mk_jumbo void hmac_append(hmac_s* hmac, void const* msg, int msg_len);
mk_jumbo void hmac_finish(hmac_s* hmac, void* digest);


#undef block_len
#undef hash_s
#undef hmac_s
#undef hmac_init
#undef hmac_append
#undef hmac_finish


#undef concat_
#undef concat


#include "../../hash/base/mk_hash_base_alg_name_undef.h"
