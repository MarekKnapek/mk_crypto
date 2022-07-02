#ifndef mk_include_guard_win_mac_hmac
#define mk_include_guard_win_mac_hmac


#include "../src/utils/mk_jumbo.h"


enum mk_win_mac_hmac_e
{
	mk_win_mac_hmac_md2,
	mk_win_mac_hmac_md4,
	mk_win_mac_hmac_md5,
	mk_win_mac_hmac_sha1,
	mk_win_mac_hmac_sha2_256,
	mk_win_mac_hmac_sha2_384,
	mk_win_mac_hmac_sha2_512
};


typedef struct { void* m_val; } mk_win_mac_hmac_h;


mk_jumbo void mk_win_mac_hmac_init(mk_win_mac_hmac_h* hmac, enum mk_win_mac_hmac_e type, void const* key, int key_len);
mk_jumbo void mk_win_mac_hmac_append(mk_win_mac_hmac_h hmac, void const* msg, int msg_len);
mk_jumbo void mk_win_mac_hmac_finish(mk_win_mac_hmac_h hmac, void* digest);


#endif
