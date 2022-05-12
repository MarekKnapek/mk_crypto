#include "mk_sha2_256.h"

#include "mk_sha2_detail_256.h"

#include "../utils/mk_assert.h"

#include "../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../mk_int/src/exact/mk_uint_64.h"

#include <stddef.h> /* size_t */


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4711) /* warning C4711: function 'xxx' selected for automatic inline expansion */
#endif


void mk_sha2_256_init(struct mk_sha2_256_state_s* self)
{
	static struct mk_uint32_s const mk_sha2_256_detail_init[] =
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

	mk_assert(self);

	self->m_state[0] = mk_sha2_256_detail_init[0];
	self->m_state[1] = mk_sha2_256_detail_init[1];
	self->m_state[2] = mk_sha2_256_detail_init[2];
	self->m_state[3] = mk_sha2_256_detail_init[3];
	self->m_state[4] = mk_sha2_256_detail_init[4];
	self->m_state[5] = mk_sha2_256_detail_init[5];
	self->m_state[6] = mk_sha2_256_detail_init[6];
	self->m_state[7] = mk_sha2_256_detail_init[7];
	mk_uint64_zero(&self->m_len);
}

void mk_sha2_256_append(struct mk_sha2_256_state_s* self, void const* msg, size_t msg_len_bytes)
{
	mk_assert(self);
	
	mk_sha2_detail_256_append(self->m_state, &self->m_len, self->m_block, msg, msg_len_bytes);
}

void mk_sha2_256_finish(struct mk_sha2_256_state_s* self, void* digest)
{
	mk_assert(self);
	mk_assert(digest);

	mk_sha2_detail_256_finish(self->m_state, &self->m_len, self->m_block, digest);
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
