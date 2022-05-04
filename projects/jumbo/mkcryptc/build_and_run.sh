set -e

gcc -std=c89 -O3 -DNDEBUG -Wall -Wextra -Wpedantic -o mkcryptc.exe mkcryptc.c
./mkcryptc.exe encrypt ctr aes128 pbkdf2 hmac-sha1 hunter2 sugar 1000 mkcryptc.exe mkcryptc.out1
./mkcryptc.exe decrypt ctr aes128 pbkdf2 hmac-sha1 hunter2 sugar 1000 mkcryptc.out1 mkcryptc.out2
