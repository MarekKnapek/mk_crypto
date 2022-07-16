#ifndef mk_include_guard_hash_base_hash_sha2_512256
#define mk_include_guard_hash_base_hash_sha2_512256


#include "../detail/mk_hash_base_detail_sha2_512.h"

#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_sha2_512256_s
{
	struct mk_hash_base_detail_sha2_512_s m_512;
};


#define mk_hash_base_hash_sha2_512256_block_len 128
#define mk_hash_base_hash_sha2_512256_digest_len 32
static char const mk_hash_base_hash_sha2_512256_name[] = "SHA-512/256";
static int const mk_hash_base_hash_sha2_512256_name_len = (int)sizeof(mk_hash_base_hash_sha2_512256_name) - 1;


mk_jumbo void mk_hash_base_hash_sha2_512256_init(struct mk_hash_base_hash_sha2_512256_s* self);
mk_jumbo void mk_hash_base_hash_sha2_512256_append_blocks(struct mk_hash_base_hash_sha2_512256_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_sha2_512256_finish(struct mk_hash_base_hash_sha2_512256_s* self, void* block, int idx, void* digest);


#endif
