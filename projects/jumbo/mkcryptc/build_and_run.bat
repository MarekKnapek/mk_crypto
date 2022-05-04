@echo off

cl /nologo /O2 /D NDEBUG /D _CRT_SECURE_NO_WARNINGS /W4 mkcryptc.c || exit /b
mkcryptc.exe encrypt ctr aes128 pbkdf2 hmac-sha1 hunter2 sugar 1000 mkcryptc.exe mkcryptc.out1
mkcryptc.exe decrypt ctr aes128 pbkdf2 hmac-sha1 hunter2 sugar 1000 mkcryptc.out1 mkcryptc.out2
