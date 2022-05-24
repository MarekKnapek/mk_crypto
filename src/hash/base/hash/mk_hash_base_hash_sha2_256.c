#include "mk_hash_base_hash_sha2_256.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_32.h"


static struct mk_uint32_s const mk_sha2_256_base_detail_init[8] =
{
	mk_uint32_c(0x6a09e667),
	mk_uint32_c(0xbb67ae85),
	mk_uint32_c(0x3c6ef372),
	mk_uint32_c(0xa54ff53a),
	mk_uint32_c(0x510e527f),
	mk_uint32_c(0x9b05688c),
	mk_uint32_c(0x1f83d9ab),
	mk_uint32_c(0x5be0cd19),
};


mk_jumbo void mk_hash_base_hash_sha2_256_init(struct mk_hash_base_hash_sha2_256_s* self)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_256_init(&self->m_256, mk_sha2_256_base_detail_init);
}

mk_jumbo void mk_hash_base_hash_sha2_256_append_blocks(struct mk_hash_base_hash_sha2_256_s* self, int nblocks, void const* pblocks)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_256_append_blocks(&self->m_256, nblocks, pblocks);
}

mk_jumbo void mk_hash_base_hash_sha2_256_finish(struct mk_hash_base_hash_sha2_256_s* self, void* block, int idx, void* digest)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_256_finish(&self->m_256, block, idx, digest);
}