#ifndef mk_include_guard_operation_mode_impl
#define mk_include_guard_operation_mode_impl


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


enum mk_operation_mode_detail_max_block_len_e { mk_operation_mode_detail_max_block_len = 16 };


mk_extern_c void mk_operation_mode_detail_xor(int count, unsigned char const* src1, unsigned char const* src2, unsigned char* output);


#undef mk_extern_c


#endif
