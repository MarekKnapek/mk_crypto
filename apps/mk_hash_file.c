#include "mk_hash_file.h"

#include "../src/mk_md2.h"
#include "../src/mk_md4.h"
#include "../src/mk_md5.h"
#include "../src/mk_sha1.h"
#include "../src/mk_sha2_224.h"
#include "../src/mk_sha2_256.h"
#include "../src/mk_sha2_384.h"
#include "../src/mk_sha2_512.h"
#include "../src/mk_sha2_512224.h"
#include "../src/mk_sha2_512256.h"
#include "../src/mk_sha3_224.h"
#include "../src/mk_sha3_256.h"
#include "../src/mk_sha3_384.h"
#include "../src/mk_sha3_512.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <stddef.h> /* NULL size_t */
#include <stdio.h> /* fopen fseek SEEK_END ftell rewind fread feof fclose */
#include <stdlib.h> /* malloc free */


struct hash_states_s
{
	struct mk_md2_state_s m_state_md2;
	struct mk_md4_state_s m_state_md4;
	struct mk_md5_state_s m_state_md5;
	struct mk_sha1_state_s m_state_sha1;
	struct mk_sha2_224_state_s m_state_sha2_224;
	struct mk_sha2_256_state_s m_state_sha2_256;
	struct mk_sha2_384_state_s m_state_sha2_384;
	struct mk_sha2_512_state_s m_state_sha2_512;
	struct mk_sha2_512224_state_s m_state_sha2_512224;
	struct mk_sha2_512256_state_s m_state_sha2_512256;
	struct mk_sha3_224_state_s m_state_sha3_224;
	struct mk_sha3_256_state_s m_state_sha3_256;
	struct mk_sha3_384_state_s m_state_sha3_384;
	struct mk_sha3_512_state_s m_state_sha3_512;
};

typedef void(*init_t)(void* state);
typedef void(*append_t)(void* state, void const* msg, size_t msg_len_bytes);
typedef void(*finish_t)(void* state, void* digest);

struct alg_descr_s
{
	int m_digest_len_bytes;
	int m_offset;
	int m_digest_offset;
	init_t m_init;
	append_t m_append;
	finish_t m_finish;
};

enum mk_hash_file_state_e
{
	mk_hash_file_state_e_open,
	mk_hash_file_state_e_init,
	mk_hash_file_state_e_read,
	mk_hash_file_state_e_append,
	mk_hash_file_state_e_finish,
	mk_hash_file_state_e_done,
};

struct mk_hash_file_s
{
	enum mk_hash_file_state_e m_state;
	char const* m_file_name;
	FILE* m_file;
	unsigned char m_buff[512];
	int m_buff_len;
	long m_read;
	int m_cur_alg;
	long m_steps_total;
	struct hash_states_s m_hash_states;
	struct mk_hash_file_digests_s m_digests;
};


