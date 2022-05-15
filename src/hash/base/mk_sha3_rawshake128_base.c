#include "mk_sha3_rawshake128_base.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_jumbo.h"


mk_jumbo void mk_sha3_rawshake128_base_init(struct mk_sha3_rawshake128_base_s* sha3_rawshake128_base)
{
	mk_assert(sha3_rawshake128_base);

	mk_sha3_base_detail_init(&sha3_rawshake128_base->m_sha3);
}

mk_jumbo void mk_sha3_rawshake128_base_append_blocks(struct mk_sha3_rawshake128_base_s* sha3_rawshake128_base, int nblocks, void const* pblocks)
{
	mk_assert(sha3_rawshake128_base);

	mk_sha3_base_detail_append_blocks(&sha3_rawshake128_base->m_sha3, 168, nblocks, pblocks);
}

mk_jumbo void mk_sha3_rawshake128_base_finish(struct mk_sha3_rawshake128_base_s* sha3_rawshake128_base, void* block, int idx, int digest_len, void* digest)
{
	mk_assert(sha3_rawshake128_base);

	mk_sha3_base_detail_finish(&sha3_rawshake128_base->m_sha3, 168, block, idx, mk_sha3_base_detail_domain_rawshake, digest_len, digest);
}
