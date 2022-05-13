#ifndef mk_include_guard_md5_base
#define mk_include_guard_md5_base


#include "../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_md5_base_s
{
	struct mk_uint32_s m_state[4];
	struct mk_uint64_s m_len;
};


void mk_md5_base_init(struct mk_md5_base_s* md5_base);
void mk_md5_base_append_blocks(struct mk_md5_base_s* md5_base, int nblocks, void const* pblocks);
void mk_md5_base_finish(struct mk_md5_base_s* md5_base, void const* msg, int msg_len, void* digest);


#endif
