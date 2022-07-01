#include "mk_hash_base_alg_id.h"


#if alg_id == alg_id_xof_sha3_rawshake128
#include "xof/mk_hash_base_xof_sha3_rawshake128.h"
#elif alg_id == alg_id_xof_sha3_rawshake256
#include "xof/mk_hash_base_xof_sha3_rawshake256.h"
#elif alg_id == alg_id_xof_sha3_shake128
#include "xof/mk_hash_base_xof_sha3_shake128.h"
#elif alg_id == alg_id_xof_sha3_shake256
#include "xof/mk_hash_base_xof_sha3_shake256.h"
#endif
