#ifndef mk_include_guard_hmac
#define mk_include_guard_hmac


#include "mk_hash_fn.h"

#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_hmac_e
{
	mk_hmac_md2,
	mk_hmac_md4,
	mk_hmac_md5,
	mk_hmac_sha1,
	mk_hmac_sha2_224,
	mk_hmac_sha2_256,
	mk_hmac_sha2_384,
	mk_hmac_sha2_512,
	mk_hmac_sha2_512224,
	mk_hmac_sha2_512256,
	mk_hmac_sha3_224,
	mk_hmac_sha3_256,
	mk_hmac_sha3_384,
	mk_hmac_sha3_512,
};

struct mk_hmac_s
{
	struct mk_hash_fn_s m_hash_fn;
	unsigned char m_opad[mk_hash_fn_max_block_len];
};


/* rfc 2104 */


mk_extern_c void mk_hmac_init(struct mk_hmac_s* hmac, enum mk_hmac_e id, void const* key, int key_len);
mk_extern_c void mk_hmac_append(struct mk_hmac_s* hmac, void const* msg, size_t msg_len_bytes);
mk_extern_c void mk_hmac_finish(struct mk_hmac_s* hmac, void* digest);


#undef mk_extern_c


#endif
