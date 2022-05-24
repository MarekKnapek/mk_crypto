#ifndef mk_include_guard_hash_base_hash_sha2_224
#define mk_include_guard_hash_base_hash_sha2_224


#include "../detail/mk_hash_base_detail_sha2_256.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_sha2_224_s
{
	struct mk_hash_base_detail_sha2_256_s m_256;
};


enum mk_hash_base_hash_sha2_224_block_len_e { mk_hash_base_hash_sha2_224_block_len = 64 };
enum mk_hash_base_hash_sha2_224_digest_len_e { mk_hash_base_hash_sha2_224_digest_len = 28 };


mk_jumbo void mk_hash_base_hash_sha2_224_init(struct mk_hash_base_hash_sha2_224_s* self);
mk_jumbo void mk_hash_base_hash_sha2_224_append_blocks(struct mk_hash_base_hash_sha2_224_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_sha2_224_finish(struct mk_hash_base_hash_sha2_224_s* self, void* block, int idx, void* digest);


#endif
