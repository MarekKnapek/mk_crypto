#ifndef mk_include_guard_hash_function
#define mk_include_guard_hash_function


#include "utils/mk_jumbo.h"


enum mk_hash_function_e
{
	mk_hash_function_md2,
	mk_hash_function_md4,
	mk_hash_function_md5,
	mk_hash_function_sha1,
	mk_hash_function_sha2_224,
	mk_hash_function_sha2_256,
	mk_hash_function_sha2_384,
	mk_hash_function_sha2_512,
	mk_hash_function_sha2_512224,
	mk_hash_function_sha2_512256,
	mk_hash_function_sha3_224,
	mk_hash_function_sha3_256,
	mk_hash_function_sha3_384,
	mk_hash_function_sha3_512,
};

typedef struct { void* m_val; } mk_hash_function_h;


mk_jumbo mk_hash_function_h mk_hash_function_create(enum mk_hash_function_e type);
mk_jumbo int mk_hash_function_is_good(mk_hash_function_h hash_function);
mk_jumbo enum mk_hash_function_e mk_hash_function_get_type(mk_hash_function_h hash_function);
mk_jumbo void mk_hash_function_append(mk_hash_function_h hash_function, void const* msg, int msg_len);
mk_jumbo void mk_hash_function_finish(mk_hash_function_h hash_function, void* digest);
mk_jumbo void mk_hash_function_destroy(mk_hash_function_h hash_function);


#endif
