#include "mk_hash_base_hash_sha3_224.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"


mk_jumbo void mk_hash_base_hash_sha3_224_init(struct mk_hash_base_hash_sha3_224_s* self)
{
	mk_assert(self);

	mk_hash_base_detail_sha3_init(&self->m_sha3);
}

mk_jumbo void mk_hash_base_hash_sha3_224_append_blocks(struct mk_hash_base_hash_sha3_224_s* self, int nblocks, void const* pblocks)
{
	mk_assert(self);
	mk_assert(pblocks || nblocks == 0);
	mk_assert(nblocks >= 0);

	mk_hash_base_detail_sha3_append_blocks(&self->m_sha3, mk_hash_base_hash_sha3_224_block_len, nblocks, pblocks);
}

mk_jumbo void mk_hash_base_hash_sha3_224_finish(struct mk_hash_base_hash_sha3_224_s* self, void* block, int idx, void* digest)
{
	mk_assert(self);
	mk_assert(digest);

	mk_hash_base_detail_sha3_finish(&self->m_sha3, mk_hash_base_hash_sha3_224_block_len, block, idx, mk_hash_base_detail_sha3_domain_sha3, mk_hash_base_hash_sha3_224_digest_len, digest);
}
