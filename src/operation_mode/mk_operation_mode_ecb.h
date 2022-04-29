#ifndef mk_include_guard_operation_mode_ecb
#define mk_include_guard_operation_mode_ecb


#include "mk_operation_mode_base.h"
#include "../mk_block_cipher.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_operation_mode_ecb_s
{
	struct mk_operation_mode_base_s m_base;
};


mk_extern_c void mk_operation_mode_init_ecb(struct mk_operation_mode_ecb_s* ecb, enum mk_block_cipher_e block_cipher, unsigned char const* key);
mk_extern_c enum mk_block_cipher_e mk_operation_mode_get_block_cipher_ecb(struct mk_operation_mode_ecb_s* ecb);
mk_extern_c unsigned char const* mk_operation_mode_get_key_ecb(struct mk_operation_mode_ecb_s* ecb);
mk_extern_c void mk_operation_mode_encrypt_blocks_ecb(struct mk_operation_mode_ecb_s* ecb, int blocks, unsigned char const* input, unsigned char* output);
mk_extern_c void mk_operation_mode_decrypt_blocks_ecb(struct mk_operation_mode_ecb_s* ecb, int blocks, unsigned char const* input, unsigned char* output);


#undef mk_extern_c


#endif
