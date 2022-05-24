#include "mk_hash_base_hash_alg_id.h"


#if alg_id == alg_id_hash_md2
#include "hash/mk_hash_base_hash_md2.h"
#define alg hash_md2
#elif alg_id == alg_id_hash_md4
#include "hash/mk_hash_base_hash_md4.h"
#define alg hash_md4
#elif alg_id == alg_id_hash_md5
#include "hash/mk_hash_base_hash_md5.h"
#define alg hash_md5
#elif alg_id == alg_id_hash_sha1
#include "hash/mk_hash_base_hash_sha1.h"
#define alg hash_sha1
#elif alg_id == alg_id_hash_sha2_224
#include "hash/mk_hash_base_hash_sha2_224.h"
#define alg hash_sha2_224
#elif alg_id == alg_id_hash_sha2_256
#include "hash/mk_hash_base_hash_sha2_256.h"
#define alg hash_sha2_256
#elif alg_id == alg_id_hash_sha2_384
#include "hash/mk_hash_base_hash_sha2_384.h"
#define alg hash_sha2_384
#elif alg_id == alg_id_hash_sha2_512
#include "hash/mk_hash_base_hash_sha2_512.h"
#define alg hash_sha2_512
#elif alg_id == alg_id_hash_sha2_512224
#include "hash/mk_hash_base_hash_sha2_512224.h"
#define alg hash_sha2_512224
#elif alg_id == alg_id_hash_sha2_512256
#include "hash/mk_hash_base_hash_sha2_512256.h"
#define alg hash_sha2_512256
#elif alg_id == alg_id_hash_sha3_224
#include "hash/mk_hash_base_hash_sha3_224.h"
#define alg hash_sha3_224
#elif alg_id == alg_id_hash_sha3_256
#include "hash/mk_hash_base_hash_sha3_256.h"
#define alg hash_sha3_256
#elif alg_id == alg_id_hash_sha3_384
#include "hash/mk_hash_base_hash_sha3_384.h"
#define alg hash_sha3_384
#elif alg_id == alg_id_hash_sha3_512
#include "hash/mk_hash_base_hash_sha3_512.h"
#define alg hash_sha3_512
#endif