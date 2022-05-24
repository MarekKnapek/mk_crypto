#include "mk_hash_base_xof_alg_id.h"


#if alg_id == alg_id_xof_sha3_rawshake128
#include "xof/mk_hash_base_xof_sha3_rawshake128.h"
#define alg xof_sha3_rawshake128
#elif alg_id == alg_id_xof_sha3_rawshake256
#include "xof/mk_hash_base_xof_sha3_rawshake256.h"
#define alg xof_sha3_rawshake256
#elif alg_id == alg_id_xof_sha3_shake128
#include "xof/mk_hash_base_xof_sha3_shake128.h"
#define alg xof_sha3_shake128
#elif alg_id == alg_id_xof_sha3_shake256
#include "xof/mk_hash_base_xof_sha3_shake256.h"
#define alg xof_sha3_shake256
#endif
