#include "mk_hash_sha3_shake128.h"


#define alg sha3_shake128
#include "mk_hash_xof.c.inl"
#undef alg
