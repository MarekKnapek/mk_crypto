#include "mk_mac_hmac_md5.h"

#include "../../hash/base/mk_hash_base_alg_id.h"

#define alg_id alg_id_hash_md5
#include "mk_mac_hmac.c.inl"
#undef alg_id
