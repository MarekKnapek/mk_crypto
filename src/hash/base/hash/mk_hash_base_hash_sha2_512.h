#ifndef mk_include_guard_hash_base_hash_sha2_512
#define mk_include_guard_hash_base_hash_sha2_512


#include "../detail/mk_hash_base_detail_sha2_512.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_sha2_512_s
{
	struct mk_hash_base_detail_sha2_512_s m_512;
};


enum mk_hash_base_hash_sha2_512_block_len_e { mk_hash_base_hash_sha2_512_block_len = 128 };
enum mk_hash_base_hash_sha2_512_digest_len_e { mk_hash_base_hash_sha2_512_digest_len = 64 };
static char const mk_hash_base_hash_sha2_512_name[] = "SHA-512";
static int const mk_hash_base_hash_sha2_512_name_len = (int)sizeof(mk_hash_base_hash_sha2_512_name) - 1;


mk_jumbo void mk_hash_base_hash_sha2_512_init(struct mk_hash_base_hash_sha2_512_s* self);
mk_jumbo void mk_hash_base_hash_sha2_512_append_blocks(struct mk_hash_base_hash_sha2_512_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_sha2_512_finish(struct mk_hash_base_hash_sha2_512_s* self, void* block, int idx, void* digest);


#endif
