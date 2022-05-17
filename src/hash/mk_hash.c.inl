#undef stringify
#undef include_base_impl
#undef include_base
#define stringify(x) #x
#define include_base_impl(x) stringify(base/mk_ ## x ## _base.h)
#define include_base(x) include_base_impl(x)


#include include_base(alg)
#include "block/mk_block.h.inl"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


#define concat3_impl(a, b, c) a ## b ## c
#define concat3(a, b, c) concat3_impl(a, b, c)


mk_jumbo void concat3(mk_hash_, alg, _init)(struct concat3(mk_, alg, _s)* alg)
{
	mk_assert(alg);

	concat3(mk_, alg, _base_init)(&alg->m_base);
	alg->m_idx = 0;
}

mk_jumbo void concat3(mk_hash_, alg, _append)(struct concat3(mk_, alg, _s)* alg, void const* msg, int msg_len)
{
	mk_assert(alg);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	concat3(mk_block_, alg, _append)(&alg->m_base, alg->m_block, &alg->m_idx, msg, msg_len);
}

mk_jumbo void concat3(mk_hash_, alg, _finish)(struct concat3(mk_, alg, _s)* alg, void* digest)
{
	mk_assert(alg);
	mk_assert(digest);

	concat3(mk_, alg, _base_finish)(&alg->m_base, alg->m_block, alg->m_idx, digest);
}


#undef stringify
#undef include_base_impl
#undef include_base
#undef concat3_impl
#undef concat3
