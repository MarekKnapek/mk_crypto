#include "mk_hash_file.h"

#include "../../src/hash/hash/mk_hash_hash_md2.h"
#include "../../src/hash/hash/mk_hash_hash_md4.h"
#include "../../src/hash/hash/mk_hash_hash_md5.h"
#include "../../src/hash/hash/mk_hash_hash_sha1.h"
#include "../../src/hash/hash/mk_hash_hash_sha2_224.h"
#include "../../src/hash/hash/mk_hash_hash_sha2_256.h"
#include "../../src/hash/hash/mk_hash_hash_sha2_384.h"
#include "../../src/hash/hash/mk_hash_hash_sha2_512.h"
#include "../../src/hash/hash/mk_hash_hash_sha2_512224.h"
#include "../../src/hash/hash/mk_hash_hash_sha2_512256.h"
#include "../../src/hash/hash/mk_hash_hash_sha3_224.h"
#include "../../src/hash/hash/mk_hash_hash_sha3_256.h"
#include "../../src/hash/hash/mk_hash_hash_sha3_384.h"
#include "../../src/hash/hash/mk_hash_hash_sha3_512.h"

#include "../../src/utils/mk_assert.h"
#include "../../src/utils/mk_inline.h"
#include "../../src/utils/mk_jumbo.h"

#include <stddef.h> /* NULL */
#include <stdio.h> /* fopen fseek SEEK_END ftell rewind fread feof fclose */
#include <stdlib.h> /* malloc free */


static mk_inline void cast_md2_init(void* self){ mk_hash_hash_md2_init((struct mk_hash_hash_md2_s*)self); }
static mk_inline void cast_md4_init(void* self){ mk_hash_hash_md4_init((struct mk_hash_hash_md4_s*)self); }
static mk_inline void cast_md5_init(void* self){ mk_hash_hash_md5_init((struct mk_hash_hash_md5_s*)self); }
static mk_inline void cast_sha1_init(void* self){ mk_hash_hash_sha1_init((struct mk_hash_hash_sha1_s*)self); }
static mk_inline void cast_sha2_224_init(void* self){ mk_hash_hash_sha2_224_init((struct mk_hash_hash_sha2_224_s*)self); }
static mk_inline void cast_sha2_256_init(void* self){ mk_hash_hash_sha2_256_init((struct mk_hash_hash_sha2_256_s*)self); }
static mk_inline void cast_sha2_384_init(void* self){ mk_hash_hash_sha2_384_init((struct mk_hash_hash_sha2_384_s*)self); }
static mk_inline void cast_sha2_512_init(void* self){ mk_hash_hash_sha2_512_init((struct mk_hash_hash_sha2_512_s*)self); }
static mk_inline void cast_sha2_512224_init(void* self){ mk_hash_hash_sha2_512224_init((struct mk_hash_hash_sha2_512224_s*)self); }
static mk_inline void cast_sha2_512256_init(void* self){ mk_hash_hash_sha2_512256_init((struct mk_hash_hash_sha2_512256_s*)self); }
static mk_inline void cast_sha3_224_init(void* self){ mk_hash_hash_sha3_224_init((struct mk_hash_hash_sha3_224_s*)self); }
static mk_inline void cast_sha3_256_init(void* self){ mk_hash_hash_sha3_256_init((struct mk_hash_hash_sha3_256_s*)self); }
static mk_inline void cast_sha3_384_init(void* self){ mk_hash_hash_sha3_384_init((struct mk_hash_hash_sha3_384_s*)self); }
static mk_inline void cast_sha3_512_init(void* self){ mk_hash_hash_sha3_512_init((struct mk_hash_hash_sha3_512_s*)self); }

