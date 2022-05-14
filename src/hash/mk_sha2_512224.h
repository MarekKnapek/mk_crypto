#ifndef mk_include_guard_sha2_512224
#define mk_include_guard_sha2_512224


#include "base/mk_sha2_512224_base.h"


struct mk_sha2_512224_s
{
	struct mk_sha2_512224_base_s m_state;
	int m_idx;
	unsigned char m_block[128];
};


void mk_sha2_512224_init(struct mk_sha2_512224_s* sha2_512224);
void mk_sha2_512224_append(struct mk_sha2_512224_s* sha2_512224, void const* msg, int msg_len);
void mk_sha2_512224_finish(struct mk_sha2_512224_s* sha2_512224, void* digest);


#endif
