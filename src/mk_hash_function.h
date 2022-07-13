#ifndef mk_include_guard_hash_function
#define mk_include_guard_hash_function


#include "hash/base/mk_hash_base_enum.h"

#include "utils/mk_jumbo.h"


typedef struct mk_hash_function_s { void* m_val; } mk_hash_function_h;


mk_jumbo mk_hash_function_h mk_hash_function_create(enum mk_hash_e type);
mk_jumbo int mk_hash_function_is_good(mk_hash_function_h hash_function);
mk_jumbo enum mk_hash_e mk_hash_function_get_type(mk_hash_function_h hash_function);
mk_jumbo void mk_hash_function_reinit(mk_hash_function_h hash_function);
mk_jumbo void mk_hash_function_append(mk_hash_function_h hash_function, void const* msg, int msg_len);
mk_jumbo void mk_hash_function_finish(mk_hash_function_h hash_function, void* digest);
mk_jumbo void mk_hash_function_destroy(mk_hash_function_h hash_function);


#endif
