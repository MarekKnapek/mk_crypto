@echo off

cl /nologo /Wall /WX /O2 /Ob2 /D NDEBUG /D _CRT_SECURE_NO_WARNINGS mk_hash_file_c.c || exit /b
mk_hash_file_c.exe mk_hash_file_c.c
