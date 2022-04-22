#include "mk_win_md4.h"

#include "../utils/mk_assert.h"


void mk_win_md4_init(struct mk_win_md4_state_s* self)
{
	HCRYPTPROV csp;
	HCRYPTHASH hash;
	BOOL csp_created;
	BOOL hash_created;

	mk_assert(self);

	csp_created = CryptAcquireContextW(&csp, NULL, MS_DEF_PROV_W, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);

	hash_created = CryptCreateHash(csp, CALG_MD4, 0, 0, &hash);
	mk_assert(hash_created != FALSE);

	self->m_csp = csp;
	self->m_hash = hash;
}

void mk_win_md4_append(struct mk_win_md4_state_s* self, void const* msg, size_t msg_len_bytes)
{
	BOOL hashed;

	mk_assert(self);
	mk_assert(msg_len_bytes <= (DWORD)-1);

	hashed = CryptHashData(self->m_hash, msg, (DWORD)msg_len_bytes, 0);
	mk_assert(hashed != FALSE);
}

void mk_win_md4_finish(struct mk_win_md4_state_s* self, void* digest)
{
	DWORD digest_len;
	BOOL got_hash;
	BOOL hash_freed;
	BOOL csp_freed;

	mk_assert(self);
	mk_assert(digest);

	digest_len = 16;
	got_hash = CryptGetHashParam(self->m_hash, HP_HASHVAL, (BYTE*)digest, &digest_len, 0);
	mk_assert(got_hash != FALSE);
	mk_assert(digest_len == 16);

	hash_freed = CryptDestroyHash(self->m_hash);
	mk_assert(hash_freed != FALSE);

	csp_freed = CryptReleaseContext(self->m_csp, 0);
	mk_assert(csp_freed != FALSE);
}
