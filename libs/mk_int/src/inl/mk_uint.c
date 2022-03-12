#include "../utils/mk_assert.h"

#include <limits.h> /* CHAR_BIT */


#define mk_uint_bits (sizeof(mk_uint_t) * CHAR_BIT)
#define mk_uint_small_bits (sizeof(mk_uint_small_t) * CHAR_BIT)
#define mk_uint_bits_to_words(x) (((x) + (mk_uint_small_bits - 1)) / mk_uint_small_bits)
#define mk_uint_parts (mk_uint_bits_to_words(mk_uint_bits))


void mk_uint_zero(mk_uint_t* out)
{
	MK_ASSERT(out);

	int i;

	for(i = 0; i != mk_uint_parts; ++i)
	{
		mk_uint_small_zero(out->m_data + i);
	}
}

void mk_uint_one(mk_uint_t* out)
{
	MK_ASSERT(out);

	int i;

	mk_uint_small_one(out->m_data + 0);
	for(i = 1; i != mk_uint_parts; ++i)
	{
		mk_uint_small_zero(out->m_data + i);
	}
}

void mk_uint_from_int(mk_uint_t* out, unsigned in)
{
	MK_ASSERT(out);

	int parts;
	int i;

	parts = sizeof(in) / sizeof(mk_uint_small_t);
	parts = parts < mk_uint_parts ? parts : mk_uint_parts;
	for(i = 0; i != parts; ++i)
	{
		mk_uint_small_from_int(out->m_data + i, in >> (i * mk_uint_small_bits));
	}
	for(i = parts; i != mk_uint_parts; ++i)
	{
		mk_uint_small_zero(out->m_data + i);
	}
}


void mk_uint_or(mk_uint_t* out, mk_uint_t const* a, mk_uint_t const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	mk_uint_t r;
	int i;
	
	for(i = 0; i != mk_uint_parts; ++i)
	{
		mk_uint_small_or(r.m_data + i, a->m_data + i, b->m_data + i);
	}

	*out = r;
}

void mk_uint_and(mk_uint_t* out, mk_uint_t const* a, mk_uint_t const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	mk_uint_t r;
	int i;
	
	for(i = 0; i != mk_uint_parts; ++i)
	{
		mk_uint_small_and(r.m_data + i, a->m_data + i, b->m_data + i);
	}

	*out = r;
}

void mk_uint_xor(mk_uint_t* out, mk_uint_t const* a, mk_uint_t const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	mk_uint_t r;
	int i;
	
	for(i = 0; i != mk_uint_parts; ++i)
	{
		mk_uint_small_xor(r.m_data + i, a->m_data + i, b->m_data + i);
	}

	*out = r;
}


void mk_uint_shl(mk_uint_t* out, mk_uint_t const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < mk_uint_bits);

	mk_uint_t r;
	int parts;
	int bits;
	int rem;
	int i;
	mk_uint_small_t tmp;

	parts = n / mk_uint_small_bits;
	bits = n % mk_uint_small_bits;
	for(i = 0; i != parts; ++i)
	{
		mk_uint_small_zero(r.m_data + i);
	}
	if(bits == 0)
	{
		for(i = parts; i != mk_uint_parts; ++i)
		{
			r.m_data[i] = x->m_data[i - parts];
		}
		*out = r;
		return;
	}
	rem = mk_uint_small_bits - bits;
	mk_uint_small_shl(r.m_data + parts, x->m_data + 0, bits);
	for(i = parts + 1; i != mk_uint_parts; ++i)
	{
		mk_uint_small_shl(r.m_data + i, x->m_data + i - parts, bits);
		mk_uint_small_shr(&tmp, x->m_data + i - parts - 1, rem);
		mk_uint_small_or(r.m_data + i, r.m_data + i, &tmp);
	}

	*out = r;
}