static struct alg_descr_s const s_alg_descrs[] =
{
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_md2),         offsetof(struct hash_states_s, m_state_md2),         offsetof(struct mk_hash_file_digests_s, m_md2),         (init_t)&mk_md2_init,         (append_t)&mk_md2_append,         (finish_t)&mk_md2_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_md4),         offsetof(struct hash_states_s, m_state_md4),         offsetof(struct mk_hash_file_digests_s, m_md4),         (init_t)&mk_md4_init,         (append_t)&mk_md4_append,         (finish_t)&mk_md4_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_md5),         offsetof(struct hash_states_s, m_state_md5),         offsetof(struct mk_hash_file_digests_s, m_md5),         (init_t)&mk_md5_init,         (append_t)&mk_md5_append,         (finish_t)&mk_md5_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha1),        offsetof(struct hash_states_s, m_state_sha1),        offsetof(struct mk_hash_file_digests_s, m_sha1),        (init_t)&mk_sha1_init,        (append_t)&mk_sha1_append,        (finish_t)&mk_sha1_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_224),    offsetof(struct hash_states_s, m_state_sha2_224),    offsetof(struct mk_hash_file_digests_s, m_sha2_224),    (init_t)&mk_sha2_224_init,    (append_t)&mk_sha2_224_append,    (finish_t)&mk_sha2_224_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_256),    offsetof(struct hash_states_s, m_state_sha2_256),    offsetof(struct mk_hash_file_digests_s, m_sha2_256),    (init_t)&mk_sha2_256_init,    (append_t)&mk_sha2_256_append,    (finish_t)&mk_sha2_256_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_384),    offsetof(struct hash_states_s, m_state_sha2_384),    offsetof(struct mk_hash_file_digests_s, m_sha2_384),    (init_t)&mk_sha2_384_init,    (append_t)&mk_sha2_384_append,    (finish_t)&mk_sha2_384_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_512),    offsetof(struct hash_states_s, m_state_sha2_512),    offsetof(struct mk_hash_file_digests_s, m_sha2_512),    (init_t)&mk_sha2_512_init,    (append_t)&mk_sha2_512_append,    (finish_t)&mk_sha2_512_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_512224), offsetof(struct hash_states_s, m_state_sha2_512224), offsetof(struct mk_hash_file_digests_s, m_sha2_512224), (init_t)&mk_sha2_512224_init, (append_t)&mk_sha2_512224_append, (finish_t)&mk_sha2_512224_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_512256), offsetof(struct hash_states_s, m_state_sha2_512256), offsetof(struct mk_hash_file_digests_s, m_sha2_512256), (init_t)&mk_sha2_512256_init, (append_t)&mk_sha2_512256_append, (finish_t)&mk_sha2_512256_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_224),    offsetof(struct hash_states_s, m_state_sha3_224),    offsetof(struct mk_hash_file_digests_s, m_sha3_224),    (init_t)&mk_sha3_224_init,    (append_t)&mk_sha3_224_append,    (finish_t)&mk_sha3_224_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_256),    offsetof(struct hash_states_s, m_state_sha3_256),    offsetof(struct mk_hash_file_digests_s, m_sha3_256),    (init_t)&mk_sha3_256_init,    (append_t)&mk_sha3_256_append,    (finish_t)&mk_sha3_256_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_384),    offsetof(struct hash_states_s, m_state_sha3_384),    offsetof(struct mk_hash_file_digests_s, m_sha3_384),    (init_t)&mk_sha3_384_init,    (append_t)&mk_sha3_384_append,    (finish_t)&mk_sha3_384_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_512),    offsetof(struct hash_states_s, m_state_sha3_512),    offsetof(struct mk_hash_file_digests_s, m_sha3_512),    (init_t)&mk_sha3_512_init,    (append_t)&mk_sha3_512_append,    (finish_t)&mk_sha3_512_finish},
};


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err; err = (x); if(err != 0){ return err; } }while(0)


static mk_inline int mk_hash_file_step_open(struct mk_hash_file_s* self)
{
	long file_len;
	int alg_count;
	long chunk_count;

	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_e_open);
	mk_assert(self->m_file_name);

	self->m_file = fopen(self->m_file_name, "rb");
	mk_check(self->m_file);

	mk_check(fseek(self->m_file, 0, SEEK_END) == 0);
	file_len = ftell(self->m_file);
	mk_check(file_len != -1);
	rewind(self->m_file);

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	chunk_count = (file_len + (int)sizeof(self->m_buff) - 1) / (int)sizeof(self->m_buff);
	self->m_steps_total = alg_count + chunk_count * (1 + alg_count) + alg_count;

	self->m_cur_alg = 0;
	self->m_state = mk_hash_file_state_e_init;
	return 0;
}

static mk_inline int mk_hash_file_step_init(struct mk_hash_file_s* self)
{
	void* hash_state;
	int alg_count;

	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_e_init);

	hash_state = (unsigned char*)&self->m_hash_states + s_alg_descrs[self->m_cur_alg].m_offset;
	s_alg_descrs[self->m_cur_alg].m_init(hash_state);
	++self->m_cur_alg;

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	if(self->m_cur_alg == alg_count)
	{
		self->m_state = mk_hash_file_state_e_read;
	}
	return 0;
}

static mk_inline int mk_hash_file_step_read(struct mk_hash_file_s* self)
{
	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_e_read);

	self->m_buff_len = (int)fread(self->m_buff, 1, sizeof(self->m_buff), self->m_file);
	if(self->m_buff_len == 0)
	{
		mk_check(feof(self->m_file) != 0);
		mk_check(fclose(self->m_file) == 0);
		self->m_file = NULL;
		self->m_cur_alg = 0;
		self->m_state = mk_hash_file_state_e_finish;
		return 0;
	}
	self->m_read += self->m_buff_len;

	self->m_cur_alg = 0;
	self->m_state = mk_hash_file_state_e_append;
	return 0;
}

static mk_inline int mk_hash_file_step_append(struct mk_hash_file_s* self)
{
	void* hash_state;
	int alg_count;

	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_e_append);

	hash_state = (unsigned char*)&self->m_hash_states + s_alg_descrs[self->m_cur_alg].m_offset;
	s_alg_descrs[self->m_cur_alg].m_append(hash_state, self->m_buff, self->m_buff_len);
	++self->m_cur_alg;

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	if(self->m_cur_alg == alg_count)
	{
		self->m_state = mk_hash_file_state_e_read;
	}
	return 0;
}

