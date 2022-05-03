#include "mk_hash_function.h"

#include "mk_hash_fn.h"

#include <stdlib.h> /* malloc free */


mk_hash_function_h mk_hash_function_create(enum mk_hash_function_e id)
{
	struct mk_hash_fn_s* hash_fn;

	hash_fn = malloc(sizeof(struct mk_hash_fn_s));
	if(hash_fn)
	{
		mk_hash_fn_init(hash_fn, (enum mk_hash_fn_e)id);
	}

	return (mk_hash_function_h)hash_fn;
}

enum mk_hash_function_e mk_hash_function_get_id(mk_hash_function_h hf)
{
	return (enum mk_hash_function_e)((struct mk_hash_fn_s*)hf)->m_id;
}

int mk_hash_function_get_block_len(mk_hash_function_h hf)
{
	return mk_hash_fn_get_block_len(((struct mk_hash_fn_s*)hf)->m_id);
}

int mk_hash_function_get_digest_len(mk_hash_function_h hf)
{
	return mk_hash_fn_get_digest_len(((struct mk_hash_fn_s*)hf)->m_id);
}

void mk_hash_function_reinit(mk_hash_function_h hf, enum mk_hash_function_e id)
{
	mk_hash_fn_init((struct mk_hash_fn_s*)hf, (enum mk_hash_fn_e)id);
}

void mk_hash_function_append(mk_hash_function_h hf, void const* msg, size_t msg_len_bytes)
{
	mk_hash_fn_append((struct mk_hash_fn_s*)hf, msg, msg_len_bytes);
}

void mk_hash_function_finish(mk_hash_function_h hf, void* digest)
{
	mk_hash_fn_finish((struct mk_hash_fn_s*)hf, digest);
}

void mk_hash_function_destroy(mk_hash_function_h hf)
{
	free((struct mk_hash_fn_s*)hf);
}
