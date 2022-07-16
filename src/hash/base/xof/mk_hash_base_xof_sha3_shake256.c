#include "mk_hash_base_xof_sha3_shake256.h"

#include "../detail/mk_hash_base_detail_sha3.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"


mk_jumbo void mk_hash_base_xof_sha3_shake256_init(struct mk_hash_base_xof_sha3_shake256_s* hash_base_xof_sha3_shake256)
{
	mk_assert(hash_base_xof_sha3_shake256);

	mk_hash_base_detail_sha3_init(&hash_base_xof_sha3_shake256->m_sha3);
}

mk_jumbo void mk_hash_base_xof_sha3_shake256_append_blocks(struct mk_hash_base_xof_sha3_shake256_s* hash_base_xof_sha3_shake256, void const* pblocks, int nblocks)
{
	mk_assert(hash_base_xof_sha3_shake256);
	mk_assert(pblocks || nblocks == 0);
	mk_assert(nblocks >= 0);

	mk_hash_base_detail_sha3_append_blocks(&hash_base_xof_sha3_shake256->m_sha3, mk_hash_base_xof_sha3_shake256_block_len, pblocks, nblocks);
}

mk_jumbo void mk_hash_base_xof_sha3_shake256_finish(struct mk_hash_base_xof_sha3_shake256_s* hash_base_xof_sha3_shake256, void* block, int idx, int digest_len, void* digest)
{
	mk_assert(hash_base_xof_sha3_shake256);
	mk_assert(block);
	mk_assert(idx >= 0 && idx < mk_hash_base_xof_sha3_shake256_block_len);
	mk_assert(digest_len > 0);
	mk_assert(digest);

	mk_hash_base_detail_sha3_finish(&hash_base_xof_sha3_shake256->m_sha3, mk_hash_base_xof_sha3_shake256_block_len, block, idx, mk_hash_base_detail_sha3_domain_shake, digest_len, digest);
}
