#include "mkcryptc.h"

#include "../../utils/mk_assert.h"
#include "../../utils/mk_inline.h"

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


struct inputs_s
{
	int direction;
	enum mk_operation_mode_e operation_mode;
	int cfb_f;
	int ctr_be;
	enum mk_block_cipher_e block_cipher;
	enum mk_pbkdf2_hash_e prf;
	char const* password;
	int password_len;
	char const* salt;
	int salt_len;
	long iterations;
	char const* input_file_name;
	char const* output_file_name;
};


#define check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err = (x); if(err != 0){ return err; } }while(0)


static mk_inline int mkcryptc_detail_parse_direction(int* argc_, char const* const** argv_, int* direction_)
{
	int argc;
	char const* const* argv;
	int len;
	int direction;

	mk_assert(argc_);
	mk_assert(argv_);
	mk_assert(direction_);

	argc = *argc_;
	argv = *argv_;

	check(argc >= 1);
	len = (int)strlen(argv[0]);
	if(len == sizeof(s_command_encrypt) - 1 && memcmp(argv[0], s_command_encrypt, sizeof(s_command_encrypt) - 1) == 0){ direction = 0; }
	else if(len == sizeof(s_command_decrypt) - 1 && memcmp(argv[0], s_command_decrypt, sizeof(s_command_decrypt) - 1) == 0){ direction = 1; }
	else{ check(0); }
	--argc;
	++argv;

	*argc_ = argc;
	*argv_ = argv;
	*direction_ = direction;
	return 0;
}

static mk_inline int mkcryptc_detail_parse_operation_mode(int* argc_, char const* const** argv_, enum mk_operation_mode_e* operation_mode_, int* cfb_f_, int* ctr_be_)
{
	int argc;
	char const* const* argv;
	int len;
	enum mk_operation_mode_e operation_mode;
	int cfb_f;
	int ctr_be;

	mk_assert(argc_);
	mk_assert(argv_);
	mk_assert(operation_mode_);
	mk_assert(cfb_f_);
	mk_assert(ctr_be_);

	argc = *argc_;
	argv = *argv_;

	cfb_f = 0; /**/
	ctr_be = 0; /**/
	check(argc >= 1);
	len = (int)strlen(argv[0]);
	if(len == sizeof(s_operation_mode_cbc) - 1 && memcmp(argv[0], s_operation_mode_cbc, sizeof(s_operation_mode_cbc) - 1) == 0){ operation_mode = mk_operation_mode_cbc; }
	else if(len == sizeof(s_operation_mode_cfb) - 1 && memcmp(argv[0], s_operation_mode_cfb, sizeof(s_operation_mode_cfb) - 1) == 0){ operation_mode = mk_operation_mode_cfb; cfb_f = 0; }
	else if(len == sizeof(s_operation_mode_cfb_f) - 1 && memcmp(argv[0], s_operation_mode_cfb_f, sizeof(s_operation_mode_cfb_f) - 1) == 0){ operation_mode = mk_operation_mode_cfb; cfb_f = 1; }
	else if(len == sizeof(s_operation_mode_ctr) - 1 && memcmp(argv[0], s_operation_mode_ctr, sizeof(s_operation_mode_ctr) - 1) == 0){ operation_mode = mk_operation_mode_ctr; ctr_be = 0; }
	else if(len == sizeof(s_operation_mode_ctr_be) - 1 && memcmp(argv[0], s_operation_mode_ctr_be, sizeof(s_operation_mode_ctr_be) - 1) == 0){ operation_mode = mk_operation_mode_ctr; ctr_be = 1; }
	else if(len == sizeof(s_operation_mode_ecb) - 1 && memcmp(argv[0], s_operation_mode_ecb, sizeof(s_operation_mode_ecb) - 1) == 0){ operation_mode = mk_operation_mode_ecb; }
	else if(len == sizeof(s_operation_mode_ofb) - 1 && memcmp(argv[0], s_operation_mode_ofb, sizeof(s_operation_mode_ofb) - 1) == 0){ operation_mode = mk_operation_mode_ofb; }
	else{ check(0); }
	--argc;
	++argv;

	*argc_ = argc;
	*argv_ = argv;
	*operation_mode_ = operation_mode;
	*cfb_f_ = cfb_f;
	*ctr_be_ = ctr_be;
	return 0;
}

