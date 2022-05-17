#include "mk_hash_sha3_rawshake256.h"


#define alg sha3_rawshake256
#include "mk_hash_xof.c.inl"
#undef alg
