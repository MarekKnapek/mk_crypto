#ifndef mk_include_guard_sha2_256
#define mk_include_guard_sha2_256


#include "../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../mk_int/src/exact/mk_uint_64.h"

#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_sha2_256_state_s
{
	struct mk_uint32_s m_state[8];
	struct mk_uint64_s m_len;
	unsigned char m_block[64];
};


mk_extern_c void mk_sha2_256_init(struct mk_sha2_256_state_s* self);
mk_extern_c void mk_sha2_256_append(struct mk_sha2_256_state_s* self, void const* msg, size_t msg_len_bytes);
mk_extern_c void mk_sha2_256_finish(struct mk_sha2_256_state_s* self, void* digest);


#undef mk_extern_c


#endif
