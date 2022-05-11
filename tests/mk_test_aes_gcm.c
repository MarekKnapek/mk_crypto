#include "mk_test_aes_gcm.h"

#include "../src/mk_crypto.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"


/* http://www.csrc.nist.gov/groups/ST/toolkit/BCM/documents/proposedmodes/gcm/gcm-revised-spec.pdf */


struct mk_test_aes_gcm_detail_test_case_s
{
	void const* m_key;
	int m_key_len;
	void const* m_iv;
	int m_iv_len;
	void const* m_aad;
	int m_aad_len;
	void const* m_plain_text;
	int m_plain_text_len;
	void const* m_cipher_text;
	int m_cipher_text_len;
	void const* m_tag;
	int m_tag_len;
};


static char const s_key_0[] = "00000000000000000000000000000000";
static char const s_key_1[] = "00000000000000000000000000000000";
static char const s_key_2[] = "feffe9928665731c6d6a8f9467308308";
static char const s_key_3[] = "feffe9928665731c6d6a8f9467308308";
static char const s_key_4[] = "feffe9928665731c6d6a8f9467308308";
static char const s_key_5[] = "feffe9928665731c6d6a8f9467308308";
static char const s_key_6[] = "000000000000000000000000000000000000000000000000";
static char const s_key_7[] = "000000000000000000000000000000000000000000000000";
static char const s_key_8[] = "feffe9928665731c6d6a8f9467308308feffe9928665731c";
static char const s_key_9[] = "feffe9928665731c6d6a8f9467308308feffe9928665731c";
static char const s_key_a[] = "feffe9928665731c6d6a8f9467308308feffe9928665731c";
static char const s_key_b[] = "feffe9928665731c6d6a8f9467308308feffe9928665731c";
static char const s_key_c[] = "0000000000000000000000000000000000000000000000000000000000000000";
static char const s_key_d[] = "0000000000000000000000000000000000000000000000000000000000000000";
static char const s_key_e[] = "feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308";
static char const s_key_f[] = "feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308";
static char const s_key_g[] = "feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308";
static char const s_key_h[] = "feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308";

static char const s_iv_0[] = "000000000000000000000000";
static char const s_iv_1[] = "000000000000000000000000";
static char const s_iv_2[] = "cafebabefacedbaddecaf888";
static char const s_iv_3[] = "cafebabefacedbaddecaf888";
static char const s_iv_4[] = "cafebabefacedbad";
static char const s_iv_5[] = "9313225df88406e555909c5aff5269aa6a7a9538534f7da1e4c303d2a318a728c3c0c95156809539fcf0e2429a6b525416aedbf5a0de6a57a637b39b";
static char const s_iv_6[] = "000000000000000000000000";
static char const s_iv_7[] = "000000000000000000000000";
static char const s_iv_8[] = "cafebabefacedbaddecaf888";
static char const s_iv_9[] = "cafebabefacedbaddecaf888";
static char const s_iv_a[] = "cafebabefacedbad";
static char const s_iv_b[] = "9313225df88406e555909c5aff5269aa6a7a9538534f7da1e4c303d2a318a728c3c0c95156809539fcf0e2429a6b525416aedbf5a0de6a57a637b39b";
static char const s_iv_c[] = "000000000000000000000000";
static char const s_iv_d[] = "000000000000000000000000";
static char const s_iv_e[] = "cafebabefacedbaddecaf888";
static char const s_iv_f[] = "cafebabefacedbaddecaf888";
static char const s_iv_g[] = "cafebabefacedbad";
static char const s_iv_h[] = "9313225df88406e555909c5aff5269aa6a7a9538534f7da1e4c303d2a318a728c3c0c95156809539fcf0e2429a6b525416aedbf5a0de6a57a637b39b";

static char const s_aad_0[] = "";
static char const s_aad_1[] = "";
static char const s_aad_2[] = "";
static char const s_aad_3[] = "feedfacedeadbeeffeedfacedeadbeefabaddad2";
static char const s_aad_4[] = "feedfacedeadbeeffeedfacedeadbeefabaddad2";
static char const s_aad_5[] = "feedfacedeadbeeffeedfacedeadbeefabaddad2";
static char const s_aad_6[] = "";
static char const s_aad_7[] = "";
static char const s_aad_8[] = "";
static char const s_aad_9[] = "feedfacedeadbeeffeedfacedeadbeefabaddad2";
static char const s_aad_a[] = "feedfacedeadbeeffeedfacedeadbeefabaddad2";
static char const s_aad_b[] = "feedfacedeadbeeffeedfacedeadbeefabaddad2";
static char const s_aad_c[] = "";
static char const s_aad_d[] = "";
static char const s_aad_e[] = "";
static char const s_aad_f[] = "feedfacedeadbeeffeedfacedeadbeefabaddad2";
static char const s_aad_g[] = "feedfacedeadbeeffeedfacedeadbeefabaddad2";
static char const s_aad_h[] = "feedfacedeadbeeffeedfacedeadbeefabaddad2";