static mk_inline void cast_md2_append(void* self, void const* msg, int msg_len){ mk_hash_hash_md2_append((struct mk_hash_hash_md2_s*)self, msg, msg_len); }
static mk_inline void cast_md4_append(void* self, void const* msg, int msg_len){ mk_hash_hash_md4_append((struct mk_hash_hash_md4_s*)self, msg, msg_len); }
static mk_inline void cast_md5_append(void* self, void const* msg, int msg_len){ mk_hash_hash_md5_append((struct mk_hash_hash_md5_s*)self, msg, msg_len); }
static mk_inline void cast_sha1_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha1_append((struct mk_hash_hash_sha1_s*)self, msg, msg_len); }
static mk_inline void cast_sha2_224_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha2_224_append((struct mk_hash_hash_sha2_224_s*)self, msg, msg_len); }
static mk_inline void cast_sha2_256_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha2_256_append((struct mk_hash_hash_sha2_256_s*)self, msg, msg_len); }
static mk_inline void cast_sha2_384_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha2_384_append((struct mk_hash_hash_sha2_384_s*)self, msg, msg_len); }
static mk_inline void cast_sha2_512_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha2_512_append((struct mk_hash_hash_sha2_512_s*)self, msg, msg_len); }
static mk_inline void cast_sha2_512224_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha2_512224_append((struct mk_hash_hash_sha2_512224_s*)self, msg, msg_len); }
static mk_inline void cast_sha2_512256_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha2_512256_append((struct mk_hash_hash_sha2_512256_s*)self, msg, msg_len); }
static mk_inline void cast_sha3_224_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha3_224_append((struct mk_hash_hash_sha3_224_s*)self, msg, msg_len); }
static mk_inline void cast_sha3_256_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha3_256_append((struct mk_hash_hash_sha3_256_s*)self, msg, msg_len); }
static mk_inline void cast_sha3_384_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha3_384_append((struct mk_hash_hash_sha3_384_s*)self, msg, msg_len); }
static mk_inline void cast_sha3_512_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha3_512_append((struct mk_hash_hash_sha3_512_s*)self, msg, msg_len); }

static mk_inline void cast_md2_finish(void* self, void* digest){ mk_hash_hash_md2_finish((struct mk_hash_hash_md2_s*)self, digest); }
static mk_inline void cast_md4_finish(void* self, void* digest){ mk_hash_hash_md4_finish((struct mk_hash_hash_md4_s*)self, digest); }
static mk_inline void cast_md5_finish(void* self, void* digest){ mk_hash_hash_md5_finish((struct mk_hash_hash_md5_s*)self, digest); }
static mk_inline void cast_sha1_finish(void* self, void* digest){ mk_hash_hash_sha1_finish((struct mk_hash_hash_sha1_s*)self, digest); }
static mk_inline void cast_sha2_224_finish(void* self, void* digest){ mk_hash_hash_sha2_224_finish((struct mk_hash_hash_sha2_224_s*)self, digest); }
static mk_inline void cast_sha2_256_finish(void* self, void* digest){ mk_hash_hash_sha2_256_finish((struct mk_hash_hash_sha2_256_s*)self, digest); }
static mk_inline void cast_sha2_384_finish(void* self, void* digest){ mk_hash_hash_sha2_384_finish((struct mk_hash_hash_sha2_384_s*)self, digest); }
static mk_inline void cast_sha2_512_finish(void* self, void* digest){ mk_hash_hash_sha2_512_finish((struct mk_hash_hash_sha2_512_s*)self, digest); }
static mk_inline void cast_sha2_512224_finish(void* self, void* digest){ mk_hash_hash_sha2_512224_finish((struct mk_hash_hash_sha2_512224_s*)self, digest); }
static mk_inline void cast_sha2_512256_finish(void* self, void* digest){ mk_hash_hash_sha2_512256_finish((struct mk_hash_hash_sha2_512256_s*)self, digest); }
static mk_inline void cast_sha3_224_finish(void* self, void* digest){ mk_hash_hash_sha3_224_finish((struct mk_hash_hash_sha3_224_s*)self, digest); }
static mk_inline void cast_sha3_256_finish(void* self, void* digest){ mk_hash_hash_sha3_256_finish((struct mk_hash_hash_sha3_256_s*)self, digest); }
static mk_inline void cast_sha3_384_finish(void* self, void* digest){ mk_hash_hash_sha3_384_finish((struct mk_hash_hash_sha3_384_s*)self, digest); }
static mk_inline void cast_sha3_512_finish(void* self, void* digest){ mk_hash_hash_sha3_512_finish((struct mk_hash_hash_sha3_512_s*)self, digest); }


struct hash_states_s
{
	struct mk_hash_hash_md2_s m_md2;
	struct mk_hash_hash_md4_s m_md4;
	struct mk_hash_hash_md5_s m_md5;
	struct mk_hash_hash_sha1_s m_sha1;
	struct mk_hash_hash_sha2_224_s m_sha2_224;
	struct mk_hash_hash_sha2_256_s m_sha2_256;
	struct mk_hash_hash_sha2_384_s m_sha2_384;
	struct mk_hash_hash_sha2_512_s m_sha2_512;
	struct mk_hash_hash_sha2_512224_s m_sha2_512224;
	struct mk_hash_hash_sha2_512256_s m_sha2_512256;
	struct mk_hash_hash_sha3_224_s m_sha3_224;
	struct mk_hash_hash_sha3_256_s m_sha3_256;
	struct mk_hash_hash_sha3_384_s m_sha3_384;
	struct mk_hash_hash_sha3_512_s m_sha3_512;
};

