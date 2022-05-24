#include "mk_hash_fn.h"

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

#include "utils/mk_assert.h"
#include "utils/mk_jumbo.h"


#define mk_assert_type(type) mk_assert( \
	(type) == mk_hash_fn_md2 || \
	(type) == mk_hash_fn_md4 || \
	(type) == mk_hash_fn_md5 || \
	(type) == mk_hash_fn_sha1 || \
	(type) == mk_hash_fn_sha2_224 || \
	(type) == mk_hash_fn_sha2_256 || \
	(type) == mk_hash_fn_sha2_384 || \
	(type) == mk_hash_fn_sha2_512 || \
	(type) == mk_hash_fn_sha2_512224 || \
	(type) == mk_hash_fn_sha2_512256 || \
	(type) == mk_hash_fn_sha3_224 || \
	(type) == mk_hash_fn_sha3_256 || \
	(type) == mk_hash_fn_sha3_384 || \
	(type) == mk_hash_fn_sha3_512 || \
	0)


mk_jumbo void mk_hash_fn_init(struct mk_hash_fn_s* hash_fn, enum mk_hash_fn_e type)
{
	mk_assert(hash_fn);
	mk_assert_type(type);

	hash_fn->m_type = type;
	switch(type)
	{
		case mk_hash_fn_md2: mk_hash_hash_md2_init(&hash_fn->m_state.m_md2); break;
		case mk_hash_fn_md4: mk_hash_hash_md4_init(&hash_fn->m_state.m_md4); break;
		case mk_hash_fn_md5: mk_hash_hash_md5_init(&hash_fn->m_state.m_md5); break;
		case mk_hash_fn_sha1: mk_hash_hash_sha1_init(&hash_fn->m_state.m_sha1); break;
		case mk_hash_fn_sha2_224: mk_hash_hash_sha2_224_init(&hash_fn->m_state.m_sha2_224); break;
		case mk_hash_fn_sha2_256: mk_hash_hash_sha2_256_init(&hash_fn->m_state.m_sha2_256); break;
		case mk_hash_fn_sha2_384: mk_hash_hash_sha2_384_init(&hash_fn->m_state.m_sha2_384); break;
		case mk_hash_fn_sha2_512: mk_hash_hash_sha2_512_init(&hash_fn->m_state.m_sha2_512); break;
		case mk_hash_fn_sha2_512224: mk_hash_hash_sha2_512224_init(&hash_fn->m_state.m_sha2_512224); break;
		case mk_hash_fn_sha2_512256: mk_hash_hash_sha2_512256_init(&hash_fn->m_state.m_sha2_512256); break;
		case mk_hash_fn_sha3_224: mk_hash_hash_sha3_224_init(&hash_fn->m_state.m_sha3_224); break;
		case mk_hash_fn_sha3_256: mk_hash_hash_sha3_256_init(&hash_fn->m_state.m_sha3_256); break;
		case mk_hash_fn_sha3_384: mk_hash_hash_sha3_384_init(&hash_fn->m_state.m_sha3_384); break;
		case mk_hash_fn_sha3_512: mk_hash_hash_sha3_512_init(&hash_fn->m_state.m_sha3_512); break;
	}
}

mk_jumbo enum mk_hash_fn_e mk_hash_fn_get_type(struct mk_hash_fn_s* hash_fn)
{
	mk_assert(hash_fn);
	mk_assert_type(hash_fn->m_type);

	return hash_fn->m_type;
}

