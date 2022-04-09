set -e

gcc -std=c89 -Wall -Wextra -Wpedantic -o tests.exe tests.c
./tests.exe
