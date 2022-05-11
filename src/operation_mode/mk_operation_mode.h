#ifndef mk_include_guard_operation_mode
#define mk_include_guard_operation_mode


#include "mk_operation_mode_cbc.h"
#include "mk_operation_mode_cfb.h"
#include "mk_operation_mode_ctr.h"
#include "mk_operation_mode_ecb.h"
#include "mk_operation_mode_gcm.h"
#include "mk_operation_mode_ofb.h"
#include "../mk_block_cipher.h"
#include "../mk_padding.h"


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_operation_mode_e
{
	mk_operation_mode_cbc,
	mk_operation_mode_cfb,
	mk_operation_mode_ctr,
	mk_operation_mode_ecb,
	mk_operation_mode_gcm,
	mk_operation_mode_ofb,
};

struct mk_operation_mode_s
{
	enum mk_operation_mode_e m_type;
	union
	{
		struct mk_operation_mode_cbc_s m_cbc;
		struct mk_operation_mode_cfb_s m_cfb;
		struct mk_operation_mode_ctr_s m_ctr;
		struct mk_operation_mode_ecb_s m_ecb;
		struct mk_operation_mode_gcm_s m_gcm;
		struct mk_operation_mode_ofb_s m_ofb;
	} m_mode;
};


mk_extern_c void mk_operation_mode_init(struct mk_operation_mode_s* operation_mode, enum mk_operation_mode_e type, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len);
mk_extern_c enum mk_block_cipher_e mk_operation_mode_get_block_cipher(struct mk_operation_mode_s* operation_mode);
mk_extern_c void mk_operation_mode_set_param_iv(struct mk_operation_mode_s* operation_mode, void const* iv, int iv_len);
mk_extern_c void mk_operation_mode_set_param_aad_append(struct mk_operation_mode_s* operation_mode, void const* aad, int aad_len);
mk_extern_c void mk_operation_mode_set_param_aad_finish(struct mk_operation_mode_s* operation_mode, void const* aad, int aad_len);
mk_extern_c void mk_operation_mode_set_param_cfb_s_bytes(struct mk_operation_mode_s* operation_mode, int cfb_s_bytes);
mk_extern_c void mk_operation_mode_set_param_ctr_endian(struct mk_operation_mode_s* operation_mode, int ctr_endian);
mk_extern_c void mk_operation_mode_encrypt_blocks(struct mk_operation_mode_s* operation_mode, int blocks, unsigned char const* input, unsigned char* output);
mk_extern_c void mk_operation_mode_decrypt_blocks(struct mk_operation_mode_s* operation_mode, int blocks, unsigned char const* input, unsigned char* output);
mk_extern_c int mk_operation_mode_encrypt_finish(struct mk_operation_mode_s* operation_mode, void const* input, int input_len, void* output, int output_len);
mk_extern_c void mk_operation_mode_decrypt_finish(struct mk_operation_mode_s* operation_mode, void const* input, int input_len, void* output, int* output_len);


#undef mk_extern_c


#endif
