#ifndef mk_include_guard_sha3_rawshake128_base
#define mk_include_guard_sha3_rawshake128_base


#include "mk_sha3_base_detail.h"


struct mk_sha3_rawshake128_base_s
{
	struct mk_sha3_base_detail_s m_sha3;
};


void mk_sha3_rawshake128_base_init(struct mk_sha3_rawshake128_base_s* sha3_rawshake128_base);
void mk_sha3_rawshake128_base_append_blocks(struct mk_sha3_rawshake128_base_s* sha3_rawshake128_base, int nblocks, void const* pblocks);
void mk_sha3_rawshake128_base_finish(struct mk_sha3_rawshake128_base_s* sha3_rawshake128_base, void* block, int idx, int digest_len, void* digest);


#endif