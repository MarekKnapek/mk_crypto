set -e

gcc -std=c89 -O3 -DNDEBUG -Dmk_want_jumbo=1 -Wall -Wextra -Wpedantic -Wno-unused-function -o mkhfsc.exe mkhfsc.c
./mkhfsc.exe SHA3-512 mkhfsc.c
