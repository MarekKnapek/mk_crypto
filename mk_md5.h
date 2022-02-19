#ifndef MK_INCLUDE_GUARD_MD5
#define MK_INCLUDE_GUARD_MD5


#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t, uint64_t */ /* C99 */


#ifdef __cplusplus
#define MK_EXTERN_C extern "C"
#else
#define MK_EXTERN_C
#endif


struct mk_md5_state_s
{
	uint32_t m_a;
	uint32_t m_b;
	uint32_t m_c;
	uint32_t m_d;
	uint64_t m_len;
	unsigned char m_block[16 * sizeof(uint32_t)];
};

struct mk_md5_digest_s
{
	unsigned char m_bytes[16];
};


MK_EXTERN_C void mk_md5_init(struct mk_md5_state_s* self);
MK_EXTERN_C void mk_md5_append(struct mk_md5_state_s* self, void const* data, size_t len);
MK_EXTERN_C void mk_md5_finish(struct mk_md5_state_s const* self, struct mk_md5_digest_s* digest);


#undef MK_EXTERN_C


#endif
