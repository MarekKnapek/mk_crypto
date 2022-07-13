#ifndef mk_include_guard_kdf_pbkdf2
#define mk_include_guard_kdf_pbkdf2


#include "hash/base/mk_hash_base_enum.h"

#include "utils/mk_jumbo.h"


mk_jumbo void mk_kdf_pbkdf2(enum mk_hash_e prf, void const* password, int password_len, void const* salt, int salt_len, long iterations, int key_len, void* key);


#endif
