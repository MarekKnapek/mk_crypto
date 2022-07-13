#define alg_id mk_hash_block_hash_alg_id
#include "../base/mk_hash_base_hash.h"
#undef alg_id

#include "../../utils/mk_jumbo.h"


#define alg_id mk_hash_block_hash_alg_id
#include "../base/mk_hash_base_alg_name_def.h"
#undef alg_id
#include "../../utils/mk_concat_def.h"


#define base_s concat(concat(struct mk_hash_base_hash_, alg_name), _s)
#define append concat(concat(mk_hash_block_hash_, alg_name), _append)


mk_jumbo void append(base_s* base, void* block, int* pidx, void const* msg, int msg_len);


#undef base_s
#undef append


#include "../base/mk_hash_base_alg_name_undef.h"
#include "../../utils/mk_concat_undef.h"
