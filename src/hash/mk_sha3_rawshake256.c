#include "mk_sha3_rawshake256.h"

#include "base/mk_sha3_rawshake256_base.h"
#include "block/mk_sha3_rawshake256_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_sha3_rawshake256_init(struct mk_sha3_rawshake256_s* sha3_rawshake256)
{
	mk_assert(sha3_rawshake256);

	mk_sha3_rawshake256_base_init(&sha3_rawshake256->m_state);
	sha3_rawshake256->m_idx = 0;
}

mk_jumbo void mk_sha3_rawshake256_append(struct mk_sha3_rawshake256_s* sha3_rawshake256, void const* msg, int msg_len)
{
	mk_assert(sha3_rawshake256);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_sha3_rawshake256_block_append(&sha3_rawshake256->m_state, sha3_rawshake256->m_block, &sha3_rawshake256->m_idx, msg, msg_len);
}

mk_jumbo void mk_sha3_rawshake256_finish(struct mk_sha3_rawshake256_s* sha3_rawshake256, int digest_len, void* digest)
{
	mk_assert(sha3_rawshake256);
	mk_assert(digest);

	mk_sha3_rawshake256_base_finish(&sha3_rawshake256->m_state, sha3_rawshake256->m_block, sha3_rawshake256->m_idx, digest_len, digest);
}
