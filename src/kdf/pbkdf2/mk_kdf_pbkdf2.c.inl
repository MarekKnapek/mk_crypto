#include "../../../../mk_int/src/exact/mk_uint_32.h"
#include "../../mac/hmac/mk_mac_hmac.h"

#include "../../utils/mk_jumbo.h"
#include "../../utils/mk_assert.h"

#include <string.h> /* memcpy */


#include "../../hash/base/mk_hash_base_alg_name_def.h"


#define concat_(a, b) a ## b
#define concat(a, b) concat_(a, b)


#define digest_len concat(concat(mk_hash_base_hash_, alg_name), _digest_len)
#define hmac_s concat(concat(struct mk_mac_hmac_, alg_name), _s)
#define hmac_init concat(concat(mk_mac_hmac_, alg_name), _init)
#define hmac_append concat(concat(mk_mac_hmac_, alg_name), _append)
#define hmac_finish concat(concat(mk_mac_hmac_, alg_name), _finish)
#define pbkdf2 concat(mk_kdf_pbkdf2_, alg_name)


/* rfc 2898 */


mk_jumbo void pbkdf2(void const* password, int password_len, void const* salt, int salt_len, long iterations, int key_len, void* key)
{
	unsigned char* output;
	struct mk_uint32_s i;
	int tn;
	int rest;
	int ti;
	unsigned char ibuff[4];
	hmac_s hmac;
	unsigned char fi[digest_len];
	unsigned char ui[digest_len];
	long cn;
	long ci;
	int j;
	int to_copy;

	mk_assert(password || password_len == 0);
	mk_assert(password_len >= 0);
	mk_assert(salt || salt_len == 0);
	mk_assert(salt_len >= 0);
	mk_assert(iterations > 0);
	mk_assert(key_len > 0);
	mk_assert(key);

	output = (unsigned char*)key;
	mk_uint32_zero(&i);
	tn = (key_len - 1) / digest_len;
	rest = key_len - tn * digest_len;
	for(ti = 0; ti != tn + 1; ++ti)
	{
		mk_uint32_inc(&i);
		mk_uint32_to_buff_be(&i, ibuff);
		hmac_init(&hmac, password, password_len);
		hmac_append(&hmac, salt, salt_len);
		hmac_append(&hmac, ibuff, sizeof(ibuff));
		hmac_finish(&hmac, fi);
		memcpy(ui, fi, digest_len);
		cn = iterations;
		for(ci = 1; ci != cn; ++ci)
		{
			hmac_init(&hmac, password, password_len);
			hmac_append(&hmac, ui, digest_len);
			hmac_finish(&hmac, ui);
			for(j = 0; j != digest_len; ++j){ fi[j] ^= ui[j]; }
		}
		to_copy = ti == tn ? rest : digest_len;
		memcpy(output, fi, to_copy);
		output += to_copy;
	}
}


#undef digest_len
#undef hmac_s
#undef hmac_init
#undef hmac_append
#undef hmac_finish
#undef pbkdf2


#undef concat_
#undef concat


#include "../../hash/base/mk_hash_base_alg_name_undef.h"
