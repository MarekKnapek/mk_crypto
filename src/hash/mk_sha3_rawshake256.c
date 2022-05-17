#include "mk_sha3_rawshake256.h"


#define alg sha3_rawshake256
#include "mk_xof.c.inl"
#undef alg
