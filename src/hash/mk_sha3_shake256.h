#ifndef mk_include_guard_sha3_shake256
#define mk_include_guard_sha3_shake256


#include "base/mk_sha3_shake256_base.h"


struct mk_sha3_shake256_s
{
	struct mk_sha3_shake256_base_s m_state;
	int m_idx;
	unsigned char m_block[136];
};


void mk_sha3_shake256_init(struct mk_sha3_shake256_s* sha3_shake256);
void mk_sha3_shake256_append(struct mk_sha3_shake256_s* sha3_shake256, void const* msg, int msg_len);
void mk_sha3_shake256_finish(struct mk_sha3_shake256_s* sha3_shake256, int digest_len, void* digest);


#endif
