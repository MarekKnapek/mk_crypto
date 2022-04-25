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
	mk_crypto_operation_mode_cts,
	mk_crypto_operation_mode_ecb,
	mk_crypto_operation_mode_ofb,
	mk_crypto_operation_mode_pcbc,
};

enum mk_crypto_algorithm_e
{
	mk_crypto_algorithm_aes128,
	mk_crypto_algorithm_aes192,
	mk_crypto_algorithm_aes256,
};


mk_extern_c mk_crypto_h mk_crypto_create(enum mk_crypto_operation_mode_e operation_mode, enum mk_crypto_algorithm_e algorithm, void const* iv, void const* key);
mk_extern_c void mk_crypto_encrypt(mk_crypto_h crypto, int final, void const* input, int input_len_bytes, void* output);
mk_extern_c void mk_crypto_destroy(mk_crypto_h crypto);


#undef mk_extern_c


#endif
