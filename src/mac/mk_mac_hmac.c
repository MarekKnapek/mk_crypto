#include "mk_mac_hmac.h"

#include "../hash/base/mk_hash_base_enum.h"
#include "hmac/mk_mac_hmac_hash.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"


mk_jumbo void mk_mac_hmac_init(enum mk_hash_e type, union mk_mac_hmac_pu hmac, void const* key, int key_len)
{
	mk_assert(mk_hash_e_is_good(type));
	mk_assert(hmac.m_u);
	mk_assert(key || key_len == 0);
	mk_assert(key_len >= 0);

	switch(type)
	{
		#include "../hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xvarname(alg) concat(m_, alg)
		#define xinit(alg) concat(concat(mk_mac_hmac_, alg), _init)
		#define xcontent(alg) case xenum(alg): mk_assert(hmac.xvarname(alg)); xinit(alg)(hmac.xvarname(alg), key, key_len); break;
		xmacro
		#undef xenum
		#undef xvarname
		#undef xinit
		#undef xcontent
		#include "../hash/base/mk_hash_base_xmacro_undef.h"
	}
}

mk_jumbo void mk_mac_hmac_append(enum mk_hash_e type, union mk_mac_hmac_pu hmac, void const* msg, int msg_len)
{
	mk_assert(mk_hash_e_is_good(type));
	mk_assert(hmac.m_u);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	switch(type)
	{
		#include "../hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xvarname(alg) concat(m_, alg)
		#define xappend(alg) concat(concat(mk_mac_hmac_, alg), _append)
		#define xcontent(alg) case xenum(alg): mk_assert(hmac.xvarname(alg)); xappend(alg)(hmac.xvarname(alg), msg, msg_len); break;
		xmacro
		#undef xenum
		#undef xvarname
		#undef xappend
		#undef xcontent
		#include "../hash/base/mk_hash_base_xmacro_undef.h"
	}
}

mk_jumbo void mk_mac_hmac_finish(enum mk_hash_e type, union mk_mac_hmac_pu hmac, void* digest)
{
	mk_assert(mk_hash_e_is_good(type));
	mk_assert(hmac.m_u);
	mk_assert(digest);

	switch(type)
	{
		#include "../hash/base/mk_hash_base_xmacro_def.h"
		#define xenum(alg) concat(mk_hash_e_, alg)
		#define xvarname(alg) concat(m_, alg)
		#define xfinish(alg) concat(concat(mk_mac_hmac_, alg), _finish)
		#define xcontent(alg) case xenum(alg): mk_assert(hmac.xvarname(alg)); xfinish(alg)(hmac.xvarname(alg), digest); break;
		xmacro
		#undef xenum
		#undef xvarname
		#undef xfinish
		#undef xcontent
		#include "../hash/base/mk_hash_base_xmacro_undef.h"
	}
}
