#include "mk_sha2_384.h"

#include "base/mk_sha2_384_base.h"
#include "block/mk_sha2_384_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_sha2_384_init(struct mk_sha2_384_s* sha2_384)
{
	mk_assert(sha2_384);

	mk_sha2_384_base_init(&sha2_384->m_state);
	sha2_384->m_idx = 0;
}

mk_jumbo void mk_sha2_384_append(struct mk_sha2_384_s* sha2_384, void const* msg, int msg_len)
{
	mk_assert(sha2_384);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_sha2_384_block_append(&sha2_384->m_state, sha2_384->m_block, &sha2_384->m_idx, msg, msg_len);
}

mk_jumbo void mk_sha2_384_finish(struct mk_sha2_384_s* sha2_384, void* digest)
{
	mk_assert(sha2_384);
	mk_assert(digest);

	mk_sha2_384_base_finish(&sha2_384->m_state, sha2_384->m_block, sha2_384->m_idx, digest);
}
