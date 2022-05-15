#ifndef mk_include_guard_sha3_256
#define mk_include_guard_sha3_256


#include "base/mk_sha3_256_base.h"


struct mk_sha3_256_s
{
	struct mk_sha3_256_base_s m_state;
	int m_idx;
	unsigned char m_block[136];
};


void mk_sha3_256_init(struct mk_sha3_256_s* sha3_256);
void mk_sha3_256_append(struct mk_sha3_256_s* sha3_256, void const* msg, int msg_len);
void mk_sha3_256_finish(struct mk_sha3_256_s* sha3_256, void* digest);


#endif
