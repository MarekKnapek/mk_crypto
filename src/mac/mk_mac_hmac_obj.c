#include "mk_mac_hmac_obj.h"

#include "../hash/base/mk_hash_base_enum.h"
#include "hmac/mk_mac_hmac_hash.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_clobber.h"
#include "../utils/mk_jumbo.h"

#include <stddef.h> /* NULL */
#include <stdlib.h> /* malloc free */


#define mk_mac_hmac_obj_is_good_macro(hmac) ((!!((hmac).m_val)) && mk_hash_e_is_good(*((enum mk_hash_e*)((hmac).m_val))))


#include "../hash/base/mk_hash_base_xmacro_def.h"
#define xtypebig(alg) concat(concat(struct mk_mac_hmac_obj_, alg), _s)
#define xtypesmol(alg) concat(concat(struct mk_mac_hmac_, alg), _s)
#define xcontent(alg) \
	xtypebig(alg) \
	{ \
		enum mk_hash_e m_tag; \
		xtypesmol(alg) m_val; \
	};
xmacro
#undef xtypebig
#undef xtypesmol
#undef xcontent
#include "../hash/base/mk_hash_base_xmacro_undef.h"


mk_jumbo mk_mac_hmac_obj_h mk_mac_hmac_obj_create(enum mk_hash_e type, void const* key, int key_len)
{
	mk_mac_hmac_obj_h hmac;

	mk_assert(mk_hash_e_is_good(type));
	mk_assert(key || key_len == 0);
	mk_assert(key_len >= 0);

	mk_clobber(&hmac);
	switch(type)
	{
		#include "../hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xtype(alg) concat(concat(struct mk_mac_hmac_obj_, alg), _s)
		#define xinit(alg) concat(concat(mk_mac_hmac_, alg), _init)
		#define xcontent(alg) \
			case xenum(alg): \
			{ \
				hmac.m_val = malloc((int)(sizeof(xtype(alg)))); \
				if(hmac.m_val) \
				{ \
					((xtype(alg)*)(hmac.m_val))->m_tag = type; \
					xinit(alg)(&(((xtype(alg)*)(hmac.m_val))->m_val), key, key_len); \
				} \
			}; \
			break;
		xmacro
		#undef xenum
		#undef xtype
		#undef xinit
		#undef xcontent
		#include "../hash/base/mk_hash_base_xmacro_undef.h"
	}
	mk_assert(mk_mac_hmac_obj_is_good_macro(hmac));
	return hmac;
}

mk_jumbo int mk_mac_hmac_obj_is_good(mk_mac_hmac_obj_h hmac)
{
	return mk_mac_hmac_obj_is_good_macro(hmac);
}

mk_jumbo enum mk_hash_e mk_mac_hmac_obj_get_type(mk_mac_hmac_obj_h hmac)
{
	mk_assert(mk_mac_hmac_obj_is_good_macro(hmac));

	return *(enum mk_hash_e*)hmac.m_val;
}

mk_jumbo void mk_mac_hmac_obj_reinit(mk_mac_hmac_obj_h hmac, void const* key, int key_len)
{
	enum mk_hash_e type;

	mk_assert(mk_mac_hmac_obj_is_good_macro(hmac));

	type = mk_mac_hmac_obj_get_type(hmac);
	mk_assert(mk_hash_e_is_good(type));
	switch(type)
	{
		#include "../hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xtype(alg) concat(concat(struct mk_mac_hmac_obj_, alg), _s)
		#define xinit(alg) concat(concat(mk_mac_hmac_, alg), _init)
		#define xcontent(alg) case xenum(alg): xinit(alg)(&(((xtype(alg)*)(hmac.m_val))->m_val), key, key_len); break;
		xmacro
		#undef xenum
		#undef xtype
		#undef xinit
		#undef xcontent
		#include "../hash/base/mk_hash_base_xmacro_undef.h"
	}
}

mk_jumbo void mk_mac_hmac_obj_append(mk_mac_hmac_obj_h hmac, void const* msg, int msg_len)
{
	enum mk_hash_e type;

	mk_assert(mk_mac_hmac_obj_is_good_macro(hmac));
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	type = mk_mac_hmac_obj_get_type(hmac);
	mk_assert(mk_hash_e_is_good(type));
	switch(type)
	{
		#include "../hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xtype(alg) concat(concat(struct mk_mac_hmac_obj_, alg), _s)
		#define xappend(alg) concat(concat(mk_mac_hmac_, alg), _append)
		#define xcontent(alg) case xenum(alg): xappend(alg)(&(((xtype(alg)*)(hmac.m_val))->m_val), msg, msg_len); break;
		xmacro
		#undef xenum
		#undef xtype
		#undef xappend
		#undef xcontent
		#include "../hash/base/mk_hash_base_xmacro_undef.h"
	}
}

mk_jumbo void mk_mac_hmac_obj_finish(mk_mac_hmac_obj_h hmac, void* digest)
{
	enum mk_hash_e type;

	mk_assert(mk_mac_hmac_obj_is_good_macro(hmac));
	mk_assert(digest);

	type = mk_mac_hmac_obj_get_type(hmac);
	mk_assert(mk_hash_e_is_good(type));
	switch(type)
	{
		#include "../hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xtype(alg) concat(concat(struct mk_mac_hmac_obj_, alg), _s)
		#define xfinish(alg) concat(concat(mk_mac_hmac_, alg), _finish)
		#define xcontent(alg) case xenum(alg): xfinish(alg)(&(((xtype(alg)*)(hmac.m_val))->m_val), digest); break;
		xmacro
		#undef xenum
		#undef xtype
		#undef xinit
		#undef xcontent
		#include "../hash/base/mk_hash_base_xmacro_undef.h"
	}
}

mk_jumbo void mk_mac_hmac_obj_destroy(mk_mac_hmac_obj_h hmac)
{
	free(hmac.m_val);
}


#undef mk_mac_hmac_obj_is_good_macro
