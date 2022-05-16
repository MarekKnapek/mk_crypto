#ifndef mk_include_guard_win_sha2_384
#define mk_include_guard_win_sha2_384


#include "../utils/mk_jumbo.h"

#include <windows.h>
#include <wincrypt.h>


struct mk_win_sha2_384_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


mk_jumbo void mk_win_sha2_384_init(struct mk_win_sha2_384_s* win_sha2_384);
mk_jumbo void mk_win_sha2_384_append(struct mk_win_sha2_384_s* win_sha2_384, void const* msg, int msg_len);
mk_jumbo void mk_win_sha2_384_finish(struct mk_win_sha2_384_s* win_sha2_384, void* digest);


#endif
