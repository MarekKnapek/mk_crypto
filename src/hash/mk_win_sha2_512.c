#include "mk_win_sha2_512.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"

#include <stddef.h> /* NULL */

#include <windows.h>
#include <wincrypt.h>


mk_jumbo void mk_win_sha2_512_init(struct mk_win_sha2_512_s* win_sha2_512)
{
	BOOL csp_created;
	HCRYPTPROV csp;
	BOOL hash_created;
	HCRYPTHASH hash;

	mk_assert(win_sha2_512);

	csp_created = CryptAcquireContextA(&csp, NULL, MS_ENH_RSA_AES_PROV_A, PROV_RSA_AES, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);

	hash_created = CryptCreateHash(csp, CALG_SHA_512, 0, 0, &hash);
	mk_assert(hash_created != FALSE);

	win_sha2_512->m_csp = csp;
	win_sha2_512->m_hash = hash;
}

mk_jumbo void mk_win_sha2_512_append(struct mk_win_sha2_512_s* win_sha2_512, void const* msg, int msg_len)
{
	BOOL hashed;

	mk_assert(win_sha2_512);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	hashed = CryptHashData(win_sha2_512->m_hash, msg, msg_len, 0);
	mk_assert(hashed != FALSE);
}

mk_jumbo void mk_win_sha2_512_finish(struct mk_win_sha2_512_s* win_sha2_512, void* digest)
{
	DWORD digest_len;
	BOOL got_hash;
	BOOL hash_freed;
	BOOL csp_freed;

	mk_assert(win_sha2_512);
	mk_assert(digest);

	digest_len = 64;
	got_hash = CryptGetHashParam(win_sha2_512->m_hash, HP_HASHVAL, digest, &digest_len, 0);
	mk_assert(got_hash != FALSE);
	mk_assert(digest_len == 64);

	hash_freed = CryptDestroyHash(win_sha2_512->m_hash);
	mk_assert(hash_freed != FALSE);

	csp_freed = CryptReleaseContext(win_sha2_512->m_csp, 0);
	mk_assert(csp_freed != FALSE);
}
