#include "mk_sha2_512256_base.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_jumbo.h"

#include "../../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../../mk_int/src/exact/mk_uint_128.h"

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


mk_jumbo void mk_sha2_512256_base_init(struct mk_sha2_512256_base_s* sha2_512256_base)
{
	mk_assert(sha2_512256_base);

	sha2_512256_base->m_512.m_state[0] = mk_sha2_512256_base_detail_init[0];
	sha2_512256_base->m_512.m_state[1] = mk_sha2_512256_base_detail_init[1];
	sha2_512256_base->m_512.m_state[2] = mk_sha2_512256_base_detail_init[2];
	sha2_512256_base->m_512.m_state[3] = mk_sha2_512256_base_detail_init[3];
	sha2_512256_base->m_512.m_state[4] = mk_sha2_512256_base_detail_init[4];
	sha2_512256_base->m_512.m_state[5] = mk_sha2_512256_base_detail_init[5];
	sha2_512256_base->m_512.m_state[6] = mk_sha2_512256_base_detail_init[6];
	sha2_512256_base->m_512.m_state[7] = mk_sha2_512256_base_detail_init[7];
	mk_uint128_zero(&sha2_512256_base->m_512.m_len);
}

mk_jumbo void mk_sha2_512256_base_append_blocks(struct mk_sha2_512256_base_s* sha2_512256_base, int nblocks, void const* pblocks)
{
	mk_assert(sha2_512256_base);

	mk_sha2_base_detail_512_append_blocks(&sha2_512256_base->m_512, nblocks, pblocks);
}

mk_jumbo void mk_sha2_512256_base_finish(struct mk_sha2_512256_base_s* sha2_512256_base, void* block, int idx, void* digest)
{
	unsigned char buff[64];

	mk_assert(sha2_512256_base);

	mk_sha2_base_detail_512_finish(&sha2_512256_base->m_512, block, idx, &buff);
	memcpy(digest, buff, 32);
}
