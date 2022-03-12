#include "mk_uint_128.h"


#include "mk_uint_int.h"


#define mk_uint_small_t unsigned int
#define mk_uint_small_zero mk_uint_int_zero
#define mk_uint_small_one mk_uint_int_one
#define mk_uint_small_or mk_uint_int_or
#define mk_uint_small_and mk_uint_int_and
#define mk_uint_small_xor mk_uint_int_xor
#define mk_uint_small_shl mk_uint_int_shl
#define mk_uint_small_shr mk_uint_int_shr
#define mk_uint_small_lt mk_uint_int_lt
#define mk_uint_small_le mk_uint_int_le
#define mk_uint_small_add mk_uint_int_add
#define mk_uint_small_sub mk_uint_int_sub


#define mk_uint_t struct mk_uint128_s
#define mk_uint_zero mk_uint128_zero
#define mk_uint_one mk_uint128_one
#define mk_uint_or mk_uint128_or
#define mk_uint_and mk_uint128_and
#define mk_uint_xor mk_uint128_xor
#define mk_uint_shl mk_uint128_shl
#define mk_uint_shr mk_uint128_shr
#define mk_uint_lt mk_uint128_lt
#define mk_uint_le mk_uint128_le
#define mk_uint_add mk_uint128_add
#define mk_uint_sub mk_uint128_sub


#include "../inl/mk_uint.c"


#undef mk_uint_small_t
#undef mk_uint_small_zero
#undef mk_uint_small_one
#undef mk_uint_small_or
#undef mk_uint_small_and
#undef mk_uint_small_xor
#undef mk_uint_small_shl
#undef mk_uint_small_shr
#undef mk_uint_small_lt
#undef mk_uint_small_le
#undef mk_uint_small_add
#undef mk_uint_small_sub


#undef mk_uint_t
#undef mk_uint_zero
#undef mk_uint_one
#undef mk_uint_or
#undef mk_uint_and
#undef mk_uint_xor
#undef mk_uint_shl
#undef mk_uint_shr
#undef mk_uint_lt
#undef mk_uint_le
#undef mk_uint_add
#undef mk_uint_sub
