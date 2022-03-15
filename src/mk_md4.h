#ifndef MK_INCLUDE_GUARD_MD4
#define MK_INCLUDE_GUARD_MD4


#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t, uint64_t */ /* C99 */


#ifdef __cplusplus
#define MK_EXTERN_C extern "C"
#else
#define MK_EXTERN_C
#endif


struct mk_md4_state_s
{
	uint32_t m_abcd[4];
	uint64_t m_len;
	union
	{
		unsigned char m_bytes[16 * sizeof(uint32_t)];
		uint32_t m_words[16];
	} m_block;
};

struct mk_md4_digest_s
{
	union
	{
		unsigned char m_bytes[4 * sizeof(uint32_t)];
		uint32_t m_words[4];
	} m_data; /* 4 32bit words, 16 bytes, 128 bits */
};


MK_EXTERN_C void mk_md4_init(struct mk_md4_state_s* self);
MK_EXTERN_C void mk_md4_append(struct mk_md4_state_s* self, void const* data, size_t len);
MK_EXTERN_C void mk_md4_finish(struct mk_md4_state_s* self, void* digest);


#undef MK_EXTERN_C


#endif
