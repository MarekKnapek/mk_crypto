#include "../../utils/mk_jumbo.h"


#define alg_id mk_kdf_pbkdf2_hash_alg_id
#include "../../hash/base/mk_hash_base_alg_name_def.h"
#undef alg_id
#include "../../utils/mk_concat_def.h"


#define pbkdf2 concat(mk_kdf_pbkdf2_hash_, alg_name)


/* rfc 2898 */


mk_jumbo void pbkdf2(void const* password, int password_len, void const* salt, int salt_len, long iterations, int key_len, void* key);


#undef pbkdf2


#include "../../hash/base/mk_hash_base_alg_name_undef.h"
#include "../../utils/mk_concat_undef.h"
