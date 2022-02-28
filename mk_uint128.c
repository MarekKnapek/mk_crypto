#include "mk_uint128.h"

#include <assert.h> /* assert static_assert */


void mk_uint128_zero(struct mk_uint128_s* res)
{
	assert(res);

	res->m_lo = 0;
	res->m_hi = 0;
}

void mk_uint128_add(struct mk_uint128_s* res, struct mk_uint128_s const* a, struct mk_uint128_s const* b)
{
	assert(res);
	assert(a);
	assert(b);

	struct mk_uint128_s r;

	r.m_hi = a->m_hi + b->m_hi;
	r.m_lo = a->m_lo + b->m_lo;
	if(r.m_lo < a->m_lo)
	{
		++r.m_hi;
	}

	*res = r;
}

void mk_uint128_add_size(struct mk_uint128_s* res, struct mk_uint128_s const* a, size_t b)
{
	static_assert(sizeof(size_t) <= sizeof(uint64_t), "");

	struct mk_uint128_s tmp;

	tmp.m_lo = b;
	tmp.m_hi = 0;

	mk_uint128_add(res, a, &tmp);
}

void mk_uint128_shl(struct mk_uint128_s* res, struct mk_uint128_s const* x, int n)
{
	assert(res);
	assert(x);
	assert(n >= 0 && n < 64);

	struct mk_uint128_s r;

	r.m_hi = (x->m_hi << n) | (x->m_lo >> (64 - n));
	r.m_lo = x->m_lo << n;

	*res = r;
}
