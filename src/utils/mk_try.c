#include "mk_try.h"

#include "mk_jumbo.h"


#if defined(NDEBUG)
#else
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4019) /* warning C4019: empty statement at global scope */
#include <intrin.h>
#pragma warning(pop)
#endif
#endif


mk_jumbo void mk_try_break_point(void)
{
#if defined(NDEBUG)
#else
#if defined(_MSC_VER)
	__debugbreak();
#endif
#endif
}
