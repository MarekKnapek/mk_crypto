set -e

gcc -std=c89 -O3 -Wall -Wextra -Wpedantic -o mk_win_hash_file.exe mk_win_hash_file.c -lcomdlg32
./mk_win_hash_file.exe mk_win_hash_file.c
