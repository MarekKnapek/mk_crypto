#ifndef mk_include_guard_hash_base_hash_md4
#define mk_include_guard_hash_base_hash_md4


#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_hash_base_hash_md4_s
{
	struct mk_uint32_s m_state[4];
	struct mk_uint64_s m_len;
};


enum mk_hash_base_hash_md4_block_len_e { mk_hash_base_hash_md4_block_len = 64 };
enum mk_hash_base_hash_md4_digest_len_e { mk_hash_base_hash_md4_digest_len = 16 };


mk_jumbo void mk_hash_base_hash_md4_init(struct mk_hash_base_hash_md4_s* self);
mk_jumbo void mk_hash_base_hash_md4_append_blocks(struct mk_hash_base_hash_md4_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_md4_finish(struct mk_hash_base_hash_md4_s* self, void* block, int idx, void* digest);


#endif
