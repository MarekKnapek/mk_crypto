#include "mk_hash_fn.h"

#include "../utils/mk_assert.h"


#define mk_assert_id(id) \
	mk_assert \
	( \
		(id) == mk_hash_fn_md2 || \
		(id) == mk_hash_fn_md4 || \
		(id) == mk_hash_fn_md5 || \
		(id) == mk_hash_fn_sha1 || \
		(id) == mk_hash_fn_sha2_224 || \
		(id) == mk_hash_fn_sha2_256 || \
		(id) == mk_hash_fn_sha2_384 || \
		(id) == mk_hash_fn_sha2_512 || \
		(id) == mk_hash_fn_sha2_512224 || \
		(id) == mk_hash_fn_sha2_512256 || \
		(id) == mk_hash_fn_sha3_224 || \
		(id) == mk_hash_fn_sha3_256 || \
		(id) == mk_hash_fn_sha3_384 || \
		(id) == mk_hash_fn_sha3_512 || \
		0 \
	);


int mk_hash_fn_get_block_len(enum mk_hash_fn_e id)
{
	mk_assert_id(id);

	switch(id)
	{
		case mk_hash_fn_md2: return 16; break;
		case mk_hash_fn_md4: return 64; break;
		case mk_hash_fn_md5: return 64; break;
		case mk_hash_fn_sha1: return 64; break;
		case mk_hash_fn_sha2_224: return 64; break;
		case mk_hash_fn_sha2_256: return 64; break;
		case mk_hash_fn_sha2_384: return 64; break;
		case mk_hash_fn_sha2_512: return 64; break;
		case mk_hash_fn_sha2_512224: return 64; break;
		case mk_hash_fn_sha2_512256: return 64; break;
		case mk_hash_fn_sha3_224: return 144; break;
		case mk_hash_fn_sha3_256: return 136; break;
		case mk_hash_fn_sha3_384: return 104; break;
		case mk_hash_fn_sha3_512: return 72; break;
	}

	return 0;
}

int mk_hash_fn_get_digest_len(enum mk_hash_fn_e id)
{
	mk_assert_id(id);

	switch(id)
	{
		case mk_hash_fn_md2: return 16; break;
		case mk_hash_fn_md4: return 16; break;
		case mk_hash_fn_md5: return 16; break;
		case mk_hash_fn_sha1: return 20; break;
		case mk_hash_fn_sha2_224: return 28; break;
		case mk_hash_fn_sha2_256: return 32; break;
		case mk_hash_fn_sha2_384: return 48; break;
		case mk_hash_fn_sha2_512: return 64; break;
		case mk_hash_fn_sha2_512224: return 28; break;
		case mk_hash_fn_sha2_512256: return 32; break;
		case mk_hash_fn_sha3_224: return 28; break;
		case mk_hash_fn_sha3_256: return 32; break;
		case mk_hash_fn_sha3_384: return 48; break;
		case mk_hash_fn_sha3_512: return 64; break;
	}

	return 0;
}

void mk_hash_fn_init(struct mk_hash_fn_s* hash_fn, enum mk_hash_fn_e id)
{
	mk_assert(hash_fn);
	mk_assert_id(id);

	hash_fn->m_id = id;
	switch(id)
	{
		case mk_hash_fn_md2: mk_md2_init(&hash_fn->m_state.m_md2); break;
		case mk_hash_fn_md4: mk_md4_init(&hash_fn->m_state.m_md4); break;
		case mk_hash_fn_md5: mk_md5_init(&hash_fn->m_state.m_md5); break;
		case mk_hash_fn_sha1: mk_sha1_init(&hash_fn->m_state.m_sha1); break;
		case mk_hash_fn_sha2_224: mk_sha2_224_init(&hash_fn->m_state.m_sha2_224); break;
		case mk_hash_fn_sha2_256: mk_sha2_256_init(&hash_fn->m_state.m_sha2_256); break;
		case mk_hash_fn_sha2_384: mk_sha2_384_init(&hash_fn->m_state.m_sha2_384); break;
		case mk_hash_fn_sha2_512: mk_sha2_512_init(&hash_fn->m_state.m_sha2_512); break;
		case mk_hash_fn_sha2_512224: mk_sha2_512224_init(&hash_fn->m_state.m_sha2_512224); break;
		case mk_hash_fn_sha2_512256: mk_sha2_512256_init(&hash_fn->m_state.m_sha2_512256); break;
		case mk_hash_fn_sha3_224: mk_sha3_224_init(&hash_fn->m_state.m_sha3_224); break;
		case mk_hash_fn_sha3_256: mk_sha3_256_init(&hash_fn->m_state.m_sha3_256); break;
		case mk_hash_fn_sha3_384: mk_sha3_384_init(&hash_fn->m_state.m_sha3_384); break;
		case mk_hash_fn_sha3_512: mk_sha3_512_init(&hash_fn->m_state.m_sha3_512); break;
	}
}

