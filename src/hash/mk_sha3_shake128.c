#include "mk_sha3_shake128.h"

#include "base/mk_sha3_shake128_base.h"
#include "block/mk_sha3_shake128_block.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_sha3_shake128_init(struct mk_sha3_shake128_s* sha3_shake128)
{
	mk_assert(sha3_shake128);

	mk_sha3_shake128_base_init(&sha3_shake128->m_state);
	sha3_shake128->m_idx = 0;
}

mk_jumbo void mk_sha3_shake128_append(struct mk_sha3_shake128_s* sha3_shake128, void const* msg, int msg_len)
{
	mk_assert(sha3_shake128);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_sha3_shake128_block_append(&sha3_shake128->m_state, sha3_shake128->m_block, &sha3_shake128->m_idx, msg, msg_len);
}

mk_jumbo void mk_sha3_shake128_finish(struct mk_sha3_shake128_s* sha3_shake128, int digest_len, void* digest)
{
	mk_assert(sha3_shake128);
	mk_assert(digest);

	mk_sha3_shake128_base_finish(&sha3_shake128->m_state, sha3_shake128->m_block, sha3_shake128->m_idx, digest_len, digest);
}
