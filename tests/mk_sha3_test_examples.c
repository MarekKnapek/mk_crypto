#include "mk_sha3_test_examples.h"

#include "mk_test_utils.h"

#include "../src/hash/hash/mk_hash_hash_sha3_224.h"
#include "../src/hash/hash/mk_hash_hash_sha3_256.h"
#include "../src/hash/hash/mk_hash_hash_sha3_384.h"
#include "../src/hash/hash/mk_hash_hash_sha3_512.h"
#include "../src/hash/xof/mk_hash_xof_sha3_shake128.h"
#include "../src/hash/xof/mk_hash_xof_sha3_shake256.h"

#include "../src/utils/mk_assert.h"
#include "../src/utils/mk_inline.h"

#include <string.h> /* memcmp */


/*

https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values

https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA3-224_1600.pdf
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA3-256_1600.pdf
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA3-384_1600.pdf
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA3-512_1600.pdf
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHAKE128_Msg1600.pdf
https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHAKE256_Msg1600.pdf

*/


static mk_inline void cast_sha3_224_init(void* self){ mk_hash_hash_sha3_224_init((struct mk_hash_hash_sha3_224_s*)self); }
static mk_inline void cast_sha3_256_init(void* self){ mk_hash_hash_sha3_256_init((struct mk_hash_hash_sha3_256_s*)self); }
static mk_inline void cast_sha3_384_init(void* self){ mk_hash_hash_sha3_384_init((struct mk_hash_hash_sha3_384_s*)self); }
static mk_inline void cast_sha3_512_init(void* self){ mk_hash_hash_sha3_512_init((struct mk_hash_hash_sha3_512_s*)self); }
static mk_inline void cast_sha3_shake128_init(void* self){ mk_hash_xof_sha3_shake128_init((struct mk_hash_xof_sha3_shake128_s*)self); }
static mk_inline void cast_sha3_shake256_init(void* self){ mk_hash_xof_sha3_shake256_init((struct mk_hash_xof_sha3_shake256_s*)self); }

static mk_inline void cast_sha3_224_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha3_224_append((struct mk_hash_hash_sha3_224_s*)self, msg, msg_len); }
static mk_inline void cast_sha3_256_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha3_256_append((struct mk_hash_hash_sha3_256_s*)self, msg, msg_len); }
static mk_inline void cast_sha3_384_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha3_384_append((struct mk_hash_hash_sha3_384_s*)self, msg, msg_len); }
static mk_inline void cast_sha3_512_append(void* self, void const* msg, int msg_len){ mk_hash_hash_sha3_512_append((struct mk_hash_hash_sha3_512_s*)self, msg, msg_len); }
static mk_inline void cast_sha3_shake128_append(void* self, void const* msg, int msg_len){ mk_hash_xof_sha3_shake128_append((struct mk_hash_xof_sha3_shake128_s*)self, msg, msg_len); }
static mk_inline void cast_sha3_shake256_append(void* self, void const* msg, int msg_len){ mk_hash_xof_sha3_shake256_append((struct mk_hash_xof_sha3_shake256_s*)self, msg, msg_len); }

static mk_inline void cast_sha3_224_finish(void* self, void* digest){ mk_hash_hash_sha3_224_finish((struct mk_hash_hash_sha3_224_s*)self, digest); }
static mk_inline void cast_sha3_256_finish(void* self, void* digest){ mk_hash_hash_sha3_256_finish((struct mk_hash_hash_sha3_256_s*)self, digest); }
static mk_inline void cast_sha3_384_finish(void* self, void* digest){ mk_hash_hash_sha3_384_finish((struct mk_hash_hash_sha3_384_s*)self, digest); }
static mk_inline void cast_sha3_512_finish(void* self, void* digest){ mk_hash_hash_sha3_512_finish((struct mk_hash_hash_sha3_512_s*)self, digest); }
static mk_inline void cast_sha3_shake128_finish(void* self, void* digest){ mk_hash_xof_sha3_shake128_finish((struct mk_hash_xof_sha3_shake128_s*)self, 4096 / 8, digest); }
static mk_inline void cast_sha3_shake256_finish(void* self, void* digest){ mk_hash_xof_sha3_shake256_finish((struct mk_hash_xof_sha3_shake256_s*)self, 4096 / 8, digest); }


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err_; err_ = (x); if(err_ != 0){ return err; } }while(0)


