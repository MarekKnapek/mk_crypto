#include "mk_sha2_384.h"

#include "mk_sha2_detail_512.h"

#include "../utils/mk_assert.h"

#include "../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../mk_int/src/exact/mk_uint_128.h"

#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */


void mk_sha2_384_init(struct mk_sha2_384_state_s* self)
{
	static struct mk_uint64_s const mk_sha2_384_detail_init[] =
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

	mk_assert(self);

	self->m_state[0] = mk_sha2_384_detail_init[0];
	self->m_state[1] = mk_sha2_384_detail_init[1];
	self->m_state[2] = mk_sha2_384_detail_init[2];
	self->m_state[3] = mk_sha2_384_detail_init[3];
	self->m_state[4] = mk_sha2_384_detail_init[4];
	self->m_state[5] = mk_sha2_384_detail_init[5];
	self->m_state[6] = mk_sha2_384_detail_init[6];
	self->m_state[7] = mk_sha2_384_detail_init[7];
	mk_uint128_zero(&self->m_len);
}

void mk_sha2_384_append(struct mk_sha2_384_state_s* self, void const* msg, size_t msg_len_bytes)
{
	mk_assert(self);
	
	mk_sha2_detail_512_append(self->m_state, &self->m_len, self->m_block, msg, msg_len_bytes);
}

void mk_sha2_384_finish(struct mk_sha2_384_state_s* self, void* digest)
{
	unsigned char buff[64];

	mk_assert(self);
	mk_assert(digest);

	mk_sha2_detail_512_finish(self->m_state, &self->m_len, self->m_block, buff);
	memcpy(digest, buff, 48);
}
