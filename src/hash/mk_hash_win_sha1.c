#include "mk_hash_win_sha1.h"

#define alg sha1
#define alg_prov MS_DEF_PROV_A
#define alg_prov_type PROV_RSA_FULL
#define alg_id CALG_SHA1
#define alg_digest_len 20
#include "mk_hash_win.c.inl"
#undef alg
#undef alg_prov
#undef alg_prov_type
#undef alg_id
#undef alg_digest_len
