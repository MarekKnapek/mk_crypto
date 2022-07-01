#include "mk_hash_xof_sha3_rawshake128.h"

#include "../base/mk_hash_base_alg_id.h"

#define alg_id alg_id_xof_sha3_rawshake128
#include "mk_hash_xof.c.inl"
#undef alg_id
