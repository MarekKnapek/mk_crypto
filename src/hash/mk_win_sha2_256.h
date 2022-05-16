#ifndef mk_include_guard_win_sha2_256
#define mk_include_guard_win_sha2_256


#include "../utils/mk_jumbo.h"

#include <windows.h>
#include <wincrypt.h>


struct mk_win_sha2_256_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


mk_jumbo void mk_win_sha2_256_init(struct mk_win_sha2_256_s* win_sha2_256);
mk_jumbo void mk_win_sha2_256_append(struct mk_win_sha2_256_s* win_sha2_256, void const* msg, int msg_len);
mk_jumbo void mk_win_sha2_256_finish(struct mk_win_sha2_256_s* win_sha2_256, void* digest);


#endif
