#ifndef mk_include_guard_base_sha2_512224
#define mk_include_guard_base_sha2_512224


#include "mk_sha2_base_detail_512.h"

#include "../../utils/mk_jumbo.h"


struct mk_sha2_512224_base_s
{
	struct mk_sha2_base_detail_512_s m_512;
};


enum mk_sha2_512224_base_block_len_e{ mk_sha2_512224_base_block_len = 128 };
enum mk_sha2_512224_base_digest_len_e{ mk_sha2_512224_base_digest_len = 28 };


mk_jumbo void mk_sha2_512224_base_init(struct mk_sha2_512224_base_s* sha2_512224_base);
mk_jumbo void mk_sha2_512224_base_append_blocks(struct mk_sha2_512224_base_s* sha2_512224_base, int nblocks, void const* pblocks);
mk_jumbo void mk_sha2_512224_base_finish(struct mk_sha2_512224_base_s* sha2_512224_base, void* block, int idx, void* digest);


#endif
