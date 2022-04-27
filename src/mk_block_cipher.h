#ifndef mk_include_guard_block_cipher
#define mk_include_guard_block_cipher


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_block_cipher_e
{
	mk_block_cipher_aes128,
	mk_block_cipher_aes192,
	mk_block_cipher_aes256,
};


mk_extern_c int mk_block_cipher_get_block_len(enum mk_block_cipher_e block_cipher);
mk_extern_c int mk_block_cipher_get_key_len(enum mk_block_cipher_e block_cipher);
mk_extern_c void mk_block_cipher_init_key(enum mk_block_cipher_e block_cipher, unsigned char const* input, unsigned char* output, int output_len);
mk_extern_c void mk_block_cipher_encrypt_block(enum mk_block_cipher_e block_cipher, unsigned char const* key, unsigned char const* input, unsigned char* output);
mk_extern_c void mk_block_cipher_decrypt_block(enum mk_block_cipher_e block_cipher, unsigned char const* key, unsigned char const* input, unsigned char* output);


#undef mk_extern_c


#endif
