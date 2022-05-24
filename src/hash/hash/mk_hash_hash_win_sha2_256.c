#include "mk_hash_hash_win_sha2_256.h"

#define alg sha2_256
#define alg_prov MS_ENH_RSA_AES_PROV_A
#define alg_prov_type PROV_RSA_AES
#define alg_id CALG_SHA_256
#define alg_digest_len 32
#include "mk_hash_hash_win.c.inl"
#undef alg
#undef alg_prov
#undef alg_prov_type
#undef alg_id
#undef alg_digest_len
