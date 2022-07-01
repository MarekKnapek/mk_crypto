#ifndef mk_include_guard_hash_base_hash_sha3_384
#define mk_include_guard_hash_base_hash_sha3_384


#include "../detail/mk_hash_base_detail_sha3.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_sha3_384_s
{
	struct mk_hash_base_detail_sha3_s m_sha3;
};


enum mk_hash_base_hash_sha3_384_block_len_e { mk_hash_base_hash_sha3_384_block_len = 104 };
enum mk_hash_base_hash_sha3_384_digest_len_e { mk_hash_base_hash_sha3_384_digest_len = 48 };
static char const mk_hash_base_hash_sha3_384_name[] = "SHA3-384";
static int const mk_hash_base_hash_sha3_384_name_len = (int)sizeof(mk_hash_base_hash_sha3_384_name) - 1;


mk_jumbo void mk_hash_base_hash_sha3_384_init(struct mk_hash_base_hash_sha3_384_s* self);
mk_jumbo void mk_hash_base_hash_sha3_384_append_blocks(struct mk_hash_base_hash_sha3_384_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_sha3_384_finish(struct mk_hash_base_hash_sha3_384_s* self, void* block, int idx, void* digest);


#endif
