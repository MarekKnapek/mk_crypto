#include "mk_sha2_512224.h"

#include "mk_sha2_detail_512.h"

#include "../utils/mk_assert.h"

#include "../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../mk_int/src/exact/mk_uint_128.h"

#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */


void mk_sha2_512224_init(struct mk_sha2_512224_state_s* self)
{
	static struct mk_uint64_s const mk_sha2_512224_detail_init[] =
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

	mk_assert(self);

	self->m_state[0] = mk_sha2_512224_detail_init[0];
	self->m_state[1] = mk_sha2_512224_detail_init[1];
	self->m_state[2] = mk_sha2_512224_detail_init[2];
	self->m_state[3] = mk_sha2_512224_detail_init[3];
	self->m_state[4] = mk_sha2_512224_detail_init[4];
	self->m_state[5] = mk_sha2_512224_detail_init[5];
	self->m_state[6] = mk_sha2_512224_detail_init[6];
	self->m_state[7] = mk_sha2_512224_detail_init[7];
	mk_uint128_zero(&self->m_len);
}

void mk_sha2_512224_append(struct mk_sha2_512224_state_s* self, void const* msg, size_t msg_len_bytes)
{
	mk_assert(self);
	
	mk_sha2_detail_512_append(self->m_state, &self->m_len, self->m_block, msg, msg_len_bytes);
}

void mk_sha2_512224_finish(struct mk_sha2_512224_state_s* self, void* digest)
{
	unsigned char buff[64];

	mk_assert(self);
	mk_assert(digest);

	mk_sha2_detail_512_finish(self->m_state, &self->m_len, self->m_block, buff);
	memcpy(digest, buff, 28);
}
