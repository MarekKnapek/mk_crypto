#ifndef mk_include_guard_win_cryptong
#define mk_include_guard_win_cryptong


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


typedef void* mk_win_cryptong_h;

enum mk_win_cryptong_operation_mode_e
{
	mk_win_cryptong_operation_mode_cbc,
	mk_win_cryptong_operation_mode_ccm,
	mk_win_cryptong_operation_mode_cfb,
	mk_win_cryptong_operation_mode_ecb,
	mk_win_cryptong_operation_mode_gcm,
};

enum mk_win_cryptong_algorithm_e
{
	mk_win_cryptong_algorithm_aes128,
	mk_win_cryptong_algorithm_aes192,
	mk_win_cryptong_algorithm_aes256,
};


mk_extern_c mk_win_cryptong_h mk_win_cryptong_create(enum mk_win_cryptong_operation_mode_e operation_mode, enum mk_win_cryptong_algorithm_e algorithm, void const* iv, void const* key);
mk_extern_c void mk_win_cryptong_encrypt(mk_win_cryptong_h win_cryptong_h, int final, void const* input, int input_len_bytes, void* output);
mk_extern_c void mk_win_cryptong_destroy(mk_win_cryptong_h win_cryptong_h);


#undef mk_extern_c


#endif
