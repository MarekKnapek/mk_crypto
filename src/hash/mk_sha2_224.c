#include "mk_sha2_224.h"

#include "mk_sha2_detail_256.h"

#include "../utils/mk_assert.h"

#include "../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../mk_int/src/exact/mk_uint_64.h"

#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4711) /* warning C4711: function 'xxx' selected for automatic inline expansion */
#endif


void mk_sha2_224_init(struct mk_sha2_224_state_s* self)
{
	static struct mk_uint32_s const mk_sha2_224_detail_init[] =
	{
		mk_uint32_c(0xc1059ed8),
		mk_uint32_c(0x367cd507),
		mk_uint32_c(0x3070dd17),
		mk_uint32_c(0xf70e5939),
		mk_uint32_c(0xffc00b31),
		mk_uint32_c(0x68581511),
		mk_uint32_c(0x64f98fa7),
		mk_uint32_c(0xbefa4fa4),
	};

	mk_assert(self);

	self->m_state[0] = mk_sha2_224_detail_init[0];
	self->m_state[1] = mk_sha2_224_detail_init[1];
	self->m_state[2] = mk_sha2_224_detail_init[2];
	self->m_state[3] = mk_sha2_224_detail_init[3];
	self->m_state[4] = mk_sha2_224_detail_init[4];
	self->m_state[5] = mk_sha2_224_detail_init[5];
	self->m_state[6] = mk_sha2_224_detail_init[6];
	self->m_state[7] = mk_sha2_224_detail_init[7];
	mk_uint64_zero(&self->m_len);
}

void mk_sha2_224_append(struct mk_sha2_224_state_s* self, void const* msg, size_t msg_len_bytes)
{
	mk_assert(self);
	
	mk_sha2_detail_256_append(self->m_state, &self->m_len, self->m_block, msg, msg_len_bytes);
}

void mk_sha2_224_finish(struct mk_sha2_224_state_s* self, void* digest)
{
	unsigned char buff[32];

	mk_assert(self);
	mk_assert(digest);

	mk_sha2_detail_256_finish(self->m_state, &self->m_len, self->m_block, buff);
	memcpy(digest, buff, 28);
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
