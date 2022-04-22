#ifndef mk_include_guard_aes
#define mk_include_guard_aes


#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_aes_key_len_e
{
	mk_aes_key_len_128,
	mk_aes_key_len_192,
	mk_aes_key_len_256,
};

enum mk_aes_operation_mode_e
{
	mk_aes_operation_mode_cbc,
	mk_aes_operation_mode_ecb,
	mk_aes_operation_mode_ofb,
	mk_aes_operation_mode_cfb,
	mk_aes_operation_mode_cts,
};

enum mk_aes_padding_e
{
	mk_aes_padding_pkcs7,
	mk_aes_padding_zero,
};


struct mk_aes_128_s
{
	enum mk_aes_operation_mode_e m_om;
	unsigned char m_iv[16];
	unsigned char m_key[16];
};

mk_extern_c void mk_aes_128_encrypt_init(struct mk_aes_128_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key);
mk_extern_c void mk_aes_128_encrypt_blocks(struct mk_aes_128_s* self, void const* msg, int n, void* out);
mk_extern_c void mk_aes_128_encrypt_finish(struct mk_aes_128_s* self, void const* msg, int msg_len, void* out);

mk_extern_c void mk_aes_128_decrypt_init(struct mk_aes_128_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key);
mk_extern_c void mk_aes_128_decrypt_blocks(struct mk_aes_128_s* self, void const* msg, int n, void* out);
mk_extern_c void mk_aes_128_decrypt_finish(struct mk_aes_128_s* self, void const* msg, void* out);


struct mk_aes_192_s
{
	enum mk_aes_operation_mode_e m_om;
	unsigned char m_iv[16];
	unsigned char m_key[24];
};

mk_extern_c void mk_aes_192_encrypt_init(struct mk_aes_192_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key);
mk_extern_c void mk_aes_192_encrypt_blocks(struct mk_aes_192_s* self, void const* msg, int n, void* out);
mk_extern_c void mk_aes_192_encrypt_finish(struct mk_aes_192_s* self, void const* msg, int msg_len, void* out);

mk_extern_c void mk_aes_192_decrypt_init(struct mk_aes_192_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key);
mk_extern_c void mk_aes_192_decrypt_blocks(struct mk_aes_192_s* self, void const* msg, int n, void* out);
mk_extern_c void mk_aes_192_decrypt_finish(struct mk_aes_192_s* self, void const* msg, void* out);


struct mk_aes_256_s
{
	enum mk_aes_operation_mode_e m_om;
	unsigned char m_iv[16];
	unsigned char m_key[32];
};

mk_extern_c void mk_aes_256_encrypt_init(struct mk_aes_256_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key);
mk_extern_c void mk_aes_256_encrypt_blocks(struct mk_aes_256_s* self, void const* msg, int n, void* out);
mk_extern_c void mk_aes_256_encrypt_finish(struct mk_aes_256_s* self, void const* msg, int msg_len, void* out);

mk_extern_c void mk_aes_256_decrypt_init(struct mk_aes_256_s* self, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key);
mk_extern_c void mk_aes_256_decrypt_blocks(struct mk_aes_256_s* self, void const* msg, int n, void* out);
mk_extern_c void mk_aes_256_decrypt_finish(struct mk_aes_256_s* self, void const* msg, void* out);


struct mk_aes_s
{
	enum mk_aes_key_len_e m_key_len;
	union
	{
		struct mk_aes_128_s m_aes_128;
		struct mk_aes_192_s m_aes_192;
		struct mk_aes_256_s m_aes_256;
	};
};

mk_extern_c void mk_aes_encrypt_init(struct mk_aes_s* self, enum mk_aes_key_len_e key_len, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key);
mk_extern_c void mk_aes_encrypt_blocks(struct mk_aes_s* self, void const* msg, int n, void* out);
mk_extern_c void mk_aes_encrypt_finish(struct mk_aes_s* self, void const* msg, int msg_len, void* out);

mk_extern_c void mk_aes_decrypt_init(struct mk_aes_s* self, enum mk_aes_key_len_e key_len, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key);
mk_extern_c void mk_aes_decrypt_blocks(struct mk_aes_s* self, void const* msg, int n, void* out);
mk_extern_c void mk_aes_decrypt_finish(struct mk_aes_s* self, void const* msg, void* out);

mk_extern_c void mk_aes_encrypt_msg(enum mk_aes_key_len_e key_len, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key, void const* msg, size_t msg_len, void* out);
mk_extern_c void mk_aes_decrypt_msg(enum mk_aes_key_len_e key_len, enum mk_aes_operation_mode_e om, enum mk_aes_padding_e padding, void const* iv, void const* key, void const* msg, size_t msg_len, void* out);


#undef mk_extern_c


#endif
