#include "mk_mac_hmac.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


#define mk_assert_type(type) mk_assert( \
	(type) == mk_mac_hmac_md2 || \
	(type) == mk_mac_hmac_md4 || \
	(type) == mk_mac_hmac_md5 || \
	(type) == mk_mac_hmac_sha1 || \
	(type) == mk_mac_hmac_sha2_224 || \
	(type) == mk_mac_hmac_sha2_256 || \
	(type) == mk_mac_hmac_sha2_384 || \
	(type) == mk_mac_hmac_sha2_512 || \
	(type) == mk_mac_hmac_sha2_512224 || \
	(type) == mk_mac_hmac_sha2_512256 || \
	(type) == mk_mac_hmac_sha3_224 || \
	(type) == mk_mac_hmac_sha3_256 || \
	(type) == mk_mac_hmac_sha3_384 || \
	(type) == mk_mac_hmac_sha3_512)


mk_jumbo void mk_mac_hmac_init(enum mk_mac_hmac_e type, union mk_mac_hmac_pu hmac, void const* key, int key_len)
{
	mk_assert_type(type);
	mk_assert(key || key_len == 0);
	mk_assert(key_len >= 0);

	switch(type)
	{
		case mk_mac_hmac_md2        : mk_assert(hmac.m_md2        ); mk_mac_hmac_md2_init        (hmac.m_md2        , key, key_len); break;
		case mk_mac_hmac_md4        : mk_assert(hmac.m_md4        ); mk_mac_hmac_md4_init        (hmac.m_md4        , key, key_len); break;
		case mk_mac_hmac_md5        : mk_assert(hmac.m_md5        ); mk_mac_hmac_md5_init        (hmac.m_md5        , key, key_len); break;
		case mk_mac_hmac_sha1       : mk_assert(hmac.m_sha1       ); mk_mac_hmac_sha1_init       (hmac.m_sha1       , key, key_len); break;
		case mk_mac_hmac_sha2_224   : mk_assert(hmac.m_sha2_224   ); mk_mac_hmac_sha2_224_init   (hmac.m_sha2_224   , key, key_len); break;
		case mk_mac_hmac_sha2_256   : mk_assert(hmac.m_sha2_256   ); mk_mac_hmac_sha2_256_init   (hmac.m_sha2_256   , key, key_len); break;
		case mk_mac_hmac_sha2_384   : mk_assert(hmac.m_sha2_384   ); mk_mac_hmac_sha2_384_init   (hmac.m_sha2_384   , key, key_len); break;
		case mk_mac_hmac_sha2_512   : mk_assert(hmac.m_sha2_512   ); mk_mac_hmac_sha2_512_init   (hmac.m_sha2_512   , key, key_len); break;
		case mk_mac_hmac_sha2_512224: mk_assert(hmac.m_sha2_512224); mk_mac_hmac_sha2_512224_init(hmac.m_sha2_512224, key, key_len); break;
		case mk_mac_hmac_sha2_512256: mk_assert(hmac.m_sha2_512256); mk_mac_hmac_sha2_512256_init(hmac.m_sha2_512256, key, key_len); break;
		case mk_mac_hmac_sha3_224   : mk_assert(hmac.m_sha3_224   ); mk_mac_hmac_sha3_224_init   (hmac.m_sha3_224   , key, key_len); break;
		case mk_mac_hmac_sha3_256   : mk_assert(hmac.m_sha3_256   ); mk_mac_hmac_sha3_256_init   (hmac.m_sha3_256   , key, key_len); break;
		case mk_mac_hmac_sha3_384   : mk_assert(hmac.m_sha3_384   ); mk_mac_hmac_sha3_384_init   (hmac.m_sha3_384   , key, key_len); break;
		case mk_mac_hmac_sha3_512   : mk_assert(hmac.m_sha3_512   ); mk_mac_hmac_sha3_512_init   (hmac.m_sha3_512   , key, key_len); break;
	}
}

