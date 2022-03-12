#ifndef MK_INCLUDE_GUARD_UINT32
#define MK_INCLUDE_GUARD_UINT32


#include "mk_uint_16.h"


#define mk_uint_small_t struct mk_uint16_s


#define mk_uint_bits 32
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


#include "../inl/mk_uint.h"


#undef mk_uint_small_t


#undef mk_uint_bits
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


#endif
