#ifndef mk_include_guard_hash_block_sha3_shake256
#define mk_include_guard_hash_block_sha3_shake256


#include "../../base/mk_hash_base_alg_id.h"

#define alg_id alg_id_xof_sha3_shake256
#include "mk_hash_block_xof.h.inl"
#undef alg_id


#endif
