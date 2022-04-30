#ifndef mk_include_guard_operation_mode_ctr
#define mk_include_guard_operation_mode_ctr


#include "mk_operation_mode_base.h"
#include "../mk_block_cipher.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_operation_mode_ctr_s
{
	struct mk_operation_mode_base_s m_base;
	unsigned char m_iv[mk_block_cipher_block_len_max];
};


mk_extern_c void mk_operation_mode_init_ctr(struct mk_operation_mode_ctr_s* ctr, enum mk_block_cipher_e block_cipher, unsigned char const* key);
mk_extern_c enum mk_block_cipher_e mk_operation_mode_get_block_cipher_ctr(struct mk_operation_mode_ctr_s* ctr);
mk_extern_c unsigned char const* mk_operation_mode_get_key_ctr(struct mk_operation_mode_ctr_s* ctr);
mk_extern_c void mk_operation_mode_set_param_iv_ctr(struct mk_operation_mode_ctr_s* ctr, unsigned char const* iv);
mk_extern_c void mk_operation_mode_encrypt_blocks_ctr(struct mk_operation_mode_ctr_s* ctr, int blocks, unsigned char const* input, unsigned char* output);
mk_extern_c void mk_operation_mode_decrypt_blocks_ctr(struct mk_operation_mode_ctr_s* ctr, int blocks, unsigned char const* input, unsigned char* output);


#undef mk_extern_c


#endif
