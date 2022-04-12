#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4464) /* warning C4464: relative include path contains '..' */
#endif


#include "../src/mk_md2.c"
#include "../src/mk_md4.c"
#include "../src/mk_md5.c"
#include "../src/mk_sha1.c"
#include "../src/mk_sha2_224.c"
#include "../src/mk_sha2_256.c"
#include "../src/mk_sha2_384.c"
#include "../src/mk_sha2_512.c"
#include "../src/mk_sha2_512224.c"
#include "../src/mk_sha2_512256.c"
#include "../src/mk_sha3_224.c"
#include "../src/mk_sha3_256.c"
#include "../src/mk_sha3_384.c"
#include "../src/mk_sha3_512.c"

#include "../src/mk_sha2_detail_256.c"
#include "../src/mk_sha2_detail_512.c"
#include "../src/mk_sha3_detail.c"

#include "../../mk_int/src/exact/mk_uint_32.c"
#include "../../mk_int/src/exact/mk_uint_64.c"
#include "../../mk_int/src/exact/mk_uint_128.c"

#include "../../mk_int/src/base/mk_uint_base_int.c"
#include "../../mk_int/src/base/mk_uint_base_long.c"
#include "../../mk_int/src/base/mk_uint_base_llong.c"
#include "../../mk_int/src/base/mk_uint_base_128.c"


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
