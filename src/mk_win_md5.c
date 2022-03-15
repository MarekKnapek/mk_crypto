#include "mk_win_md5.h"

#include "../utils/mk_assert.h"


void mk_win_md5_init(struct mk_win_md5_state_s* self)
{
	mk_assert(self);

	HCRYPTPROV csp;
	BOOL csp_created = CryptAcquireContextW(&csp, NULL, MS_DEF_PROV_W, PROV_RSA_FULL, CRYPT_SILENT);
	mk_assert(csp_created != FALSE);
	
	HCRYPTHASH hash;
	BOOL hash_alg_created = CryptCreateHash(csp, CALG_MD5, 0, 0, &hash);
	mk_assert(hash_alg_created != FALSE);

	self->m_csp = csp;
	self->m_hash = hash;
}

void mk_win_md5_append(struct mk_win_md5_state_s* self, void const* msg, size_t msg_len_bytes)
{
	mk_assert(self);
	
	BOOL hashed = CryptHashData(self->m_hash, msg, (DWORD)msg_len_bytes, 0);
	mk_assert(hashed != FALSE);
}

void mk_win_md5_finish(struct mk_win_md5_state_s* self, void* digest)
{
	mk_assert(self);
	mk_assert(digest);

	DWORD digest_len = 16;
	BOOL got_hash = CryptGetHashParam(self->m_hash, HP_HASHVAL, (BYTE*)digest, &digest_len, 0);
	mk_assert(got_hash != FALSE);
	mk_assert(digest_len == 16);

	BOOL hash_freed = CryptDestroyHash(self->m_hash);
	mk_assert(hash_freed != FALSE);

	BOOL csp_freed = CryptReleaseContext(self->m_csp, 0);
	mk_assert(csp_freed != FALSE);
}
