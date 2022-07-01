#include "../../base/mk_hash_base_hash.h"

#include "../../../utils/mk_jumbo.h"


#include "../../base/mk_hash_base_alg_name_def.h"


#define concat_(a, b) a ## b
#define concat(a, b) concat_(a, b)

#define hash_s concat(concat(struct mk_hash_base_hash_, alg_name), _s)
#define append concat(concat(mk_hash_block_hash_, alg_name), _append)


mk_jumbo void append(hash_s* base, void* block, int* pidx, void const* msg, int msg_len);


#undef hash_s
#undef append

#undef concat_
#undef concat


#include "../../base/mk_hash_base_alg_name_undef.h"
