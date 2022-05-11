#ifndef mk_include_guard_crypto
#define mk_include_guard_crypto


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


typedef void* mk_crypto_h;

enum mk_crypto_operation_mode_e
{
	mk_crypto_operation_mode_cbc,
	mk_crypto_operation_mode_cfb,
	mk_crypto_operation_mode_ctr,
	mk_crypto_operation_mode_ecb,
	mk_crypto_operation_mode_gcm,
	mk_crypto_operation_mode_ofb,
};

enum mk_crypto_block_cipher_e
{
	mk_crypto_block_cipher_aes128,
	mk_crypto_block_cipher_aes192,
	mk_crypto_block_cipher_aes256,
};

enum mk_crypto_padding_e
{
	mk_crypto_padding_pkcs7,
	mk_crypto_padding_10s,
	mk_crypto_padding_10s1,
	mk_crypto_padding_zero,
	mk_crypto_padding_none,
};

enum mk_crypto_param_e
{
	mk_crypto_param_iv,
	mk_crypto_param_aad_append,
	mk_crypto_param_aad_finish,
	mk_crypto_param_cfb_s_bytes,
	mk_crypto_param_ctr_endian,
};


mk_extern_c mk_crypto_h mk_crypto_create(enum mk_crypto_operation_mode_e operation_mode, enum mk_crypto_block_cipher_e block_cipher, enum mk_crypto_padding_e padding, void const* key, int key_len);
mk_extern_c void mk_crypto_set_param(mk_crypto_h crypto, enum mk_crypto_param_e param, void const* value);
mk_extern_c int mk_crypto_encrypt(mk_crypto_h crypto, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes);
mk_extern_c int mk_crypto_decrypt(mk_crypto_h crypto, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes);
mk_extern_c void mk_crypto_destroy(mk_crypto_h crypto);


#undef mk_extern_c


#endif
