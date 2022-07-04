#ifndef mk_include_guard_kdf_pbkdf2_md2
#define mk_include_guard_kdf_pbkdf2_md2


#include "../../hash/base/mk_hash_base_alg_id.h"

#ifdef alg_id
#define was_kdf_pbkdf2
#else
#define alg_id alg_id_hash_md2
#endif
#include "mk_kdf_pbkdf2.h.inl"
#ifdef was_kdf_pbkdf2
#undef was_kdf_pbkdf2
#else
#undef alg_id
#endif


#endif
