#include "../base/mk_hash_base_hash.h"

#include "../../utils/mk_jumbo.h"


#include "../base/mk_hash_base_alg_name_def.h"


#define concat_(a, b) a ## b
#define concat(a, b) concat_(a, b)

#define base_s concat(concat(struct mk_hash_base_hash_, alg_name), _s)
#define block_len concat(concat(mk_hash_base_hash_, alg_name), _block_len)
#define hash_s concat(concat(struct mk_hash_hash_, alg_name), _s)
#define init concat(concat(mk_hash_hash_, alg_name), _init)
#define append concat(concat(mk_hash_hash_, alg_name), _append)
#define finish concat(concat(mk_hash_hash_, alg_name), _finish)


hash_s
{
	base_s m_base;
	int m_idx;
	unsigned char m_block[block_len];
};


mk_jumbo void init(hash_s* self);
mk_jumbo void append(hash_s* self, void const* msg, int msg_len);
mk_jumbo void finish(hash_s* self, void* digest);


#undef base_s
#undef block_len
#undef hash_s
#undef init
#undef append
#undef finish

#undef concat_
#undef concat


#include "../base/mk_hash_base_alg_name_undef.h"
