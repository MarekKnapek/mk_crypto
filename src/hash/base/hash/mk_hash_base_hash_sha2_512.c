#include "mk_hash_base_hash_sha2_512.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"


static struct mk_uint64_s const mk_sha2_512_base_detail_init[8] =
{
	mk_uint64_c(0x6a09e667, 0xf3bcc908),
	mk_uint64_c(0xbb67ae85, 0x84caa73b),
	mk_uint64_c(0x3c6ef372, 0xfe94f82b),
	mk_uint64_c(0xa54ff53a, 0x5f1d36f1),
	mk_uint64_c(0x510e527f, 0xade682d1),
	mk_uint64_c(0x9b05688c, 0x2b3e6c1f),
	mk_uint64_c(0x1f83d9ab, 0xfb41bd6b),
	mk_uint64_c(0x5be0cd19, 0x137e2179),
};


mk_jumbo void mk_hash_base_hash_sha2_512_init(struct mk_hash_base_hash_sha2_512_s* self)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_512_init(&self->m_512, mk_sha2_512_base_detail_init);
}

mk_jumbo void mk_hash_base_hash_sha2_512_append_blocks(struct mk_hash_base_hash_sha2_512_s* self, int nblocks, void const* pblocks)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_512_append_blocks(&self->m_512, nblocks, pblocks);
}

mk_jumbo void mk_hash_base_hash_sha2_512_finish(struct mk_hash_base_hash_sha2_512_s* self, void* block, int idx, void* digest)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_512_finish(&self->m_512, block, idx, digest);
}
