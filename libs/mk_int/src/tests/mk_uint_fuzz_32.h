#ifndef MK_INCLUDE_GUARD_UINT_FUZZ_32
#define MK_INCLUDE_GUARD_UINT_FUZZ_32


void mk_uint_fuzz_32_from_int(unsigned char const* data);
void mk_uint_fuzz_32_or(unsigned char const* data);
void mk_uint_fuzz_32_and(unsigned char const* data);
void mk_uint_fuzz_32_xor(unsigned char const* data);
void mk_uint_fuzz_32_shl(unsigned char const* data);
void mk_uint_fuzz_32_shr(unsigned char const* data);
void mk_uint_fuzz_32_lt(unsigned char const* data);
void mk_uint_fuzz_32_le(unsigned char const* data);
void mk_uint_fuzz_32_add(unsigned char const* data);
void mk_uint_fuzz_32_sub(unsigned char const* data);

void mk_uint_fuzz_32(unsigned char const* data);


#endif
