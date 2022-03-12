#include "mk_uint_char.h"

#include "../utils/mk_assert.h"


void mk_uint_char_zero(unsigned char* out)
{
	MK_ASSERT(out);

	*out = 0;
}

void mk_uint_char_one(unsigned char* out)
{
	MK_ASSERT(out);

	*out = 1;
}

void mk_uint_char_from_int(unsigned char* out, unsigned in)
{
	MK_ASSERT(out);

	*out = (unsigned char)in;
}

unsigned mk_uint_char_to_int(unsigned char const* x)
{
	MK_ASSERT(x);

	return (unsigned)*x;
}


void mk_uint_char_or(unsigned char* out, unsigned char const* a, unsigned char const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned char r;

	r = *a | *b;

	*out = r;
}

void mk_uint_char_and(unsigned char* out, unsigned char const* a, unsigned char const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned char r;

	r = *a & *b;

	*out = r;
}

void mk_uint_char_xor(unsigned char* out, unsigned char const* a, unsigned char const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned char r;

	r = *a ^ *b;

	*out = r;
}


void mk_uint_char_shl(unsigned char* out, unsigned char const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < 8);

	unsigned char r;

	r = *x << n;

	*out = r;
}

void mk_uint_char_shr(unsigned char* out, unsigned char const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < 8);

	unsigned char r;

	r = *x >> n;

	*out = r;
}


int mk_uint_char_lt(unsigned char const* a, unsigned char const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	return *a < *b;
}

int mk_uint_char_le(unsigned char const* a, unsigned char const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	return *a <= *b;
}


void mk_uint_char_add(unsigned char* out, unsigned char const* a, unsigned char const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned char r;
	
	r = *a + *b;

	*out = r;
}

void mk_uint_char_sub(unsigned char* out, unsigned char const* a, unsigned char const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned char r;
	
	r = *a - *b;

	*out = r;
}
