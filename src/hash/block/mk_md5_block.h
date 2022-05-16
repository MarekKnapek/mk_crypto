#ifndef mk_include_guard_md5_block
#define mk_include_guard_md5_block


#include "../base/mk_md5_base.h"

#include "../../utils/mk_jumbo.h"


mk_jumbo void mk_md5_block_append(struct mk_md5_base_s* md5_base, void* block, int* pidx, void const* msg, int msg_len);


#endif