static mk_inline int mkcryptc_detail_parse_block_cipher(int* argc_, char const* const** argv_, enum mk_block_cipher_e* block_cipher_)
{
	int argc;
	char const* const* argv;
	int len;
	enum mk_block_cipher_e block_cipher;

	mk_assert(argc_);
	mk_assert(argv_);
	mk_assert(block_cipher_);

	argc = *argc_;
	argv = *argv_;

	check(argc >= 1);
	len = (int)strlen(argv[0]);
	if(len == sizeof(s_block_cipher_aes128) - 1 && memcmp(argv[0], s_block_cipher_aes128, sizeof(s_block_cipher_aes128) - 1) == 0){ block_cipher = mk_block_cipher_aes128; }
	else if(len == sizeof(s_block_cipher_aes192) - 1 && memcmp(argv[0], s_block_cipher_aes192, sizeof(s_block_cipher_aes192) - 1) == 0){ block_cipher = mk_block_cipher_aes192; }
	else if(len == sizeof(s_block_cipher_aes256) - 1 && memcmp(argv[0], s_block_cipher_aes256, sizeof(s_block_cipher_aes256) - 1) == 0){ block_cipher = mk_block_cipher_aes256; }
	else{ check(0); }
	--argc;
	++argv;

	*argc_ = argc;
	*argv_ = argv;
	*block_cipher_ = block_cipher;
	return 0;
}

static mk_inline int mkcryptc_detail_parse_pbkdf(int* argc_, char const* const** argv_)
{
	int argc;
	char const* const* argv;
	int len;

	mk_assert(argc_);
	mk_assert(argv_);

	argc = *argc_;
	argv = *argv_;

	check(argc >= 1);
	len = (int)strlen(argv[0]);
	if(len == sizeof(s_kdf_pbkdf2) - 1 && memcmp(argv[0], s_kdf_pbkdf2, sizeof(s_kdf_pbkdf2) - 1) == 0){}
	else{ check(0); }
	--argc;
	++argv;

	*argc_ = argc;
	*argv_ = argv;
	return 0;
}

static mk_inline int mkcryptc_detail_parse_prf(int* argc_, char const* const** argv_, enum mk_pbkdf2_hash_e* prf_)
{
	int argc;
	char const* const* argv;
	int len;
	enum mk_pbkdf2_hash_e prf;

	mk_assert(argc_);
	mk_assert(argv_);
	mk_assert(prf_);

	argc = *argc_;
	argv = *argv_;

	check(argc >= 1);
	len = (int)strlen(argv[0]);
	if(len == sizeof(s_pbkdf2_hash_hmac_md2) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_md2, sizeof(s_pbkdf2_hash_hmac_md2) - 1) == 0){ prf = mk_pbkdf2_hash_md2; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_md4) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_md4, sizeof(s_pbkdf2_hash_hmac_md4) - 1) == 0){ prf = mk_pbkdf2_hash_md4; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_md5) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_md5, sizeof(s_pbkdf2_hash_hmac_md5) - 1) == 0){ prf = mk_pbkdf2_hash_md5; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha1) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha1, sizeof(s_pbkdf2_hash_hmac_sha1) - 1) == 0){ prf = mk_pbkdf2_hash_sha1; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_224) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha2_224, sizeof(s_pbkdf2_hash_hmac_sha2_224) - 1) == 0){ prf = mk_pbkdf2_hash_sha2_224; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_256) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha2_256, sizeof(s_pbkdf2_hash_hmac_sha2_256) - 1) == 0){ prf = mk_pbkdf2_hash_sha2_256; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_384) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha2_384, sizeof(s_pbkdf2_hash_hmac_sha2_384) - 1) == 0){ prf = mk_pbkdf2_hash_sha2_384; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_512) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha2_512, sizeof(s_pbkdf2_hash_hmac_sha2_512) - 1) == 0){ prf = mk_pbkdf2_hash_sha2_512; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_512224) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha2_512224, sizeof(s_pbkdf2_hash_hmac_sha2_512224) - 1) == 0){ prf = mk_pbkdf2_hash_sha2_512224; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha2_512256) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha2_512256, sizeof(s_pbkdf2_hash_hmac_sha2_512256) - 1) == 0){ prf = mk_pbkdf2_hash_sha2_512256; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha3_224) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha3_224, sizeof(s_pbkdf2_hash_hmac_sha3_224) - 1) == 0){ prf = mk_pbkdf2_hash_sha3_224; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha3_256) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha3_256, sizeof(s_pbkdf2_hash_hmac_sha3_256) - 1) == 0){ prf = mk_pbkdf2_hash_sha3_256; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha3_384) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha3_384, sizeof(s_pbkdf2_hash_hmac_sha3_384) - 1) == 0){ prf = mk_pbkdf2_hash_sha3_384; }
	else if(len == sizeof(s_pbkdf2_hash_hmac_sha3_512) - 1 && memcmp(argv[0], s_pbkdf2_hash_hmac_sha3_512, sizeof(s_pbkdf2_hash_hmac_sha3_512) - 1) == 0){ prf = mk_pbkdf2_hash_sha3_512; }
	else{ check(0); }
	--argc;
	++argv;

	*argc_ = argc;
	*argv_ = argv;
	*prf_ = prf;
	return 0;
}

