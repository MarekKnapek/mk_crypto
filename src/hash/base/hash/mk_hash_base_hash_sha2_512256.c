#include "mk_hash_base_hash_sha2_512256.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memcpy */


static struct mk_uint64_s const mk_sha2_512256_base_detail_init[8] =
{
	mk_uint64_c(0x22312194, 0xfc2bf72c),
	mk_uint64_c(0x9f555fa3, 0xc84c64c2),
	mk_uint64_c(0x2393b86b, 0x6f53b151),
	mk_uint64_c(0x96387719, 0x5940eabd),
	mk_uint64_c(0x96283ee2, 0xa88effe3),
	mk_uint64_c(0xbe5e1e25, 0x53863992),
	mk_uint64_c(0x2b0199fc, 0x2c85b8aa),
	mk_uint64_c(0x0eb72ddc, 0x81c52ca2),
};


mk_jumbo void mk_hash_base_hash_sha2_512256_init(struct mk_hash_base_hash_sha2_512256_s* self)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_512_init(&self->m_512, mk_sha2_512256_base_detail_init);
}

mk_jumbo void mk_hash_base_hash_sha2_512256_append_blocks(struct mk_hash_base_hash_sha2_512256_s* self, int nblocks, void const* pblocks)
{
	mk_assert(self);

	mk_hash_base_detail_sha2_512_append_blocks(&self->m_512, nblocks, pblocks);
}

mk_jumbo void mk_hash_base_hash_sha2_512256_finish(struct mk_hash_base_hash_sha2_512256_s* self, void* block, int idx, void* digest)
{
	unsigned char buff[64];

	mk_assert(self);

	mk_hash_base_detail_sha2_512_finish(&self->m_512, block, idx, &buff);
	memcpy(digest, buff, mk_hash_base_hash_sha2_512256_digest_len);
}
