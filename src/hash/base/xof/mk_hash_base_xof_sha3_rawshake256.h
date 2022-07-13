#ifndef mk_include_guard_hash_base_xof_sha3_rawshake256
#define mk_include_guard_hash_base_xof_sha3_rawshake256


#include "../detail/mk_hash_base_detail_sha3.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_xof_sha3_rawshake256_s
{
	struct mk_hash_base_detail_sha3_s m_sha3;
};


enum mk_hash_base_xof_sha3_rawshake256_block_len_e{ mk_hash_base_xof_sha3_rawshake256_block_len = 136 };


mk_jumbo void mk_hash_base_xof_sha3_rawshake256_init(struct mk_hash_base_xof_sha3_rawshake256_s* hash_base_xof_sha3_rawshake256);
mk_jumbo void mk_hash_base_xof_sha3_rawshake256_append_blocks(struct mk_hash_base_xof_sha3_rawshake256_s* hash_base_xof_sha3_rawshake256, void const* pblocks, int nblocks);
mk_jumbo void mk_hash_base_xof_sha3_rawshake256_finish(struct mk_hash_base_xof_sha3_rawshake256_s* hash_base_xof_sha3_rawshake256, void* block, int idx, int digest_len, void* digest);


#endif
