#ifndef mk_include_guard_hash_base_hash_md2
#define mk_include_guard_hash_base_hash_md2


#include "../../../utils/mk_jumbo.h"


struct mk_hash_base_hash_md2_s
{
	unsigned char m_state[16];
	unsigned char m_checksum[16];
};


enum mk_hash_base_hash_md2_block_len_e { mk_hash_base_hash_md2_block_len = 16 };
enum mk_hash_base_hash_md2_digest_len_e { mk_hash_base_hash_md2_digest_len = 16 };
static char const mk_hash_base_hash_md2_name[] = "MD2";
static int const mk_hash_base_hash_md2_name_len = (int)sizeof(mk_hash_base_hash_md2_name) - 1;


mk_jumbo void mk_hash_base_hash_md2_init(struct mk_hash_base_hash_md2_s* self);
mk_jumbo void mk_hash_base_hash_md2_append_blocks(struct mk_hash_base_hash_md2_s* self, int nblocks, void const* pblocks);
mk_jumbo void mk_hash_base_hash_md2_finish(struct mk_hash_base_hash_md2_s* self, void* block, int idx, void* digest);


#endif
