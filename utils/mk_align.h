#ifndef mk_include_guard_align
#define mk_include_guard_align


#if __STDC_VERSION__ >= 201112L


#include <stdalign.h>


#define mk_alignof alignof


#elif __cplusplus >= 201103L


#define mk_alignof alignof


#else


#define mk_alignof sizeof


#endif


#endif
