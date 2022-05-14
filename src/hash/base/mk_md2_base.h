#ifndef mk_include_guard_md2_base
#define mk_include_guard_md2_base


struct mk_md2_base_s
{
	unsigned char m_state[16];
	unsigned char m_checksum[16];
};


void mk_md2_base_init(struct mk_md2_base_s* md2_base);
void mk_md2_base_append_blocks(struct mk_md2_base_s* md2_base, int nblocks, void const* pblocks);
void mk_md2_base_finish(struct mk_md2_base_s* md2_base, void* block, int idx, void* digest);


#endif
