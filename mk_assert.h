#ifndef mk_include_guard_assert
#define mk_include_guard_assert


#ifdef NDEBUG


#define mk_assert(x) (__assume(x))


#else


#include <assert.h>


#define mk_assert assert


#endif


#endif