typedef void(*init_t)(void* state);
typedef void(*append_t)(void* state, void const* msg, int msg_len);
typedef void(*finish_t)(void* state, void* digest);

struct alg_descr_s
{
	int m_digest_len;
	int m_offset;
	int m_digest_offset;
	init_t m_init;
	append_t m_append;
	finish_t m_finish;
};

enum mk_hash_file_state_e
{
	mk_hash_file_state_init,
	mk_hash_file_state_read,
	mk_hash_file_state_append,
	mk_hash_file_state_finish,
	mk_hash_file_state_done,
};

struct mk_hash_file_s
{
	enum mk_hash_file_state_e m_state;
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
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_md2),         offsetof(struct hash_states_s, m_md2),         offsetof(struct mk_hash_file_digests_s, m_md2),         &cast_md2_init,         &cast_md2_append,         &cast_md2_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_md4),         offsetof(struct hash_states_s, m_md4),         offsetof(struct mk_hash_file_digests_s, m_md4),         &cast_md4_init,         &cast_md4_append,         &cast_md4_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_md5),         offsetof(struct hash_states_s, m_md5),         offsetof(struct mk_hash_file_digests_s, m_md5),         &cast_md5_init,         &cast_md5_append,         &cast_md5_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha1),        offsetof(struct hash_states_s, m_sha1),        offsetof(struct mk_hash_file_digests_s, m_sha1),        &cast_sha1_init,        &cast_sha1_append,        &cast_sha1_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_224),    offsetof(struct hash_states_s, m_sha2_224),    offsetof(struct mk_hash_file_digests_s, m_sha2_224),    &cast_sha2_224_init,    &cast_sha2_224_append,    &cast_sha2_224_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_256),    offsetof(struct hash_states_s, m_sha2_256),    offsetof(struct mk_hash_file_digests_s, m_sha2_256),    &cast_sha2_256_init,    &cast_sha2_256_append,    &cast_sha2_256_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_384),    offsetof(struct hash_states_s, m_sha2_384),    offsetof(struct mk_hash_file_digests_s, m_sha2_384),    &cast_sha2_384_init,    &cast_sha2_384_append,    &cast_sha2_384_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_512),    offsetof(struct hash_states_s, m_sha2_512),    offsetof(struct mk_hash_file_digests_s, m_sha2_512),    &cast_sha2_512_init,    &cast_sha2_512_append,    &cast_sha2_512_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_512224), offsetof(struct hash_states_s, m_sha2_512224), offsetof(struct mk_hash_file_digests_s, m_sha2_512224), &cast_sha2_512224_init, &cast_sha2_512224_append, &cast_sha2_512224_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha2_512256), offsetof(struct hash_states_s, m_sha2_512256), offsetof(struct mk_hash_file_digests_s, m_sha2_512256), &cast_sha2_512256_init, &cast_sha2_512256_append, &cast_sha2_512256_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_224),    offsetof(struct hash_states_s, m_sha3_224),    offsetof(struct mk_hash_file_digests_s, m_sha3_224),    &cast_sha3_224_init,    &cast_sha3_224_append,    &cast_sha3_224_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_256),    offsetof(struct hash_states_s, m_sha3_256),    offsetof(struct mk_hash_file_digests_s, m_sha3_256),    &cast_sha3_256_init,    &cast_sha3_256_append,    &cast_sha3_256_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_384),    offsetof(struct hash_states_s, m_sha3_384),    offsetof(struct mk_hash_file_digests_s, m_sha3_384),    &cast_sha3_384_init,    &cast_sha3_384_append,    &cast_sha3_384_finish},
	{sizeof(((struct mk_hash_file_digests_s*)0)->m_sha3_512),    offsetof(struct hash_states_s, m_sha3_512),    offsetof(struct mk_hash_file_digests_s, m_sha3_512),    &cast_sha3_512_init,    &cast_sha3_512_append,    &cast_sha3_512_finish},
};


#ifdef NDEBUG
#define mk_check(x) do{ if(!(x)){ return 1; } }while(0)
#else
#define mk_check(x) do{ if(!(x)){ return (int)__LINE__; } }while(0)
#endif
#define mk_try(x) do{ int err; err = (x); if(err != 0){ return err; } }while(0)


