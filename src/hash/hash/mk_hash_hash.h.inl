#include "../base/mk_hash_base_hash.h.inl"

#include "../../utils/mk_jumbo.h"


#define concat3_impl(a, b, c) a ## b ## c
#define concat3(a, b, c) concat3_impl(a, b, c)


struct concat3(mk_hash_, alg, _s)
{
	struct concat3(mk_hash_base_, alg, _s) m_base;
	int m_idx;
	unsigned char m_block[concat3(mk_hash_base_, alg, _block_len)];
};


mk_jumbo void concat3(mk_hash_, alg, _init)(struct concat3(mk_hash_, alg, _s)* self);
mk_jumbo void concat3(mk_hash_, alg, _append)(struct concat3(mk_hash_, alg, _s)* self, void const* msg, int msg_len);
mk_jumbo void concat3(mk_hash_, alg, _finish)(struct concat3(mk_hash_, alg, _s)* self, void* digest);


#undef concat3_impl
#undef concat3

#undef alg_id
#undef alg
