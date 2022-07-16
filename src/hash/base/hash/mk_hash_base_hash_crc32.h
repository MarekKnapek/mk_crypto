#ifndef mk_include_guard_hash_base_hash_crc32
#define mk_include_guard_hash_base_hash_crc32


#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_32.h"


struct mk_hash_base_hash_crc32_s
{
	struct mk_uint32_s m_state;
};


#define mk_hash_base_hash_crc32_block_len 1
#define mk_hash_base_hash_crc32_digest_len 4
static char const mk_hash_base_hash_crc32_name[] = "CRC-32";
static int const mk_hash_base_hash_crc32_name_len = (int)sizeof(mk_hash_base_hash_crc32_name) - 1;


mk_jumbo void mk_hash_base_hash_crc32_init(struct mk_hash_base_hash_crc32_s* self);
mk_jumbo void mk_hash_base_hash_crc32_append_blocks(struct mk_hash_base_hash_crc32_s* self, void const* pblocks, int nblocks);
mk_jumbo void mk_hash_base_hash_crc32_finish(struct mk_hash_base_hash_crc32_s* self, void* block, int idx, void* digest);


#endif
