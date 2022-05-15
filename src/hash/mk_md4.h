#ifndef mk_include_guard_md4
#define mk_include_guard_md4


#include "../utils/mk_jumbo.h"
#include "base/mk_md4_base.h"


struct mk_md4_s
{
	struct mk_md4_base_s m_state;
	int m_idx;
	unsigned char m_block[64];
};


mk_jumbo void mk_md4_init(struct mk_md4_s* md4);
mk_jumbo void mk_md4_append(struct mk_md4_s* md4, void const* msg, int msg_len);
mk_jumbo void mk_md4_finish(struct mk_md4_s* md4, void* digest);


#endif
