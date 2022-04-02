#include "mk_sha2_512.h"

#include "mk_sha2_detail_512.h"

#include "../utils/mk_assert.h"

#include "../../mk_int/src/exact/mk_uint_64.h"
#include "../../mk_int/src/exact/mk_uint_128.h"

#include <stddef.h> /* size_t */


void mk_sha2_512_init(struct mk_sha2_512_state_s* self)
{
	static struct mk_uint64_s const mk_sha2_512_detail_init[] =
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

	mk_assert(self);

	self->m_state[0] = mk_sha2_512_detail_init[0];
	self->m_state[1] = mk_sha2_512_detail_init[1];
	self->m_state[2] = mk_sha2_512_detail_init[2];
	self->m_state[3] = mk_sha2_512_detail_init[3];
	self->m_state[4] = mk_sha2_512_detail_init[4];
	self->m_state[5] = mk_sha2_512_detail_init[5];
	self->m_state[6] = mk_sha2_512_detail_init[6];
	self->m_state[7] = mk_sha2_512_detail_init[7];
	mk_uint128_zero(&self->m_len);
}

void mk_sha2_512_append(struct mk_sha2_512_state_s* self, void const* msg, size_t msg_len_bytes)
{
	mk_assert(self);
	
	mk_sha2_detail_512_append(self->m_state, &self->m_len, self->m_block, msg, msg_len_bytes);
}

void mk_sha2_512_finish(struct mk_sha2_512_state_s* self, void* digest)
{
	mk_assert(self);
	mk_assert(digest);

	mk_sha2_detail_512_finish(self->m_state, &self->m_len, self->m_block, digest);
}
