set -e

gcc -std=c89 -Wall -Wextra -Wpedantic -o mk_hash_file.exe mk_hash_file.c
./mk_hash_file.exe mk_hash_file.c
