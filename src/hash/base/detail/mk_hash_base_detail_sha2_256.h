#ifndef mk_include_guard_hash_base_detail_sha2_256
#define mk_include_guard_hash_base_detail_sha2_256


#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_hash_base_detail_sha2_256_s
{
	struct mk_uint32_s m_state[8];
	struct mk_uint64_s m_len;
};


mk_jumbo void mk_hash_base_detail_sha2_256_init(struct mk_hash_base_detail_sha2_256_s* hash_base_detail_sha2_256, struct mk_uint32_s const* iv);
mk_jumbo void mk_hash_base_detail_sha2_256_append_blocks(struct mk_hash_base_detail_sha2_256_s* hash_base_detail_sha2_256, void const* pblocks, int nblocks);
mk_jumbo void mk_hash_base_detail_sha2_256_finish(struct mk_hash_base_detail_sha2_256_s* hash_base_detail_sha2_256, void* block, int idx, void* digest);


#endif
