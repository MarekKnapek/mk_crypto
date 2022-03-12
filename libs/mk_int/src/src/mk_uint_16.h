#ifndef MK_INCLUDE_GUARD_UINT16
#define MK_INCLUDE_GUARD_UINT16


#include "mk_uint_8.h"


#define mk_uint_small_t struct mk_uint8_s


#define mk_uint_bits 16
#define mk_uint_t struct mk_uint16_s
#define mk_uint_zero mk_uint16_zero
#define mk_uint_from_int mk_uint16_from_int
#define mk_uint_one mk_uint16_one
#define mk_uint_or mk_uint16_or
#define mk_uint_and mk_uint16_and
#define mk_uint_xor mk_uint16_xor
#define mk_uint_shl mk_uint16_shl
#define mk_uint_shr mk_uint16_shr
#define mk_uint_lt mk_uint16_lt
#define mk_uint_le mk_uint16_le
#define mk_uint_add mk_uint16_add
#define mk_uint_sub mk_uint16_sub


#include "../inl/mk_uint.h"


#undef mk_uint_small_t


#undef mk_uint_bits
#undef mk_uint_t
#undef mk_uint_zero
#undef mk_uint_one
#undef mk_uint_from_int
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