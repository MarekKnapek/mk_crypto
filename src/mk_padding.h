#ifndef mk_include_guard_padding
#define mk_include_guard_padding


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_padding_e
{
	mk_padding_pkcs7,
	mk_padding_10s,
	mk_padding_10s1,
	mk_padding_zero,
	mk_padding_none,
};


mk_extern_c int mk_padding_add(enum mk_padding_e padding, int block_len, void* input, int input_len);
mk_extern_c int mk_padding_rem(enum mk_padding_e padding, int block_len, void const* input);


#undef mk_extern_c


#endif
