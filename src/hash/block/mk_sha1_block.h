#ifndef mk_include_guard_sha1_block
#define mk_include_guard_sha1_block


#include "../base/mk_sha1_base.h"

#include "../../utils/mk_jumbo.h"


mk_jumbo void mk_sha1_block_append(struct mk_sha1_base_s* sha1_base, void* block, int* pidx, void const* msg, int msg_len);


#endif
