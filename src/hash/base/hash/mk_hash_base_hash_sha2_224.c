#include "mk_hash_base_hash_sha2_224.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_32.h"

#include <string.h> /* memcpy */


static struct mk_uint32_s const mk_sha2_224_base_detail_init[8] =
{
	mk_uint32_c(0xc1059ed8ul),
	mk_uint32_c(0x367cd507ul),
	mk_uint32_c(0x3070dd17ul),
	mk_uint32_c(0xf70e5939ul),
	mk_uint32_c(0xffc00b31ul),
	mk_uint32_c(0x68581511ul),
	mk_uint32_c(0x64f98fa7ul),
	mk_uint32_c(0xbefa4fa4ul),
};


mk_jumbo void mk_hash_base_hash_sha2_224_init(struct mk_hash_base_hash_sha2_224_s* self)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_256_init(&self->m_256, mk_sha2_224_base_detail_init);
}

mk_jumbo void mk_hash_base_hash_sha2_224_append_blocks(struct mk_hash_base_hash_sha2_224_s* self, int nblocks, void const* pblocks)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_256_append_blocks(&self->m_256, nblocks, pblocks);
}

mk_jumbo void mk_hash_base_hash_sha2_224_finish(struct mk_hash_base_hash_sha2_224_s* self, void* block, int idx, void* digest)
{
	unsigned char buff[32];

	mk_assert(self);

	mk_hash_base_detail_sha2_256_finish(&self->m_256, block, idx, &buff);
	memcpy(digest, buff, mk_hash_base_hash_sha2_224_digest_len);
}
