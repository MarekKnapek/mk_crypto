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
	mk_hash_file_state_e_init,
	mk_hash_file_state_e_file_open,
	mk_hash_file_state_e_file_read,
	mk_hash_file_state_e_finish,
	mk_hash_file_state_e_done,
};

struct mk_hash_file_s
{
	enum mk_hash_file_state_e m_state;
	char const* m_file_name;
	FILE* m_file;
	long m_file_len;
	long m_read;
	struct hash_states_s m_hash_states;
	struct mk_hash_file_digests_s m_digests;
};


static struct alg_descr_s const s_alg_descrs[] =
{
	{16, offsetof(struct hash_states_s, m_state_md2),         offsetof(struct mk_hash_file_digests_s, m_md2),         (init_t)&mk_md2_init,         (append_t)&mk_md2_append,         (finish_t)&mk_md2_finish},
	{16, offsetof(struct hash_states_s, m_state_md4),         offsetof(struct mk_hash_file_digests_s, m_md4),         (init_t)&mk_md4_init,         (append_t)&mk_md4_append,         (finish_t)&mk_md4_finish},
	{16, offsetof(struct hash_states_s, m_state_md5),         offsetof(struct mk_hash_file_digests_s, m_md5),         (init_t)&mk_md5_init,         (append_t)&mk_md5_append,         (finish_t)&mk_md5_finish},
	{20, offsetof(struct hash_states_s, m_state_sha1),        offsetof(struct mk_hash_file_digests_s, m_sha1),        (init_t)&mk_sha1_init,        (append_t)&mk_sha1_append,        (finish_t)&mk_sha1_finish},
	{28, offsetof(struct hash_states_s, m_state_sha2_224),    offsetof(struct mk_hash_file_digests_s, m_sha2_224),    (init_t)&mk_sha2_224_init,    (append_t)&mk_sha2_224_append,    (finish_t)&mk_sha2_224_finish},
	{32, offsetof(struct hash_states_s, m_state_sha2_256),    offsetof(struct mk_hash_file_digests_s, m_sha2_256),    (init_t)&mk_sha2_256_init,    (append_t)&mk_sha2_256_append,    (finish_t)&mk_sha2_256_finish},
	{48, offsetof(struct hash_states_s, m_state_sha2_384),    offsetof(struct mk_hash_file_digests_s, m_sha2_384),    (init_t)&mk_sha2_384_init,    (append_t)&mk_sha2_384_append,    (finish_t)&mk_sha2_384_finish},
	{64, offsetof(struct hash_states_s, m_state_sha2_512),    offsetof(struct mk_hash_file_digests_s, m_sha2_512),    (init_t)&mk_sha2_512_init,    (append_t)&mk_sha2_512_append,    (finish_t)&mk_sha2_512_finish},
	{28, offsetof(struct hash_states_s, m_state_sha2_512224), offsetof(struct mk_hash_file_digests_s, m_sha2_512224), (init_t)&mk_sha2_512224_init, (append_t)&mk_sha2_512224_append, (finish_t)&mk_sha2_512224_finish},
	{32, offsetof(struct hash_states_s, m_state_sha2_512256), offsetof(struct mk_hash_file_digests_s, m_sha2_512256), (init_t)&mk_sha2_512256_init, (append_t)&mk_sha2_512256_append, (finish_t)&mk_sha2_512256_finish},
};


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err; err = (x); if(err != 0){ return err; } }while(0)


static mk_inline int mk_hash_file_step_init(struct mk_hash_file_s* self)
{
	int alg_count;
	int i;
	void* hash_state;

	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_e_init);

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	for(i = 0; i != alg_count; ++i)
	{
		hash_state = (unsigned char*)&self->m_hash_states + s_alg_descrs[i].m_offset;
		s_alg_descrs[i].m_init(hash_state);
	}

	self->m_state = mk_hash_file_state_e_file_open;
	return 0;
}

