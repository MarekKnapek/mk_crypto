#ifndef mk_include_guard_win_hash
#define mk_include_guard_win_hash


#include "../src/utils/mk_jumbo.h"


enum mk_win_hash_e
{
	mk_win_hash_e_md2,
	mk_win_hash_e_md4,
	mk_win_hash_e_md5,
	mk_win_hash_e_sha1,
	mk_win_hash_e_sha2_256,
	mk_win_hash_e_sha2_384,
	mk_win_hash_e_sha2_512
};


typedef struct { void* m_val; } mk_win_hash_h;


mk_jumbo void mk_win_hash_init(mk_win_hash_h* hmac, enum mk_win_hash_e type);
mk_jumbo void mk_win_hash_append(mk_win_hash_h hmac, void const* msg, int msg_len);
mk_jumbo void mk_win_hash_finish(mk_win_hash_h hmac, void* digest);


#endif
