#undef stringify
#undef include_base_impl
#undef include_base
#define stringify(x) #x
#define include_base_impl(x) stringify(base/mk_ ## x ## _base.h)
#define include_base(x) include_base_impl(x)


#include include_base(alg)

#include "../utils/mk_jumbo.h"


#define concat3_impl(a, b, c) a ## b ## c
#define concat3(a, b, c) concat3_impl(a, b, c)


struct concat3(mk_, alg, _s)
{
	struct concat3(mk_, alg, _base_s) m_base;
	int m_idx;
	unsigned char m_block[concat3(mk_, alg, _base_block_len)];
};


mk_jumbo void concat3(mk_hash_, alg, _init)(struct concat3(mk_, alg, _s)* alg);
mk_jumbo void concat3(mk_hash_, alg, _append)(struct concat3(mk_, alg, _s)* alg, void const* msg, int msg_len);
mk_jumbo void concat3(mk_hash_, alg, _finish)(struct concat3(mk_, alg, _s)* alg, int digest_len, void* digest);


#undef stringify
#undef include_base_impl
#undef include_base
#undef concat3_impl
#undef concat3
