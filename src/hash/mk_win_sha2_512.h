#ifndef mk_include_guard_win_sha2_512
#define mk_include_guard_win_sha2_512


#include "../utils/mk_jumbo.h"

#include <windows.h>
#include <wincrypt.h>


struct mk_win_sha2_512_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


mk_jumbo void mk_win_sha2_512_init(struct mk_win_sha2_512_s* win_sha2_512);
mk_jumbo void mk_win_sha2_512_append(struct mk_win_sha2_512_s* win_sha2_512, void const* msg, int msg_len);
mk_jumbo void mk_win_sha2_512_finish(struct mk_win_sha2_512_s* win_sha2_512, void* digest);


#endif