mk_jumbo void mk_mac_hmac_append(enum mk_mac_hmac_e type, union mk_mac_hmac_pu hmac, void const* msg, int msg_len)
{
	mk_assert_type(type);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	switch(type)
	{
		case mk_mac_hmac_md2        : mk_assert(hmac.m_md2        ); mk_mac_hmac_md2_append        (hmac.m_md2        , msg, msg_len); break;
		case mk_mac_hmac_md4        : mk_assert(hmac.m_md4        ); mk_mac_hmac_md4_append        (hmac.m_md4        , msg, msg_len); break;
		case mk_mac_hmac_md5        : mk_assert(hmac.m_md5        ); mk_mac_hmac_md5_append        (hmac.m_md5        , msg, msg_len); break;
		case mk_mac_hmac_sha1       : mk_assert(hmac.m_sha1       ); mk_mac_hmac_sha1_append       (hmac.m_sha1       , msg, msg_len); break;
		case mk_mac_hmac_sha2_224   : mk_assert(hmac.m_sha2_224   ); mk_mac_hmac_sha2_224_append   (hmac.m_sha2_224   , msg, msg_len); break;
		case mk_mac_hmac_sha2_256   : mk_assert(hmac.m_sha2_256   ); mk_mac_hmac_sha2_256_append   (hmac.m_sha2_256   , msg, msg_len); break;
		case mk_mac_hmac_sha2_384   : mk_assert(hmac.m_sha2_384   ); mk_mac_hmac_sha2_384_append   (hmac.m_sha2_384   , msg, msg_len); break;
		case mk_mac_hmac_sha2_512   : mk_assert(hmac.m_sha2_512   ); mk_mac_hmac_sha2_512_append   (hmac.m_sha2_512   , msg, msg_len); break;
		case mk_mac_hmac_sha2_512224: mk_assert(hmac.m_sha2_512224); mk_mac_hmac_sha2_512224_append(hmac.m_sha2_512224, msg, msg_len); break;
		case mk_mac_hmac_sha2_512256: mk_assert(hmac.m_sha2_512256); mk_mac_hmac_sha2_512256_append(hmac.m_sha2_512256, msg, msg_len); break;
		case mk_mac_hmac_sha3_224   : mk_assert(hmac.m_sha3_224   ); mk_mac_hmac_sha3_224_append   (hmac.m_sha3_224   , msg, msg_len); break;
		case mk_mac_hmac_sha3_256   : mk_assert(hmac.m_sha3_256   ); mk_mac_hmac_sha3_256_append   (hmac.m_sha3_256   , msg, msg_len); break;
		case mk_mac_hmac_sha3_384   : mk_assert(hmac.m_sha3_384   ); mk_mac_hmac_sha3_384_append   (hmac.m_sha3_384   , msg, msg_len); break;
		case mk_mac_hmac_sha3_512   : mk_assert(hmac.m_sha3_512   ); mk_mac_hmac_sha3_512_append   (hmac.m_sha3_512   , msg, msg_len); break;
	}
}

mk_jumbo void mk_mac_hmac_finish(enum mk_mac_hmac_e type, union mk_mac_hmac_pu hmac, void* digest)
{
	mk_assert_type(type);
	mk_assert(digest);

	switch(type)
	{
		case mk_mac_hmac_md2        : mk_assert(hmac.m_md2        ); mk_mac_hmac_md2_finish        (hmac.m_md2        , digest); break;
		case mk_mac_hmac_md4        : mk_assert(hmac.m_md4        ); mk_mac_hmac_md4_finish        (hmac.m_md4        , digest); break;
		case mk_mac_hmac_md5        : mk_assert(hmac.m_md5        ); mk_mac_hmac_md5_finish        (hmac.m_md5        , digest); break;
		case mk_mac_hmac_sha1       : mk_assert(hmac.m_sha1       ); mk_mac_hmac_sha1_finish       (hmac.m_sha1       , digest); break;
		case mk_mac_hmac_sha2_224   : mk_assert(hmac.m_sha2_224   ); mk_mac_hmac_sha2_224_finish   (hmac.m_sha2_224   , digest); break;
		case mk_mac_hmac_sha2_256   : mk_assert(hmac.m_sha2_256   ); mk_mac_hmac_sha2_256_finish   (hmac.m_sha2_256   , digest); break;
		case mk_mac_hmac_sha2_384   : mk_assert(hmac.m_sha2_384   ); mk_mac_hmac_sha2_384_finish   (hmac.m_sha2_384   , digest); break;
		case mk_mac_hmac_sha2_512   : mk_assert(hmac.m_sha2_512   ); mk_mac_hmac_sha2_512_finish   (hmac.m_sha2_512   , digest); break;
		case mk_mac_hmac_sha2_512224: mk_assert(hmac.m_sha2_512224); mk_mac_hmac_sha2_512224_finish(hmac.m_sha2_512224, digest); break;
		case mk_mac_hmac_sha2_512256: mk_assert(hmac.m_sha2_512256); mk_mac_hmac_sha2_512256_finish(hmac.m_sha2_512256, digest); break;
		case mk_mac_hmac_sha3_224   : mk_assert(hmac.m_sha3_224   ); mk_mac_hmac_sha3_224_finish   (hmac.m_sha3_224   , digest); break;
		case mk_mac_hmac_sha3_256   : mk_assert(hmac.m_sha3_256   ); mk_mac_hmac_sha3_256_finish   (hmac.m_sha3_256   , digest); break;
		case mk_mac_hmac_sha3_384   : mk_assert(hmac.m_sha3_384   ); mk_mac_hmac_sha3_384_finish   (hmac.m_sha3_384   , digest); break;
		case mk_mac_hmac_sha3_512   : mk_assert(hmac.m_sha3_512   ); mk_mac_hmac_sha3_512_finish   (hmac.m_sha3_512   , digest); break;
	}
}


#undef mk_assert_type
