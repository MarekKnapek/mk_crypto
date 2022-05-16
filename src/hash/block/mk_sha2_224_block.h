#ifndef mk_include_guard_sha2_224_block
#define mk_include_guard_sha2_224_block


#include "../base/mk_sha2_224_base.h"

#include "../../utils/mk_jumbo.h"


mk_jumbo void mk_sha2_224_block_append(struct mk_sha2_224_base_s* sha2_224_base, void* block, int* pidx, void const* msg, int msg_len);


#endif
