#ifndef mk_include_guard_sha1
#define mk_include_guard_sha1


#include "../../mk_int/src/exact/mk_uint_32.h"
#include "../../mk_int/src/exact/mk_uint_64.h"

#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_sha1_state_s
{
	struct mk_uint32_s m_abcde[5];
	struct mk_uint64_s m_len;
	struct mk_uint32_s m_block[16];
};


mk_extern_c void mk_sha1_init(struct mk_sha1_state_s* self);
mk_extern_c void mk_sha1_append(struct mk_sha1_state_s* self, void const* data, size_t len);
mk_extern_c void mk_sha1_finish(struct mk_sha1_state_s* self, void* digest);


#undef mk_extern_c


#endif
