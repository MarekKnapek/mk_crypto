set -e

gcc -std=c89 -O2 -DNDEBUG -Wall -Wextra -Wpedantic -o tests.exe tests.c
./tests.exe
