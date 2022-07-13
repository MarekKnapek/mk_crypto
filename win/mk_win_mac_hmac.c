#include "mk_win_mac_hmac.h"

#include "../src/utils/mk_assert.h"
#include "../src/utils/mk_clobber.h"
#include "../src/utils/mk_jumbo.h"

#include <stddef.h> /* NULL */
#include <stdlib.h> /* malloc free */

#include <windows.h>
#include <wincrypt.h>


#define is_type_good(type) \
	( \
		(type) == mk_win_mac_hmac_e_md2 || \
		(type) == mk_win_mac_hmac_e_md4 || \
		(type) == mk_win_mac_hmac_e_md5 || \
		(type) == mk_win_mac_hmac_e_sha1 || \
		(type) == mk_win_mac_hmac_e_sha2_256 || \
		(type) == mk_win_mac_hmac_e_sha2_384 || \
		(type) == mk_win_mac_hmac_e_sha2_512 \
	)


struct mk_win_mac_hmac_s
{
	HCRYPTPROV m_prov;
	HCRYPTKEY m_key;
	HCRYPTHASH m_hash;
};


mk_jumbo void mk_win_mac_hmac_init(mk_win_mac_hmac_h* hmac, enum mk_win_mac_hmac_e type, void const* key, int key_len)
{
	struct key_data_s
	{
		BLOBHEADER m_header;
		DWORD m_len;
	};

	BOOL acquired;
	HCRYPTPROV prov;
	int key_data_len;
	void* mem1;
	struct key_data_s* key_data;
	BOOL imported;
	HCRYPTKEY hkey;
	BOOL created;
	HCRYPTHASH hash;
	ALG_ID alg;
	HMAC_INFO mac;
	BOOL set;
	void* mem2;
	struct mk_win_mac_hmac_s* self;

	mk_assert(hmac);
	mk_assert(is_type_good(type));
	mk_assert(key || key_len == 0);
	mk_assert(key_len >= 0);

	acquired = CryptAcquireContextA(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(acquired != 0);

	key_data_len = sizeof(struct key_data_s) + key_len;
	mem1 = malloc(key_data_len);
	mk_assert(mem1);
	key_data = (struct key_data_s*)mem1;
	key_data->m_header.bType = PLAINTEXTKEYBLOB;
	key_data->m_header.bVersion = CUR_BLOB_VERSION;
	key_data->m_header.reserved = 0;
	key_data->m_header.aiKeyAlg = CALG_RC2;
	key_data->m_len = (DWORD)key_len;
	memcpy(((unsigned char*)key_data) + sizeof(struct key_data_s), key, key_len);
	imported = CryptImportKey(prov, (BYTE const*)key_data, (DWORD)key_data_len, 0, CRYPT_IPSEC_HMAC_KEY, &hkey);
	mk_assert(imported != 0);
	free(mem1);

	created = CryptCreateHash(prov, CALG_HMAC, hkey, 0, &hash);
	mk_assert(created != 0);

	mk_clobber(&alg);
	switch(type)
	{
		case mk_win_mac_hmac_e_md2: alg = CALG_MD2; break;
		case mk_win_mac_hmac_e_md4: alg = CALG_MD4; break;
		case mk_win_mac_hmac_e_md5: alg = CALG_MD5; break;
		case mk_win_mac_hmac_e_sha1: alg = CALG_SHA1; break;
		case mk_win_mac_hmac_e_sha2_256: alg = CALG_SHA_256; break;
		case mk_win_mac_hmac_e_sha2_384: alg = CALG_SHA_384; break;
		case mk_win_mac_hmac_e_sha2_512: alg = CALG_SHA_512; break;
	}
	mac.HashAlgid = alg;
	mac.pbInnerString = NULL;
	mac.cbInnerString = 0;
	mac.pbOuterString = NULL;
	mac.cbOuterString = 0;
	set = CryptSetHashParam(hash, HP_HMAC_INFO, (BYTE const*)&mac, 0);
	mk_assert(set != 0);

	mem2 = malloc(sizeof(struct mk_win_mac_hmac_s));
	mk_assert(mem2);
	self = (struct mk_win_mac_hmac_s*)mem2;
	self->m_prov = prov;
	self->m_key = hkey;
	self->m_hash = hash;
	hmac->m_val = mem2;
}

mk_jumbo void mk_win_mac_hmac_append(mk_win_mac_hmac_h hmac, void const* msg, int msg_len)
{
	struct mk_win_mac_hmac_s* self;
	BOOL hashed;

	mk_assert(hmac.m_val);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	self = (struct mk_win_mac_hmac_s*)hmac.m_val;
	hashed = CryptHashData(self->m_hash, (BYTE const*)msg, (DWORD)msg_len, 0);
	mk_assert(hashed != 0);
}

mk_jumbo void mk_win_mac_hmac_finish(mk_win_mac_hmac_h hmac, void* digest)
{
	void* mem;
	struct mk_win_mac_hmac_s* self;
	BOOL got1;
	DWORD len;
	BOOL got2;
	BOOL destroyedh;
	BOOL destroyedk;
	BOOL destroyedc;

	mk_assert(hmac.m_val);
	mk_assert(digest);

	mem = hmac.m_val;
	self = (struct mk_win_mac_hmac_s*)mem;

	mk_clobber(&len);
	got1 = CryptGetHashParam(self->m_hash, HP_HASHVAL, NULL, &len, 0);
	mk_assert(got1 != 0);
	got2 = CryptGetHashParam(self->m_hash, HP_HASHVAL, (BYTE*)digest, &len, 0);
	mk_assert(got2 != 0);

	destroyedh = CryptDestroyHash(self->m_hash);
	mk_assert(destroyedh != 0);
	destroyedk = CryptDestroyKey(self->m_key);
	mk_assert(destroyedk != 0);
	destroyedc = CryptReleaseContext(self->m_prov, 0);
	mk_assert(destroyedc != 0);

	free(mem);
}


#undef is_type_good
