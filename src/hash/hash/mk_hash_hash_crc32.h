#ifndef mk_include_guard_hash_hash_crc32
#define mk_include_guard_hash_hash_crc32


#include "../base/mk_hash_base_alg_id.h"

#ifdef alg_id
#define was_hash_hash
#else
#define alg_id alg_id_hash_crc32
#endif
#include "mk_hash_hash.h.inl"
#ifdef was_hash_hash
#undef was_hash_hash
#else
#undef alg_id
#endif


#endif