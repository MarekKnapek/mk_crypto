#ifndef mk_include_guard_hash_fn
#define mk_include_guard_hash_fn


#include "hash/hash/mk_hash_hash_md2.h"
#include "hash/hash/mk_hash_hash_md4.h"
#include "hash/hash/mk_hash_hash_md5.h"
#include "hash/hash/mk_hash_hash_sha1.h"
#include "hash/hash/mk_hash_hash_sha2_224.h"
#include "hash/hash/mk_hash_hash_sha2_256.h"
#include "hash/hash/mk_hash_hash_sha2_384.h"
#include "hash/hash/mk_hash_hash_sha2_512.h"
#include "hash/hash/mk_hash_hash_sha2_512224.h"
#include "hash/hash/mk_hash_hash_sha2_512256.h"
#include "hash/hash/mk_hash_hash_sha3_224.h"
#include "hash/hash/mk_hash_hash_sha3_256.h"
#include "hash/hash/mk_hash_hash_sha3_384.h"
#include "hash/hash/mk_hash_hash_sha3_512.h"

#include "utils/mk_jumbo.h"


enum mk_hash_fn_e
{
	mk_hash_fn_md2,
	mk_hash_fn_md4,
	mk_hash_fn_md5,
	mk_hash_fn_sha1,
	mk_hash_fn_sha2_224,
	mk_hash_fn_sha2_256,
	mk_hash_fn_sha2_384,
	mk_hash_fn_sha2_512,
	mk_hash_fn_sha2_512224,
	mk_hash_fn_sha2_512256,
	mk_hash_fn_sha3_224,
	mk_hash_fn_sha3_256,
	mk_hash_fn_sha3_384,
	mk_hash_fn_sha3_512,
};

union mk_hash_fn_u
{
	struct mk_hash_hash_md2_s m_md2;
	struct mk_hash_hash_md4_s m_md4;
	struct mk_hash_hash_md5_s m_md5;
	struct mk_hash_hash_sha1_s m_sha1;
	struct mk_hash_hash_sha2_224_s m_sha2_224;
	struct mk_hash_hash_sha2_256_s m_sha2_256;
	struct mk_hash_hash_sha2_384_s m_sha2_384;
	struct mk_hash_hash_sha2_512_s m_sha2_512;
	struct mk_hash_hash_sha2_512224_s m_sha2_512224;
	struct mk_hash_hash_sha2_512256_s m_sha2_512256;
	struct mk_hash_hash_sha3_224_s m_sha3_224;
	struct mk_hash_hash_sha3_256_s m_sha3_256;
	struct mk_hash_hash_sha3_384_s m_sha3_384;
	struct mk_hash_hash_sha3_512_s m_sha3_512;
};

struct mk_hash_fn_s
{
	enum mk_hash_fn_e m_type;
	union mk_hash_fn_u m_state;
};


mk_jumbo void mk_hash_fn_init(struct mk_hash_fn_s* hash_fn, enum mk_hash_fn_e type);
mk_jumbo enum mk_hash_fn_e mk_hash_fn_get_type(struct mk_hash_fn_s* hash_fn);
mk_jumbo void mk_hash_fn_append(struct mk_hash_fn_s* hash_fn, void const* msg, int msg_len);
mk_jumbo void mk_hash_fn_finish(struct mk_hash_fn_s* hash_fn, void* digest);


#endif
