#ifndef mk_include_guard_win_aes
#define mk_include_guard_win_aes


#include <windows.h>
#include <wincrypt.h>


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_win_aes_key_len_e
{
	mk_win_aes_key_len_128,
	mk_win_aes_key_len_192,
	mk_win_aes_key_len_256,
};

enum mk_win_aes_operation_mode_e
{
	mk_win_aes_operation_mode_cbc,
	mk_win_aes_operation_mode_ecb,
	mk_win_aes_operation_mode_ofb,
	mk_win_aes_operation_mode_cfb,
	mk_win_aes_operation_mode_cts,
};

enum mk_win_aes_padding_e
{
	mk_win_aes_padding_pkcs7,
};

struct mk_win_aes_s
{
	HCRYPTPROV m_csp;
	HCRYPTKEY m_ck;
};


mk_extern_c void mk_win_aes_encrypt_init(struct mk_win_aes_s* self, enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key);
mk_extern_c void mk_win_aes_encrypt_blocks(struct mk_win_aes_s* self, void const* msg, int n, void* out);
mk_extern_c void mk_win_aes_encrypt_finish(struct mk_win_aes_s* self, void const* msg, int msg_len, void* out);

mk_extern_c void mk_win_aes_decrypt_init(struct mk_win_aes_s* self, enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key);
mk_extern_c void mk_win_aes_decrypt_blocks(struct mk_win_aes_s* self, void const* msg, int n, void* out);
mk_extern_c void mk_win_aes_decrypt_finish(struct mk_win_aes_s* self, void const* msg, void* out);

mk_extern_c void mk_win_aes_encrypt_msg(enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key, void const* msg, int msg_len, void* out);
mk_extern_c void mk_win_aes_decrypt_msg(enum mk_win_aes_key_len_e key_len, enum mk_win_aes_operation_mode_e om, enum mk_win_aes_padding_e padding, void const* iv, void const* key, void const* msg, int msg_len, void* out);


#undef mk_extern_c


#endif
