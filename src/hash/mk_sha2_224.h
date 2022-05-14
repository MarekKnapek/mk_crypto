#ifndef mk_include_guard_sha2_224
#define mk_include_guard_sha2_224


#include "base/mk_sha2_224_base.h"


struct mk_sha2_224_s
{
	struct mk_sha2_224_base_s m_state;
	int m_idx;
	unsigned char m_block[64];
};


void mk_sha2_224_init(struct mk_sha2_224_s* sha2_224);
void mk_sha2_224_append(struct mk_sha2_224_s* sha2_224, void const* msg, int msg_len);
void mk_sha2_224_finish(struct mk_sha2_224_s* sha2_224, void* digest);


#endif
