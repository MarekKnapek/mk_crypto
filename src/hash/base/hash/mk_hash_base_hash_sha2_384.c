#include "mk_hash_base_hash_sha2_384.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memcpy */


static struct mk_uint64_s const mk_sha2_384_base_detail_init[8] =
{
	mk_uint64_c(0xcbbb9d5d, 0xc1059ed8),
	mk_uint64_c(0x629a292a, 0x367cd507),
	mk_uint64_c(0x9159015a, 0x3070dd17),
	mk_uint64_c(0x152fecd8, 0xf70e5939),
	mk_uint64_c(0x67332667, 0xffc00b31),
	mk_uint64_c(0x8eb44a87, 0x68581511),
	mk_uint64_c(0xdb0c2e0d, 0x64f98fa7),
	mk_uint64_c(0x47b5481d, 0xbefa4fa4),
};


mk_jumbo void mk_hash_base_hash_sha2_384_init(struct mk_hash_base_hash_sha2_384_s* self)
{
	mk_assert(self);
	
	mk_hash_base_detail_sha2_512_init(&self->m_512, mk_sha2_384_base_detail_init);
}

mk_jumbo void mk_hash_base_hash_sha2_384_append_blocks(struct mk_hash_base_hash_sha2_384_s* self, int nblocks, void const* pblocks)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_512_append_blocks(&self->m_512, nblocks, pblocks);
}

mk_jumbo void mk_hash_base_hash_sha2_384_finish(struct mk_hash_base_hash_sha2_384_s* self, void* block, int idx, void* digest)
{
	unsigned char buff[64];

	mk_assert(self);

	mk_hash_base_detail_sha2_512_finish(&self->m_512, block, idx, &buff);
	memcpy(digest, buff, mk_hash_base_hash_sha2_384_digest_len);
}
