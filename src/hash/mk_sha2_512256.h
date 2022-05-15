#ifndef mk_include_guard_sha2_512256
#define mk_include_guard_sha2_512256


#include "base/mk_sha2_512256_base.h"

#include "../utils/mk_jumbo.h"


struct mk_sha2_512256_s
{
	struct mk_sha2_512256_base_s m_state;
	int m_idx;
	unsigned char m_block[128];
};


mk_jumbo void mk_sha2_512256_init(struct mk_sha2_512256_s* sha2_512256);
mk_jumbo void mk_sha2_512256_append(struct mk_sha2_512256_s* sha2_512256, void const* msg, int msg_len);
mk_jumbo void mk_sha2_512256_finish(struct mk_sha2_512256_s* sha2_512256, void* digest);


#endif
