#include "mk_sha3_256.h"

#include "base/mk_sha3_256_base.h"
#include "block/mk_sha3_256_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_sha3_256_init(struct mk_sha3_256_s* sha3_256)
{
	mk_assert(sha3_256);

	mk_sha3_256_base_init(&sha3_256->m_state);
	sha3_256->m_idx = 0;
}

mk_jumbo void mk_sha3_256_append(struct mk_sha3_256_s* sha3_256, void const* msg, int msg_len)
{
	mk_assert(sha3_256);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_sha3_256_block_append(&sha3_256->m_state, sha3_256->m_block, &sha3_256->m_idx, msg, msg_len);
}

mk_jumbo void mk_sha3_256_finish(struct mk_sha3_256_s* sha3_256, void* digest)
{
	mk_assert(sha3_256);
	mk_assert(digest);

	mk_sha3_256_base_finish(&sha3_256->m_state, sha3_256->m_block, sha3_256->m_idx, digest);
}
