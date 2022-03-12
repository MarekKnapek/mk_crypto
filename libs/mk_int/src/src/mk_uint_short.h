#ifndef MK_INCLUDE_GUARD_UINT_SHORT
#define MK_INCLUDE_GUARD_UINT_SHORT


void mk_uint_short_zero(unsigned short* out);
void mk_uint_short_one(unsigned short* out);
void mk_uint_short_from_int(unsigned short* out, unsigned in);

void mk_uint_short_or(unsigned short* out, unsigned short const* a, unsigned short const* b);
void mk_uint_short_and(unsigned short* out, unsigned short const* a, unsigned short const* b);
void mk_uint_short_xor(unsigned short* out, unsigned short const* a, unsigned short const* b);

void mk_uint_short_shl(unsigned short* out, unsigned short const* x, int n);
void mk_uint_short_shr(unsigned short* out, unsigned short const* x, int n);

int mk_uint_short_lt(unsigned short const* a, unsigned short const* b);
int mk_uint_short_le(unsigned short const* a, unsigned short const* b);

void mk_uint_short_add(unsigned short* out, unsigned short const* a, unsigned short const* b);
void mk_uint_short_sub(unsigned short* out, unsigned short const* a, unsigned short const* b);


#endif
