#ifndef MK_INCLUDE_GUARD_ASSERT
#define MK_INCLUDE_GUARD_ASSERT


#ifdef NDEBUG


#include "mk_unreachable.h"


#define MK_ASSERT(X) do{ if(!(X)){ mk_unreachable(); } }while(0)


#else


#include <assert.h>


#define MK_ASSERT assert


#endif


#endif
