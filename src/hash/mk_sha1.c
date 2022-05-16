#include "mk_sha1.h"

#include "base/mk_sha1_base.h"
#include "block/mk_sha1_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_sha1_init(struct mk_sha1_s* sha1)
{
	mk_assert(sha1);

	mk_sha1_base_init(&sha1->m_state);
	sha1->m_idx = 0;
}

mk_jumbo void mk_sha1_append(struct mk_sha1_s* sha1, void const* msg, int msg_len)
{
	mk_assert(sha1);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_sha1_block_append(&sha1->m_state, sha1->m_block, &sha1->m_idx, msg, msg_len);
}

mk_jumbo void mk_sha1_finish(struct mk_sha1_s* sha1, void* digest)
{
	mk_assert(sha1);
	mk_assert(digest);

	mk_sha1_base_finish(&sha1->m_state, sha1->m_block, sha1->m_idx, digest);
}
