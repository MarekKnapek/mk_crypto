#include "mk_hash_block_hash_sha2_256.h"

#include "../../base/mk_hash_base_alg_id.h"

#define alg_id alg_id_hash_sha2_256
#include "mk_hash_block_hash.c.inl"
#undef alg_id