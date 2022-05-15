#ifndef mk_include_guard_sha1_base
#define mk_include_guard_sha1_base


#include "../../utils/mk_jumbo.h"

#include "../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_sha1_base_s
{
	struct mk_uint32_s m_state[5];
	struct mk_uint64_s m_len;
};


mk_jumbo void mk_sha1_base_init(struct mk_sha1_base_s* sha1_base);
mk_jumbo void mk_sha1_base_append_blocks(struct mk_sha1_base_s* sha1_base, int nblocks, void const* pblocks);
mk_jumbo void mk_sha1_base_finish(struct mk_sha1_base_s* sha1_base, void* block, int idx, void* digest);


#endif
