#ifndef mk_include_guard_hash_base_detail_sha2_512
#define mk_include_guard_hash_base_detail_sha2_512


#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"
#include "../../../../../mk_int/src/exact/mk_uint_128.h"


struct mk_hash_base_detail_sha2_512_s
{
	struct mk_uint64_s m_state[8];
	struct mk_uint128_s m_len;
};


mk_jumbo void mk_hash_base_detail_sha2_512_init(struct mk_hash_base_detail_sha2_512_s* hash_base_detail_sha2_512, struct mk_uint64_s const* iv);
mk_jumbo void mk_hash_base_detail_sha2_512_append_blocks(struct mk_hash_base_detail_sha2_512_s* hash_base_detail_sha2_512, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_detail_sha2_512_finish(struct mk_hash_base_detail_sha2_512_s* hash_base_detail_sha2_512, void* block, int idx, void* digest);


#endif