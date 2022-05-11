#ifndef mk_include_guard_operation_mode_gcm
#define mk_include_guard_operation_mode_gcm


#include "mk_operation_mode_base.h"
#include "../mk_block_cipher.h"
#include "../mk_padding.h"

#include "../../../mk_int/src/exact/mk_uint_64.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_operation_mode_gcm_s
{
	struct mk_operation_mode_base_s m_base;
	unsigned char m_h[16];
	unsigned char m_j0[16];
	unsigned char m_cb[16];
	unsigned char m_aad_block[16];
	unsigned char m_tag[16];
	int m_aad_idx;
	struct mk_uint64_s m_aad_len;
	struct mk_uint64_s m_msg_len;
};


mk_extern_c void mk_operation_mode_init_gcm(struct mk_operation_mode_gcm_s* gcm, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len);
mk_extern_c enum mk_block_cipher_e mk_operation_mode_get_block_cipher_gcm(struct mk_operation_mode_gcm_s* gcm);
mk_extern_c unsigned char const* mk_operation_mode_get_key_gcm(struct mk_operation_mode_gcm_s* gcm);
mk_extern_c void mk_operation_mode_set_param_iv_gcm(struct mk_operation_mode_gcm_s* gcm, unsigned char const* iv, int iv_len);
mk_extern_c void mk_operation_mode_set_param_aad_append_gcm(struct mk_operation_mode_gcm_s* gcm, void const* aad, int aad_len);
mk_extern_c void mk_operation_mode_set_param_aad_finish_gcm(struct mk_operation_mode_gcm_s* gcm, void const* aad, int aad_len);
mk_extern_c void mk_operation_mode_encrypt_blocks_gcm(struct mk_operation_mode_gcm_s* gcm, int blocks, unsigned char const* input, unsigned char* output);
mk_extern_c void mk_operation_mode_decrypt_blocks_gcm(struct mk_operation_mode_gcm_s* gcm, int blocks, unsigned char const* input, unsigned char* output);
mk_extern_c int mk_operation_mode_encrypt_finish_gcm(struct mk_operation_mode_gcm_s* gcm, unsigned char const* input, int input_len, unsigned char* output, int output_len);
mk_extern_c void mk_operation_mode_decrypt_finish_gcm(struct mk_operation_mode_gcm_s* gcm, unsigned char const* input, int input_len, unsigned char* output, int* output_len);


#undef mk_extern_c


#endif
