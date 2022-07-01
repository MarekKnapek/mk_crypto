#include "mk_hash_base_alg_id.h"


#if alg_id == alg_id_hash_md2
#define alg_name md2
#elif alg_id == alg_id_hash_md4
#define alg_name md4
#elif alg_id == alg_id_hash_md5
#define alg_name md5
#elif alg_id == alg_id_hash_sha1
#define alg_name sha1
#elif alg_id == alg_id_hash_sha2_224
#define alg_name sha2_224
#elif alg_id == alg_id_hash_sha2_256
#define alg_name sha2_256
#elif alg_id == alg_id_hash_sha2_384
#define alg_name sha2_384
#elif alg_id == alg_id_hash_sha2_512
#define alg_name sha2_512
#elif alg_id == alg_id_hash_sha2_512224
#define alg_name sha2_512224
#elif alg_id == alg_id_hash_sha2_512256
#define alg_name sha2_512256
#elif alg_id == alg_id_hash_sha3_224
#define alg_name sha3_224
#elif alg_id == alg_id_hash_sha3_256
#define alg_name sha3_256
#elif alg_id == alg_id_hash_sha3_384
#define alg_name sha3_384
#elif alg_id == alg_id_hash_sha3_512
#define alg_name sha3_512

#elif alg_id == alg_id_xof_sha3_rawshake128
#define alg_name sha3_rawshake128
#elif alg_id == alg_id_xof_sha3_rawshake256
#define alg_name sha3_rawshake256
#elif alg_id == alg_id_xof_sha3_shake128
#define alg_name sha3_shake128
#elif alg_id == alg_id_xof_sha3_shake256
#define alg_name sha3_shake256
#endif
