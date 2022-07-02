#ifndef mk_include_guard_mac_hmac_obj
#define mk_include_guard_mac_hmac_obj


#include "../utils/mk_jumbo.h"


enum mk_mac_hmac_obj_e
{
	mk_mac_hmac_obj_md2,
	mk_mac_hmac_obj_md4,
	mk_mac_hmac_obj_md5,
	mk_mac_hmac_obj_sha1,
	mk_mac_hmac_obj_sha2_224,
	mk_mac_hmac_obj_sha2_256,
	mk_mac_hmac_obj_sha2_384,
	mk_mac_hmac_obj_sha2_512,
	mk_mac_hmac_obj_sha2_512224,
	mk_mac_hmac_obj_sha2_512256,
	mk_mac_hmac_obj_sha3_224,
	mk_mac_hmac_obj_sha3_256,
	mk_mac_hmac_obj_sha3_384,
	mk_mac_hmac_obj_sha3_512
};


typedef struct { void* m_val; } mk_mac_hmac_obj_h;


mk_jumbo void mk_mac_hmac_obj_init(mk_mac_hmac_obj_h* hmac, enum mk_mac_hmac_obj_e type, void const* key, int key_len);
mk_jumbo void mk_mac_hmac_obj_append(mk_mac_hmac_obj_h hmac, void const* msg, int msg_len);
mk_jumbo void mk_mac_hmac_obj_finish(mk_mac_hmac_obj_h hmac, void* digest);


#endif
