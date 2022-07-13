#define alg_id mk_hash_xof_alg_id
#include "../base/mk_hash_base_xof.h"
#undef alg_id

#define mk_hash_block_xof_alg_id mk_hash_xof_alg_id
#include "../../hash/block/mk_hash_block_xof.h.inl"
#undef mk_hash_block_xof_alg_id

#include "../../utils/mk_assert.h"
#include "../../utils/mk_jumbo.h"


#define alg_id mk_hash_xof_alg_id
#include "../base/mk_hash_base_alg_name_def.h"
#undef alg_id
#include "../../utils/mk_concat_def.h"


#define base_s concat(concat(struct mk_hash_base_hash_, alg_name), _s)
#define block_len concat(concat(mk_hash_base_hash_, alg_name), _block_len)
#define base_init concat(concat(mk_hash_base_xof_, alg_name), _init)
#define block_append concat(concat(mk_hash_block_xof_, alg_name), _append)
#define base_finish concat(concat(mk_hash_base_xof_, alg_name), _finish)
#define xof_s concat(concat(struct mk_hash_xof_, alg_name), _s)
#define init concat(concat(mk_hash_xof_, alg_name), _init)
#define append concat(concat(mk_hash_xof_, alg_name), _append)
#define finish concat(concat(mk_hash_xof_, alg_name), _finish)


mk_jumbo void init(xof_s* self)
{
	mk_assert(self);

	base_init(&self->m_base);
	self->m_idx = 0;
}

mk_jumbo void append(xof_s* self, void const* msg, int msg_len)
{
	mk_assert(self);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	block_append(&self->m_base, self->m_block, &self->m_idx, msg, msg_len);
}

mk_jumbo void finish(xof_s* self, int digest_len, void* digest)
{
	mk_assert(self);
	mk_assert(digest_len > 0);
	mk_assert(digest);

	base_finish(&self->m_base, self->m_block, self->m_idx, digest_len, digest);
}


#undef base_s
#undef block_len
#undef base_init
#undef block_append
#undef base_finish
#undef xof_s
#undef init
#undef append
#undef finish

#undef concat_
#undef concat


#include "../base/mk_hash_base_alg_name_undef.h"
#include "../../utils/mk_concat_undef.h"
