#ifndef mk_include_guard_md5
#define mk_include_guard_md5


#include "base/mk_md5_base.h"

#include "../utils/mk_jumbo.h"


struct mk_md5_s
{
	struct mk_md5_base_s m_state;
	int m_idx;
	unsigned char m_block[64];
};


mk_jumbo void mk_md5_init(struct mk_md5_s* md5);
mk_jumbo void mk_md5_append(struct mk_md5_s* md5, void const* msg, int msg_len);
mk_jumbo void mk_md5_finish(struct mk_md5_s* md5, void* digest);


#endif
