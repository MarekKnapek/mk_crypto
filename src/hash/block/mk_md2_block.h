#ifndef mk_include_guard_md2_block
#define mk_include_guard_md2_block


#include "../base/mk_md2_base.h"

#include "../../utils/mk_jumbo.h"


mk_jumbo void mk_md2_block_append(struct mk_md2_base_s* md2_base, void* block, int* pidx, void const* msg, int msg_len);


#endif
