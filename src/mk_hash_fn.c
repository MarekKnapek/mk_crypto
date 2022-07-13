#include "mk_hash_fn.h"

#include "mk_hash.h"

#include "utils/mk_assert.h"
#include "utils/mk_jumbo.h"


mk_jumbo void mk_hash_fn_init(struct mk_hash_fn_s* hash_fn, enum mk_hash_e type)
{
	mk_assert(hash_fn);
	mk_assert(mk_hash_e_is_good(type));

	hash_fn->m_tag = type;
	mk_hash_init(type, &hash_fn->m_val);
}

mk_jumbo enum mk_hash_fn_e mk_hash_fn_get_type(struct mk_hash_fn_s* hash_fn)
{
	mk_assert(hash_fn);
	mk_assert(mk_hash_e_is_good(hash_fn->m_tag));

	return hash_fn->m_tag;
}

mk_jumbo void mk_hash_fn_append(struct mk_hash_fn_s* hash_fn, void const* msg, int msg_len)
{
	mk_assert(hash_fn);
	mk_assert(mk_hash_e_is_good(hash_fn->m_tag));
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_hash_append(hash_fn->m_tag, &hash_fn->m_val, msg, msg_len);
}

mk_jumbo void mk_hash_fn_finish(struct mk_hash_fn_s* hash_fn, void* digest)
{
	mk_assert(hash_fn);
	mk_assert(mk_hash_e_is_good(hash_fn->m_tag));
	mk_assert(digest);

	mk_hash_finish(hash_fn->m_tag, &hash_fn->m_val, digest);
}
