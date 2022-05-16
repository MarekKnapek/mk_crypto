#ifndef mk_include_guard_win_md2
#define mk_include_guard_win_md2


#include "../utils/mk_jumbo.h"

#include <windows.h>
#include <wincrypt.h>


struct mk_win_md2_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


mk_jumbo void mk_win_md2_init(struct mk_win_md2_s* win_md2);
mk_jumbo void mk_win_md2_append(struct mk_win_md2_s* win_md2, void const* msg, int msg_len);
mk_jumbo void mk_win_md2_finish(struct mk_win_md2_s* win_md2, void* digest);


#endif
