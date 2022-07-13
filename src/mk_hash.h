#ifndef mk_include_guard_hash
#define mk_include_guard_hash


#include "hash/base/mk_hash_base_enum.h"

#include "utils/mk_jumbo.h"


mk_jumbo int mk_hash_get_block_len(enum mk_hash_e type);
mk_jumbo int mk_hash_get_digest_len(enum mk_hash_e type);
mk_jumbo char const* mk_hash_get_name(enum mk_hash_e type);
mk_jumbo int mk_hash_get_name_len(enum mk_hash_e type);

mk_jumbo void mk_hash_init(enum mk_hash_e type, void* hash);
mk_jumbo void mk_hash_append(enum mk_hash_e type, void* hash, void const* msg, int msg_len);
mk_jumbo void mk_hash_finish(enum mk_hash_e type, void* hash, void* digest);


#endif
