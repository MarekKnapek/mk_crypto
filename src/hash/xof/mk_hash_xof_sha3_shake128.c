#include "mk_hash_xof_sha3_shake128.h"

#include "../base/mk_hash_base_xof_alg_id.h"

#define alg_id alg_id_xof_sha3_shake128
#include "mk_hash_xof.c.inl"
#undef alg_id
#undef alg