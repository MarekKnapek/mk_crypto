#ifndef mk_include_guard_aes
#define mk_include_guard_aes
#endif


#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_aes_key_len_e
{
	mk_aes_key_len_e_128,
	mk_aes_key_len_e_192,
	mk_aes_key_len_e_256,
};


struct mk_aes_128_encrypt_state_s
{
	unsigned char m_key[16];
	unsigned char m_block[16];
	int m_idx;
};

mk_extern_c void mk_aes_128_encrypt_init(struct mk_aes_128_encrypt_state_s* self, void const* key);
mk_extern_c void mk_aes_128_encrypt_append(struct mk_aes_128_encrypt_state_s* self, void const* clear_text, size_t* clear_text_len_bytes, void* cipher_text, size_t* cipher_text_len_bytes);
mk_extern_c void mk_aes_128_encrypt_finish(struct mk_aes_128_encrypt_state_s* self, void* cipher_text, size_t* cipher_text_len_bytes);

mk_extern_c void mk_aes_128_encrypt(void const* key, void const* clear_text, size_t clear_text_len, void* cipher_text);


mk_extern_c void mk_aes_encrypt_128(unsigned char const* clear_text, size_t clear_text_len, unsigned char const* key, unsigned char* cipher_text);
mk_extern_c void mk_aes_encrypt_192(unsigned char const* clear_text, size_t clear_text_len, unsigned char const* key, unsigned char* cipher_text);
mk_extern_c void mk_aes_encrypt_256(unsigned char const* clear_text, size_t clear_text_len, unsigned char const* key, unsigned char* cipher_text);
mk_extern_c void mk_aes_encrypt(enum mk_aes_key_len_e key_len, unsigned char const* clear_text, size_t clear_text_len, unsigned char const* key, unsigned char* cipher_text);
void mk_aes_test(void);

#undef mk_extern_c
