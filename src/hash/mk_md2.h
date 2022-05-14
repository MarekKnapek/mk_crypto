#ifndef mk_include_guard_md2
#define mk_include_guard_md2


#include "base/mk_md2_base.h"


struct mk_md2_s
{
	struct mk_md2_base_s m_state;
	int m_idx;
	unsigned char m_block[16];
};


void mk_md2_init(struct mk_md2_s* md2);
void mk_md2_append(struct mk_md2_s* md2, void const* msg, int msg_len);
void mk_md2_finish(struct mk_md2_s* md2, void* digest);


#endif
