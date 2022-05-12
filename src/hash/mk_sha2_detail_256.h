#ifndef mk_include_guard_sha2_detail_256
#define mk_include_guard_sha2_detail_256


#include "../../../mk_int/src/exact/mk_uint_32.h"
#include "../../../mk_int/src/exact/mk_uint_64.h"


void mk_sha2_detail_256_process_block(struct mk_uint32_s state[8], unsigned char const msg[64]);
void mk_sha2_detail_256_append(struct mk_uint32_s state[8], struct mk_uint64_s* len, unsigned char block[64], void const* msg, size_t msg_len_bytes);
void mk_sha2_detail_256_finish(struct mk_uint32_s state[8], struct mk_uint64_s* len, unsigned char block[64], void* digest);


#endif