static mk_inline int mkcryptc_detail_parse_string(int* argc_, char const* const** argv_, char const** string_, int* string_len_)
{
	int argc;
	char const* const* argv;
	int len;
	char const* string;
	int string_len;

	mk_assert(argc_);
	mk_assert(argv_);
	mk_assert(string_);
	mk_assert(string_len_);

	argc = *argc_;
	argv = *argv_;

	check(argc >= 1);
	len = (int)strlen(argv[0]);
	string = argv[0];
	string_len = len;
	--argc;
	++argv;

	*argc_ = argc;
	*argv_ = argv;
	*string_ = string;
	*string_len_ = string_len;
	return 0;
}

static mk_inline int mkcryptc_detail_parse_password(int* argc_, char const* const** argv_, char const** password_, int* password_len_)
{
	return mkcryptc_detail_parse_string(argc_, argv_, password_, password_len_);
}

static mk_inline int mkcryptc_detail_parse_salt(int* argc_, char const* const** argv_, char const** salt_, int* salt_len_)
{
	return mkcryptc_detail_parse_string(argc_, argv_, salt_, salt_len_);
}

static mk_inline int mkcryptc_detail_parse_long(int* argc_, char const* const** argv_, long* lng_)
{
	int argc;
	char const* const* argv;
	int len;
	long lng;
	char* endp;

	mk_assert(argc_);
	mk_assert(argv_);
	mk_assert(lng_);

	argc = *argc_;
	argv = *argv_;

	check(argc >= 1);
	len = (int)strlen(argv[0]);
	lng = strtol(argv[0], &endp, 10);
	check(endp != argv[0] && endp == argv[0] + len && lng != 0 && lng != LONG_MAX && lng != LONG_MIN);
	--argc;
	++argv;

	*argc_ = argc;
	*argv_ = argv;
	*lng_ = lng;
	return 0;
}

static mk_inline int mkcryptc_detail_parse_iterations(int* argc_, char const* const** argv_, long* iterations_)
{
	mk_try(mkcryptc_detail_parse_long(argc_, argv_, iterations_));
	check(*iterations_ > 0);

	return 0;
}

static mk_inline int mkcryptc_detail_parse_string_nolen(int* argc_, char const* const** argv_, char const** string_)
{
	int argc;
	char const* const* argv;
	char const* string;

	mk_assert(argc_);
	mk_assert(argv_);
	mk_assert(string_);

	argc = *argc_;
	argv = *argv_;

	check(argc >= 1);
	string = argv[0];
	--argc;
	++argv;

	*argc_ = argc;
	*argv_ = argv;
	*string_ = string;
	return 0;
}

static mk_inline int mkcryptc_detail_parse_input_file_name(int* argc_, char const* const** argv_, char const** input_file_name_)
{
	return mkcryptc_detail_parse_string_nolen(argc_, argv_, input_file_name_);
}

static mk_inline int mkcryptc_detail_parse_output_file_name(int* argc_, char const* const** argv_, char const** output_file_name_)
{
	return mkcryptc_detail_parse_string_nolen(argc_, argv_, output_file_name_);
}

static mk_inline int mkcryptc_detail_parse_inputs(int* argc, char const* const** argv, struct inputs_s* inputs)
{
	mk_assert(argc);
	mk_assert(argv);
	mk_assert(inputs);

	mk_try(mkcryptc_detail_parse_direction(argc, argv, &inputs->direction));
	mk_try(mkcryptc_detail_parse_operation_mode(argc, argv, &inputs->operation_mode, &inputs->cfb_f, &inputs->ctr_be));
	mk_try(mkcryptc_detail_parse_block_cipher(argc, argv, &inputs->block_cipher));
	mk_try(mkcryptc_detail_parse_pbkdf(argc, argv));
	mk_try(mkcryptc_detail_parse_prf(argc, argv, &inputs->prf));
	mk_try(mkcryptc_detail_parse_password(argc, argv, &inputs->password, &inputs->password_len));
	mk_try(mkcryptc_detail_parse_salt(argc, argv, &inputs->salt, &inputs->salt_len));
	mk_try(mkcryptc_detail_parse_iterations(argc, argv, &inputs->iterations));
	mk_try(mkcryptc_detail_parse_input_file_name(argc, argv, &inputs->input_file_name));
	mk_try(mkcryptc_detail_parse_output_file_name(argc, argv, &inputs->output_file_name));

	return 0;
}

