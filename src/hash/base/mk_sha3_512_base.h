#ifndef mk_include_guard_sha3_512_base
#define mk_include_guard_sha3_512_base


#include "mk_sha3_base_detail.h"

#include "../../utils/mk_jumbo.h"


struct mk_sha3_512_base_s
{
	struct mk_sha3_base_detail_s m_sha3;
};


mk_jumbo void mk_sha3_512_base_init(struct mk_sha3_512_base_s* sha3_512_base);
mk_jumbo void mk_sha3_512_base_append_blocks(struct mk_sha3_512_base_s* sha3_512_base, int nblocks, void const* pblocks);
mk_jumbo void mk_sha3_512_base_finish(struct mk_sha3_512_base_s* sha3_512_base, void* block, int idx, void* digest);


#endif
