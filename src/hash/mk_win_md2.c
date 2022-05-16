#include "mk_win_md2.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"

#include <stddef.h> /* NULL */

#include <windows.h>
#include <wincrypt.h>


mk_jumbo void mk_win_md2_init(struct mk_win_md2_s* win_md2)
{
	BOOL csp_created;
	HCRYPTPROV csp;
	BOOL hash_created;
	HCRYPTHASH hash;

	mk_assert(win_md2);

	csp_created = CryptAcquireContextA(&csp, NULL, MS_DEF_PROV_A, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);

	hash_created = CryptCreateHash(csp, CALG_MD2, 0, 0, &hash);
	mk_assert(hash_created != FALSE);

	win_md2->m_csp = csp;
	win_md2->m_hash = hash;
}

mk_jumbo void mk_win_md2_append(struct mk_win_md2_s* win_md2, void const* msg, int msg_len)
{
	BOOL hashed;

	mk_assert(win_md2);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	hashed = CryptHashData(win_md2->m_hash, msg, msg_len, 0);
	mk_assert(hashed != FALSE);
}

mk_jumbo void mk_win_md2_finish(struct mk_win_md2_s* win_md2, void* digest)
{
	DWORD digest_len;
	BOOL got_hash;
	BOOL hash_freed;
	BOOL csp_freed;

	mk_assert(win_md2);
	mk_assert(digest);

	digest_len = 16;
	got_hash = CryptGetHashParam(win_md2->m_hash, HP_HASHVAL, digest, &digest_len, 0);
	mk_assert(got_hash != FALSE);
	mk_assert(digest_len == 16);

	hash_freed = CryptDestroyHash(win_md2->m_hash);
	mk_assert(hash_freed != FALSE);

	csp_freed = CryptReleaseContext(win_md2->m_csp, 0);
	mk_assert(csp_freed != FALSE);
}
