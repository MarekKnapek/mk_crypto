#ifndef mk_include_guard_base_md5
#define mk_include_guard_base_md5


#include "../../utils/mk_jumbo.h"

#include "../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../../mk_int/src/exact/mk_uint_64.h"


struct mk_md5_base_s
{
	struct mk_uint32_s m_state[4];
	struct mk_uint64_s m_len;
};


enum mk_md5_base_block_len_e{ mk_md5_base_block_len = 64 };
enum mk_md5_base_digest_len_e{ mk_md5_base_digest_len = 16 };


mk_jumbo void mk_md5_base_init(struct mk_md5_base_s* md5_base);
mk_jumbo void mk_md5_base_append_blocks(struct mk_md5_base_s* md5_base, int nblocks, void const* pblocks);
mk_jumbo void mk_md5_base_finish(struct mk_md5_base_s* md5_base, void* block, int idx, void* digest);


#endif
