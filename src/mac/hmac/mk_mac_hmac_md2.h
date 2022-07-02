#ifndef mk_include_guard_mac_hmac_md2
#define mk_include_guard_mac_hmac_md2


#include "../../hash/base/mk_hash_base_alg_id.h"

#ifdef alg_id
#define was_mac_hmac
#else
#define alg_id alg_id_hash_md2
#endif
#include "mk_mac_hmac.h.inl"
#ifdef was_mac_hmac
#undef was_mac_hmac
#else
#undef alg_id
#endif


#endif
