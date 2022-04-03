#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h> /* NULL */
#include <string.h> /* memcpy */
#include <stdio.h> /* fclose fread feof */

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_inline.h"
#include "../../../src/mk_md2.h"
#include "../../../src/mk_md4.h"
#include "../../../src/mk_md5.h"
#include "../../../src/mk_sha1.h"
#include "../../../src/mk_sha2_224.h"
#include "../../../src/mk_sha2_256.h"
#include "../../../src/mk_sha2_384.h"
#include "../../../src/mk_sha2_512.h"
#include "../../../src/mk_sha2_512224.h"
#include "../../../src/mk_sha2_512256.h"

#pragma warning(push)
#pragma warning(disable:4668) /* warning C4668: 'xxx' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif' */
#include <windows.h>
#pragma warning(pop)
#include <tchar.h> /* _tfopen _tWinMain */


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err; err = (x); if(err != 0){ return err; } }while(0)


struct hash_states_s
{
	struct mk_md2_state_s m_state_md2;
	struct mk_md4_state_s m_state_md4;
	struct mk_md5_state_s m_state_md5;
	struct mk_sha1_state_s m_state_sha1;
	struct mk_sha2_224_state_s m_state_sha2_224;
	struct mk_sha2_256_state_s m_state_sha2_256;
	struct mk_sha2_384_state_s m_state_sha2_384;
	struct mk_sha2_512_state_s m_state_sha2_512;
	struct mk_sha2_512224_state_s m_state_sha2_512224;
	struct mk_sha2_512256_state_s m_state_sha2_512256;
};

struct alg_descr_s
{
	TCHAR const* m_name;
	int m_name_len;
	int m_digest_len_bytes;
	int m_offset;
	int m_digest_offset;
	void(*m_init)(void* state);
	void(*m_append_bytes)(void* state, void const* msg, size_t msg_len_bytes);
	void(*m_finish)(void* state, void* digest);
};

struct digests_s
{
	unsigned char m_md2[16];
	unsigned char m_md4[16];
	unsigned char m_md5[16];
	unsigned char m_sha1[20];
	unsigned char m_sha2_224[28];
	unsigned char m_sha2_256[32];
	unsigned char m_sha2_384[48];
	unsigned char m_sha2_512[64];
	unsigned char m_sha2_512224[28];
	unsigned char m_sha2_512256[32];
};


static TCHAR const s_alg_name_00[] = TEXT("MD2");
static TCHAR const s_alg_name_01[] = TEXT("MD4");
static TCHAR const s_alg_name_02[] = TEXT("MD5");
static TCHAR const s_alg_name_03[] = TEXT("SHA-1");
static TCHAR const s_alg_name_04[] = TEXT("SHA-224");
static TCHAR const s_alg_name_05[] = TEXT("SHA-256");
static TCHAR const s_alg_name_06[] = TEXT("SHA-384");
static TCHAR const s_alg_name_07[] = TEXT("SHA-512");
static TCHAR const s_alg_name_08[] = TEXT("SHA-512/224");
static TCHAR const s_alg_name_09[] = TEXT("SHA-512/256");