static mk_inline int mk_hash_file_step_init(struct mk_hash_file_s* self)
{
	void* hash_state;
	int alg_count;

	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_init);

	hash_state = (unsigned char*)&self->m_hash_states + s_alg_descrs[self->m_cur_alg].m_offset;
	s_alg_descrs[self->m_cur_alg].m_init(hash_state);
	++self->m_cur_alg;

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	if(self->m_cur_alg == alg_count)
	{
		self->m_state = mk_hash_file_state_read;
	}
	return 0;
}

static mk_inline int mk_hash_file_step_read(struct mk_hash_file_s* self)
{
	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_read);

	self->m_buff_len = (int)fread(self->m_buff, 1, sizeof(self->m_buff), self->m_file);
	if(self->m_buff_len == 0)
	{
		mk_check(feof(self->m_file) != 0);
		mk_check(fclose(self->m_file) == 0);
		self->m_file = NULL;
		self->m_cur_alg = 0;
		self->m_state = mk_hash_file_state_finish;
		return 0;
	}
	self->m_read += self->m_buff_len;

	self->m_cur_alg = 0;
	self->m_state = mk_hash_file_state_append;
	return 0;
}

static mk_inline int mk_hash_file_step_append(struct mk_hash_file_s* self)
{
	void* hash_state;
	int alg_count;

	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_append);

	hash_state = (unsigned char*)&self->m_hash_states + s_alg_descrs[self->m_cur_alg].m_offset;
	s_alg_descrs[self->m_cur_alg].m_append(hash_state, self->m_buff, self->m_buff_len);
	++self->m_cur_alg;

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	if(self->m_cur_alg == alg_count)
	{
		self->m_state = mk_hash_file_state_read;
	}
	return 0;
}

static mk_inline int mk_hash_file_step_finish(struct mk_hash_file_s* self)
{
	void* hash_state;
	void* digest;
	int alg_count;

	mk_assert(self);
	mk_assert(self->m_state == mk_hash_file_state_finish);

	hash_state = (unsigned char*)&self->m_hash_states + s_alg_descrs[self->m_cur_alg].m_offset;
	digest = (unsigned char*)&self->m_digests + s_alg_descrs[self->m_cur_alg].m_digest_offset;
	s_alg_descrs[self->m_cur_alg].m_finish(hash_state, digest);
	++self->m_cur_alg;

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	if(self->m_cur_alg == alg_count)
	{
		self->m_state = mk_hash_file_state_done;
	}
	return 0;
}


mk_jumbo int mk_hash_file_create(mk_hash_file_handle* hf, char const* file_name)
{
	FILE* file;
	long file_len;
	int alg_count;
	long chunk_count;
	long steps_total;
	struct mk_hash_file_s* self;

	mk_assert(hf);
	mk_assert(file_name && *file_name);

	file = fopen(file_name, "rb");
	mk_check(file);
	if(!(fseek(file, 0, SEEK_END) == 0))
	{
		mk_check(fclose(file) == 0);
		mk_check(0);
	}
	file_len = ftell(file);
	if(!(file_len != -1))
	{
		mk_check(fclose(file) == 0);
		mk_check(0);
	}
	rewind(file);

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	chunk_count = file_len / (int)sizeof(self->m_buff);
	chunk_count += chunk_count * (int)sizeof(self->m_buff) == file_len ? 0 : 1;
	steps_total = alg_count + chunk_count * (1 + alg_count) + alg_count;

	self = (struct mk_hash_file_s*)malloc(sizeof(struct mk_hash_file_s));
	if(!(self))
	{
		mk_check(fclose(file) == 0);
		mk_check(0);
	}

	self->m_state = mk_hash_file_state_init;
	self->m_file = file;
	self->m_read = 0;
	self->m_cur_alg = 0;
	self->m_steps_total = steps_total;

	*hf = (mk_hash_file_handle)self;
	return 0;
}

mk_jumbo int mk_hash_file_step(mk_hash_file_handle hash_file)
{
	struct mk_hash_file_s* self;

	mk_assert(hash_file);

	self = (struct mk_hash_file_s*)hash_file;
	mk_assert
	(
		self->m_state == mk_hash_file_state_init ||
		self->m_state == mk_hash_file_state_read ||
		self->m_state == mk_hash_file_state_append ||
		self->m_state == mk_hash_file_state_finish ||
		self->m_state == mk_hash_file_state_done
	);

	switch(self->m_state)
	{
		case mk_hash_file_state_init:   return mk_hash_file_step_init(self);   break;
		case mk_hash_file_state_read:   return mk_hash_file_step_read(self);   break;
		case mk_hash_file_state_append: return mk_hash_file_step_append(self); break;
		case mk_hash_file_state_finish: return mk_hash_file_step_finish(self); break;
		case mk_hash_file_state_done:   return 0;                              break;
	};
	return 0;
}

