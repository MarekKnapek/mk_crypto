#include "mk_uint_32.h"


#include "mk_uint_16.h"


#define mk_uint_small_t struct mk_uint16_s
#define mk_uint_small_zero mk_uint16_zero
#define mk_uint_small_one mk_uint16_one
#define mk_uint_small_or mk_uint16_or
#define mk_uint_small_and mk_uint16_and
#define mk_uint_small_xor mk_uint16_xor
#define mk_uint_small_shl mk_uint16_shl
#define mk_uint_small_shr mk_uint16_shr
#define mk_uint_small_lt mk_uint16_lt
#define mk_uint_small_le mk_uint16_le
#define mk_uint_small_add mk_uint16_add
#define mk_uint_small_sub mk_uint16_sub


#define mk_uint_t struct mk_uint32_s
#define mk_uint_zero mk_uint32_zero
#define mk_uint_one mk_uint32_one
#define mk_uint_or mk_uint32_or
#define mk_uint_and mk_uint32_and
#define mk_uint_xor mk_uint32_xor
#define mk_uint_shl mk_uint32_shl
#define mk_uint_shr mk_uint32_shr
#define mk_uint_lt mk_uint32_lt
#define mk_uint_le mk_uint32_le
#define mk_uint_add mk_uint32_add
#define mk_uint_sub mk_uint32_sub


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
