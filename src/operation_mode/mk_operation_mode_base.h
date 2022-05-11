#ifndef mk_include_guard_operation_mode_base
#define mk_include_guard_operation_mode_base


#include "../mk_block_cipher.h"
#include "../mk_padding.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_operation_mode_base_s
{
	enum mk_block_cipher_e m_block_cipher;
	enum mk_padding_e m_padding;
	unsigned char m_key[mk_block_cipher_key_len_max];
};


mk_extern_c void mk_operation_mode_init_base(struct mk_operation_mode_base_s* base, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len);
mk_extern_c enum mk_block_cipher_e mk_operation_mode_get_block_cipher_base(struct mk_operation_mode_base_s* base);
mk_extern_c enum mk_padding_e mk_operation_mode_get_padding_base(struct mk_operation_mode_base_s* base);
mk_extern_c void const* mk_operation_mode_get_key_base(struct mk_operation_mode_base_s* base);


#undef mk_extern_c


#endif
