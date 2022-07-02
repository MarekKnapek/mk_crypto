#ifndef mk_include_guard_mac_hmac
#define mk_include_guard_mac_hmac


#include "hmac/mk_mac_hmac_md2.h"
#include "hmac/mk_mac_hmac_md4.h"
#include "hmac/mk_mac_hmac_md5.h"
#include "hmac/mk_mac_hmac_sha1.h"
#include "hmac/mk_mac_hmac_sha2_224.h"
#include "hmac/mk_mac_hmac_sha2_256.h"
#include "hmac/mk_mac_hmac_sha2_384.h"
#include "hmac/mk_mac_hmac_sha2_512.h"
#include "hmac/mk_mac_hmac_sha2_512224.h"
#include "hmac/mk_mac_hmac_sha2_512256.h"
#include "hmac/mk_mac_hmac_sha3_224.h"
#include "hmac/mk_mac_hmac_sha3_256.h"
#include "hmac/mk_mac_hmac_sha3_384.h"
#include "hmac/mk_mac_hmac_sha3_512.h"

#include "../utils/mk_jumbo.h"


enum mk_mac_hmac_e
{
	mk_mac_hmac_md2,
	mk_mac_hmac_md4,
	mk_mac_hmac_md5,
	mk_mac_hmac_sha1,
	mk_mac_hmac_sha2_224,
	mk_mac_hmac_sha2_256,
	mk_mac_hmac_sha2_384,
	mk_mac_hmac_sha2_512,
	mk_mac_hmac_sha2_512224,
	mk_mac_hmac_sha2_512256,
	mk_mac_hmac_sha3_224,
	mk_mac_hmac_sha3_256,
	mk_mac_hmac_sha3_384,
	mk_mac_hmac_sha3_512
};


union mk_mac_hmac_u
{
	struct mk_mac_hmac_md2_s m_md2;
	struct mk_mac_hmac_md4_s m_md4;
	struct mk_mac_hmac_md5_s m_md5;
	struct mk_mac_hmac_sha1_s m_sha1;
	struct mk_mac_hmac_sha2_224_s m_sha2_224;
	struct mk_mac_hmac_sha2_256_s m_sha2_256;
	struct mk_mac_hmac_sha2_384_s m_sha2_384;
	struct mk_mac_hmac_sha2_512_s m_sha2_512;
	struct mk_mac_hmac_sha2_512224_s m_sha2_512224;
	struct mk_mac_hmac_sha2_512256_s m_sha2_512256;
	struct mk_mac_hmac_sha3_224_s m_sha3_224;
	struct mk_mac_hmac_sha3_256_s m_sha3_256;
	struct mk_mac_hmac_sha3_384_s m_sha3_384;
	struct mk_mac_hmac_sha3_512_s m_sha3_512;
};

union mk_mac_hmac_pu
{
	union mk_mac_hmac_u* m_u;
	struct mk_mac_hmac_md2_s* m_md2;
	struct mk_mac_hmac_md4_s* m_md4;
	struct mk_mac_hmac_md5_s* m_md5;
	struct mk_mac_hmac_sha1_s* m_sha1;
	struct mk_mac_hmac_sha2_224_s* m_sha2_224;
	struct mk_mac_hmac_sha2_256_s* m_sha2_256;
	struct mk_mac_hmac_sha2_384_s* m_sha2_384;
	struct mk_mac_hmac_sha2_512_s* m_sha2_512;
	struct mk_mac_hmac_sha2_512224_s* m_sha2_512224;
	struct mk_mac_hmac_sha2_512256_s* m_sha2_512256;
	struct mk_mac_hmac_sha3_224_s* m_sha3_224;
	struct mk_mac_hmac_sha3_256_s* m_sha3_256;
	struct mk_mac_hmac_sha3_384_s* m_sha3_384;
	struct mk_mac_hmac_sha3_512_s* m_sha3_512;
};


mk_jumbo void mk_mac_hmac_init(enum mk_mac_hmac_e type, union mk_mac_hmac_pu hmac, void const* key, int key_len);
mk_jumbo void mk_mac_hmac_append(enum mk_mac_hmac_e type, union mk_mac_hmac_pu hmac, void const* msg, int msg_len);
mk_jumbo void mk_mac_hmac_finish(enum mk_mac_hmac_e type, union mk_mac_hmac_pu hmac, void* digest);


#endif
