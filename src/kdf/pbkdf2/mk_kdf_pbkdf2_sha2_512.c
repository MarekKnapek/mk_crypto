#include "mk_kdf_pbkdf2_sha2_512.h"

#include "../../hash/base/mk_hash_base_alg_id.h"

#define alg_id alg_id_hash_sha2_512
#include "mk_kdf_pbkdf2.c.inl"
#undef alg_id