void mk_uint_shr(mk_uint_t* out, mk_uint_t const* x, int n)
{
	MK_ASSERT(out);
	MK_ASSERT(x);
	MK_ASSERT(n >= 0 && n < mk_uint_bits);

	mk_uint_t r;
	int parts;
	int bits;
	int rem;
	int i;
	mk_uint_small_t tmp;

	parts = n / mk_uint_small_bits;
	bits = n % mk_uint_small_bits;
	for(i = 0; i != parts; ++i)
	{
		mk_uint_small_zero(r.m_data + mk_uint_parts - 1 - i);
	}
	if(bits == 0)
	{
		for(i = parts; i != mk_uint_parts; ++i)
		{
			r.m_data[mk_uint_parts - 1 - i] = x->m_data[mk_uint_parts - 1 - i + parts];
		}
		*out = r;
		return;
	}
	rem = mk_uint_small_bits - bits;
	mk_uint_small_shr(r.m_data + mk_uint_parts - 1 - parts, x->m_data + mk_uint_parts - 1, bits);
	for(i = parts + 1; i != mk_uint_parts; ++i)
	{
		mk_uint_small_shr(r.m_data + mk_uint_parts - 1 - i, x->m_data + mk_uint_parts - 1 - i + parts, bits);
		mk_uint_small_shl(&tmp, x->m_data + mk_uint_parts - 1 - i + parts + 1, rem);
		mk_uint_small_or(r.m_data + mk_uint_parts - 1 - i, r.m_data + mk_uint_parts - 1 - i, &tmp);
	}

	*out = r;
}


int mk_uint_lt(mk_uint_t const* a, mk_uint_t const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	int r;
	int i;
	int lt;
	int gt;

	for(i = 0; i != mk_uint_parts - 1; ++i)
	{
		lt = mk_uint_small_lt(a->m_data + mk_uint_parts - 1 - i, b->m_data + mk_uint_parts - 1 - i);
		if(lt)
		{
			return lt;
		}
		gt = mk_uint_small_lt(b->m_data + mk_uint_parts - 1 - i, a->m_data + mk_uint_parts - 1 - i);
		if(gt)
		{
			return !gt;
		}
	}
	r = mk_uint_small_lt(a->m_data + 0, b->m_data + 0);

	return r;
}

int mk_uint_le(mk_uint_t const* a, mk_uint_t const* b)
{
	MK_ASSERT(a);
	MK_ASSERT(b);

	int r;
	int i;
	int lt;
	int gt;

	for(i = 0; i != mk_uint_parts - 1; ++i)
	{
		lt = mk_uint_small_lt(a->m_data + mk_uint_parts - 1 - i, b->m_data + mk_uint_parts - 1 - i);
		if(lt)
		{
			return lt;
		}
		gt = mk_uint_small_lt(b->m_data + mk_uint_parts - 1 - i, a->m_data + mk_uint_parts - 1 - i);
		if(gt)
		{
			return !gt;
		}
	}
	r = mk_uint_small_le(a->m_data + 0, b->m_data + 0);

	return r;
}


void mk_uint_add(mk_uint_t* out, mk_uint_t const* a, mk_uint_t const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	mk_uint_t r;
	int i;
	int overflow;
	mk_uint_small_t one;

	overflow = 0;
	mk_uint_small_add(r.m_data + 0, a->m_data + 0, b->m_data + 0);
	for(i = 1; i != mk_uint_parts; ++i)
	{
		overflow =
			overflow == 0 ?
			(
				mk_uint_small_lt(r.m_data + i - 1, a->m_data + i - 1) ||
				mk_uint_small_lt(r.m_data + i - 1, b->m_data + i - 1)
			) :
			(
				mk_uint_small_le(r.m_data + i - 1, a->m_data + i - 1) ||
				mk_uint_small_le(r.m_data + i - 1, b->m_data + i - 1)
			);
		mk_uint_small_add(r.m_data + i, a->m_data + i, b->m_data + i);
		if(overflow)
		{
			mk_uint_small_one(&one);
			mk_uint_small_add(r.m_data + i, r.m_data + i, &one);
		}
	}

	*out = r;
}

void mk_uint_sub(mk_uint_t* out, mk_uint_t const* a, mk_uint_t const* b)
{
	MK_ASSERT(out);
	MK_ASSERT(a);
	MK_ASSERT(b);

	mk_uint_t r;
	int i;
	int overflow;
	mk_uint_small_t one;

	overflow = 0;
	mk_uint_small_sub(r.m_data + 0, a->m_data + 0, b->m_data + 0);
	for(i = 1; i != mk_uint_parts; ++i)
	{
		overflow =
			overflow == 0 ?
			mk_uint_small_lt(a->m_data + i - 1, b->m_data + i - 1) :
			mk_uint_small_le(a->m_data + i - 1, b->m_data + i - 1);
		mk_uint_small_sub(r.m_data + i, a->m_data + i, b->m_data + i);
		if(overflow)
		{
			mk_uint_small_one(&one);
			mk_uint_small_sub(r.m_data + i, r.m_data + i, &one);
		}
	}

	*out = r;
}


#undef mk_uint_bits
#undef mk_uint_small_bits
#undef mk_uint_bits_to_words
#undef mk_uint_parts
