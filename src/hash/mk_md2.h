#ifndef mk_include_guard_md2
#define mk_include_guard_md2


#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_md2_state_s
{
	unsigned char m_state[16];
	unsigned char m_checksum[16];
	unsigned char m_block[16];
	int m_idx;
};


mk_extern_c void mk_md2_init(struct mk_md2_state_s* self);
mk_extern_c void mk_md2_append(struct mk_md2_state_s* self, void const* msg, size_t msg_len_bytes);
mk_extern_c void mk_md2_finish(struct mk_md2_state_s* self, void* digest);


#undef mk_extern_c


#endif
