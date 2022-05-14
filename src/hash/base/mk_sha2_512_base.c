#include "mk_sha2_512_base.h"

#include "../../utils/mk_assert.h"

#include "../../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../../mk_int/src/exact/mk_uint_128.h"


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


void mk_sha2_512_base_init(struct mk_sha2_512_base_s* sha2_512_base)
{
	mk_assert(sha2_512_base);

	sha2_512_base->m_512.m_state[0] = mk_sha2_512_base_detail_init[0];
	sha2_512_base->m_512.m_state[1] = mk_sha2_512_base_detail_init[1];
	sha2_512_base->m_512.m_state[2] = mk_sha2_512_base_detail_init[2];
	sha2_512_base->m_512.m_state[3] = mk_sha2_512_base_detail_init[3];
	sha2_512_base->m_512.m_state[4] = mk_sha2_512_base_detail_init[4];
	sha2_512_base->m_512.m_state[5] = mk_sha2_512_base_detail_init[5];
	sha2_512_base->m_512.m_state[6] = mk_sha2_512_base_detail_init[6];
	sha2_512_base->m_512.m_state[7] = mk_sha2_512_base_detail_init[7];
	mk_uint128_zero(&sha2_512_base->m_512.m_len);
}

void mk_sha2_512_base_append_blocks(struct mk_sha2_512_base_s* sha2_512_base, int nblocks, void const* pblocks)
{
	mk_assert(sha2_512_base);

	mk_sha2_base_detail_512_append_blocks(&sha2_512_base->m_512, nblocks, pblocks);
}

void mk_sha2_512_base_finish(struct mk_sha2_512_base_s* sha2_512_base, void* block, int idx, void* digest)
{
	mk_assert(sha2_512_base);

	mk_sha2_base_detail_512_finish(&sha2_512_base->m_512, block, idx, digest);
}
