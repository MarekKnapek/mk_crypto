#ifndef mk_include_guard_win_md4
#define mk_include_guard_win_md4


#include <stddef.h> /* size_t */

#include <windows.h>
#include <wincrypt.h>


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_win_md4_state_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


mk_extern_c void mk_win_md4_init(struct mk_win_md4_state_s* self);
mk_extern_c void mk_win_md4_append(struct mk_win_md4_state_s* self, void const* msg, size_t msg_len_bytes);
mk_extern_c void mk_win_md4_finish(struct mk_win_md4_state_s* self, void* digest);


#undef mk_extern_c


#endif
