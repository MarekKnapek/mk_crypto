#include "mk_sha2_512224_base.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_jumbo.h"

#include "../../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../../mk_int/src/exact/mk_uint_128.h"

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


mk_jumbo void mk_sha2_512224_base_init(struct mk_sha2_512224_base_s* sha2_512224_base)
{
	mk_assert(sha2_512224_base);

	sha2_512224_base->m_512.m_state[0] = mk_sha2_512224_base_detail_init[0];
	sha2_512224_base->m_512.m_state[1] = mk_sha2_512224_base_detail_init[1];
	sha2_512224_base->m_512.m_state[2] = mk_sha2_512224_base_detail_init[2];
	sha2_512224_base->m_512.m_state[3] = mk_sha2_512224_base_detail_init[3];
	sha2_512224_base->m_512.m_state[4] = mk_sha2_512224_base_detail_init[4];
	sha2_512224_base->m_512.m_state[5] = mk_sha2_512224_base_detail_init[5];
	sha2_512224_base->m_512.m_state[6] = mk_sha2_512224_base_detail_init[6];
	sha2_512224_base->m_512.m_state[7] = mk_sha2_512224_base_detail_init[7];
	mk_uint128_zero(&sha2_512224_base->m_512.m_len);
}

mk_jumbo void mk_sha2_512224_base_append_blocks(struct mk_sha2_512224_base_s* sha2_512224_base, int nblocks, void const* pblocks)
{
	mk_assert(sha2_512224_base);

	mk_sha2_base_detail_512_append_blocks(&sha2_512224_base->m_512, nblocks, pblocks);
}

mk_jumbo void mk_sha2_512224_base_finish(struct mk_sha2_512224_base_s* sha2_512224_base, void* block, int idx, void* digest)
{
	unsigned char buff[64];

	mk_assert(sha2_512224_base);

	mk_sha2_base_detail_512_finish(&sha2_512224_base->m_512, block, idx, &buff);
	memcpy(digest, buff, 28);
}
