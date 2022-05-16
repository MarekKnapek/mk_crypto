#include "mk_md5.h"

#include "base/mk_md5_base.h"
#include "block/mk_md5_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_md5_init(struct mk_md5_s* md5)
{
	mk_assert(md5);

	mk_md5_base_init(&md5->m_state);
	md5->m_idx = 0;
}

mk_jumbo void mk_md5_append(struct mk_md5_s* md5, void const* msg, int msg_len)
{
	mk_assert(md5);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_md5_block_append(&md5->m_state, md5->m_block, &md5->m_idx, msg, msg_len);
}

mk_jumbo void mk_md5_finish(struct mk_md5_s* md5, void* digest)
{
	mk_assert(md5);
	mk_assert(digest);

	mk_md5_base_finish(&md5->m_state, md5->m_block, md5->m_idx, digest);
}
