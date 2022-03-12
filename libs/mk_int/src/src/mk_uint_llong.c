#include "mk_uint_llong.h"

#include "../utils/mk_assert.h"


void mk_uint_llong_zero(unsigned long long* out)
{
	MK_ASSERT(out);

	*out = 0;
}

void mk_uint_llong_one(unsigned long long* out)
{
	MK_ASSERT(out);

	*out = 1;
}


void mk_uint_llong_or(unsigned long long* out, unsigned long long const* a, unsigned long long const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned long long r;

	r = *a | *b;

	*out = r;
}

void mk_uint_llong_and(unsigned long long* out, unsigned long long const* a, unsigned long long const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned long long r;

	r = *a & *b;

	*out = r;
}

void mk_uint_llong_xor(unsigned long long* out, unsigned long long const* a, unsigned long long const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned long long r;

	r = *a ^ *b;

	*out = r;
}


void mk_uint_llong_shl(unsigned long long* out, unsigned long long const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < 64);

	unsigned long long r;

	r = *x << n;

	*out = r;
}

void mk_uint_llong_shr(unsigned long long* out, unsigned long long const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < 64);

	unsigned long long r;

	r = *x >> n;

	*out = r;
}


int mk_uint_llong_lt(unsigned long long const* a, unsigned long long const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	return *a < *b;
}

int mk_uint_llong_le(unsigned long long const* a, unsigned long long const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	return *a <= *b;
}


void mk_uint_llong_add(unsigned long long* out, unsigned long long const* a, unsigned long long const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned long long r;
	
	r = *a + *b;

	*out = r;
}

void mk_uint_llong_sub(unsigned long long* out, unsigned long long const* a, unsigned long long const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	unsigned long long r;
	
	r = *a - *b;

	*out = r;
}
