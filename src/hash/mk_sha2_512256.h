#ifndef mk_include_guard_sha2_512256
#define mk_include_guard_sha2_512256


#include "base/mk_sha2_512256_base.h"


struct mk_sha2_512256_s
{
	struct mk_sha2_512256_base_s m_state;
	int m_idx;
	unsigned char m_block[128];
};


void mk_sha2_512256_init(struct mk_sha2_512256_s* sha2_512256);
void mk_sha2_512256_append(struct mk_sha2_512256_s* sha2_512256, void const* msg, int msg_len);
void mk_sha2_512256_finish(struct mk_sha2_512256_s* sha2_512256, void* digest);


#endif
