#include "mk_hash_base_xof_sha3_rawshake256.h"

#include "../detail/mk_hash_base_detail_sha3.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"


mk_jumbo void mk_hash_base_xof_sha3_rawshake256_init(struct mk_hash_base_xof_sha3_rawshake256_s* hash_base_xof_sha3_rawshake256)
{
	mk_assert(hash_base_xof_sha3_rawshake256);

	mk_hash_base_detail_sha3_init(&hash_base_xof_sha3_rawshake256->m_sha3);
}

mk_jumbo void mk_hash_base_xof_sha3_rawshake256_append_blocks(struct mk_hash_base_xof_sha3_rawshake256_s* hash_base_xof_sha3_rawshake256, int nblocks, void const* pblocks)
{
	mk_assert(hash_base_xof_sha3_rawshake256);

	mk_hash_base_detail_sha3_append_blocks(&hash_base_xof_sha3_rawshake256->m_sha3, mk_hash_base_xof_sha3_rawshake256_block_len, nblocks, pblocks);
}

mk_jumbo void mk_hash_base_xof_sha3_rawshake256_finish(struct mk_hash_base_xof_sha3_rawshake256_s* hash_base_xof_sha3_rawshake256, void* block, int idx, int digest_len, void* digest)
{
	mk_assert(hash_base_xof_sha3_rawshake256);

	mk_hash_base_detail_sha3_finish(&hash_base_xof_sha3_rawshake256->m_sha3, mk_hash_base_xof_sha3_rawshake256_block_len, block, idx, mk_hash_base_detail_sha3_domain_rawshake, digest_len, digest);
}
