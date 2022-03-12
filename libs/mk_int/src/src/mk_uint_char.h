#ifndef MK_INCLUDE_GUARD_UINT_CHAR
#define MK_INCLUDE_GUARD_UINT_CHAR


void mk_uint_char_zero(unsigned char* out);
void mk_uint_char_one(unsigned char* out);
void mk_uint_char_from_int(unsigned char* out, unsigned in);
unsigned mk_uint_char_to_int(unsigned char const* x);

void mk_uint_char_or(unsigned char* out, unsigned char const* a, unsigned char const* b);
void mk_uint_char_and(unsigned char* out, unsigned char const* a, unsigned char const* b);
void mk_uint_char_xor(unsigned char* out, unsigned char const* a, unsigned char const* b);

void mk_uint_char_shl(unsigned char* out, unsigned char const* x, int n);
void mk_uint_char_shr(unsigned char* out, unsigned char const* x, int n);

int mk_uint_char_lt(unsigned char const* a, unsigned char const* b);
int mk_uint_char_le(unsigned char const* a, unsigned char const* b);

void mk_uint_char_add(unsigned char* out, unsigned char const* a, unsigned char const* b);
void mk_uint_char_sub(unsigned char* out, unsigned char const* a, unsigned char const* b);


#endif
