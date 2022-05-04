#include "mkcryptc.h"

#include "../../src/mk_block_cipher.h"
#include "../../src/mk_crypt.h"
#include "../../src/mk_pbkdf2.h"

#include <limits.h> /* LONG_MAX LONG_MIN */
#include <stddef.h> /* NULL */
#include <stdio.h> /* FILE size_t fopen fread fclose */
#include <stdlib.h> /* strtol srand rand */
#include <string.h> /* strlen memcmp */
#include <time.h> /* time time_t */


static char const s_command_encrypt[] = "encrypt";
static char const s_command_decrypt[] = "decrypt";

static char const s_operation_mode_cbc[] = "cbc";
static char const s_operation_mode_cfb[] = "cfb";
static char const s_operation_mode_cfb_f[] = "cfb-f";
static char const s_operation_mode_ctr[] = "ctr";
static char const s_operation_mode_ctr_be[] = "ctr-be";
static char const s_operation_mode_ecb[] = "ecb";
static char const s_operation_mode_ofb[] = "ofb";

static char const s_block_cipher_aes128[] = "aes128";
static char const s_block_cipher_aes192[] = "aes192";
static char const s_block_cipher_aes256[] = "aes256";

static char const s_kdf_pbkdf2[] = "pbkdf2";

static char const s_pbkdf2_hash_hmac_md2[] = "hmac-md2";
static char const s_pbkdf2_hash_hmac_md4[] = "hmac-md4";
static char const s_pbkdf2_hash_hmac_md5[] = "hmac-md5";
static char const s_pbkdf2_hash_hmac_sha1[] = "hmac-sha1";
static char const s_pbkdf2_hash_hmac_sha2_224[] = "hmac-sha2-224";
static char const s_pbkdf2_hash_hmac_sha2_256[] = "hmac-sha2-256";
static char const s_pbkdf2_hash_hmac_sha2_384[] = "hmac-sha2-384";
static char const s_pbkdf2_hash_hmac_sha2_512[] = "hmac-sha2-512";
static char const s_pbkdf2_hash_hmac_sha2_512224[] = "hmac-sha2-512/224";
static char const s_pbkdf2_hash_hmac_sha2_512256[] = "hmac-sha2-512/256";
static char const s_pbkdf2_hash_hmac_sha3_224[] = "hmac-sha3-224";
static char const s_pbkdf2_hash_hmac_sha3_256[] = "hmac-sha3-256";
static char const s_pbkdf2_hash_hmac_sha3_384[] = "hmac-sha3-384";
static char const s_pbkdf2_hash_hmac_sha3_512[] = "hmac-sha3-512";


#define check(x) do{ if(!(x)){ return __LINE__; } }while(0)


