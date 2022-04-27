#ifndef mk_include_guard_operation_mode
#define mk_include_guard_operation_mode


#include "../mk_block_cipher.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_operation_mode_e
{
	mk_operation_mode_cbc,
	mk_operation_mode_cfb,
	mk_operation_mode_ecb,
};


mk_extern_c void mk_operation_mode_init_iv(enum mk_operation_mode_e operation_mode, enum mk_block_cipher_e block_cipher, unsigned char const* input, unsigned char* output, int output_len);
mk_extern_c void mk_operation_mode_encrypt_blocks(enum mk_operation_mode_e operation_mode, enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output);
mk_extern_c void mk_operation_mode_decrypt_blocks(enum mk_operation_mode_e operation_mode, enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output);


#undef mk_extern_c


#endif
