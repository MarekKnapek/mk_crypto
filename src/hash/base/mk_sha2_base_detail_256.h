#ifndef mk_include_guard_sha2_base_detail_256
#define mk_include_guard_sha2_base_detail_256


#include "../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_sha2_base_detail_256_s
{
	struct mk_uint32_s m_state[8];
	struct mk_uint64_s m_len;
};


void mk_sha2_base_detail_256_append_blocks(struct mk_sha2_base_detail_256_s* sha2_base_detail_256, int nblocks, void const* pblocks);
void mk_sha2_base_detail_256_finish(struct mk_sha2_base_detail_256_s* sha2_base_detail_256, void* block, int idx, void* digest);


#endif
