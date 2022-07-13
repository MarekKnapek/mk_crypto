#include "mk_hash.h"

#include "hash/hash/mk_hash_hash.h"

#include "utils/mk_assert.h"
#include "utils/mk_jumbo.h"


mk_jumbo int mk_hash_get_block_len(enum mk_hash_e type)
{
	mk_assert(mk_hash_e_is_good(type));

	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xblocklen(alg) concat(concat(mk_hash_base_hash_, alg), _block_len)
		#define xcontent(alg) case xenum(alg): return xblocklen(alg); break;
		xmacro
		#undef xenum
		#undef xblocklen
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
	return 0;
}

mk_jumbo int mk_hash_get_digest_len(enum mk_hash_e type)
{
	mk_assert(mk_hash_e_is_good(type));

	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xdigestlen(alg) concat(concat(mk_hash_base_hash_, alg), _digest_len)
		#define xcontent(alg) case xenum(alg): return xdigestlen(alg); break;
		xmacro
		#undef xenum
		#undef xdigestlen
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
	return 0;
}

mk_jumbo char const* mk_hash_get_name(enum mk_hash_e type)
{
	mk_assert(mk_hash_e_is_good(type));

	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xname(alg) concat(concat(mk_hash_base_hash_, alg), _name)
		#define xcontent(alg) case xenum(alg): return xname(alg); break;
		xmacro
		#undef xenum
		#undef xxname
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
	return NULL;
}

mk_jumbo int mk_hash_get_name_len(enum mk_hash_e type)
{
	mk_assert(mk_hash_e_is_good(type));

	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xnamelen(alg) concat(concat(mk_hash_base_hash_, alg), _name_len)
		#define xcontent(alg) case xenum(alg): return xnamelen(alg); break;
		xmacro
		#undef xenum
		#undef xxnamelen
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
	return 0;
}


mk_jumbo void mk_hash_init(enum mk_hash_e type, void* hash)
{
	mk_assert(mk_hash_e_is_good(type));
	mk_assert(hash);

	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xinit(alg) concat(concat(mk_hash_hash_, alg), _init)
		#define xtype(alg) struct concat(concat(mk_hash_hash_, alg), _s)
		#define xcontent(alg) case xenum(alg): xinit(alg)((xtype(alg)*)hash); break;
		xmacro
		#undef xenum
		#undef xinit
		#undef xtype
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
}

mk_jumbo void mk_hash_append(enum mk_hash_e type, void* hash, void const* msg, int msg_len)
{
	mk_assert(mk_hash_e_is_good(type));
	mk_assert(hash);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xappend(alg) concat(concat(mk_hash_hash_, alg), _append)
		#define xtype(alg) struct concat(concat(mk_hash_hash_, alg), _s)
		#define xcontent(alg) case xenum(alg): xappend(alg)((xtype(alg)*)hash, msg, msg_len); break;
		xmacro
		#undef xenum
		#undef xappend
		#undef xtype
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
}

mk_jumbo void mk_hash_finish(enum mk_hash_e type, void* hash, void* digest)
{
	mk_assert(mk_hash_e_is_good(type));
	mk_assert(hash);
	mk_assert(digest);

	switch(type)
	{
		#include "hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xfinish(alg) concat(concat(mk_hash_hash_, alg), _finish)
		#define xtype(alg) struct concat(concat(mk_hash_hash_, alg), _s)
		#define xcontent(alg) case xenum(alg): xfinish(alg)((xtype(alg)*)hash, digest); break;
		xmacro
		#undef xenum
		#undef xfinish
		#undef xtype
		#undef xcontent
		#include "hash/base/mk_hash_base_xmacro_undef.h"
	}
}


#undef mk_assert_type
