#ifndef MK_INCLUDE_GUARD_ASSERT
#define MK_INCLUDE_GUARD_ASSERT


#ifdef NDEBUG


#define MK_ASSERT(x) (__assume(x))


#else


#include <assert.h>


#define MK_ASSERT assert


#endif


#endif
