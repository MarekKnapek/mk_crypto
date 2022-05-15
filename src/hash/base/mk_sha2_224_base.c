#include "mk_sha2_224_base.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_jumbo.h"

#include "../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memcpy */


static struct mk_uint32_s const mk_sha2_224_base_detail_init[8] =
{
	mk_uint32_c(0xc1059ed8),
	mk_uint32_c(0x367cd507),
	mk_uint32_c(0x3070dd17),
	mk_uint32_c(0xf70e5939),
	mk_uint32_c(0xffc00b31),
	mk_uint32_c(0x68581511),
	mk_uint32_c(0x64f98fa7),
	mk_uint32_c(0xbefa4fa4),
};


mk_jumbo void mk_sha2_224_base_init(struct mk_sha2_224_base_s* sha2_224_base)
{
	mk_assert(sha2_224_base);

	sha2_224_base->m_256.m_state[0] = mk_sha2_224_base_detail_init[0];
	sha2_224_base->m_256.m_state[1] = mk_sha2_224_base_detail_init[1];
	sha2_224_base->m_256.m_state[2] = mk_sha2_224_base_detail_init[2];
	sha2_224_base->m_256.m_state[3] = mk_sha2_224_base_detail_init[3];
	sha2_224_base->m_256.m_state[4] = mk_sha2_224_base_detail_init[4];
	sha2_224_base->m_256.m_state[5] = mk_sha2_224_base_detail_init[5];
	sha2_224_base->m_256.m_state[6] = mk_sha2_224_base_detail_init[6];
	sha2_224_base->m_256.m_state[7] = mk_sha2_224_base_detail_init[7];
	mk_uint64_zero(&sha2_224_base->m_256.m_len);
}

mk_jumbo void mk_sha2_224_base_append_blocks(struct mk_sha2_224_base_s* sha2_224_base, int nblocks, void const* pblocks)
{
	mk_assert(sha2_224_base);

	mk_sha2_base_detail_256_append_blocks(&sha2_224_base->m_256, nblocks, pblocks);
}

mk_jumbo void mk_sha2_224_base_finish(struct mk_sha2_224_base_s* sha2_224_base, void* block, int idx, void* digest)
{
	unsigned char buff[32];

	mk_assert(sha2_224_base);

	mk_sha2_base_detail_256_finish(&sha2_224_base->m_256, block, idx, &buff);
	memcpy(digest, buff, 28);
}