int mk_sha3_test_examples(void)
{
	static char const s_msg[] = "1100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101";
	static char const s_sha3_224[] = "9376816ABA503F72F96CE7EB65AC095DEEE3BE4BF9BBC2A1CB7E11E0";
	static char const s_sha3_256[] = "79F38ADEC5C20307A98EF76E8324AFBFD46CFD81B22E3973C65FA1BD9DE31787";
	static char const s_sha3_384[] = "1881DE2CA7E41EF95DC4732B8F5F002B189CC1E42B74168ED1732649CE1DBCDD76197A31FD55EE989F2D7050DD473E8F";
	static char const s_sha3_512[] = "E76DFAD22084A8B1467FCF2FFA58361BEC7628EDF5F3FDC0E4805DC48CAEECA81B7C13C30ADF52A3659584739A2DF46BE589C51CA1A4A8416DF6545A1CE8BA00";
	static char const s_sha3_shake128_4096[] = "131AB8D2B594946B9C81333F9BB6E0CE75C3B93104FA3469D3917457385DA037CF232EF7164A6D1EB448C8908186AD852D3F85A5CF28DA1AB6FE3438171978467F1C05D58C7EF38C284C41F6C2221A76F12AB1C04082660250802294FB87180213FDEF5B0ECB7DF50CA1F8555BE14D32E10F6EDCDE892C09424B29F597AFC270C904556BFCB47A7D40778D390923642B3CBD0579E60908D5A000C1D08B98EF933F806445BF87F8B009BA9E94F7266122ED7AC24E5E266C42A82FA1BBEFB7B8DB0066E16A85E0493F07DF4809AEC084A593748AC3DDE5A6D7AAE1E8B6E5352B2D71EFBB47D4CAEED5E6D633805D2D323E6FD81B4684B93A2677D45E7421C2C6AEA259B855A698FD7D13477A1FE53E5A4A6197DBEC5CE95F505B520BCD9570C4A8265A7E01F89C0C002C59BFEC6CD4A5C109258953EE5EE70CD577EE217AF21FA70178F0946C9BF6CA8751793479F6B537737E40B6ED28511D8A2D7E73EB75F8DAAC912FF906E0AB955B083BAC45A8E5E9B744C8506F37E9B4E749A184B30F43EB188D855F1B70D71FF3E50C537AC1B0F8974F0FE1A6AD295BA42F6AEC74D123A7ABEDDE6E2C0711CAB36BE5ACB1A5A11A4B1DB08BA6982EFCCD716929A7741CFC63AA4435E0B69A9063E880795C3DC5EF3272E11C497A91ACF699FEFEE206227A44C9FB359FD56AC0A9A75A743CFF6862F17D7259AB075216C0699511643B6439";
	static char const s_sha3_shake256_4096[] = "CD8A920ED141AA0407A22D59288652E9D9F1A7EE0C1E7C1CA699424DA84A904D2D700CAAE7396ECE96604440577DA4F3AA22AEB8857F961C4CD8E06F0AE6610B1048A7F64E1074CD629E85AD7566048EFC4FB500B486A3309A8F26724C0ED628001A1099422468DE726F1061D99EB9E93604D5AA7467D4B1BD6484582A384317D7F47D750B8F5499512BB85A226C4243556E696F6BD072C5AA2D9B69730244B56853D16970AD817E213E470618178001C9FB56C54FEFA5FEE67D2DA524BB3B0B61EF0E9114A92CDBB6CCCB98615CFE76E3510DD88D1CC28FF99287512F24BFAFA1A76877B6F37198E3A641C68A7C42D45FA7ACC10DAE5F3CEFB7B735F12D4E589F7A456E78C0F5E4C4471FFFA5E4FA0514AE974D8C2648513B5DB494CEA847156D277AD0E141C24C7839064CD08851BC2E7CA109FD4E251C35BB0A04FB05B364FF8C4D8B59BC303E25328C09A882E952518E1A8AE0FF265D61C465896973D7490499DC639FB8502B39456791B1B6EC5BCC5D9AC36A6DF622A070D43FED781F5F149F7B62675E7D1A4D6DEC48C1C7164586EAE06A51208C0B791244D307726505C3AD4B26B6822377257AA152037560A739714A3CA79BD605547C9B78DD1F596F2D4F1791BC689A0E9B799A37339C04275733740143EF5D2B58B96A363D4E08076A1A9D7846436E4DCA5728B6F760EEF0CA92BF0BE5615E96959D767197A0BEEB";

	struct digest_s
	{
		char const* m_digest_str;
		int m_digest_str_len;
	};

	static struct digest_s s_digests[] =
	{
		{s_sha3_224, sizeof(s_sha3_224) - 1},
		{s_sha3_256, sizeof(s_sha3_256) - 1},
		{s_sha3_384, sizeof(s_sha3_384) - 1},
		{s_sha3_512, sizeof(s_sha3_512) - 1},
		{s_sha3_shake128_4096, sizeof(s_sha3_shake128_4096) - 1},
		{s_sha3_shake256_4096, sizeof(s_sha3_shake256_4096) - 1},
	};

	typedef void(*alg_init_t)(void*);
	typedef void(*alg_append_t)(void*, void const*, int);
	typedef void(*alg_finish_t)(void*, void*);

	struct alg_descr_s
	{
		int m_digest_len;
		alg_init_t m_init;
		alg_append_t m_append;
		alg_finish_t m_finish;
	};

	static struct alg_descr_s const s_alg_descrs[] =
	{
		{mk_hash_base_hash_sha3_224_digest_len, &cast_sha3_224_init, &cast_sha3_224_append, &cast_sha3_224_finish},
		{mk_hash_base_hash_sha3_256_digest_len, &cast_sha3_256_init, &cast_sha3_256_append, &cast_sha3_256_finish},
		{mk_hash_base_hash_sha3_384_digest_len, &cast_sha3_384_init, &cast_sha3_384_append, &cast_sha3_384_finish},
		{mk_hash_base_hash_sha3_512_digest_len, &cast_sha3_512_init, &cast_sha3_512_append, &cast_sha3_512_finish},
		{512, &cast_sha3_shake128_init, &cast_sha3_shake128_append, &cast_sha3_shake128_finish},
		{512, &cast_sha3_shake256_init, &cast_sha3_shake256_append, &cast_sha3_shake256_finish},
	};

	union alg_states_u
	{
		struct mk_hash_hash_sha3_224_s m_224;
		struct mk_hash_hash_sha3_256_s m_256;
		struct mk_hash_hash_sha3_384_s m_384;
		struct mk_hash_hash_sha3_512_s m_512;
		struct mk_hash_xof_sha3_shake128_s m_shake128;
		struct mk_hash_xof_sha3_shake256_s m_shake256;
	};

	unsigned char msg_bytes[200];
	int algs;
	int i;
	unsigned char digest_baseline[512];
	union alg_states_u alg_state;
	unsigned char digest_computed[512];
	int compared;

	mk_string_bin_to_bytes(s_msg, sizeof(s_msg) - 1, &msg_bytes, sizeof(msg_bytes));
	algs = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
	for(i = 0; i != algs; ++i)
	{
		mk_string_hex_to_bytes(s_digests[i].m_digest_str, s_digests[i].m_digest_str_len, &digest_baseline, sizeof(digest_baseline));
		s_alg_descrs[i].m_init(&alg_state);
		s_alg_descrs[i].m_append(&alg_state, &msg_bytes, (sizeof(s_msg) - 1) / 8);
		s_alg_descrs[i].m_finish(&alg_state, &digest_computed);
		compared = memcmp(&digest_computed, &digest_baseline, s_alg_descrs[i].m_digest_len);
		mk_check(compared == 0);
	}
	return 0;
}


#undef mk_check
#undef mk_try
