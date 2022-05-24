#include "mk_hash_base_hash_sha2_512224.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memcpy */


static struct mk_uint64_s const mk_sha2_512224_base_detail_init[8] =
{
	mk_uint64_c(0x8c3d37c8, 0x19544da2),
	mk_uint64_c(0x73e19966, 0x89dcd4d6),
	mk_uint64_c(0x1dfab7ae, 0x32ff9c82),
	mk_uint64_c(0x679dd514, 0x582f9fcf),
	mk_uint64_c(0x0f6d2b69, 0x7bd44da8),
	mk_uint64_c(0x77e36f73, 0x04c48942),
	mk_uint64_c(0x3f9d85a8, 0x6a1d36c8),
	mk_uint64_c(0x1112e6ad, 0x91d692a1),
};


mk_jumbo void mk_hash_base_hash_sha2_512224_init(struct mk_hash_base_hash_sha2_512224_s* self)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_512_init(&self->m_512, mk_sha2_512224_base_detail_init);
}

mk_jumbo void mk_hash_base_hash_sha2_512224_append_blocks(struct mk_hash_base_hash_sha2_512224_s* self, int nblocks, void const* pblocks)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_512_append_blocks(&self->m_512, nblocks, pblocks);
}

mk_jumbo void mk_hash_base_hash_sha2_512224_finish(struct mk_hash_base_hash_sha2_512224_s* self, void* block, int idx, void* digest)
{
	unsigned char buff[64];

	mk_assert(self);

	mk_hash_base_detail_sha2_512_finish(&self->m_512, block, idx, &buff);
	memcpy(digest, buff, mk_hash_base_hash_sha2_512224_digest_len);
}