static struct alg_descr_s const s_alg_descrs[] =
{
	{s_alg_name_00, sizeof(s_alg_name_00) / sizeof(s_alg_name_00[0]) - 1, 16, offsetof(struct hash_states_s, m_state_md2),         offsetof(struct digests_s, m_md2),         (void(*)(void*))&mk_md2_init,         (void(*)(void*, void const*, size_t))&mk_md2_append,         (void(*)(void*, void*))&mk_md2_finish},
	{s_alg_name_01, sizeof(s_alg_name_01) / sizeof(s_alg_name_01[0]) - 1, 16, offsetof(struct hash_states_s, m_state_md4),         offsetof(struct digests_s, m_md4),         (void(*)(void*))&mk_md4_init,         (void(*)(void*, void const*, size_t))&mk_md4_append,         (void(*)(void*, void*))&mk_md4_finish},
	{s_alg_name_02, sizeof(s_alg_name_02) / sizeof(s_alg_name_02[0]) - 1, 16, offsetof(struct hash_states_s, m_state_md5),         offsetof(struct digests_s, m_md5),         (void(*)(void*))&mk_md5_init,         (void(*)(void*, void const*, size_t))&mk_md5_append,         (void(*)(void*, void*))&mk_md5_finish},
	{s_alg_name_03, sizeof(s_alg_name_03) / sizeof(s_alg_name_03[0]) - 1, 20, offsetof(struct hash_states_s, m_state_sha1),        offsetof(struct digests_s, m_sha1),        (void(*)(void*))&mk_sha1_init,        (void(*)(void*, void const*, size_t))&mk_sha1_append,        (void(*)(void*, void*))&mk_sha1_finish},
	{s_alg_name_04, sizeof(s_alg_name_04) / sizeof(s_alg_name_04[0]) - 1, 28, offsetof(struct hash_states_s, m_state_sha2_224),    offsetof(struct digests_s, m_sha2_224),    (void(*)(void*))&mk_sha2_224_init,    (void(*)(void*, void const*, size_t))&mk_sha2_224_append,    (void(*)(void*, void*))&mk_sha2_224_finish},
	{s_alg_name_05, sizeof(s_alg_name_05) / sizeof(s_alg_name_05[0]) - 1, 32, offsetof(struct hash_states_s, m_state_sha2_256),    offsetof(struct digests_s, m_sha2_256),    (void(*)(void*))&mk_sha2_256_init,    (void(*)(void*, void const*, size_t))&mk_sha2_256_append,    (void(*)(void*, void*))&mk_sha2_256_finish},
	{s_alg_name_06, sizeof(s_alg_name_06) / sizeof(s_alg_name_06[0]) - 1, 48, offsetof(struct hash_states_s, m_state_sha2_384),    offsetof(struct digests_s, m_sha2_384),    (void(*)(void*))&mk_sha2_384_init,    (void(*)(void*, void const*, size_t))&mk_sha2_384_append,    (void(*)(void*, void*))&mk_sha2_384_finish},
	{s_alg_name_07, sizeof(s_alg_name_07) / sizeof(s_alg_name_07[0]) - 1, 64, offsetof(struct hash_states_s, m_state_sha2_512),    offsetof(struct digests_s, m_sha2_512),    (void(*)(void*))&mk_sha2_512_init,    (void(*)(void*, void const*, size_t))&mk_sha2_512_append,    (void(*)(void*, void*))&mk_sha2_512_finish},
	{s_alg_name_08, sizeof(s_alg_name_08) / sizeof(s_alg_name_08[0]) - 1, 28, offsetof(struct hash_states_s, m_state_sha2_512224), offsetof(struct digests_s, m_sha2_512224), (void(*)(void*))&mk_sha2_512224_init, (void(*)(void*, void const*, size_t))&mk_sha2_512224_append, (void(*)(void*, void*))&mk_sha2_512224_finish},
	{s_alg_name_09, sizeof(s_alg_name_09) / sizeof(s_alg_name_09[0]) - 1, 32, offsetof(struct hash_states_s, m_state_sha2_512256), offsetof(struct digests_s, m_sha2_512256), (void(*)(void*))&mk_sha2_512256_init, (void(*)(void*, void const*, size_t))&mk_sha2_512256_append, (void(*)(void*, void*))&mk_sha2_512256_finish},
};


static mk_inline int mk_get_file_name(TCHAR* file_name, int file_name_len)
{
	OPENFILENAME ofn;
	BOOL got_ofn;

	mk_assert(file_name);

	file_name[0] = TEXT('\0');

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.hInstance = NULL;
	ofn.lpstrFilter = NULL;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 0;
	ofn.lpstrFile = file_name;
	ofn.nMaxFile = file_name_len;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = NULL;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = NULL;
	ofn.lCustData = 0;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;

	got_ofn = GetOpenFileName(&ofn);
	mk_check(got_ofn != 0);

	return 0;
}

