#ifndef mk_include_guard_sha1
#define mk_include_guard_sha1


#include "../../mk_int/src/exact/mk_uint_32.h"
#include "../../mk_int/src/exact/mk_uint_64.h"

#include <stddef.h> /* size_t */


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4820) /* warning C4820: 'xxx': 'xxx' bytes padding added after data member 'xxx' */
#endif


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_sha1_state_s
{
	struct mk_uint32_s m_state[5];
	struct mk_uint64_s m_len;
	unsigned char m_block[64];
};


mk_extern_c void mk_sha1_init(struct mk_sha1_state_s* self);
mk_extern_c void mk_sha1_append(struct mk_sha1_state_s* self, void const* msg, size_t msg_len_bytes);
mk_extern_c void mk_sha1_finish(struct mk_sha1_state_s* self, void* digest);


#undef mk_extern_c


#if defined(_MSC_VER)
#pragma warning(pop)
#endif


#endif
