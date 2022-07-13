#include "mk_win_hash.h"

#include "../src/utils/mk_assert.h"
#include "../src/utils/mk_clobber.h"
#include "../src/utils/mk_jumbo.h"

#include <stddef.h> /* NULL */
#include <stdlib.h> /* malloc free */

#include <windows.h>
#include <wincrypt.h>


#define is_type_good(type) \
	( \
		(type) == mk_win_hash_e_md2 || \
		(type) == mk_win_hash_e_md4 || \
		(type) == mk_win_hash_e_md5 || \
		(type) == mk_win_hash_e_sha1 || \
		(type) == mk_win_hash_e_sha2_256 || \
		(type) == mk_win_hash_e_sha2_384 || \
		(type) == mk_win_hash_e_sha2_512 \
	)


struct mk_win_hash_s
{
	HCRYPTPROV m_prov;
	HCRYPTHASH m_hash;
};


mk_jumbo void mk_win_hash_init(mk_win_hash_h* hmac, enum mk_win_hash_e type)
{
	BOOL acquired;
	HCRYPTPROV prov;
	DWORD prov_type;
	ALG_ID alg;
	BOOL created;
	HCRYPTHASH hash;
	void* mem;
	struct mk_win_hash_s* self;

	mk_assert(hmac);
	mk_assert(is_type_good(type));

	mk_clobber(&prov_type);
	switch(type)
	{
		case mk_win_hash_e_md2: prov_type = PROV_RSA_FULL; break;
		case mk_win_hash_e_md4: prov_type = PROV_RSA_FULL; break;
		case mk_win_hash_e_md5: prov_type = PROV_RSA_FULL; break;
		case mk_win_hash_e_sha1: prov_type = PROV_RSA_FULL; break;
		case mk_win_hash_e_sha2_256: prov_type = PROV_RSA_AES; break;
		case mk_win_hash_e_sha2_384: prov_type = PROV_RSA_AES; break;
		case mk_win_hash_e_sha2_512: prov_type = PROV_RSA_AES; break;
	}
	acquired = CryptAcquireContextA(&prov, NULL, NULL, prov_type, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(acquired != 0);

	mk_clobber(&alg);
	switch(type)
	{
		case mk_win_hash_e_md2: alg = CALG_MD2; break;
		case mk_win_hash_e_md4: alg = CALG_MD4; break;
		case mk_win_hash_e_md5: alg = CALG_MD5; break;
		case mk_win_hash_e_sha1: alg = CALG_SHA1; break;
		case mk_win_hash_e_sha2_256: alg = CALG_SHA_256; break;
		case mk_win_hash_e_sha2_384: alg = CALG_SHA_384; break;
		case mk_win_hash_e_sha2_512: alg = CALG_SHA_512; break;
	}
	created = CryptCreateHash(prov, alg, 0, 0, &hash);
	mk_assert(created != 0);

	mem = malloc(sizeof(struct mk_win_hash_s));
	mk_assert(mem);
	self = (struct mk_win_hash_s*)mem;
	self->m_prov = prov;
	self->m_hash = hash;
	hmac->m_val = mem;
}

mk_jumbo void mk_win_hash_append(mk_win_hash_h hmac, void const* msg, int msg_len)
{
	struct mk_win_hash_s* self;
	BOOL hashed;

	mk_assert(hmac.m_val);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	self = (struct mk_win_hash_s*)hmac.m_val;
	hashed = CryptHashData(self->m_hash, (BYTE const*)msg, (DWORD)msg_len, 0);
	mk_assert(hashed != 0);
}

mk_jumbo void mk_win_hash_finish(mk_win_hash_h hmac, void* digest)
{
	struct mk_win_hash_s* self;
	BOOL got1;
	DWORD len;
	BOOL got2;
	BOOL destroyedh;
	BOOL destroyedc;
	void* mem;

	mk_assert(hmac.m_val);
	mk_assert(digest);
	
	self = (struct mk_win_hash_s*)hmac.m_val;

	mk_clobber(&len);
	got1 = CryptGetHashParam(self->m_hash, HP_HASHVAL, NULL, &len, 0);
	mk_assert(got1 != 0);
	got2 = CryptGetHashParam(self->m_hash, HP_HASHVAL, (BYTE*)digest, &len, 0);
	mk_assert(got2 != 0);

	destroyedh = CryptDestroyHash(self->m_hash);
	mk_assert(destroyedh != 0);
	destroyedc = CryptReleaseContext(self->m_prov, 0);
	mk_assert(destroyedc != 0);

	mem = (void*)self;
	free(mem);
}


#undef is_type_good
