#include "mk_hash_function.h"

#include "hash/hash/mk_hash_hash.h"

#include "utils/mk_assert.h"
#include "utils/mk_clobber.h"
#include "utils/mk_jumbo.h"

#include <stddef.h> /* NULL */
#include <stdlib.h> /* malloc free */


#define mk_hash_function_is_good_macro(hash_function) ((!!((hash_function).m_val)) && mk_hash_e_is_good(*((enum mk_hash_e*)((hash_function).m_val))))


#include "hash/base/mk_hash_base_xmacro_def.h"
#define xenum(alg) concat(enum mk_hash_function_, alg)
#define xtype(alg) concat(concat(struct mk_hash_function_, alg), _s)
#define xtype_smol(alg) concat(concat(struct mk_hash_hash_, alg), _s)
#define xcontent(alg) \
	xtype(alg) \
	{ \
		xenum(alg) m_tag; \
		xtype_smol(alg) m_val; \
	};
xmacro
#undef xenum
#undef xtype
#undef xtype_smol
#undef xcontent
#include "hash/base/mk_hash_base_xmacro_undef.h"


mk_jumbo mk_hash_function_h mk_hash_function_create(enum mk_hash_e type)
{
	mk_hash_function_h hash_function;

	mk_assert(mk_hash_e_is_good(type));

	mk_clobber(&hash_function);
	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xtype(alg) concat(concat(struct mk_hash_function_, alg), _s)
		#define xinit(alg) concat(concat(mk_hash_hash_, alg), _init)
		#define xcontent(alg) \
			case xenum(alg): \
			{ \
				void* mem; \
				xtype(alg)* obj; \
				(void)0; \
				mem = malloc(sizeof(xtype(alg))); \
				if(mem) \
				{ \
					obj = (xtype(alg)*)mem; \
					obj->m_tag = type; \
					xinit(alg)(&obj->m_val); \
				} \
				hash_function.m_val = mem; \
				return hash_function; \
			} \
			break;
		xmacro
		#undef xenum
		#undef xtype
		#undef xinit
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
	return hash_function;
}

mk_jumbo int mk_hash_function_is_good(mk_hash_function_h hash_function)
{
	return mk_hash_function_is_good_macro(hash_function);
}

mk_jumbo enum mk_hash_e mk_hash_function_get_type(mk_hash_function_h hash_function)
{
	mk_assert(mk_hash_function_is_good_macro(hash_function));

	return *(enum mk_hash_e*)(hash_function.m_val);
}

mk_jumbo void mk_hash_function_reinit(mk_hash_function_h hash_function)
{
	enum mk_hash_e type;

	mk_assert(mk_hash_function_is_good_macro(hash_function));

	type = mk_hash_function_get_type(hash_function);
	mk_assert(mk_hash_e_is_good(type));
	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xtype(alg) concat(concat(struct mk_hash_function_, alg), _s)
		#define xinit(alg) concat(concat(mk_hash_hash_, alg), _init)
		#define xcontent(alg) \
			case xenum(alg): \
			{ \
				void* mem; \
				xtype(alg)* obj; \
				(void)0; \
				mem = hash_function.m_val; \
				obj = (xtype(alg)*)mem; \
				xinit(alg)(&obj->m_val); \
			} \
			break;
		xmacro
		#undef xenum
		#undef xtype
		#undef xinit
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
}

mk_jumbo void mk_hash_function_append(mk_hash_function_h hash_function, void const* msg, int msg_len)
{
	enum mk_hash_e type;

	mk_assert(mk_hash_function_is_good_macro(hash_function));
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	type = mk_hash_function_get_type(hash_function);
	mk_assert(mk_hash_e_is_good(type));
	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xtype(alg) concat(concat(struct mk_hash_function_, alg), _s)
		#define xtypesmol(alg) concat(concat(struct mk_hash_hash_, alg), _s)
		#define xappend(alg) concat(concat(mk_hash_hash_, alg), _append)
		#define xcontent(alg) \
			case xenum(alg): \
			{ \
				void* mem; \
				xtype(alg)* hash_fun; \
				xtypesmol(alg)* hash; \
				((void)0); \
				mem = hash_function.m_val; \
				hash_fun = (xtype(alg)*)mem; \
				hash = &hash_fun->m_val; \
				xappend(alg)(hash, msg, msg_len); \
			} \
			break;
		xmacro
		#undef xenum
		#undef xtype
		#undef xtypesmol
		#undef xappend
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
}

mk_jumbo void mk_hash_function_finish(mk_hash_function_h hash_function, void* digest)
{
	enum mk_hash_e type;
	
	mk_assert(mk_hash_function_is_good_macro(hash_function));
	mk_assert(digest);

	type = mk_hash_function_get_type(hash_function);
	mk_assert(mk_hash_e_is_good(type));
	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xtype(alg) concat(concat(struct mk_hash_function_, alg), _s)
		#define xtypesmol(alg) concat(concat(struct mk_hash_hash_, alg), _s)
		#define xfinish(alg) concat(concat(mk_hash_hash_, alg), _finish)
		#define xcontent(alg) \
			case xenum(alg): \
			{ \
				void* mem; \
				xtype(alg)* hash_fun; \
				xtypesmol(alg)* hash; \
				((void)0); \
				mem = hash_function.m_val; \
				hash_fun = (xtype(alg)*)mem; \
				hash = &hash_fun->m_val; \
				xfinish(alg)(hash, digest); \
			} \
			break;
		xmacro
		#undef xenum
		#undef xtype
		#undef xtypesmol
		#undef xfinish
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
}

mk_jumbo void mk_hash_function_destroy(mk_hash_function_h hash_function)
{
	mk_assert(mk_hash_function_is_good_macro(hash_function) || !hash_function.m_val);

	free(hash_function.m_val);
}


#undef mk_hash_function_is_good_macro
