#ifndef mk_include_guard_sha3_base_detail
#define mk_include_guard_sha3_base_detail


#include "../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_sha3_base_detail_s
{
	struct mk_uint64_s m_state[25];
};


enum mk_sha3_base_detail_domain_e
{
	mk_sha3_base_detail_domain_none,
	mk_sha3_base_detail_domain_sha3,
	mk_sha3_base_detail_domain_shake,
	mk_sha3_base_detail_domain_rawshake,
};


void mk_sha3_base_detail_init(struct mk_sha3_base_detail_s* sha3_base_detail);
void mk_sha3_base_detail_append_blocks(struct mk_sha3_base_detail_s* sha3_base_detail, int block_len, int nblocks, void const* pblocks);
void mk_sha3_base_detail_finish(struct mk_sha3_base_detail_s* sha3_base_detail, int block_len, void* block, int idx, enum mk_sha3_base_detail_domain_e domain, int digest_len, void* digest);


#endif
