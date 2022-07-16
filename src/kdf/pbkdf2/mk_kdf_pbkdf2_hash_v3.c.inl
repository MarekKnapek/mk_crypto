#include "../../mac/hmac/mk_mac_hmac_hash.h"

#include "../../utils/mk_jumbo.h"
#include "../../utils/mk_assert.h"

#include "../../../../mk_int/src/exact/mk_uint_32.h"

#include <string.h> /* memcpy */


#define alg_id mk_kdf_pbkdf2_hash_alg_id
#include "../../hash/base/mk_hash_base_alg_name_def.h"
#undef alg_id
#include "../../utils/mk_concat_def.h"


#define base_s concat(concat(struct mk_hash_base_hash_, alg_name), _s)
#define block_len concat(concat(mk_hash_base_hash_, alg_name), _block_len)
#define digest_len concat(concat(mk_hash_base_hash_, alg_name), _digest_len)
#define hash_s concat(concat(struct mk_hash_hash_, alg_name), _s)
#define hmac_s concat(concat(struct mk_mac_hmac_, alg_name), _s)
#define hmac_init concat(concat(mk_mac_hmac_, alg_name), _init)
#define hmac_append concat(concat(mk_mac_hmac_, alg_name), _append)
#define hmac_finish concat(concat(mk_mac_hmac_, alg_name), _finish)
#define pbkdf2 concat(mk_kdf_pbkdf2_hash_, alg_name)


/* rfc 2898 */


mk_jumbo void pbkdf2(void const* password, int password_len, void const* salt, int salt_len, long iterations, int key_len, void* key)
{
	hmac_s hmac;
	base_s precomputed_base;
	hash_s precomputed_hash;
	unsigned char* output;
	struct mk_uint32_s i;
	int tn;
	int rest;
	int ti;
	unsigned char ibuff[4];
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

	hmac_init(&hmac, password, password_len);
	mk_assert(sizeof(precomputed_base) == sizeof(hmac.m_hash.m_base));
	memcpy(&precomputed_base, &hmac.m_hash.m_base, sizeof(precomputed_base));
	hmac_append(&hmac, salt, salt_len);
	mk_assert(sizeof(precomputed_hash) == sizeof(hmac.m_hash));
	memcpy(&precomputed_hash, &hmac.m_hash, sizeof(precomputed_hash));
	output = (unsigned char*)key;
	mk_uint32_zero(&i);
	tn = (key_len - 1) / digest_len;
	rest = key_len - tn * digest_len;
	for(ti = 0; ti != tn + 1; ++ti)
	{
		mk_uint32_inc(&i);
		mk_uint32_to_buff_be(&i, ibuff);
		memcpy(&hmac.m_hash, &precomputed_hash, sizeof(precomputed_hash));
		hmac_append(&hmac, ibuff, sizeof(ibuff));
		hmac_finish(&hmac, fi);
		memcpy(ui, fi, digest_len);
		cn = iterations;
		for(ci = 1; ci != cn; ++ci)
		{
			memcpy(&hmac.m_hash.m_base, &precomputed_base, sizeof(precomputed_base));
			hmac.m_hash.m_idx = 0;
			hmac_append(&hmac, ui, digest_len);
			hmac_finish(&hmac, ui);
			for(j = 0; j != digest_len; ++j){ fi[j] ^= ui[j]; }
		}
		to_copy = ti == tn ? rest : digest_len;
		memcpy(output, fi, to_copy);
		output += to_copy;
	}
}


#undef base_s
#undef block_len
#undef digest_len
#undef hash_s
#undef hmac_s
#undef hmac_init
#undef hmac_append
#undef hmac_finish
#undef pbkdf2


#include "../../hash/base/mk_hash_base_alg_name_undef.h"
#include "../../utils/mk_concat_undef.h"
