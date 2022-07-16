#include "mk_hash_base_hash_sha2_512.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"


static struct mk_uint64_s const mk_sha2_512_base_detail_init[8] =
{
	mk_uint64_c(0x6a09e667ul, 0xf3bcc908ul),
	mk_uint64_c(0xbb67ae85ul, 0x84caa73bul),
	mk_uint64_c(0x3c6ef372ul, 0xfe94f82bul),
	mk_uint64_c(0xa54ff53aul, 0x5f1d36f1ul),
	mk_uint64_c(0x510e527ful, 0xade682d1ul),
	mk_uint64_c(0x9b05688cul, 0x2b3e6c1ful),
	mk_uint64_c(0x1f83d9abul, 0xfb41bd6bul),
	mk_uint64_c(0x5be0cd19ul, 0x137e2179ul),
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
