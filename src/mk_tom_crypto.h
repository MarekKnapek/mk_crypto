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
	mk_tom_crypto_operation_mode_ctr,
	mk_tom_crypto_operation_mode_ecb,
	mk_tom_crypto_operation_mode_ofb,
};

enum mk_tom_crypto_block_cipher_e
{
	mk_tom_crypto_block_cipher_aes128,
	mk_tom_crypto_block_cipher_aes192,
	mk_tom_crypto_block_cipher_aes256,
};

enum mk_tom_crypto_padding_e
{
	mk_tom_crypto_padding_pkcs7,
};


enum mk_tom_crypto_param_e
{
	mk_tom_crypto_param_iv,
};


mk_extern_c mk_tom_crypto_h mk_tom_crypto_create(enum mk_tom_crypto_operation_mode_e operation_mode, enum mk_tom_crypto_block_cipher_e block_cipher, enum mk_tom_crypto_padding_e padding, void const* key, int key_len);
mk_extern_c void mk_tom_crypto_set_param(mk_tom_crypto_h tom_crypto_h, enum mk_tom_crypto_param_e param, void const* value);
mk_extern_c void mk_tom_crypto_encrypt(mk_tom_crypto_h tom_crypto_h, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes);
mk_extern_c int mk_tom_crypto_decrypt(mk_tom_crypto_h tom_crypto_h, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes);
mk_extern_c void mk_tom_crypto_destroy(mk_tom_crypto_h tom_crypto_h);


#undef mk_extern_c


#endif
