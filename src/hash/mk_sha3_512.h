#ifndef mk_include_guard_sha3_512
#define mk_include_guard_sha3_512


#include "base/mk_sha3_512_base.h"

#include "../utils/mk_jumbo.h"


struct mk_sha3_512_s
{
	struct mk_sha3_512_base_s m_state;
	int m_idx;
	unsigned char m_block[72];
};


mk_jumbo void mk_sha3_512_init(struct mk_sha3_512_s* sha3_512);
mk_jumbo void mk_sha3_512_append(struct mk_sha3_512_s* sha3_512, void const* msg, int msg_len);
mk_jumbo void mk_sha3_512_finish(struct mk_sha3_512_s* sha3_512, void* digest);


#endif
