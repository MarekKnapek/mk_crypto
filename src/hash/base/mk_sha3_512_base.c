#include "mk_sha3_512_base.h"

#include "../../utils/mk_assert.h"


void mk_sha3_512_base_init(struct mk_sha3_512_base_s* sha3_512_base)
{
	mk_assert(sha3_512_base);

	mk_sha3_base_detail_init(&sha3_512_base->m_sha3);
}

void mk_sha3_512_base_append_blocks(struct mk_sha3_512_base_s* sha3_512_base, int nblocks, void const* pblocks)
{
	mk_assert(sha3_512_base);

	mk_sha3_base_detail_append_blocks(&sha3_512_base->m_sha3, 72, nblocks, pblocks);
}

void mk_sha3_512_base_finish(struct mk_sha3_512_base_s* sha3_512_base, void* block, int idx, void* digest)
{
	mk_assert(sha3_512_base);

	mk_sha3_base_detail_finish(&sha3_512_base->m_sha3, 72, block, idx, mk_sha3_base_detail_domain_sha3, 64, digest);
}
