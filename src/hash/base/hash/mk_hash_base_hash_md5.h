#ifndef mk_include_guard_hash_base_hash_md5
#define mk_include_guard_hash_base_hash_md5


#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_hash_base_hash_md5_s
{
	struct mk_uint32_s m_state[4];
	struct mk_uint64_s m_len;
};


enum mk_hash_base_hash_md5_block_len_e { mk_hash_base_hash_md5_block_len = 64 };
enum mk_hash_base_hash_md5_digest_len_e { mk_hash_base_hash_md5_digest_len = 16 };


mk_jumbo void mk_hash_base_hash_md5_init(struct mk_hash_base_hash_md5_s* self);
mk_jumbo void mk_hash_base_hash_md5_append_blocks(struct mk_hash_base_hash_md5_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_md5_finish(struct mk_hash_base_hash_md5_s* self, void* block, int idx, void* digest);


#endif
