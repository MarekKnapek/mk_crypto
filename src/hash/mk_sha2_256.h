#ifndef mk_include_guard_sha2_256
#define mk_include_guard_sha2_256


#include "base/mk_sha2_256_base.h"


struct mk_sha2_256_s
{
	struct mk_sha2_256_base_s m_state;
	int m_idx;
	unsigned char m_block[64];
};


void mk_sha2_256_init(struct mk_sha2_256_s* sha2_256);
void mk_sha2_256_append(struct mk_sha2_256_s* sha2_256, void const* msg, int msg_len);
void mk_sha2_256_finish(struct mk_sha2_256_s* sha2_256, void* digest);


#endif
