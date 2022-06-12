#ifndef mk_include_guard_utils_try
#define mk_include_guard_utils_try


#include "mk_jumbo.h"


mk_jumbo void mk_try_break_point(void);


#ifdef NDEBUG
#define mk_check(x) do{ if(!(x)){ mk_try_break_point(); return 1; } }while(0)
#else
#define mk_check(x) do{ if(!(x)){ mk_try_break_point(); return (int)__LINE__; } }while(0)
#endif

#define mk_try(x) do{ int mk_try_err = (x); if(mk_try_err != 0){ mk_try_break_point(); return mk_try_err; } }while(0)


#endif
