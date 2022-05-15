#ifndef mk_include_guard_sha3_224
#define mk_include_guard_sha3_224


#include "base/mk_sha3_224_base.h"


struct mk_sha3_224_s
{
	struct mk_sha3_224_base_s m_state;
	int m_idx;
	unsigned char m_block[144];
};


void mk_sha3_224_init(struct mk_sha3_224_s* sha3_224);
void mk_sha3_224_append(struct mk_sha3_224_s* sha3_224, void const* msg, int msg_len);
void mk_sha3_224_finish(struct mk_sha3_224_s* sha3_224, void* digest);


#endif
