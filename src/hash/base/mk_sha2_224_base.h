#ifndef mk_include_guard_sha2_224_base
#define mk_include_guard_sha2_224_base


#include "mk_sha2_base_detail_256.h"

#include "../../utils/mk_jumbo.h"


struct mk_sha2_224_base_s
{
	struct mk_sha2_base_detail_256_s m_256;
};


mk_jumbo void mk_sha2_224_base_init(struct mk_sha2_224_base_s* sha2_224_base);
mk_jumbo void mk_sha2_224_base_append_blocks(struct mk_sha2_224_base_s* sha2_224_base, int nblocks, void const* pblocks);
mk_jumbo void mk_sha2_224_base_finish(struct mk_sha2_224_base_s* sha2_224_base, void* block, int idx, void* digest);


#endif
