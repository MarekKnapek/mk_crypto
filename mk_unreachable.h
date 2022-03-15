#ifndef MK_INCLUDE_GUARD_UNREACHABLE
#define MK_INCLUDE_GUARD_UNREACHABLE


#ifdef _MSC_VER

#define mk_unreachable() __assume(0)

#endif


#endif
