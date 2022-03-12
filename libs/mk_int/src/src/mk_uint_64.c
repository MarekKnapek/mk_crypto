#include "mk_uint_64.h"


#include "mk_uint_long.h"


#define mk_uint_small_t unsigned long
#define mk_uint_small_zero mk_uint_long_zero
#define mk_uint_small_one mk_uint_long_one
#define mk_uint_small_or mk_uint_long_or
#define mk_uint_small_and mk_uint_long_and
#define mk_uint_small_xor mk_uint_long_xor
#define mk_uint_small_shl mk_uint_long_shl
#define mk_uint_small_shr mk_uint_long_shr
#define mk_uint_small_lt mk_uint_long_lt
#define mk_uint_small_le mk_uint_long_le
#define mk_uint_small_add mk_uint_long_add
#define mk_uint_small_sub mk_uint_long_sub


#define mk_uint_t struct mk_uint64_s
#define mk_uint_zero mk_uint64_zero
#define mk_uint_one mk_uint64_one
#define mk_uint_or mk_uint64_or
#define mk_uint_and mk_uint64_and
#define mk_uint_xor mk_uint64_xor
#define mk_uint_shl mk_uint64_shl
#define mk_uint_shr mk_uint64_shr
#define mk_uint_lt mk_uint64_lt
#define mk_uint_le mk_uint64_le
#define mk_uint_add mk_uint64_add
#define mk_uint_sub mk_uint64_sub


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
