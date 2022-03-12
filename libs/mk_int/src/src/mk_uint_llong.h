#ifndef MK_INCLUDE_GUARD_UINT_LLONG
#define MK_INCLUDE_GUARD_UINT_LLONG


void mk_uint_llong_zero(unsigned long long* out);
void mk_uint_llong_one(unsigned long long* out);
void mk_uint_llong_from_int(unsigned long long* out, unsigned in);

void mk_uint_llong_or(unsigned long long* out, unsigned long long const* a, unsigned long long const* b);
void mk_uint_llong_and(unsigned long long* out, unsigned long long const* a, unsigned long long const* b);
void mk_uint_llong_xor(unsigned long long* out, unsigned long long const* a, unsigned long long const* b);

void mk_uint_llong_shl(unsigned long long* out, unsigned long long const* x, int n);
void mk_uint_llong_shr(unsigned long long* out, unsigned long long const* x, int n);

int mk_uint_llong_lt(unsigned long long const* a, unsigned long long const* b);
int mk_uint_llong_le(unsigned long long const* a, unsigned long long const* b);

void mk_uint_llong_add(unsigned long long* out, unsigned long long const* a, unsigned long long const* b);
void mk_uint_llong_sub(unsigned long long* out, unsigned long long const* a, unsigned long long const* b);


#endif
