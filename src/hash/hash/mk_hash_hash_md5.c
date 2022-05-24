#include "mk_hash_hash_md5.h"

#include "../base/mk_hash_base_hash_alg_id.h"

#define alg_id alg_id_hash_md5
#include "mk_hash_hash.c.inl"
#undef alg_id
#undef alg
