#ifndef mk_include_guard_win_crypto
#define mk_include_guard_win_crypto


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


typedef void* mk_win_crypto_h;

enum mk_win_crypto_operation_mode_e
{
	mk_win_crypto_operation_mode_cbc,
	mk_win_crypto_operation_mode_cfb,
	mk_win_crypto_operation_mode_cts,
	mk_win_crypto_operation_mode_ecb,
	mk_win_crypto_operation_mode_ofb,
};

enum mk_win_crypto_algorithm_e
{
	mk_win_crypto_algorithm_aes128,
	mk_win_crypto_algorithm_aes192,
	mk_win_crypto_algorithm_aes256,
};


mk_extern_c mk_win_crypto_h mk_win_crypto_create(enum mk_win_crypto_operation_mode_e operation_mode, enum mk_win_crypto_algorithm_e algorithm, void const* iv, int iv_len, void const* key, int key_len);
mk_extern_c void mk_win_crypto_encrypt(mk_win_crypto_h win_crypto_h, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes);
mk_extern_c int mk_win_crypto_decrypt(mk_win_crypto_h win_crypto_h, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes);
mk_extern_c void mk_win_crypto_destroy(mk_win_crypto_h win_crypto_h);


#undef mk_extern_c


#endif
