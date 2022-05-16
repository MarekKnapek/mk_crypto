#ifndef mk_include_guard_win_md5
#define mk_include_guard_win_md5


#include "../utils/mk_jumbo.h"

#include <windows.h>
#include <wincrypt.h>


struct mk_win_md5_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


mk_jumbo void mk_win_md5_init(struct mk_win_md5_s* win_md5);
mk_jumbo void mk_win_md5_append(struct mk_win_md5_s* win_md5, void const* msg, int msg_len);
mk_jumbo void mk_win_md5_finish(struct mk_win_md5_s* win_md5, void* digest);


#endif
