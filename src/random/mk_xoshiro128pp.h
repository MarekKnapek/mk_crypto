#ifndef mk_include_guard_xoshiro128pp
#define mk_include_guard_xoshiro128pp


#include "../../../mk_int/src/exact/mk_uint_32.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct xoshiro128pp_s
{
	struct mk_uint32_s m_state[4];
};


mk_extern_c void mk_xoshiro128pp_seed(struct xoshiro128pp_s* self, void const* buffer);
mk_extern_c struct mk_uint32_s mk_xoshiro128pp_next(struct xoshiro128pp_s* self);


#undef mk_extern_c


#endif
