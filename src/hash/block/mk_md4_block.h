#ifndef mk_include_guard_md4_block
#define mk_include_guard_md4_block


#include "../base/mk_md4_base.h"

#include "../../utils/mk_jumbo.h"


mk_jumbo void mk_md4_block_append(struct mk_md4_base_s* md4_base, void* block, int* pidx, void const* msg, int msg_len);


#endif
