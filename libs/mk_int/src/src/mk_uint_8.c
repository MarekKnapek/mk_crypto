#include "mk_uint_8.h"


#include "mk_uint_char.h"


#define mk_uint_small_t unsigned char
#define mk_uint_small_zero mk_uint_char_zero
#define mk_uint_small_one mk_uint_char_one
#define mk_uint_small_from_int mk_uint_char_from_int
#define mk_uint_small_to_int mk_uint_char_to_int
#define mk_uint_small_or mk_uint_char_or
#define mk_uint_small_and mk_uint_char_and
#define mk_uint_small_xor mk_uint_char_xor
#define mk_uint_small_shl mk_uint_char_shl
#define mk_uint_small_shr mk_uint_char_shr
#define mk_uint_small_lt mk_uint_char_lt
#define mk_uint_small_le mk_uint_char_le
#define mk_uint_small_add mk_uint_char_add
#define mk_uint_small_sub mk_uint_char_sub


#define mk_uint_t struct mk_uint8_s
#define mk_uint_zero mk_uint8_zero
#define mk_uint_one mk_uint8_one
#define mk_uint_from_int mk_uint8_from_int
#define mk_uint_to_int mk_uint8_to_int
#define mk_uint_or mk_uint8_or
#define mk_uint_and mk_uint8_and
#define mk_uint_xor mk_uint8_xor
#define mk_uint_shl mk_uint8_shl
#define mk_uint_shr mk_uint8_shr
#define mk_uint_lt mk_uint8_lt
#define mk_uint_le mk_uint8_le
#define mk_uint_add mk_uint8_add
#define mk_uint_sub mk_uint8_sub


#include "../inl/mk_uint.c"


#undef mk_uint_small_t
#undef mk_uint_small_zero
#undef mk_uint_small_one
#undef mk_uint_small_from_int
#undef mk_uint_small_to_int
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
