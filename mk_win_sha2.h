#ifndef MK_INCLUDE_GUARD_WIN_SHA2
#define MK_INCLUDE_GUARD_WIN_SHA2


#include <stddef.h> /* size_t */

#include <windows.h>
#include <wincrypt.h>


#ifdef __cplusplus
#define MK_EXTERN_C extern "C"
#else
#define MK_EXTERN_C
#endif


struct mk_win_sha2_256_state_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


MK_EXTERN_C void mk_win_sha2_256_init(struct mk_win_sha2_256_state_s* self);
MK_EXTERN_C void mk_win_sha2_256_append(struct mk_win_sha2_256_state_s* self, void const* data, size_t len);
MK_EXTERN_C void mk_win_sha2_256_finish(struct mk_win_sha2_256_state_s* self, void* digest);


struct mk_win_sha2_512_384_state_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


MK_EXTERN_C void mk_win_sha2_512_384_init(struct mk_win_sha2_512_384_state_s* self);
MK_EXTERN_C void mk_win_sha2_512_384_append(struct mk_win_sha2_512_384_state_s* self, void const* data, size_t len);
MK_EXTERN_C void mk_win_sha2_512_384_finish(struct mk_win_sha2_512_384_state_s* self, void* digest);


struct mk_win_sha2_512_state_s
{
	HCRYPTPROV m_csp;
	HCRYPTHASH m_hash;
};


MK_EXTERN_C void mk_win_sha2_512_init(struct mk_win_sha2_512_state_s* self);
MK_EXTERN_C void mk_win_sha2_512_append(struct mk_win_sha2_512_state_s* self, void const* data, size_t len);
MK_EXTERN_C void mk_win_sha2_512_finish(struct mk_win_sha2_512_state_s* self, void* digest);


#undef MK_EXTERN_C


#endif
