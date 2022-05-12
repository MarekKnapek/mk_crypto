#include "mk_sha2_512256.h"

#include "mk_sha2_detail_512.h"

#include "../utils/mk_assert.h"

#include "../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../mk_int/src/exact/mk_uint_128.h"

#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */


void mk_sha2_512256_init(struct mk_sha2_512256_state_s* self)
{
	static struct mk_uint64_s const mk_sha2_512256_detail_init[] =
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

	mk_assert(self);

	self->m_state[0] = mk_sha2_512256_detail_init[0];
	self->m_state[1] = mk_sha2_512256_detail_init[1];
	self->m_state[2] = mk_sha2_512256_detail_init[2];
	self->m_state[3] = mk_sha2_512256_detail_init[3];
	self->m_state[4] = mk_sha2_512256_detail_init[4];
	self->m_state[5] = mk_sha2_512256_detail_init[5];
	self->m_state[6] = mk_sha2_512256_detail_init[6];
	self->m_state[7] = mk_sha2_512256_detail_init[7];
	mk_uint128_zero(&self->m_len);
}

void mk_sha2_512256_append(struct mk_sha2_512256_state_s* self, void const* msg, size_t msg_len_bytes)
{
	mk_assert(self);
	
	mk_sha2_detail_512_append(self->m_state, &self->m_len, self->m_block, msg, msg_len_bytes);
}

void mk_sha2_512256_finish(struct mk_sha2_512256_state_s* self, void* digest)
{
	unsigned char buff[64];

	mk_assert(self);
	mk_assert(digest);

	mk_sha2_detail_512_finish(self->m_state, &self->m_len, self->m_block, buff);
	memcpy(digest, buff, 32);
}
