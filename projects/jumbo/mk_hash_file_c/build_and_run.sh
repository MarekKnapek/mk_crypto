set -e

gcc -std=c89 -O2 -DNDEBUG -Wall -Wextra -Wpedantic -o mk_hash_file_c.exe mk_hash_file_c.c
./mk_hash_file_c.exe mk_hash_file_c.c
