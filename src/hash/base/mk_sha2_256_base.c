#include "mk_sha2_256_base.h"

#include "../../utils/mk_assert.h"

#include "../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../mk_int/src/exact/mk_uint_64.h"


static struct mk_uint32_s const mk_sha2_256_base_detail_init[8] =
{
	mk_uint32_c(0x6a09e667),
	mk_uint32_c(0xbb67ae85),
	mk_uint32_c(0x3c6ef372),
	mk_uint32_c(0xa54ff53a),
	mk_uint32_c(0x510e527f),
	mk_uint32_c(0x9b05688c),
	mk_uint32_c(0x1f83d9ab),
	mk_uint32_c(0x5be0cd19),
};


void mk_sha2_256_base_init(struct mk_sha2_256_base_s* sha2_256_base)
{
	mk_assert(sha2_256_base);

	sha2_256_base->m_256.m_state[0] = mk_sha2_256_base_detail_init[0];
	sha2_256_base->m_256.m_state[1] = mk_sha2_256_base_detail_init[1];
	sha2_256_base->m_256.m_state[2] = mk_sha2_256_base_detail_init[2];
	sha2_256_base->m_256.m_state[3] = mk_sha2_256_base_detail_init[3];
	sha2_256_base->m_256.m_state[4] = mk_sha2_256_base_detail_init[4];
	sha2_256_base->m_256.m_state[5] = mk_sha2_256_base_detail_init[5];
	sha2_256_base->m_256.m_state[6] = mk_sha2_256_base_detail_init[6];
	sha2_256_base->m_256.m_state[7] = mk_sha2_256_base_detail_init[7];
	mk_uint64_zero(&sha2_256_base->m_256.m_len);
}

void mk_sha2_256_base_append_blocks(struct mk_sha2_256_base_s* sha2_256_base, int nblocks, void const* pblocks)
{
	mk_assert(sha2_256_base);

	mk_sha2_base_detail_256_append_blocks(&sha2_256_base->m_256, nblocks, pblocks);
}

void mk_sha2_256_base_finish(struct mk_sha2_256_base_s* sha2_256_base, void* block, int idx, void* digest)
{
	mk_assert(sha2_256_base);

	mk_sha2_base_detail_256_finish(&sha2_256_base->m_256, block, idx, digest);
}
