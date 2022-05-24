#include "../base/mk_hash_base_hash.h.inl"
#include "../base/mk_hash_base_xof.h.inl"

#include "../../utils/mk_jumbo.h"


#define concat3_impl(a, b, c) a ## b ## c
#define concat3(a, b, c) concat3_impl(a, b, c)


mk_jumbo void concat3(mk_hash_block_, alg, _append)(struct concat3(mk_hash_base_, alg, _s)* alg_base, void* block, int* pidx, void const* msg, int msg_len);


#undef concat3_impl
#undef concat3
