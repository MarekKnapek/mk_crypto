#ifndef mk_include_guard_mac_hmac_obj
#define mk_include_guard_mac_hmac_obj


#include "../hash/base/mk_hash_base_enum.h"

#include "../utils/mk_jumbo.h"


typedef struct mk_mac_hmac_obj_s { void* m_val; } mk_mac_hmac_obj_h;


mk_jumbo mk_mac_hmac_obj_h mk_mac_hmac_obj_create(enum mk_hash_e type, void const* key, int key_len);
mk_jumbo int mk_mac_hmac_obj_is_good(mk_mac_hmac_obj_h hmac);
mk_jumbo enum mk_hash_e mk_mac_hmac_obj_get_type(mk_mac_hmac_obj_h hmac);
mk_jumbo void mk_mac_hmac_obj_reinit(mk_mac_hmac_obj_h hmac, void const* key, int key_len);
mk_jumbo void mk_mac_hmac_obj_append(mk_mac_hmac_obj_h hmac, void const* msg, int msg_len);
mk_jumbo void mk_mac_hmac_obj_finish(mk_mac_hmac_obj_h hmac, void* digest);
mk_jumbo void mk_mac_hmac_obj_destroy(mk_mac_hmac_obj_h hmac);


#endif
