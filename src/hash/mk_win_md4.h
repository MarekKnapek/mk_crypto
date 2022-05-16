#ifndef mk_include_guard_win_md4
#define mk_include_guard_win_md4


#include "../utils/mk_jumbo.h"

#include <windows.h>
#include <wincrypt.h>


struct mk_win_md4_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


mk_jumbo void mk_win_md4_init(struct mk_win_md4_s* win_md4);
mk_jumbo void mk_win_md4_append(struct mk_win_md4_s* win_md4, void const* msg, int msg_len);
mk_jumbo void mk_win_md4_finish(struct mk_win_md4_s* win_md4, void* digest);


#endif
