#ifndef mk_include_guard_hash_block_xof
#define mk_include_guard_hash_block_xof


#include "../base/mk_hash_base_alg_id.h"


#define mk_hash_block_xof_alg_id alg_id_xof_sha3_rawshake128
#include "mk_hash_block_xof.h.inl"
#undef mk_hash_block_xof_alg_id
#define mk_hash_block_xof_alg_id alg_id_xof_sha3_rawshake256
#include "mk_hash_block_xof.h.inl"
#undef mk_hash_block_xof_alg_id
#define mk_hash_block_xof_alg_id alg_id_xof_sha3_shake128
#include "mk_hash_block_xof.h.inl"
#undef mk_hash_block_xof_alg_id
#define mk_hash_block_xof_alg_id alg_id_xof_sha3_shake256
#include "mk_hash_block_xof.h.inl"
#undef mk_hash_block_xof_alg_id


#endif
