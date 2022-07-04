#include "../../utils/mk_jumbo.h"


#include "../../hash/base/mk_hash_base_alg_name_def.h"


#define concat_(a, b) a ## b
#define concat(a, b) concat_(a, b)


#define pbkdf2 concat(mk_kdf_pbkdf2_, alg_name)


/* rfc 2898 */


mk_jumbo void pbkdf2(void const* password, int password_len, void const* salt, int salt_len, long iterations, int key_len, void* key);


#undef pbkdf2


#undef concat_
#undef concat


#include "../../hash/base/mk_hash_base_alg_name_undef.h"
