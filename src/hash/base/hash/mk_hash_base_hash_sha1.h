#ifndef mk_include_guard_hash_base_hash_sha1
#define mk_include_guard_hash_base_hash_sha1


#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_hash_base_hash_sha1_s
{
	struct mk_uint32_s m_state[5];
	struct mk_uint64_s m_len;
};


enum mk_hash_base_hash_sha1_block_len_e { mk_hash_base_hash_sha1_block_len = 64 };
enum mk_hash_base_hash_sha1_digest_len_e { mk_hash_base_hash_sha1_digest_len = 20 };
static char const mk_hash_base_hash_sha1_name[] = "SHA-1";
static int const mk_hash_base_hash_sha1_name_len = (int)sizeof(mk_hash_base_hash_sha1_name) - 1;


mk_jumbo void mk_hash_base_hash_sha1_init(struct mk_hash_base_hash_sha1_s* self);
mk_jumbo void mk_hash_base_hash_sha1_append_blocks(struct mk_hash_base_hash_sha1_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_sha1_finish(struct mk_hash_base_hash_sha1_s* self, void* block, int idx, void* digest);


#endif
