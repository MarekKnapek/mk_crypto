#ifndef mk_include_guard_operation_mode_cfb
#define mk_include_guard_operation_mode_cfb


#include "../mk_block_cipher.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


mk_extern_c void mk_operation_mode_encrypt_blocks_cfb(enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output);
mk_extern_c void mk_operation_mode_decrypt_blocks_cfb(enum mk_block_cipher_e block_cipher, unsigned char* iv, unsigned char const* key, int n, unsigned char const* input, unsigned char* output);


#undef mk_extern_c


#endif
