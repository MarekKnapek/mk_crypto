#ifndef MK_INCLUDE_GUARD_WIN_MD4
#define MK_INCLUDE_GUARD_WIN_MD4


#include <stddef.h> /* size_t */

#include <windows.h>
#include <bcrypt.h>


#ifdef __cplusplus
#define MK_EXTERN_C extern "C"
#else
#define MK_EXTERN_C
#endif


struct mk_win_md4_state_s
{
	BCRYPT_ALG_HANDLE m_alg_prov;
	void* m_alg_data;
	BCRYPT_HASH_HANDLE m_alg;
};


MK_EXTERN_C void mk_win_md4_init(struct mk_win_md4_state_s* self);
MK_EXTERN_C void mk_win_md4_append(struct mk_win_md4_state_s* self, void const* data, size_t len);
MK_EXTERN_C void mk_win_md4_finish(struct mk_win_md4_state_s* self, void* digest);


#undef MK_EXTERN_C


#endif
