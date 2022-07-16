#include "mk_hash_base_hash_sha2_512224.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memcpy */


static struct mk_uint64_s const mk_sha2_512224_base_detail_init[8] =
{
	mk_uint64_c(0x8c3d37c8ul, 0x19544da2ul),
	mk_uint64_c(0x73e19966ul, 0x89dcd4d6ul),
	mk_uint64_c(0x1dfab7aeul, 0x32ff9c82ul),
	mk_uint64_c(0x679dd514ul, 0x582f9fcful),
	mk_uint64_c(0x0f6d2b69ul, 0x7bd44da8ul),
	mk_uint64_c(0x77e36f73ul, 0x04c48942ul),
	mk_uint64_c(0x3f9d85a8ul, 0x6a1d36c8ul),
	mk_uint64_c(0x1112e6adul, 0x91d692a1ul),
};


mk_jumbo void mk_hash_base_hash_sha2_512224_init(struct mk_hash_base_hash_sha2_512224_s* self)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_512_init(&self->m_512, mk_sha2_512224_base_detail_init);
}

mk_jumbo void mk_hash_base_hash_sha2_512224_append_blocks(struct mk_hash_base_hash_sha2_512224_s* self, void const* pblocks, int nblocks)
{
	mk_assert(self);
	mk_assert(pblocks || nblocks == 0);
	mk_assert(nblocks >= 0);

	mk_hash_base_detail_sha2_512_append_blocks(&self->m_512, pblocks, nblocks);
}

mk_jumbo void mk_hash_base_hash_sha2_512224_finish(struct mk_hash_base_hash_sha2_512224_s* self, void* block, int idx, void* digest)
{
	unsigned char buff[64];

	mk_assert(self);
	mk_assert(digest);

	mk_hash_base_detail_sha2_512_finish(&self->m_512, block, idx, &buff);
	memcpy(digest, buff, mk_hash_base_hash_sha2_512224_digest_len);
}
