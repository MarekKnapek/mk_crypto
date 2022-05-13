#ifndef mk_include_guard_md2
#define mk_include_guard_md2


struct mk_md2_s
{
	unsigned char m_state[2 * 16];
	int m_idx;
	unsigned char m_block[16];
};


void mk_md2_init(struct mk_md2_s* self);
void mk_md2_append(struct mk_md2_s* self, void const* msg, int msg_len);
void mk_md2_finish(struct mk_md2_s* self, void* digest);


#endif
