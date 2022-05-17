#include "mk_sha3_shake256.h"


#define alg sha3_shake256
#include "mk_xof.c.inl"
#undef alg
