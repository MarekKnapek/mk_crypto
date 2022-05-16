#include "mk_sha3_rawshake128.h"

#include "base/mk_sha3_rawshake128_base.h"
#include "block/mk_sha3_rawshake128_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_sha3_rawshake128_init(struct mk_sha3_rawshake128_s* sha3_rawshake128)
{
	mk_assert(sha3_rawshake128);

	mk_sha3_rawshake128_base_init(&sha3_rawshake128->m_state);
	sha3_rawshake128->m_idx = 0;
}

mk_jumbo void mk_sha3_rawshake128_append(struct mk_sha3_rawshake128_s* sha3_rawshake128, void const* msg, int msg_len)
{
	mk_assert(sha3_rawshake128);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_sha3_rawshake128_block_append(&sha3_rawshake128->m_state, sha3_rawshake128->m_block, &sha3_rawshake128->m_idx, msg, msg_len);
}

mk_jumbo void mk_sha3_rawshake128_finish(struct mk_sha3_rawshake128_s* sha3_rawshake128, int digest_len, void* digest)
{
	mk_assert(sha3_rawshake128);
	mk_assert(digest);

	mk_sha3_rawshake128_base_finish(&sha3_rawshake128->m_state, sha3_rawshake128->m_block, sha3_rawshake128->m_idx, digest_len, digest);
}
