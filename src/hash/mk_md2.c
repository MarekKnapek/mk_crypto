#include "mk_md2.h"

#include "base/mk_md2_base.h"
#include "block/mk_md2_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_md2_init(struct mk_md2_s* md2)
{
	mk_assert(md2);

	mk_md2_base_init(&md2->m_state);
	md2->m_idx = 0;
}

mk_jumbo void mk_md2_append(struct mk_md2_s* md2, void const* msg, int msg_len)
{
	mk_assert(md2);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_md2_block_append(&md2->m_state, md2->m_block, &md2->m_idx, msg, msg_len);
}

mk_jumbo void mk_md2_finish(struct mk_md2_s* md2, void* digest)
{
	mk_assert(md2);
	mk_assert(digest);

	mk_md2_base_finish(&md2->m_state, md2->m_block, md2->m_idx, digest);
}
