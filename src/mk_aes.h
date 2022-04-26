#ifndef mk_include_guard_aes
#define mk_include_guard_aes


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


mk_extern_c void mk_aes_encrypt_block_128(unsigned char const input[16], unsigned char const key[16], unsigned char output[16]);
mk_extern_c void mk_aes_decrypt_block_128(unsigned char const input[16], unsigned char const key[16], unsigned char output[16]);
mk_extern_c void mk_aes_encrypt_block_192(unsigned char const input[16], unsigned char const key[24], unsigned char output[16]);
mk_extern_c void mk_aes_decrypt_block_192(unsigned char const input[16], unsigned char const key[24], unsigned char output[16]);
mk_extern_c void mk_aes_encrypt_block_256(unsigned char const input[16], unsigned char const key[32], unsigned char output[16]);
mk_extern_c void mk_aes_decrypt_block_256(unsigned char const input[16], unsigned char const key[32], unsigned char output[16]);


#undef mk_extern_c


#endif
