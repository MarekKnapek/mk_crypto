#include "mk_hash_base_hash_sha2_384.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memcpy */


static struct mk_uint64_s const mk_sha2_384_base_detail_init[8] =
{
	mk_uint64_c(0xcbbb9d5dul, 0xc1059ed8ul),
	mk_uint64_c(0x629a292aul, 0x367cd507ul),
	mk_uint64_c(0x9159015aul, 0x3070dd17ul),
	mk_uint64_c(0x152fecd8ul, 0xf70e5939ul),
	mk_uint64_c(0x67332667ul, 0xffc00b31ul),
	mk_uint64_c(0x8eb44a87ul, 0x68581511ul),
	mk_uint64_c(0xdb0c2e0dul, 0x64f98fa7ul),
	mk_uint64_c(0x47b5481dul, 0xbefa4fa4ul),
};


mk_jumbo void mk_hash_base_hash_sha2_384_init(struct mk_hash_base_hash_sha2_384_s* self)
{
	mk_assert(self);
	
	mk_hash_base_detail_sha2_512_init(&self->m_512, mk_sha2_384_base_detail_init);
}

mk_jumbo void mk_hash_base_hash_sha2_384_append_blocks(struct mk_hash_base_hash_sha2_384_s* self, void const* pblocks, int nblocks)
{
	mk_assert(self);
	mk_assert(pblocks || nblocks == 0);
	mk_assert(nblocks >= 0);

	mk_hash_base_detail_sha2_512_append_blocks(&self->m_512, pblocks, nblocks);
}

mk_jumbo void mk_hash_base_hash_sha2_384_finish(struct mk_hash_base_hash_sha2_384_s* self, void* block, int idx, void* digest)
{
	unsigned char buff[64];

	mk_assert(self);
	mk_assert(digest);

	mk_hash_base_detail_sha2_512_finish(&self->m_512, block, idx, &buff);
	memcpy(digest, buff, mk_hash_base_hash_sha2_384_digest_len);
}
