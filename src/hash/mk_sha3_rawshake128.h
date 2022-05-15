#ifndef mk_include_guard_sha3_rawshake128
#define mk_include_guard_sha3_rawshake128


#include "base/mk_sha3_rawshake128_base.h"


struct mk_sha3_rawshake128_s
{
	struct mk_sha3_rawshake128_base_s m_state;
	int m_idx;
	unsigned char m_block[168];
};


void mk_sha3_rawshake128_init(struct mk_sha3_rawshake128_s* sha3_rawshake128);
void mk_sha3_rawshake128_append(struct mk_sha3_rawshake128_s* sha3_rawshake128, void const* msg, int msg_len);
void mk_sha3_rawshake128_finish(struct mk_sha3_rawshake128_s* sha3_rawshake128, int digest_len, void* digest);


#endif
