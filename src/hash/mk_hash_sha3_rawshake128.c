#include "mk_hash_sha3_rawshake128.h"


#define alg sha3_rawshake128
#include "mk_hash_xof.c.inl"
#undef alg
