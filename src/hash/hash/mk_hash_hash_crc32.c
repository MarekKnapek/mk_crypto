#include "mk_hash_hash_crc32.h"

#include "../base/mk_hash_base_alg_id.h"

#define alg_id alg_id_hash_crc32
#include "mk_hash_hash.c.inl"
#undef alg_id
