set -e

gcc -std=c89 -O2 -Wall -Wextra -Wpedantic -o tests.exe tests.c
./tests.exe
