#ifndef mk_include_guard_sha3_shake128
#define mk_include_guard_sha3_shake128


#include "base/mk_sha3_shake128_base.h"

#include "../utils/mk_jumbo.h"


struct mk_sha3_shake128_s
{
	struct mk_sha3_shake128_base_s m_state;
	int m_idx;
	unsigned char m_block[168];
};


mk_jumbo void mk_sha3_shake128_init(struct mk_sha3_shake128_s* sha3_shake128);
mk_jumbo void mk_sha3_shake128_append(struct mk_sha3_shake128_s* sha3_shake128, void const* msg, int msg_len);
mk_jumbo void mk_sha3_shake128_finish(struct mk_sha3_shake128_s* sha3_shake128, int digest_len, void* digest);


#endif
