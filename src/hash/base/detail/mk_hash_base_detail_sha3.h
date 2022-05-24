#ifndef mk_include_guard_hash_base_detail_sha3
#define mk_include_guard_hash_base_detail_sha3


#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_hash_base_detail_sha3_s
{
	struct mk_uint64_s m_state[25];
};


enum mk_hash_base_detail_sha3_domain_e
{
	mk_hash_base_detail_sha3_domain_sha3,
	mk_hash_base_detail_sha3_domain_shake,
	mk_hash_base_detail_sha3_domain_rawshake,
};


mk_jumbo void mk_hash_base_detail_sha3_init(struct mk_hash_base_detail_sha3_s* hash_base_detail_sha3);
mk_jumbo void mk_hash_base_detail_sha3_append_blocks(struct mk_hash_base_detail_sha3_s* hash_base_detail_sha3, int block_len, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_detail_sha3_finish(struct mk_hash_base_detail_sha3_s* hash_base_detail_sha3, int block_len, void* block, int idx, enum mk_hash_base_detail_sha3_domain_e domain, int digest_len, void* digest);


#endif
