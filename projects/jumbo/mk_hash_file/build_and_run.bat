@echo off

cl /nologo /W4 mk_hash_file.c || exit /b
mk_hash_file.exe mk_hash_file.c
