#ifndef mk_include_guard_sha2_384_base
#define mk_include_guard_sha2_384_base


#include "mk_sha2_base_detail_512.h"

#include "../../utils/mk_jumbo.h"


struct mk_sha2_384_base_s
{
	struct mk_sha2_base_detail_512_s m_512;
};


mk_jumbo void mk_sha2_384_base_init(struct mk_sha2_384_base_s* sha2_384_base);
mk_jumbo void mk_sha2_384_base_append_blocks(struct mk_sha2_384_base_s* sha2_384_base, int nblocks, void const* pblocks);
mk_jumbo void mk_sha2_384_base_finish(struct mk_sha2_384_base_s* sha2_384_base, void* block, int idx, void* digest);


#endif
