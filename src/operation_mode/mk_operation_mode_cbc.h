#ifndef mk_include_guard_operation_mode_cbc
#define mk_include_guard_operation_mode_cbc


#include "mk_operation_mode_base.h"
#include "../mk_block_cipher.h"
#include "../mk_padding.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_operation_mode_cbc_s
{
	struct mk_operation_mode_base_s m_base;
	unsigned char m_iv[mk_block_cipher_block_len_max];
};


mk_extern_c void mk_operation_mode_init_cbc(struct mk_operation_mode_cbc_s* cbc, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len);
mk_extern_c enum mk_block_cipher_e mk_operation_mode_get_block_cipher_cbc(struct mk_operation_mode_cbc_s* cbc);
mk_extern_c unsigned char const* mk_operation_mode_get_key_cbc(struct mk_operation_mode_cbc_s* cbc);
mk_extern_c void mk_operation_mode_set_param_iv_cbc(struct mk_operation_mode_cbc_s* cbc, void const* iv, int iv_len);
mk_extern_c void mk_operation_mode_encrypt_blocks_cbc(struct mk_operation_mode_cbc_s* cbc, int blocks, unsigned char const* input, unsigned char* output);
mk_extern_c void mk_operation_mode_decrypt_blocks_cbc(struct mk_operation_mode_cbc_s* cbc, int blocks, unsigned char const* input, unsigned char* output);
mk_extern_c int mk_operation_mode_encrypt_finish_cbc(struct mk_operation_mode_cbc_s* cbc, void const* input, int input_len, void* output, int output_len);

#undef mk_extern_c


#endif
