#ifndef mk_include_guard_sha3_shake128
#define mk_include_guard_sha3_shake128


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


struct mk_sha3_shake128_state_s
{
	struct mk_uint64_s m_state[5][5];
	int m_idx;
	unsigned char m_block[168];
};


mk_extern_c void mk_sha3_shake128_init(struct mk_sha3_shake128_state_s* self);
mk_extern_c void mk_sha3_shake128_append(struct mk_sha3_shake128_state_s* self, void const* msg, size_t msg_len_bytes);
mk_extern_c void mk_sha3_shake128_append_bits(struct mk_sha3_shake128_state_s* self, void const* msg, size_t msg_len_bits);
mk_extern_c void mk_sha3_shake128_finish(struct mk_sha3_shake128_state_s* self, void* digest, size_t digest_len_bits);


#undef mk_extern_c


#if defined(_MSC_VER)
#pragma warning(pop)
#endif


#endif
