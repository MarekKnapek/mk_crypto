#include "mk_hash_block_sha3_shake256.h"

#include "../base/mk_hash_base_xof_alg_id.h"

#define alg_id alg_id_xof_sha3_shake256
#include "mk_hash_block.c.inl"
