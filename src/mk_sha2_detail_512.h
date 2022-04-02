#ifndef mk_include_guard_sha2_detail_512
#define mk_include_guard_sha2_detail_512


#include "../../mk_int/src/exact/mk_uint_64.h"
#include "../../mk_int/src/exact/mk_uint_128.h"


void mk_sha2_detail_512_process_block(struct mk_uint64_s state[8], unsigned char const msg[128]);
void mk_sha2_detail_512_append(struct mk_uint64_s state[8], struct mk_uint128_s* len, unsigned char block[128], void const* msg, size_t msg_len_bytes);
void mk_sha2_detail_512_finish(struct mk_uint64_s state[8], struct mk_uint128_s* len, unsigned char block[128], void* digest);


#endif
