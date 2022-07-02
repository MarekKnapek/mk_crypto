#include "mk_mac_hmac_obj.h"

#include "hmac/mk_mac_hmac_md2.h"
#include "hmac/mk_mac_hmac_md4.h"
#include "hmac/mk_mac_hmac_md5.h"
#include "hmac/mk_mac_hmac_sha1.h"
#include "hmac/mk_mac_hmac_sha2_224.h"
#include "hmac/mk_mac_hmac_sha2_256.h"
#include "hmac/mk_mac_hmac_sha2_384.h"
#include "hmac/mk_mac_hmac_sha2_512.h"
#include "hmac/mk_mac_hmac_sha2_512224.h"
#include "hmac/mk_mac_hmac_sha2_512256.h"
#include "hmac/mk_mac_hmac_sha3_224.h"
#include "hmac/mk_mac_hmac_sha3_256.h"
#include "hmac/mk_mac_hmac_sha3_384.h"
#include "hmac/mk_mac_hmac_sha3_512.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"

#include <stddef.h> /* NULL */
#include <stdlib.h> /* malloc free */


#define mk_assert_type(type) mk_assert( \
	(type) == mk_mac_hmac_obj_md2 || \
	(type) == mk_mac_hmac_obj_md4 || \
	(type) == mk_mac_hmac_obj_md5 || \
	(type) == mk_mac_hmac_obj_sha1 || \
	(type) == mk_mac_hmac_obj_sha2_224 || \
	(type) == mk_mac_hmac_obj_sha2_256 || \
	(type) == mk_mac_hmac_obj_sha2_384 || \
	(type) == mk_mac_hmac_obj_sha2_512 || \
	(type) == mk_mac_hmac_obj_sha2_512224 || \
	(type) == mk_mac_hmac_obj_sha2_512256 || \
	(type) == mk_mac_hmac_obj_sha3_224 || \
	(type) == mk_mac_hmac_obj_sha3_256 || \
	(type) == mk_mac_hmac_obj_sha3_384 || \
	(type) == mk_mac_hmac_obj_sha3_512)


struct mk_mac_hmac_obj_md2_s        { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_md2_s         m_val; };
struct mk_mac_hmac_obj_md4_s        { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_md4_s         m_val; };
struct mk_mac_hmac_obj_md5_s        { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_md5_s         m_val; };
struct mk_mac_hmac_obj_sha1_s       { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha1_s        m_val; };
struct mk_mac_hmac_obj_sha2_224_s   { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha2_224_s    m_val; };
struct mk_mac_hmac_obj_sha2_256_s   { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha2_256_s    m_val; };
struct mk_mac_hmac_obj_sha2_384_s   { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha2_384_s    m_val; };
struct mk_mac_hmac_obj_sha2_512_s   { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha2_512_s    m_val; };
struct mk_mac_hmac_obj_sha2_512224_s{ enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha2_512224_s m_val; };
struct mk_mac_hmac_obj_sha2_512256_s{ enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha2_512256_s m_val; };
struct mk_mac_hmac_obj_sha3_224_s   { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha3_224_s    m_val; };
struct mk_mac_hmac_obj_sha3_256_s   { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha3_256_s    m_val; };
struct mk_mac_hmac_obj_sha3_384_s   { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha3_384_s    m_val; };
struct mk_mac_hmac_obj_sha3_512_s   { enum mk_mac_hmac_obj_e m_tag; struct mk_mac_hmac_sha3_512_s    m_val; };


