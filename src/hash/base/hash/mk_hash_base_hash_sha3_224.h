#ifndef mk_include_guard_hash_base_hash_sha3_224
#define mk_include_guard_hash_base_hash_sha3_224


#include "../detail/mk_hash_base_detail_sha3.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_sha3_224_s
{
	struct mk_hash_base_detail_sha3_s m_sha3;
};


#define mk_hash_base_hash_sha3_224_block_len 144
#define mk_hash_base_hash_sha3_224_digest_len 28
static char const mk_hash_base_hash_sha3_224_name[] = "SHA3-224";
static int const mk_hash_base_hash_sha3_224_name_len = (int)sizeof(mk_hash_base_hash_sha3_224_name) - 1;


mk_jumbo void mk_hash_base_hash_sha3_224_init(struct mk_hash_base_hash_sha3_224_s* self);
mk_jumbo void mk_hash_base_hash_sha3_224_append_blocks(struct mk_hash_base_hash_sha3_224_s* self, void const* pblocks, int nblocks);
mk_jumbo void mk_hash_base_hash_sha3_224_finish(struct mk_hash_base_hash_sha3_224_s* self, void* block, int idx, void* digest);


#endif
