#ifndef mk_include_guard_sha3_224
#define mk_include_guard_sha3_224


#include "base/mk_sha3_224_base.h"

#include "../utils/mk_jumbo.h"


struct mk_sha3_224_s
{
	struct mk_sha3_224_base_s m_state;
	int m_idx;
	unsigned char m_block[144];
};


mk_jumbo void mk_sha3_224_init(struct mk_sha3_224_s* sha3_224);
mk_jumbo void mk_sha3_224_append(struct mk_sha3_224_s* sha3_224, void const* msg, int msg_len);
mk_jumbo void mk_sha3_224_finish(struct mk_sha3_224_s* sha3_224, void* digest);


#endif
