#include "mk_mac_hmac_hash.h"


#include "../../hash/base/mk_hash_base_alg_id.h"


#define mk_mac_hmac_hash_alg_id alg_id_hash_md2
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_md4
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_md5
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha1
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha2_224
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha2_256
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha2_384
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha2_512
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha2_512224
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha2_512256
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha3_224
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha3_256
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha3_384
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
#define mk_mac_hmac_hash_alg_id alg_id_hash_sha3_512
#include "mk_mac_hmac_hash.c.inl"
#undef mk_mac_hmac_hash_alg_id
