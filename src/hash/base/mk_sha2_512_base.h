#ifndef mk_include_guard_sha2_512_base
#define mk_include_guard_sha2_512_base


#include "mk_sha2_base_detail_512.h"


struct mk_sha2_512_base_s
{
	struct mk_sha2_base_detail_512_s m_512;
};


void mk_sha2_512_base_init(struct mk_sha2_512_base_s* sha2_512_base);
void mk_sha2_512_base_append_blocks(struct mk_sha2_512_base_s* sha2_512_base, int nblocks, void const* pblocks);
void mk_sha2_512_base_finish(struct mk_sha2_512_base_s* sha2_512_base, void* block, int idx, void* digest);


#endif
