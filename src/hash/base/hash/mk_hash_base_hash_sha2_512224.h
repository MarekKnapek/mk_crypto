#ifndef mk_include_guard_hash_base_hash_sha2_512224
#define mk_include_guard_hash_base_hash_sha2_512224


#include "../detail/mk_hash_base_detail_sha2_512.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_sha2_512224_s
{
	struct mk_hash_base_detail_sha2_512_s m_512;
};


enum mk_hash_base_hash_sha2_512224_block_len_e { mk_hash_base_hash_sha2_512224_block_len = 128 };
enum mk_hash_base_hash_sha2_512224_digest_len_e { mk_hash_base_hash_sha2_512224_digest_len = 28 };
static char const mk_hash_base_hash_sha2_512224_name[] = "SHA-512/224";
static int const mk_hash_base_hash_sha2_512224_name_len = (int)sizeof(mk_hash_base_hash_sha2_512224_name) - 1;


mk_jumbo void mk_hash_base_hash_sha2_512224_init(struct mk_hash_base_hash_sha2_512224_s* self);
mk_jumbo void mk_hash_base_hash_sha2_512224_append_blocks(struct mk_hash_base_hash_sha2_512224_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_sha2_512224_finish(struct mk_hash_base_hash_sha2_512224_s* self, void* block, int idx, void* digest);


#endif
