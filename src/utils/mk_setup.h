#ifndef mk_include_guard_setup
#define mk_include_guard_setup


#if (defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 199711L)
#define mk_uint_has_inline 1
#else
#define mk_uint_has_inline 0
#endif


#if (defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L)
#define mk_uint_has_long_long 1
#else
#define mk_uint_has_long_long 0
#endif


#if defined(__SIZEOF_INT128__) && __SIZEOF_INT128__
#define mk_uint_has_128bit_int 1
#else
#define mk_uint_has_128bit_int 0
#endif


#endif
