#ifndef MK_INCLUDE_GUARD_UINT_INT
#define MK_INCLUDE_GUARD_UINT_INT


void mk_uint_int_zero(unsigned int* out);
void mk_uint_int_one(unsigned int* out);
void mk_uint_int_from_int(unsigned int* out, unsigned in);
unsigned mk_uint_int_to_int(unsigned int const* x);

void mk_uint_int_or(unsigned int* out, unsigned int const* a, unsigned int const* b);
void mk_uint_int_and(unsigned int* out, unsigned int const* a, unsigned int const* b);
void mk_uint_int_xor(unsigned int* out, unsigned int const* a, unsigned int const* b);

void mk_uint_int_shl(unsigned int* out, unsigned int const* x, int n);
void mk_uint_int_shr(unsigned int* out, unsigned int const* x, int n);

int mk_uint_int_lt(unsigned int const* a, unsigned int const* b);
int mk_uint_int_le(unsigned int const* a, unsigned int const* b);

void mk_uint_int_add(unsigned int* out, unsigned int const* a, unsigned int const* b);
void mk_uint_int_sub(unsigned int* out, unsigned int const* a, unsigned int const* b);


#endif