static mk_inline int mkcryptc_detail_init_crypt(struct mk_crypt_s* crypt, struct inputs_s* inputs)
{
	unsigned char key[mk_block_cipher_key_len_max];

	mk_assert(crypt);
	mk_assert(inputs);

	mk_pbkdf2(inputs->prf, inputs->password, inputs->password_len, inputs->salt, inputs->salt_len, inputs->iterations, mk_block_cipher_get_key_len(inputs->block_cipher), &key);

	mk_crypt_init(crypt, inputs->operation_mode, inputs->block_cipher, key);
	if(inputs->operation_mode == mk_operation_mode_cfb && inputs->cfb_f == 1)
	{
		mk_crypt_set_param_cfb_s_bytes(crypt, mk_block_cipher_get_block_len(inputs->block_cipher));
	}
	if(inputs->operation_mode == mk_operation_mode_ctr && inputs->ctr_be == 1)
	{
		mk_crypt_set_param_ctr_endian(crypt, 1);
	}

	return 0;
}

static mk_inline int mkcryptc_detail_open_file_read(char const* file_name, FILE** file_)
{
	FILE* file;

	mk_assert(file_name);
	mk_assert(file_);

	file = fopen(file_name, "rb");
	check(file);

	*file_ = file;
	return 0;
}

static mk_inline int mkcryptc_detail_open_file_write(char const* file_name, FILE** file_)
{
	FILE* file;

	mk_assert(file_name);
	mk_assert(file_);

	file = fopen(file_name, "wb");
	check(file);

	*file_ = file;
	return 0;
}

static mk_inline int mkcryptc_detail_init_iv(struct inputs_s* inputs, struct mk_crypt_s* crypt, FILE* input_file, FILE* output_file)
{
	unsigned char iv[mk_block_cipher_block_len_max];
	int i;
	size_t written;
	size_t read;

	mk_assert(inputs);
	mk_assert(crypt);
	mk_assert(input_file);
	mk_assert(output_file);

	if(inputs->operation_mode == mk_operation_mode_ecb)
	{
		return 0;
	}

	if(inputs->direction == 0)
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
		read = fread(iv, 1, sizeof(iv), input_file);
		check(read == sizeof(iv));
	}
	mk_crypt_set_param_iv(crypt, iv);
	return 0;
}

static mk_inline int mkcryptc_detail_process(int direction, struct mk_crypt_s* crypt, FILE* input_file, FILE* output_file)
{
	unsigned char* buffer_a;
	unsigned char buffer_1[512 + mk_block_cipher_block_len_max];
	unsigned char* buffer_b;
	unsigned char buffer_2[512 + mk_block_cipher_block_len_max];
	size_t read_a;
	size_t read_b;
	int crypted;
	size_t written;
	unsigned char* buffer_t;
	size_t read_t;

	mk_assert(direction == 0 || direction == 1);
	mk_assert(crypt);
	mk_assert(input_file);
	mk_assert(output_file);

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

			if( direction == 0)
			{
				crypted = mk_crypt_encrypt(crypt, 0, buffer_a, (int)read_a, buffer_a);
			}
			else
			{
				crypted = mk_crypt_decrypt(crypt, 0, buffer_a, (int)read_a, buffer_a);
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
		crypted = mk_crypt_encrypt(crypt, 1, buffer_a, (int)read_a, buffer_a);
	}
	else
	{
		crypted = mk_crypt_decrypt(crypt, 1, buffer_a, (int)read_a, buffer_a);
		check(crypted != -1);
	}
	written = fwrite(buffer_a, 1, crypted, output_file);
	check((int)written == crypted);

	return 0;
}

static mk_inline int mkcryptc_detail_close_file(FILE* file)
{
	int closed;

	mk_assert(file);

	closed = fclose(file);
	check(closed == 0);

	return 0;
}


int mkcryptc(int argc, char const* const* argv)
{
	struct inputs_s inputs;
	struct mk_crypt_s crypt;
	FILE* input_file;
	FILE* output_file;

	check(argc >= 1);
	--argc;
	++argv;

	mk_try(mkcryptc_detail_parse_inputs(&argc, &argv, &inputs));
	mk_try(mkcryptc_detail_init_crypt(&crypt, &inputs));
	mk_try(mkcryptc_detail_open_file_read(inputs.input_file_name, &input_file));
	mk_try(mkcryptc_detail_open_file_write(inputs.output_file_name, &output_file));
	mk_try(mkcryptc_detail_init_iv(&inputs, &crypt, input_file, output_file));
	mk_try(mkcryptc_detail_process(inputs.direction, &crypt, input_file, output_file));
	mk_try(mkcryptc_detail_close_file(input_file));
	mk_try(mkcryptc_detail_close_file(output_file));

	return 0;
}


#undef check
#undef mk_try
