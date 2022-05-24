#ifndef mk_include_guard_hash_base_hash_sha3_224
#define mk_include_guard_hash_base_hash_sha3_224


#include "../detail/mk_hash_base_detail_sha3.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_sha3_224_s
{
	struct mk_hash_base_detail_sha3_s m_sha3;
};


enum mk_hash_base_hash_sha3_224_block_len_e { mk_hash_base_hash_sha3_224_block_len = 144 };
enum mk_hash_base_hash_sha3_224_digest_len_e { mk_hash_base_hash_sha3_224_digest_len = 28 };


mk_jumbo void mk_hash_base_hash_sha3_224_init(struct mk_hash_base_hash_sha3_224_s* self);
mk_jumbo void mk_hash_base_hash_sha3_224_append_blocks(struct mk_hash_base_hash_sha3_224_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_sha3_224_finish(struct mk_hash_base_hash_sha3_224_s* self, void* block, int idx, void* digest);


#endif