mk_jumbo void mk_mac_hmac_obj_init(mk_mac_hmac_obj_h* hmac, enum mk_mac_hmac_obj_e type, void const* key, int key_len)
{
	int len;
	void* mem;

	mk_assert(hmac);
	mk_assert_type(type);
	mk_assert(key || key_len == 0);
	mk_assert(key_len >= 0);

	switch(type)
	{
		case mk_mac_hmac_obj_md2        : { struct mk_mac_hmac_obj_md2_s*         obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_md2_s*        )mem; obj->m_tag = mk_mac_hmac_obj_md2;         mk_mac_hmac_md2_init        (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_md4        : { struct mk_mac_hmac_obj_md4_s*         obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_md4_s*        )mem; obj->m_tag = mk_mac_hmac_obj_md4;         mk_mac_hmac_md4_init        (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_md5        : { struct mk_mac_hmac_obj_md5_s*         obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_md5_s*        )mem; obj->m_tag = mk_mac_hmac_obj_md5;         mk_mac_hmac_md5_init        (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha1       : { struct mk_mac_hmac_obj_sha1_s*        obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha1_s*       )mem; obj->m_tag = mk_mac_hmac_obj_sha1;        mk_mac_hmac_sha1_init       (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha2_224   : { struct mk_mac_hmac_obj_sha2_224_s*    obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha2_224_s*   )mem; obj->m_tag = mk_mac_hmac_obj_sha2_224;    mk_mac_hmac_sha2_224_init   (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha2_256   : { struct mk_mac_hmac_obj_sha2_256_s*    obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha2_256_s*   )mem; obj->m_tag = mk_mac_hmac_obj_sha2_256;    mk_mac_hmac_sha2_256_init   (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha2_384   : { struct mk_mac_hmac_obj_sha2_384_s*    obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha2_384_s*   )mem; obj->m_tag = mk_mac_hmac_obj_sha2_384;    mk_mac_hmac_sha2_384_init   (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha2_512   : { struct mk_mac_hmac_obj_sha2_512_s*    obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha2_512_s*   )mem; obj->m_tag = mk_mac_hmac_obj_sha2_512;    mk_mac_hmac_sha2_512_init   (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha2_512224: { struct mk_mac_hmac_obj_sha2_512224_s* obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha2_512224_s*)mem; obj->m_tag = mk_mac_hmac_obj_sha2_512224; mk_mac_hmac_sha2_512224_init(&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha2_512256: { struct mk_mac_hmac_obj_sha2_512256_s* obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha2_512256_s*)mem; obj->m_tag = mk_mac_hmac_obj_sha2_512256; mk_mac_hmac_sha2_512256_init(&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha3_224   : { struct mk_mac_hmac_obj_sha3_224_s*    obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha3_224_s*   )mem; obj->m_tag = mk_mac_hmac_obj_sha3_224;    mk_mac_hmac_sha3_224_init   (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha3_256   : { struct mk_mac_hmac_obj_sha3_256_s*    obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha3_256_s*   )mem; obj->m_tag = mk_mac_hmac_obj_sha3_256;    mk_mac_hmac_sha3_256_init   (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha3_384   : { struct mk_mac_hmac_obj_sha3_384_s*    obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha3_384_s*   )mem; obj->m_tag = mk_mac_hmac_obj_sha3_384;    mk_mac_hmac_sha3_384_init   (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
		case mk_mac_hmac_obj_sha3_512   : { struct mk_mac_hmac_obj_sha3_512_s*    obj; len = (int)sizeof(*obj); mem = malloc(len); if(!mem){ hmac->m_val = NULL; return; } obj = (struct mk_mac_hmac_obj_sha3_512_s*   )mem; obj->m_tag = mk_mac_hmac_obj_sha3_512;    mk_mac_hmac_sha3_512_init   (&obj->m_val, key, key_len); hmac->m_val = mem; } break;
	}
}

mk_jumbo void mk_mac_hmac_obj_append(mk_mac_hmac_obj_h hmac, void const* msg, int msg_len)
{
	enum mk_mac_hmac_obj_e type;

	mk_assert(hmac.m_val);
	mk_assert_type(*(enum mk_mac_hmac_obj_e*)hmac.m_val);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	type = *(enum mk_mac_hmac_obj_e*)hmac.m_val;
	switch(type)
	{
		case mk_mac_hmac_obj_md2        : { struct mk_mac_hmac_obj_md2_s*         obj = (struct mk_mac_hmac_obj_md2_s*        )hmac.m_val; mk_mac_hmac_md2_append        (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_md4        : { struct mk_mac_hmac_obj_md4_s*         obj = (struct mk_mac_hmac_obj_md4_s*        )hmac.m_val; mk_mac_hmac_md4_append        (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_md5        : { struct mk_mac_hmac_obj_md5_s*         obj = (struct mk_mac_hmac_obj_md5_s*        )hmac.m_val; mk_mac_hmac_md5_append        (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha1       : { struct mk_mac_hmac_obj_sha1_s*        obj = (struct mk_mac_hmac_obj_sha1_s*       )hmac.m_val; mk_mac_hmac_sha1_append       (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha2_224   : { struct mk_mac_hmac_obj_sha2_224_s*    obj = (struct mk_mac_hmac_obj_sha2_224_s*   )hmac.m_val; mk_mac_hmac_sha2_224_append   (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha2_256   : { struct mk_mac_hmac_obj_sha2_256_s*    obj = (struct mk_mac_hmac_obj_sha2_256_s*   )hmac.m_val; mk_mac_hmac_sha2_256_append   (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha2_384   : { struct mk_mac_hmac_obj_sha2_384_s*    obj = (struct mk_mac_hmac_obj_sha2_384_s*   )hmac.m_val; mk_mac_hmac_sha2_384_append   (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha2_512   : { struct mk_mac_hmac_obj_sha2_512_s*    obj = (struct mk_mac_hmac_obj_sha2_512_s*   )hmac.m_val; mk_mac_hmac_sha2_512_append   (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha2_512224: { struct mk_mac_hmac_obj_sha2_512224_s* obj = (struct mk_mac_hmac_obj_sha2_512224_s*)hmac.m_val; mk_mac_hmac_sha2_512224_append(&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha2_512256: { struct mk_mac_hmac_obj_sha2_512256_s* obj = (struct mk_mac_hmac_obj_sha2_512256_s*)hmac.m_val; mk_mac_hmac_sha2_512256_append(&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha3_224   : { struct mk_mac_hmac_obj_sha3_224_s*    obj = (struct mk_mac_hmac_obj_sha3_224_s*   )hmac.m_val; mk_mac_hmac_sha3_224_append   (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha3_256   : { struct mk_mac_hmac_obj_sha3_256_s*    obj = (struct mk_mac_hmac_obj_sha3_256_s*   )hmac.m_val; mk_mac_hmac_sha3_256_append   (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha3_384   : { struct mk_mac_hmac_obj_sha3_384_s*    obj = (struct mk_mac_hmac_obj_sha3_384_s*   )hmac.m_val; mk_mac_hmac_sha3_384_append   (&obj->m_val, msg, msg_len); } break;
		case mk_mac_hmac_obj_sha3_512   : { struct mk_mac_hmac_obj_sha3_512_s*    obj = (struct mk_mac_hmac_obj_sha3_512_s*   )hmac.m_val; mk_mac_hmac_sha3_512_append   (&obj->m_val, msg, msg_len); } break;
	}
}

mk_jumbo void mk_mac_hmac_obj_finish(mk_mac_hmac_obj_h hmac, void* digest)
{
	enum mk_mac_hmac_obj_e type;

	mk_assert(hmac.m_val);
	mk_assert_type(*(enum mk_mac_hmac_obj_e*)hmac.m_val);
	mk_assert(digest);

	type = *(enum mk_mac_hmac_obj_e*)hmac.m_val;
	switch(type)
	{
		case mk_mac_hmac_obj_md2        : { struct mk_mac_hmac_obj_md2_s*         obj = (struct mk_mac_hmac_obj_md2_s*        )hmac.m_val; mk_mac_hmac_md2_finish        (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_md4        : { struct mk_mac_hmac_obj_md4_s*         obj = (struct mk_mac_hmac_obj_md4_s*        )hmac.m_val; mk_mac_hmac_md4_finish        (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_md5        : { struct mk_mac_hmac_obj_md5_s*         obj = (struct mk_mac_hmac_obj_md5_s*        )hmac.m_val; mk_mac_hmac_md5_finish        (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha1       : { struct mk_mac_hmac_obj_sha1_s*        obj = (struct mk_mac_hmac_obj_sha1_s*       )hmac.m_val; mk_mac_hmac_sha1_finish       (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha2_224   : { struct mk_mac_hmac_obj_sha2_224_s*    obj = (struct mk_mac_hmac_obj_sha2_224_s*   )hmac.m_val; mk_mac_hmac_sha2_224_finish   (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha2_256   : { struct mk_mac_hmac_obj_sha2_256_s*    obj = (struct mk_mac_hmac_obj_sha2_256_s*   )hmac.m_val; mk_mac_hmac_sha2_256_finish   (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha2_384   : { struct mk_mac_hmac_obj_sha2_384_s*    obj = (struct mk_mac_hmac_obj_sha2_384_s*   )hmac.m_val; mk_mac_hmac_sha2_384_finish   (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha2_512   : { struct mk_mac_hmac_obj_sha2_512_s*    obj = (struct mk_mac_hmac_obj_sha2_512_s*   )hmac.m_val; mk_mac_hmac_sha2_512_finish   (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha2_512224: { struct mk_mac_hmac_obj_sha2_512224_s* obj = (struct mk_mac_hmac_obj_sha2_512224_s*)hmac.m_val; mk_mac_hmac_sha2_512224_finish(&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha2_512256: { struct mk_mac_hmac_obj_sha2_512256_s* obj = (struct mk_mac_hmac_obj_sha2_512256_s*)hmac.m_val; mk_mac_hmac_sha2_512256_finish(&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha3_224   : { struct mk_mac_hmac_obj_sha3_224_s*    obj = (struct mk_mac_hmac_obj_sha3_224_s*   )hmac.m_val; mk_mac_hmac_sha3_224_finish   (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha3_256   : { struct mk_mac_hmac_obj_sha3_256_s*    obj = (struct mk_mac_hmac_obj_sha3_256_s*   )hmac.m_val; mk_mac_hmac_sha3_256_finish   (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha3_384   : { struct mk_mac_hmac_obj_sha3_384_s*    obj = (struct mk_mac_hmac_obj_sha3_384_s*   )hmac.m_val; mk_mac_hmac_sha3_384_finish   (&obj->m_val, digest); } break;
		case mk_mac_hmac_obj_sha3_512   : { struct mk_mac_hmac_obj_sha3_512_s*    obj = (struct mk_mac_hmac_obj_sha3_512_s*   )hmac.m_val; mk_mac_hmac_sha3_512_finish   (&obj->m_val, digest); } break;
	}
	free(hmac.m_val);
}


#undef mk_assert_type
