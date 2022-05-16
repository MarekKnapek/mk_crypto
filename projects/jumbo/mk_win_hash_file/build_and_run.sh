set -e

gcc -std=c89 -O3 -DNDEBUG -Dmk_want_jumbo=1 -Wall -Wextra -Wpedantic -Wno-unused-function -o mk_win_hash_file.exe mk_win_hash_file.c -lcomdlg32
./mk_win_hash_file.exe mk_win_hash_file.c
