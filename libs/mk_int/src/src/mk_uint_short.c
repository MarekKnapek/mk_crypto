#include "mk_uint_short.h"

#include "../utils/mk_assert.h"


void mk_uint_short_zero(unsigned short* out)
{
	MK_ASSERT(out);

	*out = 0;
}

void mk_uint_short_one(unsigned short* out)
{
	MK_ASSERT(out);

	*out = 1;
}

void mk_uint_short_from_int(unsigned short* out, unsigned in)
{
	MK_ASSERT(out);

	*out = (unsigned short)in;
}

unsigned mk_uint_short_to_int(unsigned short const* x)
{
	MK_ASSERT(x);

	return (unsigned)*x;
}


void mk_uint_short_or(unsigned short* out, unsigned short const* a, unsigned short const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned short r;

	r = *a | *b;

	*out = r;
}

void mk_uint_short_and(unsigned short* out, unsigned short const* a, unsigned short const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned short r;

	r = *a & *b;

	*out = r;
}

void mk_uint_short_xor(unsigned short* out, unsigned short const* a, unsigned short const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned short r;

	r = *a ^ *b;

	*out = r;
}


void mk_uint_short_shl(unsigned short* out, unsigned short const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < 16);

	unsigned short r;

	r = *x << n;

	*out = r;
}

void mk_uint_short_shr(unsigned short* out, unsigned short const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < 16);

	unsigned short r;

	r = *x >> n;

	*out = r;
}


int mk_uint_short_lt(unsigned short const* a, unsigned short const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	return *a < *b;
}

int mk_uint_short_le(unsigned short const* a, unsigned short const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	return *a <= *b;
}


void mk_uint_short_add(unsigned short* out, unsigned short const* a, unsigned short const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned short r;
	
	r = *a + *b;

	*out = r;
}

void mk_uint_short_sub(unsigned short* out, unsigned short const* a, unsigned short const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned short r;
	
	r = *a - *b;

	*out = r;
}
