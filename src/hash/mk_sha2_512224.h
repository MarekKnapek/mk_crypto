#ifndef mk_include_guard_sha2_512224
#define mk_include_guard_sha2_512224


#include "base/mk_sha2_512224_base.h"

#include "../utils/mk_jumbo.h"


struct mk_sha2_512224_s
{
	struct mk_sha2_512224_base_s m_state;
	int m_idx;
	unsigned char m_block[128];
};


mk_jumbo void mk_sha2_512224_init(struct mk_sha2_512224_s* sha2_512224);
mk_jumbo void mk_sha2_512224_append(struct mk_sha2_512224_s* sha2_512224, void const* msg, int msg_len);
mk_jumbo void mk_sha2_512224_finish(struct mk_sha2_512224_s* sha2_512224, void* digest);


#endif
