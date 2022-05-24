@echo off

cl /nologo /W4 /WX /O2 /Ob2 /GL /Za /D NDEBUG /D mk_want_jumbo=1 /D _CRT_SECURE_NO_WARNINGS mk_hash_file_c.c /link /LTCG || exit /b
mk_hash_file_c.exe mk_hash_file_c.c
copy mk_hash_file_c.exe mk_hash_file_c.orig.exe

del *.pgd *.pgc
cl /nologo /W4 /WX /O2 /Ob2 /GL /Za /D NDEBUG /D mk_want_jumbo=1 /D _CRT_SECURE_NO_WARNINGS mk_hash_file_c.c /link /LTCG /GENPROFILE || exit /b
mk_hash_file_c.exe mk_hash_file_c.exe
copy mk_hash_file_c.exe mk_hash_file_c.pgo_train.exe
cl /nologo /W4 /WX /O2 /Ob2 /GL /Za /D NDEBUG /D mk_want_jumbo=1 /D _CRT_SECURE_NO_WARNINGS mk_hash_file_c.c /link /LTCG /USEPROFILE || exit /b
mk_hash_file_c.exe mk_hash_file_c.c
copy mk_hash_file_c.exe mk_hash_file_c.pgo_use.exe