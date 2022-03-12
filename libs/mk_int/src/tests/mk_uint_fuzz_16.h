#ifndef MK_INCLUDE_GUARD_UINT_FUZZ_16
#define MK_INCLUDE_GUARD_UINT_FUZZ_16


void mk_uint_fuzz_16_from_int(unsigned char const* data);
void mk_uint_fuzz_16_to_int(unsigned char const* data);
void mk_uint_fuzz_16_or(unsigned char const* data);
void mk_uint_fuzz_16_and(unsigned char const* data);
void mk_uint_fuzz_16_xor(unsigned char const* data);
void mk_uint_fuzz_16_shl(unsigned char const* data);
void mk_uint_fuzz_16_shr(unsigned char const* data);
void mk_uint_fuzz_16_lt(unsigned char const* data);
void mk_uint_fuzz_16_le(unsigned char const* data);
void mk_uint_fuzz_16_add(unsigned char const* data);
void mk_uint_fuzz_16_sub(unsigned char const* data);

void mk_uint_fuzz_16(unsigned char const* data);


#endif
