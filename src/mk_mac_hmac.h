#ifndef mk_include_guard_mac_hmac
#define mk_include_guard_mac_hmac


#include "hash/base/mk_hash_base_enum.h"
#include "mac/hmac/mk_mac_hmac_hash.h"


union mk_mac_hmac_u
{
	#include "hash/base/mk_hash_base_xmacro_def.h"
	#define xtype(alg) concat(concat(struct mk_mac_hmac_, alg), _s)
	#define xvarname(alg) concat(m_, alg)
	#define xcontent(alg) xtype(alg) xvarname(alg);
	xmacro
	#undef xtype
	#undef xvarname
	#undef xcontent
	#include "hash/base/mk_hash_base_xmacro_undef.h"
};

union mk_mac_hmac_pu
{
	union mk_mac_hmac_u* m_u;
	#include "hash/base/mk_hash_base_xmacro_def.h"
	#define xtype(alg) concat(concat(struct mk_mac_hmac_, alg), _s)
	#define xvarname(alg) concat(m_, alg)
	#define xcontent(alg) xtype(alg)* xvarname(alg);
	xmacro
	#undef xtype
	#undef xvarname
	#undef xcontent
	#include "hash/base/mk_hash_base_xmacro_undef.h"
};


mk_jumbo void mk_mac_hmac_init(enum mk_hash_e type, union mk_mac_hmac_pu hmac, void const* key, int key_len);
mk_jumbo void mk_mac_hmac_append(enum mk_hash_e type, union mk_mac_hmac_pu hmac, void const* msg, int msg_len);
mk_jumbo void mk_mac_hmac_finish(enum mk_hash_e type, union mk_mac_hmac_pu hmac, void* digest);


#endif
