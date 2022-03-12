#include "mk_uint_long.h"

#include "../utils/mk_assert.h"


void mk_uint_long_zero(unsigned long* out)
{
	MK_ASSERT(out);

	*out = 0;
}

void mk_uint_long_one(unsigned long* out)
{
	MK_ASSERT(out);

	*out = 1;
}

void mk_uint_long_from_int(unsigned long* out, unsigned in)
{
	MK_ASSERT(out);

	*out = (unsigned long)in;
}


void mk_uint_long_or(unsigned long* out, unsigned long const* a, unsigned long const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned long r;

	r = *a | *b;

	*out = r;
}

void mk_uint_long_and(unsigned long* out, unsigned long const* a, unsigned long const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned long r;

	r = *a & *b;

	*out = r;
}

void mk_uint_long_xor(unsigned long* out, unsigned long const* a, unsigned long const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned long r;

	r = *a ^ *b;

	*out = r;
}


void mk_uint_long_shl(unsigned long* out, unsigned long const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < 32);

	unsigned long r;

	r = *x << n;

	*out = r;
}

void mk_uint_long_shr(unsigned long* out, unsigned long const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < 32);

	unsigned long r;

	r = *x >> n;

	*out = r;
}


int mk_uint_long_lt(unsigned long const* a, unsigned long const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	return *a < *b;
}

int mk_uint_long_le(unsigned long const* a, unsigned long const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	return *a <= *b;
}


void mk_uint_long_add(unsigned long* out, unsigned long const* a, unsigned long const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned long r;
	
	r = *a + *b;

	*out = r;
}

void mk_uint_long_sub(unsigned long* out, unsigned long const* a, unsigned long const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned long r;
	
	r = *a - *b;

	*out = r;
}
