#ifndef mk_include_guard_hash_fn
#define mk_include_guard_hash_fn


#include "hash/hash/mk_hash_hash.h"
#include "hash/base/mk_hash_base_enum.h"

#include "utils/mk_jumbo.h"


union mk_hash_fn_u
{
	#include "hash/base/mk_hash_base_xmacro_def.h"
	#define xtype(alg) concat(concat(struct mk_hash_hash_, alg), _s)
	#define xvarname(alg) concat(m_, alg)
	#define xcontent(alg) xtype(alg) xvarname(alg);
	xmacro
	#undef xtype
	#undef xvarname
	#undef xcontent
	#include "hash/base/mk_hash_base_xmacro_undef.h"
};

struct mk_hash_fn_s
{
	enum mk_hash_e m_tag;
	union mk_hash_fn_u m_val;
};


mk_jumbo void mk_hash_fn_init(struct mk_hash_fn_s* hash_fn, enum mk_hash_e type);
mk_jumbo enum mk_hash_e mk_hash_fn_get_type(struct mk_hash_fn_s* hash_fn);
mk_jumbo void mk_hash_fn_append(struct mk_hash_fn_s* hash_fn, void const* msg, int msg_len);
mk_jumbo void mk_hash_fn_finish(struct mk_hash_fn_s* hash_fn, void* digest);


#endif
