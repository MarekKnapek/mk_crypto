#include "mk_hash_hash_win_md2.h"

#define alg md2
#define alg_prov MS_DEF_PROV_A
#define alg_prov_type PROV_RSA_FULL
#define alg_id CALG_MD2
#define alg_digest_len 16
#include "mk_hash_hash_win.c.inl"
#undef alg
#undef alg_prov
#undef alg_prov_type
#undef alg_id
#undef alg_digest_len
