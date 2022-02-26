#ifndef MK_INCLUDE_GUARD_MD2
#define MK_INCLUDE_GUARD_MD2


#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define MK_EXTERN_C extern "C"
#else
#define MK_EXTERN_C
#endif


struct mk_md2_state_s
{
	unsigned char m_state[16];
	unsigned char m_block[16];
	unsigned char m_checksum[16];
	unsigned m_len;
};

struct mk_md2_digest_s
{
	unsigned char m_data[16];
};


MK_EXTERN_C void mk_md2_init(struct mk_md2_state_s* self);
MK_EXTERN_C void mk_md2_append(struct mk_md2_state_s* self, void const* data, size_t len);
MK_EXTERN_C void mk_md2_finish(struct mk_md2_state_s* self, struct mk_md2_digest_s* digest);


#undef MK_EXTERN_C


#endif
