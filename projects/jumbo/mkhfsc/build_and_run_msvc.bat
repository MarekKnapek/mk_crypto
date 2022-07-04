@echo off

cl /nologo /W4 /WX /O2 /Ob2 /GL /Za /D NDEBUG /D mk_want_jumbo=1 /D _CRT_SECURE_NO_WARNINGS mkhfsc.c /link /LTCG || exit /b
mkhfsc.exe SHA3-512 mkhfsc.c
copy mkhfsc.exe mkhfsc.orig.exe

del *.pgd *.pgc
cl /nologo /W4 /WX /O2 /Ob2 /GL /Za /D NDEBUG /D mk_want_jumbo=1 /D _CRT_SECURE_NO_WARNINGS mkhfsc.c /link /LTCG /GENPROFILE || exit /b
mkhfsc.exe SHA3-512 mkhfsc.c
copy mkhfsc.exe mkhfsc.pgo_train.exe
cl /nologo /W4 /WX /O2 /Ob2 /GL /Za /D NDEBUG /D mk_want_jumbo=1 /D _CRT_SECURE_NO_WARNINGS mkhfsc.c /link /LTCG /USEPROFILE || exit /b
mkhfsc.exe SHA3-512 mkhfsc.c
copy mkhfsc.exe mkhfsc.pgo_use.exe
