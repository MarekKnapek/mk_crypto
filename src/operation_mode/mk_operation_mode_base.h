#ifndef mk_include_guard_operation_mode_base
#define mk_include_guard_operation_mode_base


#include "../mk_block_cipher.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_operation_mode_base_s
{
	enum mk_block_cipher_e m_block_cipher;
	unsigned char m_key[mk_block_cipher_key_len_max];
};


mk_extern_c void mk_operation_mode_init_base(struct mk_operation_mode_base_s* base, enum mk_block_cipher_e block_cipher, unsigned char const* key);
mk_extern_c enum mk_block_cipher_e mk_operation_mode_get_block_cipher_base(struct mk_operation_mode_base_s* base);
mk_extern_c unsigned char const* mk_operation_mode_get_key_base(struct mk_operation_mode_base_s* base);


#undef mk_extern_c


#endif
