#ifndef mk_include_guard_hash_base_xof_sha3_shake128
#define mk_include_guard_hash_base_xof_sha3_shake128


#include "../detail/mk_hash_base_detail_sha3.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_xof_sha3_shake128_s
{
	struct mk_hash_base_detail_sha3_s m_sha3;
};


enum mk_hash_base_xof_sha3_shake128_block_len_e{ mk_hash_base_xof_sha3_shake128_block_len = 168 };


mk_jumbo void mk_hash_base_xof_sha3_shake128_init(struct mk_hash_base_xof_sha3_shake128_s* self);
mk_jumbo void mk_hash_base_xof_sha3_shake128_append_blocks(struct mk_hash_base_xof_sha3_shake128_s* self, void const* pblocks, int nblocks);
mk_jumbo void mk_hash_base_xof_sha3_shake128_finish(struct mk_hash_base_xof_sha3_shake128_s* self, void* block, int idx, int digest_len, void* digest);


#endif
