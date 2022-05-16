#ifndef mk_include_guard_md2_base
#define mk_include_guard_md2_base


#include "../../utils/mk_jumbo.h"


struct mk_md2_base_s
{
	unsigned char m_state[16];
	unsigned char m_checksum[16];
};


enum mk_md2_base_block_len_e{ mk_md2_base_block_len = 16 };
enum mk_md2_base_digest_len_e{ mk_md2_base_digest_len = 16 };


mk_jumbo void mk_md2_base_init(struct mk_md2_base_s* md2_base);
mk_jumbo void mk_md2_base_append_blocks(struct mk_md2_base_s* md2_base, int nblocks, void const* pblocks);
mk_jumbo void mk_md2_base_finish(struct mk_md2_base_s* md2_base, void* block, int idx, void* digest);


#endif
