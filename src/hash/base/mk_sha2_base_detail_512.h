#ifndef mk_include_guard_sha2_base_detail_512
#define mk_include_guard_sha2_base_detail_512


#include "../../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../../mk_int/src/exact/mk_uint_128.h"


struct mk_sha2_base_detail_512_s
{
	struct mk_uint64_s m_state[8];
	struct mk_uint128_s m_len;
};


void mk_sha2_base_detail_512_append_blocks(struct mk_sha2_base_detail_512_s* sha2_base_detail_512, int nblocks, void const* pblocks);
void mk_sha2_base_detail_512_finish(struct mk_sha2_base_detail_512_s* sha2_base_detail_512, void* block, int idx, void* digest);


#endif
