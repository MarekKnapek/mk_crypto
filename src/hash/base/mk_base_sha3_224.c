#include "mk_sha3_224_base.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_jumbo.h"


mk_jumbo void mk_sha3_224_base_init(struct mk_sha3_224_base_s* sha3_224_base)
{
	mk_assert(sha3_224_base);

	mk_sha3_base_detail_init(&sha3_224_base->m_sha3);
}

mk_jumbo void mk_sha3_224_base_append_blocks(struct mk_sha3_224_base_s* sha3_224_base, int nblocks, void const* pblocks)
{
	mk_assert(sha3_224_base);

	mk_sha3_base_detail_append_blocks(&sha3_224_base->m_sha3, 144, nblocks, pblocks);
}

mk_jumbo void mk_sha3_224_base_finish(struct mk_sha3_224_base_s* sha3_224_base, void* block, int idx, void* digest)
{
	mk_assert(sha3_224_base);

	mk_sha3_base_detail_finish(&sha3_224_base->m_sha3, 144, block, idx, mk_sha3_base_detail_domain_sha3, 28, digest);
}
