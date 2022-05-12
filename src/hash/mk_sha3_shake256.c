#include "mk_sha3_shake256.h"

#include "mk_sha3_detail.h"

#include "../utils/mk_assert.h"

#include "../../../mk_int/src/exact/mk_uint_64.h"

#include <limits.h> /* CHAR_BIT */
#include <stddef.h> /* size_t */


void mk_sha3_shake256_init(struct mk_sha3_shake256_state_s* self)
{
	mk_assert(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_shake256_append(struct mk_sha3_shake256_state_s* self, void const* msg, size_t msg_len_bytes)
{
	mk_assert(self);

	mk_sha3_shake256_append_bits(self, msg, msg_len_bytes * CHAR_BIT);
}

void mk_sha3_shake256_append_bits(struct mk_sha3_shake256_state_s* self, void const* msg, size_t msg_len_bits)
{
	mk_assert(self);

	mk_sha3_detail_append_bits(self->m_state, &self->m_idx, self->m_block, sizeof(self->m_block) * CHAR_BIT, msg, msg_len_bits);
}

void mk_sha3_shake256_finish(struct mk_sha3_shake256_state_s* self, void* digest, size_t digest_len_bits)
{
	mk_assert(self);
	mk_assert(digest);

	mk_sha3_detail_finish(self->m_state, &self->m_idx, self->m_block, sizeof(self->m_block) * CHAR_BIT, mk_sha3_detail_domain_e_shake, digest, digest_len_bits);
}
