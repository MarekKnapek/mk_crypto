#include "mk_md4.h"

#include "base/mk_md4_base.h"
#include "block/mk_md4_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_md4_init(struct mk_md4_s* md4)
{
	mk_assert(md4);

	mk_md4_base_init(&md4->m_state);
	md4->m_idx = 0;
}

mk_jumbo void mk_md4_append(struct mk_md4_s* md4, void const* msg, int msg_len)
{
	mk_assert(md4);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_md4_block_append(&md4->m_state, md4->m_block, &md4->m_idx, msg, msg_len);
}

mk_jumbo void mk_md4_finish(struct mk_md4_s* md4, void* digest)
{
	mk_assert(md4);
	mk_assert(digest);

	mk_md4_base_finish(&md4->m_state, md4->m_block, md4->m_idx, digest);
}
