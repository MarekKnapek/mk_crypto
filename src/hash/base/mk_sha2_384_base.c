#include "mk_sha2_384_base.h"

#include "../../utils/mk_assert.h"

#include "../../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../../mk_int/src/exact/mk_uint_128.h"

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


void mk_sha2_384_base_init(struct mk_sha2_384_base_s* sha2_384_base)
{
	mk_assert(sha2_384_base);

	sha2_384_base->m_512.m_state[0] = mk_sha2_384_base_detail_init[0];
	sha2_384_base->m_512.m_state[1] = mk_sha2_384_base_detail_init[1];
	sha2_384_base->m_512.m_state[2] = mk_sha2_384_base_detail_init[2];
	sha2_384_base->m_512.m_state[3] = mk_sha2_384_base_detail_init[3];
	sha2_384_base->m_512.m_state[4] = mk_sha2_384_base_detail_init[4];
	sha2_384_base->m_512.m_state[5] = mk_sha2_384_base_detail_init[5];
	sha2_384_base->m_512.m_state[6] = mk_sha2_384_base_detail_init[6];
	sha2_384_base->m_512.m_state[7] = mk_sha2_384_base_detail_init[7];
	mk_uint128_zero(&sha2_384_base->m_512.m_len);
}

void mk_sha2_384_base_append_blocks(struct mk_sha2_384_base_s* sha2_384_base, int nblocks, void const* pblocks)
{
	mk_assert(sha2_384_base);

	mk_sha2_base_detail_512_append_blocks(&sha2_384_base->m_512, nblocks, pblocks);
}

void mk_sha2_384_base_finish(struct mk_sha2_384_base_s* sha2_384_base, void* block, int idx, void* digest)
{
	unsigned char buff[64];

	mk_assert(sha2_384_base);

	mk_sha2_base_detail_512_finish(&sha2_384_base->m_512, block, idx, &buff);
	memcpy(digest, buff, 48);
}
