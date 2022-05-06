#ifndef mk_include_guard_assert
#define mk_include_guard_assert


#ifdef NDEBUG


#if defined(_MSC_VER) && _MSC_VER >= 1200
#define mk_assert(x) __assume(x)
#elif defined (__GNUC__)
#define mk_assert(x) do{ if(!(x)){ __builtin_unreachable(); } }while(0)
#else
#define mk_assert(x) ((void)0)
#endif


#else


#include <assert.h>


#define mk_assert assert


#endif


#endif
