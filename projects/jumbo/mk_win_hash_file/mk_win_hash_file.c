#include "../../../apps/mk_hash_file_lib/mk_hash_file.h"

#include "../../../src/utils/mk_assert.h"
#include "../../../src/utils/mk_inline.h"

#include <stddef.h> /* NULL size_t */
#include <stdio.h> /* fseek SEEK_END ftell rewind fclose fread feof */
#include <string.h> /* memcpy */


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4668) /* warning C4668: 'xxx' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif' */
#endif
#include <windows.h>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
#include <commdlg.h> /* open file dialog */
#include <tchar.h> /* _tfopen _tWinMain */


#if !defined(UNICODE)
#if !defined(TEXT)
typedef char* LPTSTR;
typedef char const* LPCTSTR;
#define TEXT(x) x
#endif
#define _tWinMain WinMain
#endif


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err; err = (x); if(err != 0){ return err; } }while(0)


struct thread_param_s
{
	HANDLE m_finish_evnt;
	int m_ret;
	void* m_callback_context;
	TCHAR const* m_file_name;
	struct digests_s* m_digests;
};

struct algorithm_description_s
{
	TCHAR const* m_name;
	int m_name_len;
	int m_digest_len_bytes;
	int m_digest_offset;
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
static TCHAR const s_alg_name_10[] = TEXT("SHA3-224");
static TCHAR const s_alg_name_11[] = TEXT("SHA3-256");
static TCHAR const s_alg_name_12[] = TEXT("SHA3-384");
static TCHAR const s_alg_name_13[] = TEXT("SHA3-512");

static struct algorithm_description_s s_algorithm_descriptions[] =
{
	{s_alg_name_00, sizeof(s_alg_name_00) / sizeof(s_alg_name_00[0]) - 1, 16, offsetof(struct mk_hash_file_digests_s, m_md2)},
	{s_alg_name_01, sizeof(s_alg_name_01) / sizeof(s_alg_name_01[0]) - 1, 16, offsetof(struct mk_hash_file_digests_s, m_md4)},
	{s_alg_name_02, sizeof(s_alg_name_02) / sizeof(s_alg_name_02[0]) - 1, 16, offsetof(struct mk_hash_file_digests_s, m_md5)},
	{s_alg_name_03, sizeof(s_alg_name_03) / sizeof(s_alg_name_03[0]) - 1, 20, offsetof(struct mk_hash_file_digests_s, m_sha1)},
	{s_alg_name_04, sizeof(s_alg_name_04) / sizeof(s_alg_name_04[0]) - 1, 28, offsetof(struct mk_hash_file_digests_s, m_sha2_224)},
	{s_alg_name_05, sizeof(s_alg_name_05) / sizeof(s_alg_name_05[0]) - 1, 32, offsetof(struct mk_hash_file_digests_s, m_sha2_256)},
	{s_alg_name_06, sizeof(s_alg_name_06) / sizeof(s_alg_name_06[0]) - 1, 48, offsetof(struct mk_hash_file_digests_s, m_sha2_384)},
	{s_alg_name_07, sizeof(s_alg_name_07) / sizeof(s_alg_name_07[0]) - 1, 64, offsetof(struct mk_hash_file_digests_s, m_sha2_512)},
	{s_alg_name_08, sizeof(s_alg_name_08) / sizeof(s_alg_name_08[0]) - 1, 28, offsetof(struct mk_hash_file_digests_s, m_sha2_512224)},
	{s_alg_name_09, sizeof(s_alg_name_09) / sizeof(s_alg_name_09[0]) - 1, 32, offsetof(struct mk_hash_file_digests_s, m_sha2_512256)},
	{s_alg_name_10, sizeof(s_alg_name_10) / sizeof(s_alg_name_10[0]) - 1, 28, offsetof(struct mk_hash_file_digests_s, m_sha3_224)},
 	{s_alg_name_11, sizeof(s_alg_name_11) / sizeof(s_alg_name_11[0]) - 1, 32, offsetof(struct mk_hash_file_digests_s, m_sha3_256)},
 	{s_alg_name_12, sizeof(s_alg_name_12) / sizeof(s_alg_name_12[0]) - 1, 48, offsetof(struct mk_hash_file_digests_s, m_sha3_384)},
 	{s_alg_name_13, sizeof(s_alg_name_13) / sizeof(s_alg_name_13[0]) - 1, 64, offsetof(struct mk_hash_file_digests_s, m_sha3_512)},
};


static mk_inline int mk_get_file_name(TCHAR* file_name, int file_name_len)
{
	OPENFILENAME ofn;
	BOOL got_ofn;

	mk_assert(file_name);

	file_name[0] = TEXT('\0');

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = 0;
	ofn.hInstance = 0;
	ofn.lpstrFilter = TEXT("All Files (*.*)\0*.*\0");
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

static mk_inline int mk_display(struct mk_hash_file_digests_s const* digests)
{
	int alg_count;
	int longest_name;
	int i;
	TCHAR* ptr;
	TCHAR msg[1126];
	int j;

	alg_count = sizeof(s_algorithm_descriptions) / sizeof(s_algorithm_descriptions[0]);
	longest_name = 0;
	for(i = 0; i != alg_count; ++i)
	{
		longest_name = s_algorithm_descriptions[i].m_name_len > longest_name ? s_algorithm_descriptions[i].m_name_len : longest_name;
	}

	ptr = msg;
	for(i = 0; i != alg_count; ++i)
	{
		memcpy(ptr, s_algorithm_descriptions[i].m_name, s_algorithm_descriptions[i].m_name_len * sizeof(TCHAR));
		ptr += s_algorithm_descriptions[i].m_name_len;
		for(j = 0; j != longest_name - s_algorithm_descriptions[i].m_name_len + 1; ++j)
		{
			*ptr = TEXT(' ');
			++ptr;
		}
		mk_bytes_to_string((unsigned char const*)digests + s_algorithm_descriptions[i].m_digest_offset, s_algorithm_descriptions[i].m_digest_len_bytes, ptr);
		ptr += s_algorithm_descriptions[i].m_digest_len_bytes * 2;
		*ptr = TEXT('\n');
		++ptr;
	}
	--ptr;
	*ptr = TEXT('\0');

	MessageBox(0, msg, TEXT("mk hash file"), MB_OK | MB_ICONINFORMATION);

	return 0;
}

static LRESULT CALLBACK mk_gui_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if(msg == WM_DESTROY)
	{
		PostQuitMessage(0);
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

static mk_inline int mk_gui_run(HINSTANCE inst, mk_hash_file_handle hash_file)
{
	WNDCLASS wc;
	ATOM atom;
	HWND hwnd;
	BOOL got_msg;
	MSG msg;
	BOOL translated;
	LRESULT dispatched;
	BOOL unregistered;
	int step;
	DWORD prev_time;
	DWORD curr_time;
	int progress;
	TCHAR text[16];
	BOOL posted;
	LRESULT sent;

	mk_assert(inst);
	mk_assert(hash_file);

	wc.style = 0;
	wc.lpfnWndProc = &mk_gui_wnd_proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = inst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("mk_win_hash_file");

	atom = RegisterClass(&wc);
	mk_check(atom != 0);

	hwnd = CreateWindow(wc.lpszClassName, TEXT("mk win hash file, progress..."), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 300, 30, 0, 0, inst, NULL);
	mk_check(hwnd != 0);

	prev_time = 0;
	posted = PostMessage(hwnd, WM_NULL, 0, 0);
	(void)posted;
	for(;;)
	{
		got_msg = PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE);
		if(got_msg != 0)
		{
			got_msg = GetMessage(&msg, 0, 0, 0);
			if(got_msg == 0)
			{
				mk_check(msg.message == WM_QUIT);
				break;
			}
			translated = TranslateMessage(&msg);
			(void)translated;
			dispatched = DispatchMessage(&msg);
			(void)dispatched;
		}
		else
		{
			curr_time = GetTickCount();
			if(curr_time - prev_time >= 200)
			{
				mk_try(mk_hash_file_get_progress(hash_file, &progress));
				_stprintf(text, TEXT("%.2f %%"), (float)progress / 100.0f);
				sent = SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)text);
				(void)sent;
				prev_time = curr_time;
			}
			step = mk_hash_file_step(hash_file);
			mk_check(step == 0 || step == 1);
			if(step == 1)
			{
				posted = PostMessage(hwnd, WM_CLOSE, 0, 0);
				(void)posted;
			}
		}
	}

