#ifndef mk_include_guard_base_sha3_224
#define mk_include_guard_base_sha3_224


#include "mk_sha3_base_detail.h"

#include "../../utils/mk_jumbo.h"


struct mk_sha3_224_base_s
{
	struct mk_sha3_base_detail_s m_sha3;
};


enum mk_sha3_224_base_block_len_e{ mk_sha3_224_base_block_len = 144 };
enum mk_sha3_224_base_digest_len_e{ mk_sha3_224_base_digest_len = 28 };


mk_jumbo void mk_sha3_224_base_init(struct mk_sha3_224_base_s* sha3_224_base);
mk_jumbo void mk_sha3_224_base_append_blocks(struct mk_sha3_224_base_s* sha3_224_base, int nblocks, void const* pblocks);
mk_jumbo void mk_sha3_224_base_finish(struct mk_sha3_224_base_s* sha3_224_base, void* block, int idx, void* digest);


#endif
