#ifndef mk_include_guard_md2_base
#define mk_include_guard_md2_base


void mk_md2_base_init(void* state);
void mk_md2_base_append_blocks(void* state, int nblocks, void const* pblocks);
void mk_md2_base_finish(void* state, void const* msg, int msg_len, void* digest);


#endif
