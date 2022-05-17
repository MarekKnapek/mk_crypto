#ifndef mk_include_guard_base_sha3_256
#define mk_include_guard_base_sha3_256


#include "mk_sha3_base_detail.h"

#include "../../utils/mk_jumbo.h"


struct mk_sha3_256_base_s
{
	struct mk_sha3_base_detail_s m_sha3;
};


enum mk_sha3_256_base_block_len_e{ mk_sha3_256_base_block_len = 136 };
enum mk_sha3_256_base_digest_len_e{ mk_sha3_256_base_digest_len = 32 };


mk_jumbo void mk_sha3_256_base_init(struct mk_sha3_256_base_s* sha3_256_base);
mk_jumbo void mk_sha3_256_base_append_blocks(struct mk_sha3_256_base_s* sha3_256_base, int nblocks, void const* pblocks);
mk_jumbo void mk_sha3_256_base_finish(struct mk_sha3_256_base_s* sha3_256_base, void* block, int idx, void* digest);


#endif
