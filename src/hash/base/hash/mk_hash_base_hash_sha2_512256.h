#ifndef mk_include_guard_hash_base_hash_sha2_512256
#define mk_include_guard_hash_base_hash_sha2_512256


#include "../detail/mk_hash_base_detail_sha2_512.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_sha2_512256_s
{
	struct mk_hash_base_detail_sha2_512_s m_512;
};


enum mk_hash_base_hash_sha2_512256_block_len_e { mk_hash_base_hash_sha2_512256_block_len = 128 };
enum mk_hash_base_hash_sha2_512256_digest_len_e { mk_hash_base_hash_sha2_512256_digest_len = 32 };


mk_jumbo void mk_hash_base_hash_sha2_512256_init(struct mk_hash_base_hash_sha2_512256_s* self);
mk_jumbo void mk_hash_base_hash_sha2_512256_append_blocks(struct mk_hash_base_hash_sha2_512256_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_sha2_512256_finish(struct mk_hash_base_hash_sha2_512256_s* self, void* block, int idx, void* digest);


#endif
