#ifndef MK_INCLUDE_GUARD_MD2
#define MK_INCLUDE_GUARD_MD2


#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t */ /* C99 */


#ifdef __cplusplus
#define MK_EXTERN_C extern "C"
#else
#define MK_EXTERN_C
#endif


struct mk_md2_state_s
{
	union
	{
		struct
		{
			union
			{
				unsigned char m_bytes[16];
				uint32_t m_words[4];
			} m_state;
			union
			{
				unsigned char m_bytes[16];
				uint32_t m_words[4];
			} m_block;
			union
			{
				unsigned char m_bytes[16];
				uint32_t m_words[4];
			} m_extra;
		} m_pieces;
		union
		{
			unsigned char m_bytes[48];
			uint32_t m_words[12];
		} m_whole;
	} m_data;
	union
	{
		unsigned char m_bytes[16];
		uint32_t m_words[4];
	} m_checksum;
	unsigned m_len;
};

struct mk_md2_digest_s
{
	union
	{
		unsigned char m_bytes[16];
		uint32_t m_words[4];
	} m_data;
};


MK_EXTERN_C void mk_md2_init(struct mk_md2_state_s* self);
MK_EXTERN_C void mk_md2_append(struct mk_md2_state_s* self, void const* data, size_t len);
MK_EXTERN_C void mk_md2_finish(struct mk_md2_state_s* self, struct mk_md2_digest_s* digest);


#undef MK_EXTERN_C


#endif
