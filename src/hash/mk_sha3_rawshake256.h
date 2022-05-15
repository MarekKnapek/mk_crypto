#ifndef mk_include_guard_sha3_rawshake256
#define mk_include_guard_sha3_rawshake256


#include "base/mk_sha3_rawshake256_base.h"


struct mk_sha3_rawshake256_s
{
	struct mk_sha3_rawshake256_base_s m_state;
	int m_idx;
	unsigned char m_block[136];
};


void mk_sha3_rawshake256_init(struct mk_sha3_rawshake256_s* sha3_rawshake256);
void mk_sha3_rawshake256_append(struct mk_sha3_rawshake256_s* sha3_rawshake256, void const* msg, int msg_len);
void mk_sha3_rawshake256_finish(struct mk_sha3_rawshake256_s* sha3_rawshake256, int digest_len, void* digest);


#endif
