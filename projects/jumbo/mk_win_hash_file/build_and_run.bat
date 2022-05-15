@echo off

cl /nologo /W4 /WX /O2 /Ob2 /D NDEBUG /D _CRT_SECURE_NO_WARNINGS mk_win_hash_file.c /link /subsystem:windows user32.lib comdlg32.lib || exit /b
mk_win_hash_file.exe mk_win_hash_file.c
