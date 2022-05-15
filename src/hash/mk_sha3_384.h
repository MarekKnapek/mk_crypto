#ifndef mk_include_guard_sha3_384
#define mk_include_guard_sha3_384


#include "base/mk_sha3_384_base.h"


struct mk_sha3_384_s
{
	struct mk_sha3_384_base_s m_state;
	int m_idx;
	unsigned char m_block[104];
};


void mk_sha3_384_init(struct mk_sha3_384_s* sha3_384);
void mk_sha3_384_append(struct mk_sha3_384_s* sha3_384, void const* msg, int msg_len);
void mk_sha3_384_finish(struct mk_sha3_384_s* sha3_384, void* digest);


#endif
