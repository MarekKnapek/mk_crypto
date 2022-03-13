#ifndef MK_INCLUDE_GUARD_UINT128_
#define MK_INCLUDE_GUARD_UINT128_


#include <stddef.h> /* size_t */
#include <stdint.h> /* uint64_t */ /* C99 */


struct mk_uint128_s_
{
	uint64_t m_lo;
	uint64_t m_hi;
};


void mk_uint128_zero_(struct mk_uint128_s_* res);
void mk_uint128_add_(struct mk_uint128_s_* res, struct mk_uint128_s_ const* a, struct mk_uint128_s_ const* b);
void mk_uint128_add_size_(struct mk_uint128_s_* res, struct mk_uint128_s_ const* a, size_t b);
void mk_uint128_shl_(struct mk_uint128_s_* res, struct mk_uint128_s_ const* x, int n);


#endif
