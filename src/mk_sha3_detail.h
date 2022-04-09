#ifndef mk_include_guard_sha3_detail
#define mk_include_guard_sha3_detail


#include "../../mk_int/src/exact/mk_uint_64.h"

#include <stddef.h> /* size_t */


#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic" /* warning: comma at end of enumerator list */
#endif


enum mk_sha3_detail_domain_e
{
	mk_sha3_detail_domain_e_sha3,
	mk_sha3_detail_domain_e_shake,
	mk_sha3_detail_domain_e_rawshake,
};


void mk_sha3_detail_init(struct mk_uint64_s state[5][5], int* idx);
void mk_sha3_detail_append_bits(struct mk_uint64_s state[5][5], int* idx, unsigned char* block, int block_len_bits, void const* msg, size_t msg_len_bits);
void mk_sha3_detail_finish(struct mk_uint64_s state[5][5], int* idx, unsigned char* block, int block_len_bits, enum mk_sha3_detail_domain_e domain, void* digest, size_t digest_len_bytes);


#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif


#endif
