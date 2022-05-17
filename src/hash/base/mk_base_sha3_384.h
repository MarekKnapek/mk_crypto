#ifndef mk_include_guard_base_sha3_384
#define mk_include_guard_base_sha3_384


#include "mk_sha3_base_detail.h"

#include "../../utils/mk_jumbo.h"


struct mk_sha3_384_base_s
{
	struct mk_sha3_base_detail_s m_sha3;
};


enum mk_sha3_384_base_block_len_e{ mk_sha3_384_base_block_len = 104 };
enum mk_sha3_384_base_digest_len_e{ mk_sha3_384_base_digest_len = 48 };


mk_jumbo void mk_sha3_384_base_init(struct mk_sha3_384_base_s* sha3_384_base);
mk_jumbo void mk_sha3_384_base_append_blocks(struct mk_sha3_384_base_s* sha3_384_base, int nblocks, void const* pblocks);
mk_jumbo void mk_sha3_384_base_finish(struct mk_sha3_384_base_s* sha3_384_base, void* block, int idx, void* digest);


#endif
