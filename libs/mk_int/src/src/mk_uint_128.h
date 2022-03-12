#ifndef MK_INCLUDE_GUARD_UINT_128
#define MK_INCLUDE_GUARD_UINT_128





#define mk_uint_small_t unsigned


#define mk_uint_bits 128
#define mk_uint_t struct mk_uint128_s
#define mk_uint_zero mk_uint128_zero
#define mk_uint_one mk_uint128_one
#define mk_uint_from_int mk_uint128_from_int
#define mk_uint_to_int mk_uint128_to_int
#define mk_uint_or mk_uint128_or
#define mk_uint_and mk_uint128_and
#define mk_uint_xor mk_uint128_xor
#define mk_uint_shl mk_uint128_shl
#define mk_uint_shr mk_uint128_shr
#define mk_uint_lt mk_uint128_lt
#define mk_uint_le mk_uint128_le
#define mk_uint_add mk_uint128_add
#define mk_uint_sub mk_uint128_sub


#include "../inl/mk_uint.h"


#undef mk_uint_small_t


#undef mk_uint_bits
#undef mk_uint_t
#undef mk_uint_zero
#undef mk_uint_one
#undef mk_uint_from_int
#undef mk_uint_to_int
#undef mk_uint_or
#undef mk_uint_and
#undef mk_uint_xor
#undef mk_uint_shl
#undef mk_uint_shr
#undef mk_uint_lt
#undef mk_uint_le
#undef mk_uint_add
#undef mk_uint_sub


#endif
