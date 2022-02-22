/* MD4.H - header file for MD4C.C
 */

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
   rights reserved.

   License to copy and use this software is granted provided that it
   is identified as the "RSA Data Security, Inc. MD4 Message-Digest
   Algorithm" in all material mentioning or referencing this software
   or this function.

   License is also granted to make and use derivative works provided
   that such works are identified as "derived from the RSA Data
   Security, Inc. MD4 Message-Digest Algorithm" in all material
   mentioning or referencing the derived work.

   RSA Data Security, Inc. makes no representations concerning either
   the merchantability of this software or the suitability of this
   software for any particular purpose. It is provided "as is"
   without express or implied warranty of any kind.

   These notices must be retained in any copies of any part of this
   documentation and/or software.
 */
#include "global.h"
/* MD4 context. */
typedef struct {
  UINT4 state[4];                                   /* state (ABCD) */
  UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} MD4_CTX;

#ifdef __cplusplus
#define MK_EXTERN_C extern "C"
#else
#define MK_EXTERN_C
#endif


MK_EXTERN_C void MD4Init PROTO_LIST ((MD4_CTX *));
MK_EXTERN_C void MD4Update PROTO_LIST((MD4_CTX *, unsigned char *, unsigned int));
MK_EXTERN_C void MD4Final PROTO_LIST ((unsigned char [16], MD4_CTX *));


#undef MK_EXTERN_C
