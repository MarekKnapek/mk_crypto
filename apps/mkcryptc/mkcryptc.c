#include "mkcryptc.h"

#include "../../src/mk_block_cipher.h"
#include "../../src/mk_crypt.h"
#include "../../src/mk_pbkdf2.h"

#include <limits.h> /* LONG_MAX LONG_MIN */
#include <stddef.h> /* NULL */
#include <stdio.h> /* FILE size_t fopen fread fclose */
#include <stdlib.h> /* malloc free strtol srand rand */
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


struct main_object_s
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
	unsigned char buffer_2[512 + mk_block_cipher_block_len_max];
	size_t read_b;
	int crypted;
	unsigned char* buffer_t;
	size_t read_t;
	int fclosed;
};


#define check(x) do{ if(!(x)){ return __LINE__; } }while(0)


int mkcryptc(int argc_, char const* const* argv_)
{
	struct main_object_s* mo;

	mo = (struct main_object_s*)malloc(sizeof(struct main_object_s));
	check(mo);

	mo->argc = argc_ - 1;
	mo->argv = argv_ + 1;

	check(mo->argc >= 1);
	mo->len = (int)strlen(*mo->argv);
	if(mo->len == sizeof(s_command_encrypt) - 1 && memcmp(*mo->argv, s_command_encrypt, sizeof(s_command_encrypt) - 1) == 0){ mo->direction = 0; }
	else if(mo->len == sizeof(s_command_decrypt) - 1 && memcmp(*mo->argv, s_command_decrypt, sizeof(s_command_decrypt) - 1) == 0){ mo->direction = 1; }
	else{ check(0); }
	--mo->argc;
	++mo->argv;

	mo->cfb_f = -1;
	mo->ctr_be = -1;
	check(mo->argc >= 1);
	mo->len = (int)strlen(*mo->argv);
	if(mo->len == sizeof(s_operation_mode_cbc) - 1 && memcmp(*mo->argv, s_operation_mode_cbc, sizeof(s_operation_mode_cbc) - 1) == 0){ mo->operation_mode = mk_operation_mode_cbc; }
	else if(mo->len == sizeof(s_operation_mode_cfb) - 1 && memcmp(*mo->argv, s_operation_mode_cfb, sizeof(s_operation_mode_cfb) - 1) == 0){ mo->operation_mode = mk_operation_mode_cfb; mo->cfb_f = 0; }
	else if(mo->len == sizeof(s_operation_mode_cfb_f) - 1 && memcmp(*mo->argv, s_operation_mode_cfb_f, sizeof(s_operation_mode_cfb_f) - 1) == 0){ mo->operation_mode = mk_operation_mode_cfb; mo->cfb_f = 1; }
	else if(mo->len == sizeof(s_operation_mode_ctr) - 1 && memcmp(*mo->argv, s_operation_mode_ctr, sizeof(s_operation_mode_ctr) - 1) == 0){ mo->operation_mode = mk_operation_mode_ctr; mo->ctr_be = 0; }
	else if(mo->len == sizeof(s_operation_mode_ctr_be) - 1 && memcmp(*mo->argv, s_operation_mode_ctr_be, sizeof(s_operation_mode_ctr_be) - 1) == 0){ mo->operation_mode = mk_operation_mode_ctr; mo->ctr_be = 1; }
	else if(mo->len == sizeof(s_operation_mode_ecb) - 1 && memcmp(*mo->argv, s_operation_mode_ecb, sizeof(s_operation_mode_ecb) - 1) == 0){ mo->operation_mode = mk_operation_mode_ecb; }
	else if(mo->len == sizeof(s_operation_mode_ofb) - 1 && memcmp(*mo->argv, s_operation_mode_ofb, sizeof(s_operation_mode_ofb) - 1) == 0){ mo->operation_mode = mk_operation_mode_ofb; }
	else{ check(0); }
	--mo->argc;
	++mo->argv;

	check(mo->argc >= 1);
	mo->len = (int)strlen(*mo->argv);
	if(mo->len == sizeof(s_block_cipher_aes128) - 1 && memcmp(*mo->argv, s_block_cipher_aes128, sizeof(s_block_cipher_aes128) - 1) == 0){ mo->block_cipher = mk_block_cipher_aes128; }
	else if(mo->len == sizeof(s_block_cipher_aes192) - 1 && memcmp(*mo->argv, s_block_cipher_aes192, sizeof(s_block_cipher_aes192) - 1) == 0){ mo->block_cipher = mk_block_cipher_aes192; }
	else if(mo->len == sizeof(s_block_cipher_aes256) - 1 && memcmp(*mo->argv, s_block_cipher_aes256, sizeof(s_block_cipher_aes256) - 1) == 0){ mo->block_cipher = mk_block_cipher_aes256; }
	else{ check(0); }
	--mo->argc;
	++mo->argv;

	check(mo->argc >= 1);
	mo->len = (int)strlen(*mo->argv);
	if(mo->len == sizeof(s_kdf_pbkdf2) - 1 && memcmp(*mo->argv, s_kdf_pbkdf2, sizeof(s_kdf_pbkdf2) - 1) == 0){}
	else{ check(0); }
	--mo->argc;
	++mo->argv;

	check(mo->argc >= 1);
	mo->len = (int)strlen(*mo->argv);
	if(mo->len == sizeof(s_pbkdf2_hash_hmac_md2) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_md2, sizeof(s_pbkdf2_hash_hmac_md2) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_md2; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_md4) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_md4, sizeof(s_pbkdf2_hash_hmac_md4) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_md4; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_md5) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_md5, sizeof(s_pbkdf2_hash_hmac_md5) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_md5; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha1) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha1, sizeof(s_pbkdf2_hash_hmac_sha1) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha1; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha2_224) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha2_224, sizeof(s_pbkdf2_hash_hmac_sha2_224) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha2_224; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha2_256) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha2_256, sizeof(s_pbkdf2_hash_hmac_sha2_256) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha2_256; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha2_384) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha2_384, sizeof(s_pbkdf2_hash_hmac_sha2_384) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha2_384; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha2_512) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha2_512, sizeof(s_pbkdf2_hash_hmac_sha2_512) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha2_512; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha2_512224) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha2_512224, sizeof(s_pbkdf2_hash_hmac_sha2_512224) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha2_512224; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha2_512256) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha2_512256, sizeof(s_pbkdf2_hash_hmac_sha2_512256) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha2_512256; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha3_224) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha3_224, sizeof(s_pbkdf2_hash_hmac_sha3_224) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha3_224; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha3_256) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha3_256, sizeof(s_pbkdf2_hash_hmac_sha3_256) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha3_256; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha3_384) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha3_384, sizeof(s_pbkdf2_hash_hmac_sha3_384) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha3_384; }
	else if(mo->len == sizeof(s_pbkdf2_hash_hmac_sha3_512) - 1 && memcmp(*mo->argv, s_pbkdf2_hash_hmac_sha3_512, sizeof(s_pbkdf2_hash_hmac_sha3_512) - 1) == 0){ mo->hash_id = mk_pbkdf2_hash_sha3_512; }
	else{ check(0); }
	--mo->argc;
	++mo->argv;

	check(mo->argc >= 1);
	mo->password_len = (int)strlen(*mo->argv);
	mo->password = *mo->argv;
	--mo->argc;
	++mo->argv;

	check(mo->argc >= 1);
	mo->salt_len = (int)strlen(*mo->argv);
	mo->salt = *mo->argv;
	--mo->argc;
	++mo->argv;

	check(mo->argc >= 1);
	mo->len = (int)strlen(*mo->argv);
	mo->iterations = strtol(*mo->argv, &mo->endp, 10);
	check(mo->endp != *mo->argv && mo->endp == *mo->argv + mo->len && mo->iterations != 0 && mo->iterations != LONG_MAX && mo->iterations != LONG_MIN && mo->iterations > 0);
	--mo->argc;
	++mo->argv;

	check(mo->argc >= 1);
	mo->input_file_name = *mo->argv;
	--mo->argc;
	++mo->argv;

	check(mo->argc >= 1);
	mo->output_file_name = *mo->argv;
	--mo->argc;
	++mo->argv;

	mk_pbkdf2(mo->hash_id, mo->password, mo->password_len, mo->salt, mo->salt_len, mo->iterations, mk_block_cipher_get_key_len(mo->block_cipher), mo->key);

	mk_crypt_init(&mo->crypt, mo->operation_mode, mo->block_cipher, mo->key);
	if(mo->operation_mode == mk_operation_mode_cfb && mo->cfb_f == 1)
	{
		mk_crypt_set_param_cfb_s_bytes(&mo->crypt, mk_block_cipher_get_block_len(mo->block_cipher));
	}
	if(mo->operation_mode == mk_operation_mode_ctr && mo->ctr_be == 1)
	{
		mk_crypt_set_param_ctr_endian(&mo->crypt, 1);
	}

	mo->input_file = fopen(mo->input_file_name, "rb");
	check(mo->input_file);

	mo->output_file = fopen(mo->output_file_name, "wb");
	check(mo->output_file);

	if(mo->direction == 0)
	{
		srand((unsigned)time(NULL));
		for(mo->i = 0; mo->i != sizeof(mo->iv); ++mo->i)
		{
			mo->iv[mo->i] = rand() % 0xff;
		}

		mo->written = fwrite(mo->iv, 1, sizeof(mo->iv), mo->output_file);
		check(mo->written == sizeof(mo->iv));
	}
	else
	{
		mo->read_a = fread(mo->iv, 1, sizeof(mo->iv), mo->input_file);
		check(mo->read_a == sizeof(mo->iv));
	}

	if(mo->operation_mode != mk_operation_mode_ecb)
	{
		mk_crypt_set_param_iv(&mo->crypt, mo->iv);
	}

	mo->buffer_a = mo->buffer_1;
	mo->buffer_b = mo->buffer_2;
	mo->read_a = fread(mo->buffer_a, 1, sizeof(mo->buffer_1) - mk_block_cipher_block_len_max, mo->input_file);
	if(mo->read_a == 0)
	{
		check(feof(mo->input_file) != 0);
	}
	if(mo->read_a != 0)
	{
		for(;;)
		{
			mo->read_b = fread(mo->buffer_b, 1, sizeof(mo->buffer_1) - mk_block_cipher_block_len_max, mo->input_file);
			if(mo->read_b == 0)
			{
				check(feof(mo->input_file) != 0);
				break;
			}

			if(mo->direction == 0)
			{
				mo->crypted = mk_crypt_encrypt(&mo->crypt, 0, mo->buffer_a, (int)mo->read_a, mo->buffer_a);
			}
			else
			{
				mo->crypted = mk_crypt_decrypt(&mo->crypt, 0, mo->buffer_a, (int)mo->read_a, mo->buffer_a);
			}

			mo->written = fwrite(mo->buffer_a, 1, mo->crypted, mo->output_file);
			check((int)mo->written == mo->crypted);

			mo->buffer_t = mo->buffer_a;
			mo->buffer_a = mo->buffer_b;
			mo->buffer_b = mo->buffer_t;
			mo->read_t = mo->read_a;
			mo->read_a = mo->read_b;
			mo->read_b = mo->read_t;
		}
	}
	if(mo->direction == 0)
	{
		mo->crypted = mk_crypt_encrypt(&mo->crypt, 1, mo->buffer_a, (int)mo->read_a, mo->buffer_a);
	}
	else
	{
		mo->crypted = mk_crypt_decrypt(&mo->crypt, 1, mo->buffer_a, (int)mo->read_a, mo->buffer_a);
		check(mo->crypted != -1);
	}
	mo->written = fwrite(mo->buffer_a, 1, mo->crypted, mo->output_file);
	check((int)mo->written == mo->crypted);

	mo->fclosed = fclose(mo->output_file);
	check(mo->fclosed == 0);

	mo->fclosed = fclose(mo->input_file);
	check(mo->fclosed == 0);

	free(mo);

	return 0;
}


#undef check
