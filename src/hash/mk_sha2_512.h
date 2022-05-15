#ifndef mk_include_guard_sha2_512
#define mk_include_guard_sha2_512


#include "base/mk_sha2_512_base.h"

#include "../utils/mk_jumbo.h"


struct mk_sha2_512_s
{
	struct mk_sha2_512_base_s m_state;
	int m_idx;
	unsigned char m_block[128];
};


mk_jumbo void mk_sha2_512_init(struct mk_sha2_512_s* sha2_512);
mk_jumbo void mk_sha2_512_append(struct mk_sha2_512_s* sha2_512, void const* msg, int msg_len);
mk_jumbo void mk_sha2_512_finish(struct mk_sha2_512_s* sha2_512, void* digest);


#endif
