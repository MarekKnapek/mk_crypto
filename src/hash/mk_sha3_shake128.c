#include "mk_sha3_shake128.h"


#define alg sha3_shake128
#include "mk_xof.c.inl"
#undef alg
