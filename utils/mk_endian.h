#ifndef MK_INCLUDE_GUARD_ENDIAN
#define MK_INCLUDE_GUARD_ENDIAN


#define MK_ENDIAN_LITTLE 1
#define MK_ENDIAN_BIG 2
#define MK_ENDIAN_UNKNOWN 3

#define MK_ENDIAN MK_ENDIAN_UNKNOWN

#ifdef _MSC_VER
#undef MK_ENDIAN
#define MK_ENDIAN MK_ENDIAN_LITTLE
#endif


#endif
