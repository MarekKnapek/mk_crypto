#include "../base/mk_hash_base_xof.h.inl"
#include "../block/mk_hash_block.h.inl"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_jumbo.h"


#define concat3_impl(a, b, c) a ## b ## c
#define concat3(a, b, c) concat3_impl(a, b, c)


mk_jumbo void concat3(mk_hash_, alg, _init)(struct concat3(mk_hash_, alg, _s)* self)
{
	mk_assert(self);

	concat3(mk_hash_base_, alg, _init)(&self->m_base);
	self->m_idx = 0;
}

mk_jumbo void concat3(mk_hash_, alg, _append)(struct concat3(mk_hash_, alg, _s)* self, void const* msg, int msg_len)
{
	mk_assert(self);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	concat3(mk_hash_block_, alg, _append)(&self->m_base, self->m_block, &self->m_idx, msg, msg_len);
}

mk_jumbo void concat3(mk_hash_, alg, _finish)(struct concat3(mk_hash_, alg, _s)* self, int digest_len, void* digest)
{
	mk_assert(self);
	mk_assert(digest_len > 0);
	mk_assert(digest);

	concat3(mk_hash_base_, alg, _finish)(&self->m_base, self->m_block, self->m_idx, digest_len, digest);
}


#undef concat3_impl
#undef concat3
