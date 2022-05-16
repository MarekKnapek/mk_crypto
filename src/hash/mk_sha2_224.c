#include "mk_sha2_224.h"

#include "base/mk_sha2_224_base.h"
#include "block/mk_sha2_224_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_sha2_224_init(struct mk_sha2_224_s* sha2_224)
{
	mk_assert(sha2_224);

	mk_sha2_224_base_init(&sha2_224->m_state);
	sha2_224->m_idx = 0;
}

mk_jumbo void mk_sha2_224_append(struct mk_sha2_224_s* sha2_224, void const* msg, int msg_len)
{
	mk_assert(sha2_224);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_sha2_224_block_append(&sha2_224->m_state, sha2_224->m_block, &sha2_224->m_idx, msg, msg_len);
}

mk_jumbo void mk_sha2_224_finish(struct mk_sha2_224_s* sha2_224, void* digest)
{
	mk_assert(sha2_224);
	mk_assert(digest);

	mk_sha2_224_base_finish(&sha2_224->m_state, sha2_224->m_block, sha2_224->m_idx, digest);
}
