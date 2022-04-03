@echo off

cl /nologo /W4 mk_win_hash_file.c /link /subsystem:windows user32.lib comdlg32.lib || exit /b
mk_win_hash_file.exe mk_win_hash_file.c
