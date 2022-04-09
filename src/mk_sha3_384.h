#ifndef mk_include_guard_sha3_384
#define mk_include_guard_sha3_384


#include "../../mk_int/src/exact/mk_uint_64.h"

#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_sha3_384_state_s
{
	struct mk_uint64_s m_state[5][5];
	int m_idx;
	unsigned char m_block[104];
};


mk_extern_c void mk_sha3_384_init(struct mk_sha3_384_state_s* self);
mk_extern_c void mk_sha3_384_append(struct mk_sha3_384_state_s* self, void const* msg, size_t msg_len_bytes);
mk_extern_c void mk_sha3_384_append_bits(struct mk_sha3_384_state_s* self, void const* msg, size_t msg_len_bits);
mk_extern_c void mk_sha3_384_finish(struct mk_sha3_384_state_s* self, void* digest);


#undef mk_extern_c


#endif
