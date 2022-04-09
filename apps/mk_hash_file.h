#ifndef mk_include_guard_hash_file
#define mk_include_guard_hash_file


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


typedef void* mk_hash_file_handle;

struct mk_hash_file_digests_s
{
	unsigned char m_md2[16];
	unsigned char m_md4[16];
	unsigned char m_md5[16];
	unsigned char m_sha1[20];
	unsigned char m_sha2_224[28];
	unsigned char m_sha2_256[32];
	unsigned char m_sha2_384[48];
	unsigned char m_sha2_512[64];
	unsigned char m_sha2_512224[28];
	unsigned char m_sha2_512256[32];
	unsigned char m_sha3_224[28];
	unsigned char m_sha3_256[32];
	unsigned char m_sha3_384[48];
	unsigned char m_sha3_512[64];
};


mk_extern_c mk_hash_file_handle mk_hash_file_create(char const* file_name);
mk_extern_c int mk_hash_file_step(mk_hash_file_handle hash_file);
mk_extern_c int mk_hash_file_get_progress(mk_hash_file_handle hash_file, int* progress);
mk_extern_c int mk_hash_file_get_result(mk_hash_file_handle hash_file, struct mk_hash_file_digests_s** result);
mk_extern_c int mk_hash_file_destroy(mk_hash_file_handle hash_file);


#undef mk_extern_c


#endif
