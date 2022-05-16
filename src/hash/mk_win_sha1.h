#ifndef mk_include_guard_win_sha1
#define mk_include_guard_win_sha1


#include "../utils/mk_jumbo.h"

#include <windows.h>
#include <wincrypt.h>


struct mk_win_sha1_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


mk_jumbo void mk_win_sha1_init(struct mk_win_sha1_s* win_sha1);
mk_jumbo void mk_win_sha1_append(struct mk_win_sha1_s* win_sha1, void const* msg, int msg_len);
mk_jumbo void mk_win_sha1_finish(struct mk_win_sha1_s* win_sha1, void* digest);


#endif
