#include "mk_win_sha2.h"

#include <assert.h> /* assert static_assert */
#include <limits.h> /* CHAR_BIT */
#include <stdlib.h> /* exit EXIT_FAILURE */


static_assert(CHAR_BIT == 8, "Must have 8bit byte.");


void mk_win_sha2_256_init(struct mk_win_sha2_256_state_s* self)
{
	assert(self);

	HCRYPTPROV csp;
	BOOL csp_created = CryptAcquireContextW(&csp, NULL, MS_ENH_RSA_AES_PROV_W, PROV_RSA_AES, CRYPT_SILENT);
	if(csp_created == FALSE)
	{
		exit(EXIT_FAILURE);
	}
	
	HCRYPTHASH hash;
	BOOL hash_alg_created = CryptCreateHash(csp, CALG_SHA_256, 0, 0, &hash);
	if(hash_alg_created == FALSE)
	{
		exit(EXIT_FAILURE);
	}

	self->m_csp = csp;
	self->m_hash = hash;
}

void mk_win_sha2_256_append(struct mk_win_sha2_256_state_s* self, void const* data, size_t len)
{
	assert(self);
	
	BOOL hashed = CryptHashData(self->m_hash, data, (DWORD)len, 0);
	if(hashed == FALSE)
	{
		exit(EXIT_FAILURE);
	}
}

void mk_win_sha2_256_finish(struct mk_win_sha2_256_state_s* self, void* digest)
{
	assert(self);
	assert(digest);

	DWORD digest_len = 32;
	BOOL got_hash = CryptGetHashParam(self->m_hash, HP_HASHVAL, (BYTE*)digest, &digest_len, 0);
	if(got_hash == FALSE)
	{
		exit(EXIT_FAILURE);
	}
	if(digest_len != 32)
	{
		exit(EXIT_FAILURE);
	}

	BOOL hash_freed = CryptDestroyHash(self->m_hash);
	if(hash_freed == FALSE)
	{
		exit(EXIT_FAILURE);
	}

	BOOL csp_freed = CryptReleaseContext(self->m_csp, 0);
	if(csp_freed == FALSE)
	{
		exit(EXIT_FAILURE);
	}
}
