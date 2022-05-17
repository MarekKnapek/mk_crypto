#undef stringify
#undef include_base_impl
#undef include_base
#define stringify(x) #x
#define include_base_impl(x) stringify(../base/mk_ ## x ## _base.h)
#define include_base(x) include_base_impl(x)


#include include_base(alg)

#include "../../utils/mk_jumbo.h"


#define concat3_impl(a, b, c) a ## b ## c
#define concat3(a, b, c) concat3_impl(a, b, c)


mk_jumbo void concat3(mk_, alg, _block_append)(struct concat3(mk_, alg, _base_s)* alg_base, void* block, int* pidx, void const* msg, int msg_len);


#undef stringify
#undef include_base_impl
#undef include_bas
#undef concat3_impl
#undef concat3