static mk_inline int mk_hash_file_step_file_open(struct mk_hash_file_s* self)
{
	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_e_file_open);
	mk_assert(self->m_file_name);

	self->m_file = fopen(self->m_file_name, "rb");
	mk_check(self->m_file);

	mk_check(fseek(self->m_file, 0, SEEK_END) == 0);
	self->m_file_len = ftell(self->m_file);
	mk_check(self->m_file_len != -1);
	rewind(self->m_file);

	self->m_state = mk_hash_file_state_e_file_read;
	return 0;
}

static mk_inline int mk_hash_file_step_file_read(struct mk_hash_file_s* self)
{
	size_t read;
	unsigned char buff[1 * 1024];
	int alg_count;
	int i;
	void* hash_state;

	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_e_file_read);

	read = fread(buff, 1, sizeof(buff), self->m_file);
	if(read == 0)
	{
		mk_check(feof(self->m_file) != 0);
		mk_check(fclose(self->m_file) == 0);
		self->m_file = NULL;
		self->m_state = mk_hash_file_state_e_finish;
		return 0;
	}
	self->m_read += (long)read;
	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	for(i = 0; i != alg_count; ++i)
	{
		hash_state = (unsigned char*)&self->m_hash_states + s_alg_descrs[i].m_offset;
		s_alg_descrs[i].m_append(hash_state, buff, read);
	}

	return 0;
}

static mk_inline int mk_hash_file_step_finish(struct mk_hash_file_s* self)
{
	int alg_count;
	int i;
	void* hash_state;
	void* digest;

	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_e_finish);

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	for(i = 0; i != alg_count; ++i)
	{
		hash_state = (unsigned char*)&self->m_hash_states + s_alg_descrs[i].m_offset;
		digest = (unsigned char*)&self->m_digests + s_alg_descrs[i].m_digest_offset;
		s_alg_descrs[i].m_finish(hash_state, digest);
	}

	self->m_state = mk_hash_file_state_e_done;
	return 0;
}


mk_hash_file_handle mk_hash_file_create(char const* file_name)
{
	struct mk_hash_file_s* hash_file;

	mk_assert(file_name);

	hash_file = malloc(sizeof(struct mk_hash_file_s));
	if(!hash_file)
	{
		return NULL;
	}

	hash_file->m_state = mk_hash_file_state_e_init;
	hash_file->m_file_name = file_name;
	hash_file->m_file = NULL;
	hash_file->m_file_len = 0;
	hash_file->m_read = 0;

	return hash_file;
}

int mk_hash_file_step(mk_hash_file_handle hash_file)
{
	struct mk_hash_file_s* self;

	mk_assert(hash_file);

	self = (struct mk_hash_file_s*)hash_file;
	mk_assert(self->m_state >= mk_hash_file_state_e_init && self->m_state <= mk_hash_file_state_e_done);

	switch(self->m_state)
	{
		case mk_hash_file_state_e_init:      mk_try(mk_hash_file_step_init(self));      break;
		case mk_hash_file_state_e_file_open: mk_try(mk_hash_file_step_file_open(self)); break;
		case mk_hash_file_state_e_file_read: mk_try(mk_hash_file_step_file_read(self)); break;
		case mk_hash_file_state_e_finish:    mk_try(mk_hash_file_step_finish(self));    break;
		case mk_hash_file_state_e_done:      return 1;                                  break;
	};

	return 0;
}

int mk_hash_file_get_progress(mk_hash_file_handle hash_file, int* progress)
{
	struct mk_hash_file_s* self;

	mk_assert(hash_file);
	mk_assert(progress);

	self = (struct mk_hash_file_s*)hash_file;
	if(self->m_file_len == 0)
	{
		*progress = 0;
		return 0;
	}

	*progress = (int)(((self->m_read / 1024) * 100 * 100) / (self->m_file_len / 1024));

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

int mk_hash_file_free(mk_hash_file_handle hash_file)
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
