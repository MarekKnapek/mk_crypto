#ifndef MK_INCLUDE_GUARD_UINT_LONG
#define MK_INCLUDE_GUARD_UINT_LONG


void mk_uint_long_zero(unsigned long* out);
void mk_uint_long_one(unsigned long* out);
void mk_uint_long_from_int(unsigned long* out, unsigned in);
unsigned mk_uint_long_to_int(unsigned long const* x);

void mk_uint_long_or(unsigned long* out, unsigned long const* a, unsigned long const* b);
void mk_uint_long_and(unsigned long* out, unsigned long const* a, unsigned long const* b);
void mk_uint_long_xor(unsigned long* out, unsigned long const* a, unsigned long const* b);

void mk_uint_long_shl(unsigned long* out, unsigned long const* x, int n);
void mk_uint_long_shr(unsigned long* out, unsigned long const* x, int n);

int mk_uint_long_lt(unsigned long const* a, unsigned long const* b);
int mk_uint_long_le(unsigned long const* a, unsigned long const* b);

void mk_uint_long_add(unsigned long* out, unsigned long const* a, unsigned long const* b);
void mk_uint_long_sub(unsigned long* out, unsigned long const* a, unsigned long const* b);


#endif
