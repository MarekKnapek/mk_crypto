#include "../utils/mk_jumbo.h"

#include <windows.h>
#include <wincrypt.h>


#define concat3_impl(a, b, c) a ## b ## c
#define concat3(a, b, c) concat3_impl(a, b, c)


struct concat3(mk_hash_win_, alg, _s)
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


mk_jumbo void concat3(mk_hash_win_, alg, _init)(struct concat3(mk_hash_win_, alg, _s)* alg);
mk_jumbo void concat3(mk_hash_win_, alg, _append)(struct concat3(mk_hash_win_, alg, _s)* alg, void const* msg, int msg_len);
mk_jumbo void concat3(mk_hash_win_, alg, _finish)(struct concat3(mk_hash_win_, alg, _s)* alg, void* digest);


#undef concat3_impl
#undef concat3
