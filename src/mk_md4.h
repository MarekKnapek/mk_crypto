#ifndef mk_include_guard_md4
#define mk_include_guard_md4


#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t, uint64_t */ /* C99 */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
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


mk_extern_c void mk_md4_init(struct mk_md4_state_s* self);
mk_extern_c void mk_md4_append(struct mk_md4_state_s* self, void const* data, size_t len);
mk_extern_c void mk_md4_finish(struct mk_md4_state_s* self, void* digest);


#undef mk_extern_c


#endif
