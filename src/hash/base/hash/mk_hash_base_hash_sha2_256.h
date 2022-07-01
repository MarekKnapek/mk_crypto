#ifndef mk_include_guard_hash_base_hash_sha2_256
#define mk_include_guard_hash_base_hash_sha2_256


#include "../detail/mk_hash_base_detail_sha2_256.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_sha2_256_s
{
	struct mk_hash_base_detail_sha2_256_s m_256;
};


enum mk_hash_base_hash_sha2_256_block_len_e { mk_hash_base_hash_sha2_256_block_len = 64 };
enum mk_hash_base_hash_sha2_256_digest_len_e { mk_hash_base_hash_sha2_256_digest_len = 32 };
static char const mk_hash_base_hash_sha2_256_name[] = "SHA-256";
static int const mk_hash_base_hash_sha2_256_name_len = (int)sizeof(mk_hash_base_hash_sha2_256_name) - 1;


mk_jumbo void mk_hash_base_hash_sha2_256_init(struct mk_hash_base_hash_sha2_256_s* self);
mk_jumbo void mk_hash_base_hash_sha2_256_append_blocks(struct mk_hash_base_hash_sha2_256_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_sha2_256_finish(struct mk_hash_base_hash_sha2_256_s* self, void* block, int idx, void* digest);


#endif
