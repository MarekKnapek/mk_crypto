#ifndef mk_include_guard_crypt
#define mk_include_guard_crypt


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_crypt_operation_mode_e
{
	mk_crypt_operation_mode_cbc,
	mk_crypt_operation_mode_cfb,
	mk_crypt_operation_mode_ecb,
};

enum mk_crypt_block_cipher_e
{
	mk_crypt_block_cipher_aes128,
	mk_crypt_block_cipher_aes192,
	mk_crypt_block_cipher_aes256,
};


struct mk_crypt_s
{
	enum mk_crypt_operation_mode_e m_operation_mode;
	enum mk_crypt_block_cipher_e m_block_cipher;
	unsigned char m_iv[16];
	unsigned char m_key[32];
};


mk_extern_c void mk_crypt_init(struct mk_crypt_s* crypt, enum mk_crypt_operation_mode_e operation_mode, enum mk_crypt_block_cipher_e block_cipher, void const* iv, void const* key);
mk_extern_c void mk_crypt_encrypt(struct mk_crypt_s* crypt, int final, void const* input, int input_len_bytes, void* output);
mk_extern_c int mk_crypt_decrypt(struct mk_crypt_s* crypt, int final, void const* input, int input_len_bytes, void* output);


#undef mk_extern_c


#endif
