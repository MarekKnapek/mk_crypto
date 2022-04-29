#ifndef mk_include_guard_tom_crypto
#define mk_include_guard_tom_crypto


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


typedef void* mk_tom_crypto_h;

enum mk_tom_crypto_operation_mode_e
{
	mk_tom_crypto_operation_mode_cbc,
	mk_tom_crypto_operation_mode_cfb,
	mk_tom_crypto_operation_mode_ecb,
};

enum mk_tom_crypto_block_cipher_e
{
	mk_tom_crypto_block_cipher_aes128,
	mk_tom_crypto_block_cipher_aes192,
	mk_tom_crypto_block_cipher_aes256,
};


mk_extern_c mk_tom_crypto_h mk_tom_crypto_create(enum mk_tom_crypto_operation_mode_e operation_mode, enum mk_tom_crypto_block_cipher_e block_cipher, void const* iv, void const* key);
mk_extern_c void mk_tom_crypto_encrypt(mk_tom_crypto_h tom_crypto_h, int final, void const* input, int input_len_bytes, void* output);
mk_extern_c int mk_tom_crypto_decrypt(mk_tom_crypto_h tom_crypto_h, int final, void const* input, int input_len_bytes, void* output);
mk_extern_c void mk_tom_crypto_destroy(mk_tom_crypto_h tom_crypto_h);


#undef mk_extern_c


#endif
