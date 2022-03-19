#ifndef mk_include_guard_sha2
#define mk_include_guard_sha2


#include "../../mk_int/src/exact/mk_uint_32.h"
#include "../../mk_int/src/exact/mk_uint_64.h"
#include "../../mk_int/src/exact/mk_uint_128.h"

#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_sha2_256_224_state_s
{
	struct mk_uint32_s m_hash[8];
	struct mk_uint64_s m_len;
	struct mk_uint32_s m_block[16];
};


mk_extern_c void mk_sha2_256_224_init(struct mk_sha2_256_224_state_s* self);
mk_extern_c void mk_sha2_256_224_append(struct mk_sha2_256_224_state_s* self, void const* data, size_t len);
mk_extern_c void mk_sha2_256_224_finish(struct mk_sha2_256_224_state_s* self, void* digest);


struct mk_sha2_256_state_s
{
	struct mk_uint32_s m_hash[8];
	struct mk_uint64_s m_len;
	struct mk_uint32_s m_block[16];
};


mk_extern_c void mk_sha2_256_init(struct mk_sha2_256_state_s* self);
mk_extern_c void mk_sha2_256_append(struct mk_sha2_256_state_s* self, void const* data, size_t len);
mk_extern_c void mk_sha2_256_finish(struct mk_sha2_256_state_s* self, void* digest);


struct mk_sha2_512_224_state_s
{
	struct mk_uint64_s m_hash[8];
	struct mk_uint128_s m_len;
	struct mk_uint64_s m_block[16];
};


mk_extern_c void mk_sha2_512_224_init(struct mk_sha2_512_224_state_s* self);
mk_extern_c void mk_sha2_512_224_append(struct mk_sha2_512_224_state_s* self, void const* data, size_t len);
mk_extern_c void mk_sha2_512_224_finish(struct mk_sha2_512_224_state_s* self, void* digest);


struct mk_sha2_512_256_state_s
{
	struct mk_uint64_s m_hash[8];
	struct mk_uint128_s m_len;
	struct mk_uint64_s m_block[16];
};


mk_extern_c void mk_sha2_512_256_init(struct mk_sha2_512_256_state_s* self);
mk_extern_c void mk_sha2_512_256_append(struct mk_sha2_512_256_state_s* self, void const* data, size_t len);
mk_extern_c void mk_sha2_512_256_finish(struct mk_sha2_512_256_state_s* self, void* digest);


struct mk_sha2_512_384_state_s
{
	struct mk_uint64_s m_hash[8];
	struct mk_uint128_s m_len;
	struct mk_uint64_s m_block[16];
};


mk_extern_c void mk_sha2_512_384_init(struct mk_sha2_512_384_state_s* self);
mk_extern_c void mk_sha2_512_384_append(struct mk_sha2_512_384_state_s* self, void const* data, size_t len);
mk_extern_c void mk_sha2_512_384_finish(struct mk_sha2_512_384_state_s* self, void* digest);


struct mk_sha2_512_state_s
{
	struct mk_uint64_s m_hash[8];
	struct mk_uint128_s m_len;
	struct mk_uint64_s m_block[16];
};


mk_extern_c void mk_sha2_512_init(struct mk_sha2_512_state_s* self);
mk_extern_c void mk_sha2_512_append(struct mk_sha2_512_state_s* self, void const* data, size_t len);
mk_extern_c void mk_sha2_512_finish(struct mk_sha2_512_state_s* self, void* digest);


#undef mk_extern_c


#endif