static char const s_plain_text_0[] = "";
static char const s_plain_text_1[] = "00000000000000000000000000000000";
static char const s_plain_text_2[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b391aafd255";
static char const s_plain_text_3[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39";
static char const s_plain_text_4[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39";
static char const s_plain_text_5[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39";
static char const s_plain_text_6[] = "";
static char const s_plain_text_7[] = "00000000000000000000000000000000";
static char const s_plain_text_8[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b391aafd255";
static char const s_plain_text_9[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39";
static char const s_plain_text_a[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39";
static char const s_plain_text_b[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39";
static char const s_plain_text_c[] = "";
static char const s_plain_text_d[] = "00000000000000000000000000000000";
static char const s_plain_text_e[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b391aafd255";
static char const s_plain_text_f[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39";
static char const s_plain_text_g[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39";
static char const s_plain_text_h[] = "d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39";

static char const s_cipher_text_0[] = "";
static char const s_cipher_text_1[] = "0388dace60b6a392f328c2b971b2fe78";
static char const s_cipher_text_2[] = "42831ec2217774244b7221b784d0d49ce3aa212f2c02a4e035c17e2329aca12e21d514b25466931c7d8f6a5aac84aa051ba30b396a0aac973d58e091473f5985";
static char const s_cipher_text_3[] = "42831ec2217774244b7221b784d0d49ce3aa212f2c02a4e035c17e2329aca12e21d514b25466931c7d8f6a5aac84aa051ba30b396a0aac973d58e091";
static char const s_cipher_text_4[] = "61353b4c2806934a777ff51fa22a4755699b2a714fcdc6f83766e5f97b6c742373806900e49f24b22b097544d4896b424989b5e1ebac0f07c23f4598";
static char const s_cipher_text_5[] = "8ce24998625615b603a033aca13fb894be9112a5c3a211a8ba262a3cca7e2ca701e4a9a4fba43c90ccdcb281d48c7c6fd62875d2aca417034c34aee5";
static char const s_cipher_text_6[] = "";
static char const s_cipher_text_7[] = "98e7247c07f0fe411c267e4384b0f600";
static char const s_cipher_text_8[] = "3980ca0b3c00e841eb06fac4872a2757859e1ceaa6efd984628593b40ca1e19c7d773d00c144c525ac619d18c84a3f4718e2448b2fe324d9ccda2710acade256";
static char const s_cipher_text_9[] = "3980ca0b3c00e841eb06fac4872a2757859e1ceaa6efd984628593b40ca1e19c7d773d00c144c525ac619d18c84a3f4718e2448b2fe324d9ccda2710";
static char const s_cipher_text_a[] = "0f10f599ae14a154ed24b36e25324db8c566632ef2bbb34f8347280fc4507057fddc29df9a471f75c66541d4d4dad1c9e93a19a58e8b473fa0f062f7";
static char const s_cipher_text_b[] = "d27e88681ce3243c4830165a8fdcf9ff1de9a1d8e6b447ef6ef7b79828666e4581e79012af34ddd9e2f037589b292db3e67c036745fa22e7e9b7373b";
static char const s_cipher_text_c[] = "";
static char const s_cipher_text_d[] = "cea7403d4d606b6e074ec5d3baf39d18";
static char const s_cipher_text_e[] = "522dc1f099567d07f47f37a32a84427d643a8cdcbfe5c0c97598a2bd2555d1aa8cb08e48590dbb3da7b08b1056828838c5f61e6393ba7a0abcc9f662898015ad";
static char const s_cipher_text_f[] = "522dc1f099567d07f47f37a32a84427d643a8cdcbfe5c0c97598a2bd2555d1aa8cb08e48590dbb3da7b08b1056828838c5f61e6393ba7a0abcc9f662";
static char const s_cipher_text_g[] = "c3762df1ca787d32ae47c13bf19844cbaf1ae14d0b976afac52ff7d79bba9de0feb582d33934a4f0954cc2363bc73f7862ac430e64abe499f47c9b1f";
static char const s_cipher_text_h[] = "5a8def2f0c9e53f1f75d7853659e2a20eeb2b22aafde6419a058ab4f6f746bf40fc0c3b780f244452da3ebf1c5d82cdea2418997200ef82e44ae7e3f";

static char const s_tag_0[] = "58e2fccefa7e3061367f1d57a4e7455a";
static char const s_tag_1[] = "ab6e47d42cec13bdf53a67b21257bddf";
static char const s_tag_2[] = "4d5c2af327cd64a62cf35abd2ba6fab4";
static char const s_tag_3[] = "5bc94fbc3221a5db94fae95ae7121a47";
static char const s_tag_4[] = "3612d2e79e3b0785561be14aaca2fccb";
static char const s_tag_5[] = "619cc5aefffe0bfa462af43c1699d050";
static char const s_tag_6[] = "cd33b28ac773f74ba00ed1f312572435";
static char const s_tag_7[] = "2ff58d80033927ab8ef4d4587514f0fb";
static char const s_tag_8[] = "9924a7c8587336bfb118024db8674a14";
static char const s_tag_9[] = "2519498e80f1478f37ba55bd6d27618c";
static char const s_tag_a[] = "65dcc57fcf623a24094fcca40d3533f8";
static char const s_tag_b[] = "dcf566ff291c25bbb8568fc3d376a6d9";
static char const s_tag_c[] = "530f8afbc74536b9a963b4f1c4cb738b";
static char const s_tag_d[] = "d0d1c8a799996bf0265b98b5d48ab919";
static char const s_tag_e[] = "b094dac5d93471bdec1a502270e3cc6c";
static char const s_tag_f[] = "76fc6ece0f4e1768cddf8853bb2d551b";
static char const s_tag_g[] = "3a337dbf46a792c45e454913fe2ea8f2";
static char const s_tag_h[] = "a44a8266ee1c8eb0c8b5d4cf5ae9f19a";


static struct mk_test_aes_gcm_detail_test_case_s const s_test_cases[] =
{
	{s_key_0, sizeof(s_key_0), s_iv_0, sizeof(s_iv_0), s_aad_0, sizeof(s_aad_0), s_plain_text_0, sizeof(s_plain_text_0), s_cipher_text_0, sizeof(s_cipher_text_0), s_tag_0, sizeof(s_tag_0)},
	{s_key_1, sizeof(s_key_1), s_iv_1, sizeof(s_iv_1), s_aad_1, sizeof(s_aad_1), s_plain_text_1, sizeof(s_plain_text_1), s_cipher_text_1, sizeof(s_cipher_text_1), s_tag_1, sizeof(s_tag_1)},
	{s_key_2, sizeof(s_key_2), s_iv_2, sizeof(s_iv_2), s_aad_2, sizeof(s_aad_2), s_plain_text_2, sizeof(s_plain_text_2), s_cipher_text_2, sizeof(s_cipher_text_2), s_tag_2, sizeof(s_tag_2)},
	{s_key_3, sizeof(s_key_3), s_iv_3, sizeof(s_iv_3), s_aad_3, sizeof(s_aad_3), s_plain_text_3, sizeof(s_plain_text_3), s_cipher_text_3, sizeof(s_cipher_text_3), s_tag_3, sizeof(s_tag_3)},
	{s_key_4, sizeof(s_key_4), s_iv_4, sizeof(s_iv_4), s_aad_4, sizeof(s_aad_4), s_plain_text_4, sizeof(s_plain_text_4), s_cipher_text_4, sizeof(s_cipher_text_4), s_tag_4, sizeof(s_tag_4)},
	{s_key_5, sizeof(s_key_5), s_iv_5, sizeof(s_iv_5), s_aad_5, sizeof(s_aad_5), s_plain_text_5, sizeof(s_plain_text_5), s_cipher_text_5, sizeof(s_cipher_text_5), s_tag_5, sizeof(s_tag_5)},
	{s_key_6, sizeof(s_key_6), s_iv_6, sizeof(s_iv_6), s_aad_6, sizeof(s_aad_6), s_plain_text_6, sizeof(s_plain_text_6), s_cipher_text_6, sizeof(s_cipher_text_6), s_tag_6, sizeof(s_tag_6)},
	{s_key_7, sizeof(s_key_7), s_iv_7, sizeof(s_iv_7), s_aad_7, sizeof(s_aad_7), s_plain_text_7, sizeof(s_plain_text_7), s_cipher_text_7, sizeof(s_cipher_text_7), s_tag_7, sizeof(s_tag_7)},
	{s_key_8, sizeof(s_key_8), s_iv_8, sizeof(s_iv_8), s_aad_8, sizeof(s_aad_8), s_plain_text_8, sizeof(s_plain_text_8), s_cipher_text_8, sizeof(s_cipher_text_8), s_tag_8, sizeof(s_tag_8)},
	{s_key_9, sizeof(s_key_9), s_iv_9, sizeof(s_iv_9), s_aad_9, sizeof(s_aad_9), s_plain_text_9, sizeof(s_plain_text_9), s_cipher_text_9, sizeof(s_cipher_text_9), s_tag_9, sizeof(s_tag_9)},
	{s_key_a, sizeof(s_key_a), s_iv_a, sizeof(s_iv_a), s_aad_a, sizeof(s_aad_a), s_plain_text_a, sizeof(s_plain_text_a), s_cipher_text_a, sizeof(s_cipher_text_a), s_tag_a, sizeof(s_tag_a)},
	{s_key_b, sizeof(s_key_b), s_iv_b, sizeof(s_iv_b), s_aad_b, sizeof(s_aad_b), s_plain_text_b, sizeof(s_plain_text_b), s_cipher_text_b, sizeof(s_cipher_text_b), s_tag_b, sizeof(s_tag_b)},
	{s_key_c, sizeof(s_key_c), s_iv_c, sizeof(s_iv_c), s_aad_c, sizeof(s_aad_c), s_plain_text_c, sizeof(s_plain_text_c), s_cipher_text_c, sizeof(s_cipher_text_c), s_tag_c, sizeof(s_tag_c)},
	{s_key_d, sizeof(s_key_d), s_iv_d, sizeof(s_iv_d), s_aad_d, sizeof(s_aad_d), s_plain_text_d, sizeof(s_plain_text_d), s_cipher_text_d, sizeof(s_cipher_text_d), s_tag_d, sizeof(s_tag_d)},
	{s_key_e, sizeof(s_key_e), s_iv_e, sizeof(s_iv_e), s_aad_e, sizeof(s_aad_e), s_plain_text_e, sizeof(s_plain_text_e), s_cipher_text_e, sizeof(s_cipher_text_e), s_tag_e, sizeof(s_tag_e)},
	{s_key_f, sizeof(s_key_f), s_iv_f, sizeof(s_iv_f), s_aad_f, sizeof(s_aad_f), s_plain_text_f, sizeof(s_plain_text_f), s_cipher_text_f, sizeof(s_cipher_text_f), s_tag_f, sizeof(s_tag_f)},
	{s_key_g, sizeof(s_key_g), s_iv_g, sizeof(s_iv_g), s_aad_g, sizeof(s_aad_g), s_plain_text_g, sizeof(s_plain_text_g), s_cipher_text_g, sizeof(s_cipher_text_g), s_tag_g, sizeof(s_tag_g)},
	{s_key_h, sizeof(s_key_h), s_iv_h, sizeof(s_iv_h), s_aad_h, sizeof(s_aad_h), s_plain_text_h, sizeof(s_plain_text_h), s_cipher_text_h, sizeof(s_cipher_text_h), s_tag_h, sizeof(s_tag_h)},
};


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err; err = (x); if(err != 0){ return err; } }while(0)


static mk_inline int mk_test_aes_gcm_detail_hex_symbol_to_int(char hs)
{
	static char const s_hex_alphabet_lc[] = "0123456789abcdef";
	static char const s_hex_alphabet_uc[] = "0123456789ABCDEF";

	int i;

	for(i = 0; i != sizeof(s_hex_alphabet_lc) - 1; ++i)
	{
		if(hs == s_hex_alphabet_lc[i])
		{
			break;
		}else if(hs == s_hex_alphabet_uc[i])
		{
			break;
		}
	}
	mk_assert(i >= 0 && i <= 0xf);
	return i;
}

static mk_inline void mk_test_aes_gcm_detail_string_hex_to_bytes(void const* in, int len_in, void* out, int len_out)
{
	char const* input;
	unsigned char* output;
	int i;
	int hi;
	int lo;

	mk_assert(in);
	mk_assert(len_in % 2 == 0);
	mk_assert(out);
	mk_assert(len_out >= len_in / 2);

	input = (char const*)in;
	output = (unsigned char*)out;
	for(i = 0; i != len_in / 2; ++i)
	{
		hi = mk_test_aes_gcm_detail_hex_symbol_to_int(input[2 * i + 0]);
		lo = mk_test_aes_gcm_detail_hex_symbol_to_int(input[2 * i + 1]);
		output[i] = (unsigned char)((hi << 4) | (lo << 0));
	}
}

static mk_inline int mk_test_aes_gcm_detail_test_case_unpacked(void const* key, int key_len, void const* iv, int iv_len, void const* aad, int aad_len, void const* plain_text, int plain_text_len, void const* cipher_text, int cipher_text_len, void const* tag, int tag_len)
{
	struct aad_param_s
	{
		void const* m_aad;
		int m_aad_len;
	};

	unsigned char bin_key[32];
	unsigned char bin_iv[60];
	unsigned char bin_aad[20];
	unsigned char bin_plain_text[64];
	unsigned char bin_cipher_text[64];
	unsigned char bin_tag[16];

	enum mk_crypto_block_cipher_e block_cipher;
	mk_crypto_h crypto;
	struct aad_param_s aad_param;
	int encrypted;
	unsigned char bin_my_cipher_text[64+16];

	mk_check(key);
	mk_check(key_len == 16 * 2 + 1 || key_len == 24 * 2 + 1 || key_len == 32 * 2 + 1);
	mk_check(iv);
	mk_check((iv_len - 1) % 2 == 0);
	mk_check(aad);
	mk_check((aad_len - 1) % 2 == 0);
	mk_check(plain_text);
	mk_check((plain_text_len - 1) % 2 == 0);
	mk_check(cipher_text);
	mk_check((cipher_text_len - 1) % 2 == 0);
	mk_check(tag);
	mk_check(tag_len == 16 * 2 + 1);

	mk_test_aes_gcm_detail_string_hex_to_bytes(key, key_len - 1, &bin_key, sizeof(bin_key));
	mk_test_aes_gcm_detail_string_hex_to_bytes(iv, iv_len - 1, &bin_iv, sizeof(bin_iv));
	mk_test_aes_gcm_detail_string_hex_to_bytes(aad, aad_len - 1, &bin_aad, sizeof(bin_aad));
	mk_test_aes_gcm_detail_string_hex_to_bytes(plain_text, plain_text_len - 1, &bin_plain_text, sizeof(bin_plain_text));
	mk_test_aes_gcm_detail_string_hex_to_bytes(cipher_text, cipher_text_len - 1, &bin_cipher_text, sizeof(bin_cipher_text));
	mk_test_aes_gcm_detail_string_hex_to_bytes(tag, tag_len - 1, &bin_tag, sizeof(bin_tag));

	block_cipher = key_len == 16 * 2 + 1 ? mk_crypto_block_cipher_aes128 : key_len == 24 * 2 + 1 ? mk_crypto_block_cipher_aes192 : mk_crypto_block_cipher_aes256;

	crypto = mk_crypto_create(mk_crypto_operation_mode_gcm, block_cipher, bin_iv, (iv_len - 1) / 2, bin_key, (key_len - 1) / 2);
	mk_check(crypto);

	if(aad_len != 1)
	{
		aad_param.m_aad = bin_aad;
		aad_param.m_aad_len = (aad_len - 1) / 2;
		mk_crypto_set_param(crypto, mk_crypto_param_gcm_aad_finish, &aad_param);
	}

	encrypted = mk_crypto_encrypt(crypto, 1, bin_plain_text, (plain_text_len - 1) / 2, bin_my_cipher_text, sizeof(bin_my_cipher_text));
	//mk_check(encrypted == (plain_text_len - 1) / 2);

	mk_crypto_destroy(crypto);

	return 0;
}

static mk_inline int mk_test_aes_gcm_detail_test_case_packed(struct mk_test_aes_gcm_detail_test_case_s const* test_case)
{
	mk_check(test_case);

	mk_try(mk_test_aes_gcm_detail_test_case_unpacked(test_case->m_key, test_case->m_key_len, test_case->m_iv, test_case->m_iv_len, test_case->m_aad, test_case->m_aad_len, test_case->m_plain_text, test_case->m_plain_text_len, test_case->m_cipher_text, test_case->m_cipher_text_len, test_case->m_tag, test_case->m_tag_len));

	return 0;
}


int mk_test_aes_gcm(void)
{
	int n;
	int i;

	n = sizeof(s_test_cases) / sizeof(s_test_cases[0]);
	for(i = 0; i != n; ++i)
	{
		mk_try(mk_test_aes_gcm_detail_test_case_packed(&s_test_cases[i]));
	}

	return 0;
}


#undef mk_check
#undef mk_try
