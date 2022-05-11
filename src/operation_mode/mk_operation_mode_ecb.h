#ifndef mk_include_guard_operation_mode_ecb
#define mk_include_guard_operation_mode_ecb


#include "mk_operation_mode_base.h"
#include "../mk_block_cipher.h"
#include "../mk_padding.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_operation_mode_ecb_s
{
	struct mk_operation_mode_base_s m_base;
};


mk_extern_c void mk_operation_mode_init_ecb(struct mk_operation_mode_ecb_s* ecb, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len);
mk_extern_c enum mk_block_cipher_e mk_operation_mode_get_block_cipher_ecb(struct mk_operation_mode_ecb_s* ecb);
mk_extern_c unsigned char const* mk_operation_mode_get_key_ecb(struct mk_operation_mode_ecb_s* ecb);
mk_extern_c void mk_operation_mode_set_param_iv_ecb(struct mk_operation_mode_ecb_s* ecb, void const* iv, int iv_len);
mk_extern_c void mk_operation_mode_encrypt_blocks_ecb(struct mk_operation_mode_ecb_s* ecb, int blocks, unsigned char const* input, unsigned char* output);
mk_extern_c void mk_operation_mode_decrypt_blocks_ecb(struct mk_operation_mode_ecb_s* ecb, int blocks, unsigned char const* input, unsigned char* output);
mk_extern_c int mk_operation_mode_encrypt_finish_ecb(struct mk_operation_mode_ecb_s* ecb, void const* input, int input_len, void* output, int output_len);


#undef mk_extern_c


#endif
