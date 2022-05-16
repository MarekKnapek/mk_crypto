#ifndef mk_include_guard_sha3_rawshake128_block
#define mk_include_guard_sha3_rawshake128_block


#include "../base/mk_sha3_rawshake128_base.h"

#include "../../utils/mk_jumbo.h"


mk_jumbo void mk_sha3_rawshake128_block_append(struct mk_sha3_rawshake128_base_s* sha3_rawshake128_base, void* block, int* pidx, void const* msg, int msg_len);


#endif
