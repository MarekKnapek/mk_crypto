#ifndef mk_include_guard_md4_base
#define mk_include_guard_md4_base


#include "../../utils/mk_jumbo.h"

#include "../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_md4_base_s
{
	struct mk_uint32_s m_state[4];
	struct mk_uint64_s m_len;
};


mk_jumbo void mk_md4_base_init(struct mk_md4_base_s* md4_base);
mk_jumbo void mk_md4_base_append_blocks(struct mk_md4_base_s* md4_base, int nblocks, void const* pblocks);
mk_jumbo void mk_md4_base_finish(struct mk_md4_base_s* md4_base, void* block, int idx, void* digest);


#endif
