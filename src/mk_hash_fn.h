#ifndef mk_include_guard_hash_fn
#define mk_include_guard_hash_fn


#include "mk_md2.h"
#include "mk_md4.h"
#include "mk_md5.h"
#include "mk_sha1.h"
#include "mk_sha2_224.h"
#include "mk_sha2_256.h"
#include "mk_sha2_384.h"
#include "mk_sha2_512.h"
#include "mk_sha2_512224.h"
#include "mk_sha2_512256.h"
#include "mk_sha3_224.h"
#include "mk_sha3_256.h"
#include "mk_sha3_384.h"
#include "mk_sha3_512.h"

#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


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
	struct mk_md2_state_s m_md2;
	struct mk_md4_state_s m_md4;
	struct mk_md5_state_s m_md5;
	struct mk_sha1_state_s m_sha1;
	struct mk_sha2_224_state_s m_sha2_224;
	struct mk_sha2_256_state_s m_sha2_256;
	struct mk_sha2_384_state_s m_sha2_384;
	struct mk_sha2_512_state_s m_sha2_512;
	struct mk_sha2_512224_state_s m_sha2_512224;
	struct mk_sha2_512256_state_s m_sha2_512256;
	struct mk_sha3_224_state_s m_sha3_224;
	struct mk_sha3_256_state_s m_sha3_256;
	struct mk_sha3_384_state_s m_sha3_384;
	struct mk_sha3_512_state_s m_sha3_512;
};

struct mk_hash_fn_s
{
	enum mk_hash_fn_e m_id;
	union mk_hash_fn_u m_state;
};

enum mk_hash_fn_max_block_len_e { mk_hash_fn_max_block_len = 144 };
enum mk_hash_fn_max_digest_len_e { mk_hash_fn_max_digest_len = 64 };


mk_extern_c int mk_hash_fn_get_block_len(enum mk_hash_fn_e id);
mk_extern_c int mk_hash_fn_get_digest_len(enum mk_hash_fn_e id);
mk_extern_c void mk_hash_fn_init(struct mk_hash_fn_s* hash_fn, enum mk_hash_fn_e id);
mk_extern_c enum mk_hash_fn_e mk_hash_fn_get_id(struct mk_hash_fn_s* hash_fn);
mk_extern_c void mk_hash_fn_append(struct mk_hash_fn_s* hash_fn, void const* msg, size_t msg_len_bytes);
mk_extern_c void mk_hash_fn_finish(struct mk_hash_fn_s* hash_fn, void* digest);


#undef mk_extern_c


#endif
