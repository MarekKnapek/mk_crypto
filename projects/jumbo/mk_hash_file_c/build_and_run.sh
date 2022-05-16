set -e

gcc -std=c89 -O3 -DNDEBUG -Dmk_want_jumbo=1 -Wall -Wextra -Wpedantic -Wno-unused-function -o mk_hash_file_c.exe mk_hash_file_c.c
./mk_hash_file_c.exe mk_hash_file_c.c
