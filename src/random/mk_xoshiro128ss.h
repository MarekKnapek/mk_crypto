#ifndef mk_include_guard_xoshiro128ss
#define mk_include_guard_xoshiro128ss


#include "../../../mk_int/src/exact/mk_uint_32.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct xoshiro128ss_s
{
	struct mk_uint32_s m_state[4];
};


mk_extern_c void mk_xoshiro128ss_seed(struct xoshiro128ss_s* self, void const* buffer);
mk_extern_c struct mk_uint32_s mk_xoshiro128ss_next(struct xoshiro128ss_s* self);


#undef mk_extern_c


#endif
