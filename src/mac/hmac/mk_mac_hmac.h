#include "../../hash/base/mk_hash_base_alg_id.h"


#if alg_id == alg_id_hash_md2
#include "mk_mac_hmac_md2.h"
#elif alg_id == alg_id_hash_md4
#include "mk_mac_hmac_md4.h"
#elif alg_id == alg_id_hash_md5
#include "mk_mac_hmac_md5.h"
#elif alg_id == alg_id_hash_sha1
#include "mk_mac_hmac_sha1.h"
#elif alg_id == alg_id_hash_sha2_224
#include "mk_mac_hmac_sha2_224.h"
#elif alg_id == alg_id_hash_sha2_256
#include "mk_mac_hmac_sha2_256.h"
#elif alg_id == alg_id_hash_sha2_384
#include "mk_mac_hmac_sha2_384.h"
#elif alg_id == alg_id_hash_sha2_512
#include "mk_mac_hmac_sha2_512.h"
#elif alg_id == alg_id_hash_sha2_512224
#include "mk_mac_hmac_sha2_512224.h"
#elif alg_id == alg_id_hash_sha2_512256
#include "mk_mac_hmac_sha2_512256.h"
#elif alg_id == alg_id_hash_sha3_224
#include "mk_mac_hmac_sha3_224.h"
#elif alg_id == alg_id_hash_sha3_256
#include "mk_mac_hmac_sha3_256.h"
#elif alg_id == alg_id_hash_sha3_384
#include "mk_mac_hmac_sha3_384.h"
#elif alg_id == alg_id_hash_sha3_512
#include "mk_mac_hmac_sha3_512.h"
#endif