int mkcryptc(int argc_, char const* const* argv_)
{
	int argc;
	char const* const* argv;
	int len;
	int direction;
	enum mk_operation_mode_e operation_mode;
	int cfb_f;
	int ctr_be;
	enum mk_block_cipher_e block_cipher;
	enum mk_pbkdf2_hash_e hash_id;
	int password_len;
	char const* password;
	int salt_len;
	char const* salt;
	long iterations;
	char* endp;
	char const* input_file_name;
	char const* output_file_name;
	unsigned char key[mk_block_cipher_key_len_max];
	struct mk_crypt_s crypt;
	FILE* input_file;
	FILE* output_file;
	int i;
	unsigned char iv[mk_block_cipher_block_len_max];
	size_t written;
	size_t read_a;
	unsigned char* buffer_a;
	unsigned char buffer_1[512 + mk_block_cipher_block_len_max];
	unsigned char* buffer_b;
	unsigned char buffer_2[sizeof(buffer_1)];
	size_t read_b;
	int crypted;
	unsigned char* buffer_t;
	size_t read_t;
	int fclosed;

	argc = argc_ - 1;
	argv = argv_ + 1;

	check(argc >= 1);
	len = (int)strlen(*argv);
	if(len == sizeof(s_command_encrypt) - 1 && memcmp(*argv, s_command_encrypt, sizeof(s_command_encrypt) - 1) == 0){ direction = 0; }
	else if(len == sizeof(s_command_decrypt) - 1 && memcmp(*argv, s_command_decrypt, sizeof(s_command_decrypt) - 1) == 0){ direction = 1; }
	else{ check(0); }
	--argc;
	++argv;

	check(argc >= 1);
	len = (int)strlen(*argv);
	if(len == sizeof(s_operation_mode_cbc) - 1 && memcmp(*argv, s_operation_mode_cbc, sizeof(s_operation_mode_cbc) - 1) == 0){ operation_mode = mk_operation_mode_cbc; }
	else if(len == sizeof(s_operation_mode_cfb) - 1 && memcmp(*argv, s_operation_mode_cfb, sizeof(s_operation_mode_cfb) - 1) == 0){ operation_mode = mk_operation_mode_cfb; cfb_f = 0; }
	else if(len == sizeof(s_operation_mode_cfb_f) - 1 && memcmp(*argv, s_operation_mode_cfb_f, sizeof(s_operation_mode_cfb_f) - 1) == 0){ operation_mode = mk_operation_mode_cfb; cfb_f = 1; }
	else if(len == sizeof(s_operation_mode_ctr) - 1 && memcmp(*argv, s_operation_mode_ctr, sizeof(s_operation_mode_ctr) - 1) == 0){ operation_mode = mk_operation_mode_ctr; ctr_be = 0; }
	else if(len == sizeof(s_operation_mode_ctr_be) - 1 && memcmp(*argv, s_operation_mode_ctr_be, sizeof(s_operation_mode_ctr_be) - 1) == 0){ operation_mode = mk_operation_mode_ctr; ctr_be = 1; }
	else if(len == sizeof(s_operation_mode_ecb) - 1 && memcmp(*argv, s_operation_mode_ecb, sizeof(s_operation_mode_ecb) - 1) == 0){ operation_mode = mk_operation_mode_ecb; }
	else if(len == sizeof(s_operation_mode_ofb) - 1 && memcmp(*argv, s_operation_mode_ofb, sizeof(s_operation_mode_ofb) - 1) == 0){ operation_mode = mk_operation_mode_ofb; }
	else{ check(0); }
	--argc;
	++argv;

	check(argc >= 1);
	len = (int)strlen(*argv);
	if(len == sizeof(s_block_cipher_aes128) - 1 && memcmp(*argv, s_block_cipher_aes128, sizeof(s_block_cipher_aes128) - 1) == 0){ block_cipher = mk_block_cipher_aes128; }
	else if(len == sizeof(s_block_cipher_aes192) - 1 && memcmp(*argv, s_block_cipher_aes192, sizeof(s_block_cipher_aes192) - 1) == 0){ block_cipher = mk_block_cipher_aes192; }
	else if(len == sizeof(s_block_cipher_aes256) - 1 && memcmp(*argv, s_block_cipher_aes256, sizeof(s_block_cipher_aes256) - 1) == 0){ block_cipher = mk_block_cipher_aes256; }
	else{ check(0); }
	--argc;
	++argv;

	check(argc >= 1);
	len = (int)strlen(*argv);
	if(len == sizeof(s_kdf_pbkdf2) - 1 && memcmp(*argv, s_kdf_pbkdf2, sizeof(s_kdf_pbkdf2) - 1) == 0){}
	else{ check(0); }
	--argc;
	++argv;

	check(argc >= 1);
	len = (int)strlen(*argv);
	if(len == sizeof(s_pbkdf2_hash_hmac_md2) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_md2, sizeof(s_pbkdf2_hash_hmac_md2) - 1) == 0){ hash_id = mk_pbkdf2_hash_md2; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_md4) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_md4, sizeof(s_pbkdf2_hash_hmac_md4) - 1) == 0){ hash_id = mk_pbkdf2_hash_md4; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_md5) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_md5, sizeof(s_pbkdf2_hash_hmac_md5) - 1) == 0){ hash_id = mk_pbkdf2_hash_md5; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha1) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha1, sizeof(s_pbkdf2_hash_hmac_sha1) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha1; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_224) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha2_224, sizeof(s_pbkdf2_hash_hmac_sha2_224) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha2_224; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_256) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha2_256, sizeof(s_pbkdf2_hash_hmac_sha2_256) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha2_256; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_384) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha2_384, sizeof(s_pbkdf2_hash_hmac_sha2_384) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha2_384; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_512) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha2_512, sizeof(s_pbkdf2_hash_hmac_sha2_512) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha2_512; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_512224) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha2_512224, sizeof(s_pbkdf2_hash_hmac_sha2_512224) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha2_512224; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_512256) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha2_512256, sizeof(s_pbkdf2_hash_hmac_sha2_512256) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha2_512256; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha3_224) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha3_224, sizeof(s_pbkdf2_hash_hmac_sha3_224) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha3_224; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha3_256) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha3_256, sizeof(s_pbkdf2_hash_hmac_sha3_256) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha3_256; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha3_384) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha3_384, sizeof(s_pbkdf2_hash_hmac_sha3_384) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha3_384; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha3_512) - 1 && memcmp(*argv, s_pbkdf2_hash_hmac_sha3_512, sizeof(s_pbkdf2_hash_hmac_sha3_512) - 1) == 0){ hash_id = mk_pbkdf2_hash_sha3_512; }
	else{ check(0); }
	--argc;
	++argv;

	check(argc >= 1);
	password_len = (int)strlen(*argv);
	password = *argv;
	--argc;
	++argv;

	check(argc >= 1);
	salt_len = (int)strlen(*argv);
	salt = *argv;
	--argc;
	++argv;

	check(argc >= 1);
	len = (int)strlen(*argv);
	iterations = strtol(*argv, &endp, 10);
	check(endp != *argv && endp == *argv + len && iterations != 0 && iterations != LONG_MAX && iterations != LONG_MIN && iterations > 0);
	--argc;
	++argv;

	check(argc >= 1);
	input_file_name = *argv;
	--argc;
	++argv;

	check(argc >= 1);
	output_file_name = *argv;
	--argc;
	++argv;

	mk_pbkdf2(hash_id, password, password_len, salt, salt_len, iterations, mk_block_cipher_get_key_len(block_cipher), key);

	mk_crypt_init(&crypt, operation_mode, block_cipher, key);

	input_file = fopen(input_file_name, "rb");
	check(input_file);

	output_file = fopen(output_file_name, "wb");
	check(output_file);

	if(direction == 0)
	{
		srand((unsigned)time(NULL));
		for(i = 0; i != sizeof(iv); ++i)
		{
			iv[i] = rand() % 0xff;
		}

		written = fwrite(iv, 1, sizeof(iv), output_file);
		check(written == sizeof(iv));
	}
	else
	{
		read_a = fread(iv, 1, sizeof(iv), input_file);
		check(read_a == sizeof(iv));
	}

	if(operation_mode != mk_operation_mode_ecb)
	{
		mk_crypt_set_param_iv(&crypt, iv);
	}

	buffer_a = buffer_1;
	buffer_b = buffer_2;
	read_a = fread(buffer_a, 1, sizeof(buffer_1) - mk_block_cipher_block_len_max, input_file);
	if(read_a == 0)
	{
		check(feof(input_file) != 0);
	}
	if(read_a != 0)
	{
		for(;;)
		{
			read_b = fread(buffer_b, 1, sizeof(buffer_1) - mk_block_cipher_block_len_max, input_file);
			if(read_b == 0)
			{
				check(feof(input_file) != 0);
				break;
			}

			if(direction == 0)
			{
				crypted = mk_crypt_encrypt(&crypt, 0, buffer_a, (int)read_a, buffer_a);
			}
			else
			{
				crypted = mk_crypt_decrypt(&crypt, 0, buffer_a, (int)read_a, buffer_a);
			}

			written = fwrite(buffer_a, 1, crypted, output_file);
			check((int)written == crypted);

			buffer_t = buffer_a;
			buffer_a = buffer_b;
			buffer_b = buffer_t;
			read_t = read_a;
			read_a = read_b;
			read_b = read_t;
		}
	}
	if(direction == 0)
	{
		crypted = mk_crypt_encrypt(&crypt, 1, buffer_a, (int)read_a, buffer_a);
	}
	else
	{
		crypted = mk_crypt_decrypt(&crypt, 1, buffer_a, (int)read_a, buffer_a);
		check(crypted != -1);
	}
	written = fwrite(buffer_a, 1, crypted, output_file);
	check((int)written == crypted);

	fclosed = fclose(output_file);
	check(fclosed == 0);

	fclosed = fclose(input_file);
	check(fclosed == 0);

	return 0;
}


#undef check
