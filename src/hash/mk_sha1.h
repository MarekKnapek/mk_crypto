#ifndef mk_include_guard_sha1
#define mk_include_guard_sha1


#include "base/mk_sha1_base.h"


struct mk_sha1_s
{
	struct mk_sha1_base_s m_state;
	int m_idx;
	unsigned char m_block[64];
};


void mk_sha1_init(struct mk_sha1_s* sha1);
void mk_sha1_append(struct mk_sha1_s* sha1, void const* msg, int msg_len);
void mk_sha1_finish(struct mk_sha1_s* sha1, void* digest);


#endif
