#ifndef mk_include_guard_hash_base_hash_sha3_256
#define mk_include_guard_hash_base_hash_sha3_256


#include "../detail/mk_hash_base_detail_sha3.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_sha3_256_s
{
	struct mk_hash_base_detail_sha3_s m_sha3;
};


#define mk_hash_base_hash_sha3_256_block_len 136
#define mk_hash_base_hash_sha3_256_digest_len 32
static char const mk_hash_base_hash_sha3_256_name[] = "SHA3-256";
static int const mk_hash_base_hash_sha3_256_name_len = (int)sizeof(mk_hash_base_hash_sha3_256_name) - 1;


mk_jumbo void mk_hash_base_hash_sha3_256_init(struct mk_hash_base_hash_sha3_256_s* self);
mk_jumbo void mk_hash_base_hash_sha3_256_append_blocks(struct mk_hash_base_hash_sha3_256_s* self, void const* pblocks, int nblocks);
mk_jumbo void mk_hash_base_hash_sha3_256_finish(struct mk_hash_base_hash_sha3_256_s* self, void* block, int idx, void* digest);


#endif
