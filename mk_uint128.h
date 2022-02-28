#ifndef MK_INCLUDE_GUARD_UINT128
#define MK_INCLUDE_GUARD_UINT128


#include <stddef.h> /* size_t */
#include <stdint.h> /* uint64_t */ /* C99 */


struct mk_uint128_s
{
	uint64_t m_lo;
	uint64_t m_hi;
};


void mk_uint128_zero(struct mk_uint128_s* res);
void mk_uint128_add(struct mk_uint128_s* res, struct mk_uint128_s const* a, struct mk_uint128_s const* b);
void mk_uint128_add_size(struct mk_uint128_s* res, struct mk_uint128_s const* a, size_t b);
void mk_uint128_shl(struct mk_uint128_s* res, struct mk_uint128_s const* x, int n);


#endif