enum mk_hash_fn_e mk_hash_fn_get_id(struct mk_hash_fn_s* hash_fn)
{
	mk_assert(hash_fn);
	mk_assert_id(hash_fn->m_id);

	return hash_fn->m_id;
}

void mk_hash_fn_append(struct mk_hash_fn_s* hash_fn, void const* msg, size_t msg_len_bytes)
{
	mk_assert(hash_fn);
	mk_assert_id(hash_fn->m_id);

	switch(hash_fn->m_id)
	{
		case mk_hash_fn_md2: mk_md2_append(&hash_fn->m_state.m_md2, msg, msg_len_bytes); break;
		case mk_hash_fn_md4: mk_md4_append(&hash_fn->m_state.m_md4, msg, msg_len_bytes); break;
		case mk_hash_fn_md5: mk_md5_append(&hash_fn->m_state.m_md5, msg, msg_len_bytes); break;
		case mk_hash_fn_sha1: mk_sha1_append(&hash_fn->m_state.m_sha1, msg, msg_len_bytes); break;
		case mk_hash_fn_sha2_224: mk_sha2_224_append(&hash_fn->m_state.m_sha2_224, msg, msg_len_bytes); break;
		case mk_hash_fn_sha2_256: mk_sha2_256_append(&hash_fn->m_state.m_sha2_256, msg, msg_len_bytes); break;
		case mk_hash_fn_sha2_384: mk_sha2_384_append(&hash_fn->m_state.m_sha2_384, msg, msg_len_bytes); break;
		case mk_hash_fn_sha2_512: mk_sha2_512_append(&hash_fn->m_state.m_sha2_512, msg, msg_len_bytes); break;
		case mk_hash_fn_sha2_512224: mk_sha2_512224_append(&hash_fn->m_state.m_sha2_512224, msg, msg_len_bytes); break;
		case mk_hash_fn_sha2_512256: mk_sha2_512256_append(&hash_fn->m_state.m_sha2_512256, msg, msg_len_bytes); break;
		case mk_hash_fn_sha3_224: mk_sha3_224_append(&hash_fn->m_state.m_sha3_224, msg, msg_len_bytes); break;
		case mk_hash_fn_sha3_256: mk_sha3_256_append(&hash_fn->m_state.m_sha3_256, msg, msg_len_bytes); break;
		case mk_hash_fn_sha3_384: mk_sha3_384_append(&hash_fn->m_state.m_sha3_384, msg, msg_len_bytes); break;
		case mk_hash_fn_sha3_512: mk_sha3_512_append(&hash_fn->m_state.m_sha3_512, msg, msg_len_bytes); break;
	}
}

void mk_hash_fn_finish(struct mk_hash_fn_s* hash_fn, void* digest)
{
	mk_assert(hash_fn);
	mk_assert_id(hash_fn->m_id);

	switch(hash_fn->m_id)
	{
		case mk_hash_fn_md2: mk_md2_finish(&hash_fn->m_state.m_md2, digest); break;
		case mk_hash_fn_md4: mk_md4_finish(&hash_fn->m_state.m_md4, digest); break;
		case mk_hash_fn_md5: mk_md5_finish(&hash_fn->m_state.m_md5, digest); break;
		case mk_hash_fn_sha1: mk_sha1_finish(&hash_fn->m_state.m_sha1, digest); break;
		case mk_hash_fn_sha2_224: mk_sha2_224_finish(&hash_fn->m_state.m_sha2_224, digest); break;
		case mk_hash_fn_sha2_256: mk_sha2_256_finish(&hash_fn->m_state.m_sha2_256, digest); break;
		case mk_hash_fn_sha2_384: mk_sha2_384_finish(&hash_fn->m_state.m_sha2_384, digest); break;
		case mk_hash_fn_sha2_512: mk_sha2_512_finish(&hash_fn->m_state.m_sha2_512, digest); break;
		case mk_hash_fn_sha2_512224: mk_sha2_512224_finish(&hash_fn->m_state.m_sha2_512224, digest); break;
		case mk_hash_fn_sha2_512256: mk_sha2_512256_finish(&hash_fn->m_state.m_sha2_512256, digest); break;
		case mk_hash_fn_sha3_224: mk_sha3_224_finish(&hash_fn->m_state.m_sha3_224, digest); break;
		case mk_hash_fn_sha3_256: mk_sha3_256_finish(&hash_fn->m_state.m_sha3_256, digest); break;
		case mk_hash_fn_sha3_384: mk_sha3_384_finish(&hash_fn->m_state.m_sha3_384, digest); break;
		case mk_hash_fn_sha3_512: mk_sha3_512_finish(&hash_fn->m_state.m_sha3_512, digest); break;
	}
}


#undef mk_assert_id