static mk_inline int progress_div(unsigned long a, long b)
{
	unsigned long uahi;
	unsigned long ualo;
	unsigned long ub;
	unsigned long ahi;
	unsigned long alo;
	int i;
	unsigned long t;

	mk_assert(a <= (unsigned long)b);

	uahi = 0;
	ualo = a;
	ub = (unsigned long)b;
	ahi = 0;
	alo = ualo;
	for(i = 0; i != 4; ++i)
	{
		ahi = (ahi << 2) | (alo >> (32 - 2));
		alo = alo << 2;
		ahi = ahi + uahi;
		t = alo + ualo;
		if(t < alo || t < ualo)
		{
			++ahi;
		}
		alo = t;
		ahi = (ahi << 1) | (alo >> (32 - 1));
		alo = alo << 1;
		uahi = ahi;
		ualo = alo;
	}
	for(i = 0; i != 32; ++i)
	{
		t = ahi >> 31;
		ahi = (ahi << 1) | (alo >> (32 - 1));
		alo = alo << 1;
		if((ahi | t) >= ub)
		{
			ahi = ahi - ub;
			alo = alo + 1;
		}
	}
	return (int)alo;
}

mk_jumbo int mk_hash_file_is_done(mk_hash_file_handle hash_file)
{
	struct mk_hash_file_s const* self;

	mk_assert(hash_file);

	self = (struct mk_hash_file_s const*)hash_file;

	return self->m_state == mk_hash_file_state_done;
}

mk_jumbo int mk_hash_file_get_progress(mk_hash_file_handle hash_file, int* progress)
{
	struct mk_hash_file_s const* self;
	int alg_count;
	int chunk_count;
	unsigned long steps;
	struct mk_uint64_s a;
	struct mk_uint64_s b;

	mk_assert(hash_file);
	mk_assert(progress);

	self = (struct mk_hash_file_s const*)hash_file;
	mk_assert
	(
		self->m_state == mk_hash_file_state_init ||
		self->m_state == mk_hash_file_state_read ||
		self->m_state == mk_hash_file_state_append ||
		self->m_state == mk_hash_file_state_finish ||
		self->m_state == mk_hash_file_state_done
	);

	#define mk_max(a, b) ((a) < (b) ? (b) : (a))
	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	chunk_count = (self->m_read + (int)sizeof(self->m_buff) - 1) / (int)sizeof(self->m_buff);
	steps = 0;
	switch(self->m_state)
	{
		case mk_hash_file_state_init: steps = self->m_cur_alg; break;
		case mk_hash_file_state_read: steps = alg_count + chunk_count * (1 + alg_count); break;
		case mk_hash_file_state_append: steps = alg_count + mk_max(0, chunk_count - 1) * (1 + alg_count) + 1 + self->m_cur_alg; break;
		case mk_hash_file_state_finish: steps = alg_count + chunk_count * (1 + alg_count) + self->m_cur_alg; break;
		case mk_hash_file_state_done: steps = self->m_steps_total; break;
	};
	#undef mk_max

	if(steps <= ULONG_MAX / 10000)
	{
		*progress = (int)((steps * 10000) / self->m_steps_total);
	}
	else
	{
		mk_uint64_from_long(&a, steps);
		mk_uint64_from_int(&b, 10000);
		mk_uint64_mul(&a, &a, &b);
		mk_uint64_from_long(&b, self->m_steps_total);
		mk_uint64_div(&a, &a, &b);
		*progress = mk_uint64_to_int(&a);
	}
	return 0;
}

mk_jumbo int mk_hash_file_get_result(mk_hash_file_handle hash_file, struct mk_hash_file_digests_s** result)
{
	struct mk_hash_file_s* self;

	mk_assert(hash_file);
	mk_assert(result);

	self = (struct mk_hash_file_s*)hash_file;
	mk_assert(self->m_state == mk_hash_file_state_done);

	*result = &self->m_digests;
	return 0;
}

mk_jumbo int mk_hash_file_destroy(mk_hash_file_handle hash_file)
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
