#ifndef mk_include_guard_jumbo
#define mk_include_guard_jumbo


#include "mk_inline.h"


#if defined (mk_want_jumbo) && mk_want_jumbo == 1
#define mk_jumbo static mk_inline
#else
#define mk_jumbo
#endif


#endif