mk_jumbo void mk_hash_fn_append(struct mk_hash_fn_s* hash_fn, void const* msg, int msg_len)
{
	mk_assert(hash_fn);
	mk_assert_type(hash_fn->m_type);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	switch(hash_fn->m_type)
	{
		case mk_hash_fn_md2: mk_hash_hash_md2_append(&hash_fn->m_state.m_md2, msg, msg_len); break;
		case mk_hash_fn_md4: mk_hash_hash_md4_append(&hash_fn->m_state.m_md4, msg, msg_len); break;
		case mk_hash_fn_md5: mk_hash_hash_md5_append(&hash_fn->m_state.m_md5, msg, msg_len); break;
		case mk_hash_fn_sha1: mk_hash_hash_sha1_append(&hash_fn->m_state.m_sha1, msg, msg_len); break;
		case mk_hash_fn_sha2_224: mk_hash_hash_sha2_224_append(&hash_fn->m_state.m_sha2_224, msg, msg_len); break;
		case mk_hash_fn_sha2_256: mk_hash_hash_sha2_256_append(&hash_fn->m_state.m_sha2_256, msg, msg_len); break;
		case mk_hash_fn_sha2_384: mk_hash_hash_sha2_384_append(&hash_fn->m_state.m_sha2_384, msg, msg_len); break;
		case mk_hash_fn_sha2_512: mk_hash_hash_sha2_512_append(&hash_fn->m_state.m_sha2_512, msg, msg_len); break;
		case mk_hash_fn_sha2_512224: mk_hash_hash_sha2_512224_append(&hash_fn->m_state.m_sha2_512224, msg, msg_len); break;
		case mk_hash_fn_sha2_512256: mk_hash_hash_sha2_512256_append(&hash_fn->m_state.m_sha2_512256, msg, msg_len); break;
		case mk_hash_fn_sha3_224: mk_hash_hash_sha3_224_append(&hash_fn->m_state.m_sha3_224, msg, msg_len); break;
		case mk_hash_fn_sha3_256: mk_hash_hash_sha3_256_append(&hash_fn->m_state.m_sha3_256, msg, msg_len); break;
		case mk_hash_fn_sha3_384: mk_hash_hash_sha3_384_append(&hash_fn->m_state.m_sha3_384, msg, msg_len); break;
		case mk_hash_fn_sha3_512: mk_hash_hash_sha3_512_append(&hash_fn->m_state.m_sha3_512, msg, msg_len); break;
	}
}

mk_jumbo void mk_hash_fn_finish(struct mk_hash_fn_s* hash_fn, void* digest)
{
	mk_assert(hash_fn);
	mk_assert_type(hash_fn->m_type);
	mk_assert(digest);

	switch(hash_fn->m_type)
	{
		case mk_hash_fn_md2: mk_hash_hash_md2_finish(&hash_fn->m_state.m_md2, digest); break;
		case mk_hash_fn_md4: mk_hash_hash_md4_finish(&hash_fn->m_state.m_md4, digest); break;
		case mk_hash_fn_md5: mk_hash_hash_md5_finish(&hash_fn->m_state.m_md5, digest); break;
		case mk_hash_fn_sha1: mk_hash_hash_sha1_finish(&hash_fn->m_state.m_sha1, digest); break;
		case mk_hash_fn_sha2_224: mk_hash_hash_sha2_224_finish(&hash_fn->m_state.m_sha2_224, digest); break;
		case mk_hash_fn_sha2_256: mk_hash_hash_sha2_256_finish(&hash_fn->m_state.m_sha2_256, digest); break;
		case mk_hash_fn_sha2_384: mk_hash_hash_sha2_384_finish(&hash_fn->m_state.m_sha2_384, digest); break;
		case mk_hash_fn_sha2_512: mk_hash_hash_sha2_512_finish(&hash_fn->m_state.m_sha2_512, digest); break;
		case mk_hash_fn_sha2_512224: mk_hash_hash_sha2_512224_finish(&hash_fn->m_state.m_sha2_512224, digest); break;
		case mk_hash_fn_sha2_512256: mk_hash_hash_sha2_512256_finish(&hash_fn->m_state.m_sha2_512256, digest); break;
		case mk_hash_fn_sha3_224: mk_hash_hash_sha3_224_finish(&hash_fn->m_state.m_sha3_224, digest); break;
		case mk_hash_fn_sha3_256: mk_hash_hash_sha3_256_finish(&hash_fn->m_state.m_sha3_256, digest); break;
		case mk_hash_fn_sha3_384: mk_hash_hash_sha3_384_finish(&hash_fn->m_state.m_sha3_384, digest); break;
		case mk_hash_fn_sha3_512: mk_hash_hash_sha3_512_finish(&hash_fn->m_state.m_sha3_512, digest); break;
	}
}


#undef mk_assert_type
