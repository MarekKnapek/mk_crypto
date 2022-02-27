#ifndef MK_INCLUDE_GUARD_SHA2
#define MK_INCLUDE_GUARD_SHA2


#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t uint64_t */ /* C99 */


#ifdef __cplusplus
#define MK_EXTERN_C extern "C"
#else
#define MK_EXTERN_C
#endif


struct mk_sha2_224_state_s
{
	uint32_t m_hash[8];
	uint64_t m_len;
	unsigned char m_block[16 * sizeof(uint32_t)];
};


MK_EXTERN_C void mk_sha2_224_init(struct mk_sha2_224_state_s* self);
MK_EXTERN_C void mk_sha2_224_append(struct mk_sha2_224_state_s* self, void const* data, size_t len);
MK_EXTERN_C void mk_sha2_224_finish(struct mk_sha2_224_state_s* self, void* digest);


struct mk_sha2_256_state_s
{
	uint32_t m_hash[8];
	uint64_t m_len;
	unsigned char m_block[16 * sizeof(uint32_t)];
};


MK_EXTERN_C void mk_sha2_256_init(struct mk_sha2_256_state_s* self);
MK_EXTERN_C void mk_sha2_256_append(struct mk_sha2_256_state_s* self, void const* data, size_t len);
MK_EXTERN_C void mk_sha2_256_finish(struct mk_sha2_256_state_s* self, void* digest);


#undef MK_EXTERN_C


#endif
