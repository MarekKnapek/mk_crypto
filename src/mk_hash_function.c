#include "mk_hash_function.h"

#include "mk_hash_fn.h"

#include "utils/mk_assert.h"
#include "utils/mk_jumbo.h"

#include <stddef.h> /* NULL */
#include <stdlib.h> /* malloc free */


#define mk_assert_type(type) mk_assert( \
	(type) == mk_hash_function_md2 || \
	(type) == mk_hash_function_md4 || \
	(type) == mk_hash_function_md5 || \
	(type) == mk_hash_function_sha1 || \
	(type) == mk_hash_function_sha2_224 || \
	(type) == mk_hash_function_sha2_256 || \
	(type) == mk_hash_function_sha2_384 || \
	(type) == mk_hash_function_sha2_512 || \
	(type) == mk_hash_function_sha2_512224 || \
	(type) == mk_hash_function_sha2_512256 || \
	(type) == mk_hash_function_sha3_224 || \
	(type) == mk_hash_function_sha3_256 || \
	(type) == mk_hash_function_sha3_384 || \
	(type) == mk_hash_function_sha3_512 || \
	0)


mk_jumbo mk_hash_function_h mk_hash_function_create(enum mk_hash_function_e type)
{
	struct mk_hash_fn_s* hash_fn;
	mk_hash_function_h hash_function;

	mk_assert_type(type);

	hash_fn = (struct mk_hash_fn_s*)malloc(sizeof(struct mk_hash_fn_s));
	if(!hash_fn)
	{
		hash_function.m_val = NULL;
		return hash_function;
	}
	mk_hash_fn_init(hash_fn, (enum mk_hash_fn_e)type);
	hash_function.m_val = hash_fn;
	return hash_function;
}

mk_jumbo int mk_hash_function_is_good(mk_hash_function_h hash_function)
{
	return !!hash_function.m_val;
}

mk_jumbo enum mk_hash_function_e mk_hash_function_get_type(mk_hash_function_h hash_function)
{
	mk_assert(!!hash_function.m_val);

	return (enum mk_hash_function_e)mk_hash_fn_get_type((struct mk_hash_fn_s*)hash_function.m_val);
}

mk_jumbo void mk_hash_function_append(mk_hash_function_h hash_function, void const* msg, int msg_len)
{
	mk_assert(!!hash_function.m_val);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	mk_hash_fn_append((struct mk_hash_fn_s*)hash_function.m_val, msg, msg_len);
}

mk_jumbo void mk_hash_function_finish(mk_hash_function_h hash_function, void* digest)
{
	mk_assert(!!hash_function.m_val);
	mk_assert(digest);

	mk_hash_fn_finish((struct mk_hash_fn_s*)hash_function.m_val, digest);
}

mk_jumbo void mk_hash_function_destroy(mk_hash_function_h hash_function)
{
	free((struct mk_hash_fn_s*)hash_function.m_val);
}


#undef mk_assert_type
