#include "mk_block_sha3_shake256.h"


#define alg sha3_shake256
#include "mk_block.c.inl"
#undef alg
