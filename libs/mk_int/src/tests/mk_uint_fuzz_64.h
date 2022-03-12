#ifndef MK_INCLUDE_GUARD_UINT_FUZZ64
#define MK_INCLUDE_GUARD_UINT_FUZZ64


void mk_uint_fuzz_64_or(unsigned char const* data);
void mk_uint_fuzz_64_and(unsigned char const* data);
void mk_uint_fuzz_64_xor(unsigned char const* data);
void mk_uint_fuzz_64_shl(unsigned char const* data);
void mk_uint_fuzz_64_shr(unsigned char const* data);
void mk_uint_fuzz_64_lt(unsigned char const* data);
void mk_uint_fuzz_64_le(unsigned char const* data);
void mk_uint_fuzz_64_add(unsigned char const* data);
void mk_uint_fuzz_64_sub(unsigned char const* data);

void mk_uint_fuzz_64(unsigned char const* data);


#endif
