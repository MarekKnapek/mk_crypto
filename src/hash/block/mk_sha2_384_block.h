#ifndef mk_include_guard_sha2_384_block
#define mk_include_guard_sha2_384_block


#include "../base/mk_sha2_384_base.h"

#include "../../utils/mk_jumbo.h"


mk_jumbo void mk_sha2_384_block_append(struct mk_sha2_384_base_s* sha2_384_base, void* block, int* pidx, void const* msg, int msg_len);


#endif