static mk_inline int mk_hash_file_step_finish(struct mk_hash_file_s* self)
{
	void* hash_state;
	void* digest;
	int alg_count;

	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_e_finish);

	hash_state = (unsigned char*)&self->m_hash_states + s_alg_descrs[self->m_cur_alg].m_offset;
	digest = (unsigned char*)&self->m_digests + s_alg_descrs[self->m_cur_alg].m_digest_offset;
	s_alg_descrs[self->m_cur_alg].m_finish(hash_state, digest);
	++self->m_cur_alg;

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	if(self->m_cur_alg == alg_count)
	{
		self->m_state = mk_hash_file_state_e_done;
	}
	return 0;
}


mk_hash_file_handle mk_hash_file_create(char const* file_name)
{
	struct mk_hash_file_s* self;

	mk_assert(file_name);

	self = malloc(sizeof(struct mk_hash_file_s));
	if(!self)
	{
		return NULL;
	}

	self->m_state = mk_hash_file_state_e_open;
	self->m_file_name = file_name;
	self->m_file = NULL;
	self->m_read = 0;
	self->m_steps_total = 0;

	return self;
}

int mk_hash_file_step(mk_hash_file_handle hash_file)
{
	struct mk_hash_file_s* self;

	mk_assert(hash_file);

	self = (struct mk_hash_file_s*)hash_file;
	mk_assert(self->m_state >= mk_hash_file_state_e_open && self->m_state <= mk_hash_file_state_e_done);

	switch(self->m_state)
	{
		case mk_hash_file_state_e_open:   return mk_hash_file_step_open(self);   break;
		case mk_hash_file_state_e_init:   return mk_hash_file_step_init(self);   break;
		case mk_hash_file_state_e_read:   return mk_hash_file_step_read(self);   break;
		case mk_hash_file_state_e_append: return mk_hash_file_step_append(self); break;
		case mk_hash_file_state_e_finish: return mk_hash_file_step_finish(self); break;
		case mk_hash_file_state_e_done:   return 1;                              break;
	};

	return 0;
}

int mk_hash_file_get_progress(mk_hash_file_handle hash_file, int* progress)
{
	struct mk_hash_file_s const* self;
	int alg_count;
	int chunk_count;
	long steps;

	mk_assert(hash_file);
	mk_assert(progress);

	self = (struct mk_hash_file_s const*)hash_file;

	if(self->m_steps_total == 0)
	{
		*progress = 0;
		return 0;
	}

	#define mk_max(a, b) ((a) < (b) ? (b) : (a))
	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	chunk_count = (self->m_read + (int)sizeof(self->m_buff) - 1) / (int)sizeof(self->m_buff);
	steps = 0;
	mk_assert(self->m_state >= mk_hash_file_state_e_init && self->m_state <= mk_hash_file_state_e_done);
	switch(self->m_state)
	{
		case mk_hash_file_state_e_open: mk_assert(0); break;
		case mk_hash_file_state_e_init: steps = self->m_cur_alg; break;
		case mk_hash_file_state_e_read: steps = alg_count + chunk_count * (1 + alg_count); break;
		case mk_hash_file_state_e_append: steps = alg_count + mk_max(0, chunk_count - 1) * (1 + alg_count) + 1 + self->m_cur_alg; break;
		case mk_hash_file_state_e_finish: steps = alg_count + chunk_count * (1 + alg_count) + self->m_cur_alg; break;
		case mk_hash_file_state_e_done: steps = self->m_steps_total; break;
	};
	#undef mk_max

	*progress = (int)((steps * 100 * 100) / self->m_steps_total);
	return 0;
}

int mk_hash_file_get_result(mk_hash_file_handle hash_file, struct mk_hash_file_digests_s** result)
{
	struct mk_hash_file_s* self;

	mk_assert(hash_file);
	mk_assert(result);

	self = (struct mk_hash_file_s*)hash_file;
	mk_assert(self->m_state == mk_hash_file_state_e_done);

	*result = &self->m_digests;
	return 0;
}

int mk_hash_file_destroy(mk_hash_file_handle hash_file)
{
	struct mk_hash_file_s* self;
	
	mk_assert(hash_file);

	self = (struct mk_hash_file_s*)hash_file;
	
	if(self->m_file)
	{
		mk_check(fclose(self->m_file) == 0);
	}
	
	free(self);

	return 0;
}


#undef mk_check
#undef mk_try