static mk_inline int mk_hash_file(TCHAR const* file_name, struct digests_s* digests)
{
	int alg_count;
	int i;
	void* hash_state;
	struct hash_states_s hash_states;
	FILE* file;
	unsigned char buff[1024];
	void* digest;

	mk_assert(file_name);
	mk_assert(digests);

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	for(i = 0; i != alg_count; ++i)
	{
		hash_state = (unsigned char*)&hash_states + s_alg_descrs[i].m_offset;
		s_alg_descrs[i].m_init(hash_state);
	}

	file = _tfopen(file_name, TEXT("rb"));
	mk_check(file);

	for(;;)
	{
		size_t read = fread(buff, 1, sizeof(buff), file);
		if(read == 0)
		{
			mk_check(feof(file) != 0);
			break;
		}
		for(i = 0; i != alg_count; ++i)
		{
			hash_state = (unsigned char*)&hash_states + s_alg_descrs[i].m_offset;
			s_alg_descrs[i].m_append_bytes(hash_state, buff, read);
		}
	}
	
	mk_check(fclose(file) == 0);

	for(i = 0; i != alg_count; ++i)
	{
		hash_state = (unsigned char*)&hash_states + s_alg_descrs[i].m_offset;
		digest = (unsigned char*)digests + s_alg_descrs[i].m_digest_offset;
		s_alg_descrs[i].m_finish(hash_state, digest);
	}

	return 0;
}

static mk_inline void mk_bytes_to_string(void const* input, int count, void* output)
{
	static TCHAR const s_alphabet[] = TEXT("0123456789abcdef");
	
	unsigned char const* in;
	TCHAR* out;
	int i;

	in = (unsigned char const*)input;
	out = (TCHAR*)output;
	for(i = 0; i != count; ++i)
	{
		out[i * 2 + 0] = s_alphabet[(in[i] >> 4) & 0x0f];
		out[i * 2 + 1] = s_alphabet[(in[i] >> 0) & 0x0f];
	}
}

static mk_inline int mk_display(struct digests_s const* digests)
{
	int alg_count;
	int longest_name;
	int i;
	TCHAR* ptr;
	TCHAR msg[1024];
	int j;

	alg_count = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	longest_name = 0;
	for(i = 0; i != alg_count; ++i)
	{
		longest_name = s_alg_descrs[i].m_name_len > longest_name ? s_alg_descrs[i].m_name_len : longest_name;
	}

	ptr = msg;
	for(i = 0; i != alg_count; ++i)
	{
		memcpy(ptr, s_alg_descrs[i].m_name, s_alg_descrs[i].m_name_len * sizeof(TCHAR));
		ptr += s_alg_descrs[i].m_name_len;
		for(j = 0; j != longest_name - s_alg_descrs[i].m_name_len + 1; ++j)
		{
			*ptr = TEXT(' ');
			++ptr;
		}
		mk_bytes_to_string((unsigned char const*)digests + s_alg_descrs[i].m_digest_offset, s_alg_descrs[i].m_digest_len_bytes, ptr);
		ptr += s_alg_descrs[i].m_digest_len_bytes * 2;
		*ptr = TEXT('\n');
		++ptr;
	}
	*ptr = TEXT('\0');

	MessageBox(NULL, msg, TEXT("mk hash file"), MB_OK | MB_ICONINFORMATION);

	return 0;
}


int WINAPI _tWinMain(HINSTANCE inst, HINSTANCE prev_inst, LPTSTR cmd_line, int cmd_show)
{
	TCHAR file_name[1 * 1024];
	struct digests_s digests;

	(void)inst;
	(void)prev_inst;
	(void)cmd_line;
	(void)cmd_show;

	mk_try(mk_get_file_name(file_name, sizeof(file_name) / sizeof(file_name[0])));
	mk_try(mk_hash_file(file_name, &digests));
	mk_try(mk_display(&digests));

	return 0;
}


#include "../../../libs/mk_int.c"
#include "../../../src/mk_md2.c"
#include "../../../src/mk_md4.c"
#include "../../../src/mk_md5.c"
#include "../../../src/mk_sha1.c"
#include "../../../src/mk_sha2_224.c"
#include "../../../src/mk_sha2_256.c"
#include "../../../src/mk_sha2_384.c"
#include "../../../src/mk_sha2_512.c"
#include "../../../src/mk_sha2_512224.c"
#include "../../../src/mk_sha2_512256.c"
#include "../../../src/mk_sha2_detail_256.c"
#include "../../../src/mk_sha2_detail_512.c"
