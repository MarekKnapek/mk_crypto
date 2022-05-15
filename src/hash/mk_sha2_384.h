#ifndef mk_include_guard_sha2_384
#define mk_include_guard_sha2_384


#include "base/mk_sha2_384_base.h"

#include "../utils/mk_jumbo.h"


struct mk_sha2_384_s
{
	struct mk_sha2_384_base_s m_state;
	int m_idx;
	unsigned char m_block[128];
};


mk_jumbo void mk_sha2_384_init(struct mk_sha2_384_s* sha2_384);
mk_jumbo void mk_sha2_384_append(struct mk_sha2_384_s* sha2_384, void const* msg, int msg_len);
mk_jumbo void mk_sha2_384_finish(struct mk_sha2_384_s* sha2_384, void* digest);


#endif
