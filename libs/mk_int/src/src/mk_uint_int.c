#include "mk_uint_int.h"

#include "../utils/mk_assert.h"


void mk_uint_int_zero(unsigned int* out)
{
	MK_ASSERT(out);

	*out = 0;
}

void mk_uint_int_one(unsigned int* out)
{
	MK_ASSERT(out);

	*out = 1;
}

void mk_uint_int_from_int(unsigned int* out, unsigned in)
{
	MK_ASSERT(out);

	*out = (unsigned int)in;
}


void mk_uint_int_or(unsigned int* out, unsigned int const* a, unsigned int const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned int r;

	r = *a | *b;

	*out = r;
}

void mk_uint_int_and(unsigned int* out, unsigned int const* a, unsigned int const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned int r;

	r = *a & *b;

	*out = r;
}

void mk_uint_int_xor(unsigned int* out, unsigned int const* a, unsigned int const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned int r;

	r = *a ^ *b;

	*out = r;
}


void mk_uint_int_shl(unsigned int* out, unsigned int const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < 32);

	unsigned int r;

	r = *x << n;

	*out = r;
}

void mk_uint_int_shr(unsigned int* out, unsigned int const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < 32);

	unsigned int r;

	r = *x >> n;

	*out = r;
}


int mk_uint_int_lt(unsigned int const* a, unsigned int const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	return *a < *b;
}

int mk_uint_int_le(unsigned int const* a, unsigned int const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	return *a <= *b;
}


void mk_uint_int_add(unsigned int* out, unsigned int const* a, unsigned int const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned int r;
	
	r = *a + *b;

	*out = r;
}

void mk_uint_int_sub(unsigned int* out, unsigned int const* a, unsigned int const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned int r;
	
	r = *a - *b;

	*out = r;
}