	unregistered = UnregisterClass(wc.lpszClassName, inst);
	mk_check(unregistered != 0);

	return 0;
}


int WINAPI _tWinMain(HINSTANCE inst, HINSTANCE prev_inst, LPTSTR cmd_line, int cmd_show)
{
	TCHAR file_name_t[1 * 1024];
	mk_hash_file_handle hash_file;
	struct mk_hash_file_digests_s* digests;
	char* file_name_a;
	int step_res;
	DWORD start_time;
	DWORD curr_time;
#if defined(UNICODE)
	int cnt;
	void* ptr;
	int cnt2;
#endif

	(void)inst;
	(void)prev_inst;
	(void)cmd_line;
	(void)cmd_show;

	mk_try(mk_get_file_name(file_name_t, sizeof(file_name_t) / sizeof(file_name_t[0])));

#if defined(UNICODE)
	cnt = WideCharToMultiByte(CP_ACP, 0, file_name_t, -1, NULL, 0, NULL, NULL);
	mk_check(cnt != 0);
	ptr = malloc(cnt);
	mk_check(ptr);
	file_name_a = (char*)ptr;
	cnt2 = WideCharToMultiByte(CP_ACP, 0, file_name_t, -1, file_name_a, cnt, NULL, NULL);
	mk_check(cnt2 == cnt);
#else
	file_name_a = file_name_t;
#endif

	hash_file = mk_hash_file_create(file_name_a);
	mk_check(hash_file);

	start_time = GetTickCount();
	for(;;)
	{
		step_res = mk_hash_file_step(hash_file);
		mk_check(step_res == 0 || step_res == 1);
		if(step_res == 1)
		{
			break;
		}
		curr_time = GetTickCount();
		if(curr_time - start_time >= 200)
		{
			mk_try(mk_gui_run(inst ? inst : prev_inst, hash_file));
			break;
		}
	}

	step_res = mk_hash_file_step(hash_file);
	mk_check(step_res == 1);

	mk_try(mk_hash_file_get_result(hash_file, &digests));

	mk_try(mk_display(digests));

	mk_try(mk_hash_file_destroy(hash_file));

#if defined(UNICODE)
	free(ptr);
#endif

	return 0;
}


#include "../../../apps/mk_hash_file_lib/mk_hash_file.c"

#include "../../../libs/mk_int.c"

#include "../../../src/hash/mk_md2.c"
#include "../../../src/hash/mk_md4.c"
#include "../../../src/hash/mk_md5.c"
#include "../../../src/hash/mk_sha1.c"
#include "../../../src/hash/mk_sha2_224.c"
#include "../../../src/hash/mk_sha2_256.c"
#include "../../../src/hash/mk_sha2_384.c"
#include "../../../src/hash/mk_sha2_512.c"
#include "../../../src/hash/mk_sha2_512224.c"
#include "../../../src/hash/mk_sha2_512256.c"
#include "../../../src/hash/mk_sha2_detail_256.c"
#include "../../../src/hash/mk_sha2_detail_512.c"
#include "../../../src/hash/mk_sha3_224.c"
#include "../../../src/hash/mk_sha3_256.c"
#include "../../../src/hash/mk_sha3_384.c"
#include "../../../src/hash/mk_sha3_512.c"
#include "../../../src/hash/mk_sha3_detail.c"
