#include "mk_sha2_512.h"

#include "base/mk_sha2_512_base.h"
#include "block/mk_sha2_512_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_sha2_512_init(struct mk_sha2_512_s* sha2_512)
{
	mk_assert(sha2_512);

	mk_sha2_512_base_init(&sha2_512->m_state);
	sha2_512->m_idx = 0;
}

mk_jumbo void mk_sha2_512_append(struct mk_sha2_512_s* sha2_512, void const* msg, int msg_len)
{
	mk_assert(sha2_512);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_sha2_512_block_append(&sha2_512->m_state, sha2_512->m_block, &sha2_512->m_idx, msg, msg_len);
}

mk_jumbo void mk_sha2_512_finish(struct mk_sha2_512_s* sha2_512, void* digest)
{
	mk_assert(sha2_512);
	mk_assert(digest);

	mk_sha2_512_base_finish(&sha2_512->m_state, sha2_512->m_block, sha2_512->m_idx, digest);
}
