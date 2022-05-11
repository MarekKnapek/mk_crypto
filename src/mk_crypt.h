#ifndef mk_include_guard_crypt
#define mk_include_guard_crypt


#include "operation_mode/mk_operation_mode.h"
#include "mk_block_cipher.h"
#include "mk_padding.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_crypt_s
{
	struct mk_operation_mode_s m_operation_mode;
	unsigned char m_block[mk_block_cipher_block_len_max];
	int m_idx;
};


mk_extern_c void mk_crypt_init(struct mk_crypt_s* crypt, enum mk_operation_mode_e operation_mode, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len);
mk_extern_c void mk_crypt_set_param_iv(struct mk_crypt_s* crypt, void const* iv, int iv_len);
mk_extern_c void mk_crypt_set_param_aad_append(struct mk_crypt_s* crypt, void const* aad, int aad_len);
mk_extern_c void mk_crypt_set_param_aad_finish(struct mk_crypt_s* crypt, void const* aad, int aad_len);
mk_extern_c void mk_crypt_set_param_cfb_s_bytes(struct mk_crypt_s* crypt, int cfb_s_bytes);
mk_extern_c void mk_crypt_set_param_ctr_endian(struct mk_crypt_s* crypt, int ctr_endian);
mk_extern_c int mk_crypt_encrypt(struct mk_crypt_s* crypt, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes);
mk_extern_c int mk_crypt_decrypt(struct mk_crypt_s* crypt, int final, void const* input, int input_len_bytes, void* output, int output_len_bytes);


#undef mk_extern_c


#endif
