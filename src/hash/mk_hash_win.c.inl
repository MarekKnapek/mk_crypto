#include "../utils/mk_assert.h"
#include "../utils/mk_jumbo.h"

#include <stddef.h> /* NULL */

#include <windows.h>
#include <wincrypt.h>


#define concat3_impl(a, b, c) a ## b ## c
#define concat3(a, b, c) concat3_impl(a, b, c)


mk_jumbo void concat3(mk_hash_win_, alg, _init)(struct concat3(mk_hash_win_, alg, _s)* alg)
{
	BOOL csp_created;
	HCRYPTPROV csp;
	BOOL hash_created;
	HCRYPTHASH hash;

	mk_assert(alg);

	csp_created = CryptAcquireContextA(&csp, NULL, alg_prov, alg_prov_type, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
	mk_assert(csp_created != FALSE);

	hash_created = CryptCreateHash(csp, alg_id, 0, 0, &hash);
	mk_assert(hash_created != FALSE);

	alg->m_csp = csp;
	alg->m_hash = hash;
}

mk_jumbo void concat3(mk_hash_win_, alg, _append)(struct concat3(mk_hash_win_, alg, _s)* alg, void const* msg, int msg_len)
{
	BOOL hashed;

	mk_assert(alg);
	mk_assert(msg || msg_len == 0);
	mk_assert(msg_len >= 0);

	hashed = CryptHashData(alg->m_hash, msg, msg_len, 0);
	mk_assert(hashed != FALSE);
}

mk_jumbo void concat3(mk_hash_win_, alg, _finish)(struct concat3(mk_hash_win_, alg, _s)* alg, void* digest)
{
	DWORD digest_len;
	BOOL got_hash;
	BOOL hash_freed;
	BOOL csp_freed;

	mk_assert(alg);
	mk_assert(digest);

	digest_len = alg_digest_len;
	got_hash = CryptGetHashParam(alg->m_hash, HP_HASHVAL, digest, &digest_len, 0);
	mk_assert(got_hash != FALSE);
	mk_assert(digest_len == alg_digest_len);

	hash_freed = CryptDestroyHash(alg->m_hash);
	mk_assert(hash_freed != FALSE);

	csp_freed = CryptReleaseContext(alg->m_csp, 0);
	mk_assert(csp_freed != FALSE);
}


#undef concat3_impl
#undef concat3
