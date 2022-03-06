#include "mk_win_md4.h"

#include <assert.h> /* assert static_assert */
#include <limits.h> /* CHAR_BIT */
#include <stddef.h> /* NULL */
#include <stdlib.h> /* exit EXIT_FAILURE malloc free */


static_assert(CHAR_BIT == 8, "Must have 8bit byte.");


void mk_win_md4_init(struct mk_win_md4_state_s* self)
{
	assert(self);

	BCRYPT_ALG_HANDLE alg_prov;
	NTSTATUS got_alg_prov = BCryptOpenAlgorithmProvider(&alg_prov, BCRYPT_MD4_ALGORITHM, NULL, 0);
	if(got_alg_prov != 0)
	{
		exit(EXIT_FAILURE);
	}

	DWORD alg_size;
	ULONG param_size;
	NTSTATUS got_alg_len = BCryptGetProperty(alg_prov, BCRYPT_OBJECT_LENGTH, (void*)&alg_size, sizeof(alg_size), &param_size, 0);
	if(got_alg_len != 0)
	{
		exit(EXIT_FAILURE);
	}
	if(param_size != sizeof(DWORD))
	{
		exit(EXIT_FAILURE);
	}

	void* alg_data = malloc(alg_size);
	if(!alg_data)
	{
		exit(EXIT_FAILURE);
	}

	BCRYPT_HASH_HANDLE alg;
	NTSTATUS got_alg = BCryptCreateHash(alg_prov, &alg, alg_data, alg_size, NULL, 0, 0);
	if(got_alg != 0)
	{
		exit(EXIT_FAILURE);
	}

	self->m_alg_prov = alg_prov;
	self->m_alg_data = alg_data;
	self->m_alg = alg;
}

void mk_win_md4_append(struct mk_win_md4_state_s* self, void const* data, size_t len)
{
	assert(self);
	
	NTSTATUS hashed = BCryptHashData(self->m_alg, (void*)data, (ULONG)len, 0);
	if(hashed != 0)
	{
		exit(EXIT_FAILURE);
	}
}

void mk_win_md4_finish(struct mk_win_md4_state_s* self, void* digest)
{
	assert(self);
	assert(digest);

	DWORD digest_len;
	ULONG param_size;
	NTSTATUS got_digest_len = BCryptGetProperty(self->m_alg_prov, BCRYPT_HASH_LENGTH, (void*)&digest_len, sizeof(digest_len), &param_size, 0);
	if(got_digest_len != 0)
	{
		exit(EXIT_FAILURE);
	}
	if(param_size != sizeof(DWORD))
	{
		exit(EXIT_FAILURE);
	}
	if(digest_len != 16)
	{
		exit(EXIT_FAILURE);
	}

	NTSTATUS finished = BCryptFinishHash(self->m_alg, digest, 16, 0);
	if(finished != 0)
	{
		exit(EXIT_FAILURE);
	}

	NTSTATUS freed_alg = BCryptDestroyHash(self->m_alg);
	if(freed_alg != 0)
	{
		exit(EXIT_FAILURE);
	}

	NTSTATUS freed_alg_prov = BCryptCloseAlgorithmProvider(self->m_alg_prov, 0);
	if(freed_alg_prov != 0)
	{
		exit(EXIT_FAILURE);
	}

	free(self->m_alg_data);
}
