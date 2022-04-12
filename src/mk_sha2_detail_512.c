#include "mk_sha2_detail_256.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include "../../mk_int/src/exact/mk_uint_64.h"
#include "../../mk_int/src/exact/mk_uint_128.h"

#include <string.h> /* memcpy */


static struct mk_uint64_s const mk_sha2_detail_512_table[80] =
{
	mk_uint64_c(0x428a2f98, 0xd728ae22), mk_uint64_c(0x71374491, 0x23ef65cd), mk_uint64_c(0xb5c0fbcf, 0xec4d3b2f), mk_uint64_c(0xe9b5dba5, 0x8189dbbc),
	mk_uint64_c(0x3956c25b, 0xf348b538), mk_uint64_c(0x59f111f1, 0xb605d019), mk_uint64_c(0x923f82a4, 0xaf194f9b), mk_uint64_c(0xab1c5ed5, 0xda6d8118),
	mk_uint64_c(0xd807aa98, 0xa3030242), mk_uint64_c(0x12835b01, 0x45706fbe), mk_uint64_c(0x243185be, 0x4ee4b28c), mk_uint64_c(0x550c7dc3, 0xd5ffb4e2),
	mk_uint64_c(0x72be5d74, 0xf27b896f), mk_uint64_c(0x80deb1fe, 0x3b1696b1), mk_uint64_c(0x9bdc06a7, 0x25c71235), mk_uint64_c(0xc19bf174, 0xcf692694),
	mk_uint64_c(0xe49b69c1, 0x9ef14ad2), mk_uint64_c(0xefbe4786, 0x384f25e3), mk_uint64_c(0x0fc19dc6, 0x8b8cd5b5), mk_uint64_c(0x240ca1cc, 0x77ac9c65),
	mk_uint64_c(0x2de92c6f, 0x592b0275), mk_uint64_c(0x4a7484aa, 0x6ea6e483), mk_uint64_c(0x5cb0a9dc, 0xbd41fbd4), mk_uint64_c(0x76f988da, 0x831153b5),
	mk_uint64_c(0x983e5152, 0xee66dfab), mk_uint64_c(0xa831c66d, 0x2db43210), mk_uint64_c(0xb00327c8, 0x98fb213f), mk_uint64_c(0xbf597fc7, 0xbeef0ee4),
	mk_uint64_c(0xc6e00bf3, 0x3da88fc2), mk_uint64_c(0xd5a79147, 0x930aa725), mk_uint64_c(0x06ca6351, 0xe003826f), mk_uint64_c(0x14292967, 0x0a0e6e70),
	mk_uint64_c(0x27b70a85, 0x46d22ffc), mk_uint64_c(0x2e1b2138, 0x5c26c926), mk_uint64_c(0x4d2c6dfc, 0x5ac42aed), mk_uint64_c(0x53380d13, 0x9d95b3df),
	mk_uint64_c(0x650a7354, 0x8baf63de), mk_uint64_c(0x766a0abb, 0x3c77b2a8), mk_uint64_c(0x81c2c92e, 0x47edaee6), mk_uint64_c(0x92722c85, 0x1482353b),
	mk_uint64_c(0xa2bfe8a1, 0x4cf10364), mk_uint64_c(0xa81a664b, 0xbc423001), mk_uint64_c(0xc24b8b70, 0xd0f89791), mk_uint64_c(0xc76c51a3, 0x0654be30),
	mk_uint64_c(0xd192e819, 0xd6ef5218), mk_uint64_c(0xd6990624, 0x5565a910), mk_uint64_c(0xf40e3585, 0x5771202a), mk_uint64_c(0x106aa070, 0x32bbd1b8),
	mk_uint64_c(0x19a4c116, 0xb8d2d0c8), mk_uint64_c(0x1e376c08, 0x5141ab53), mk_uint64_c(0x2748774c, 0xdf8eeb99), mk_uint64_c(0x34b0bcb5, 0xe19b48a8),
	mk_uint64_c(0x391c0cb3, 0xc5c95a63), mk_uint64_c(0x4ed8aa4a, 0xe3418acb), mk_uint64_c(0x5b9cca4f, 0x7763e373), mk_uint64_c(0x682e6ff3, 0xd6b2b8a3),
	mk_uint64_c(0x748f82ee, 0x5defb2fc), mk_uint64_c(0x78a5636f, 0x43172f60), mk_uint64_c(0x84c87814, 0xa1f0ab72), mk_uint64_c(0x8cc70208, 0x1a6439ec),
	mk_uint64_c(0x90befffa, 0x23631e28), mk_uint64_c(0xa4506ceb, 0xde82bde9), mk_uint64_c(0xbef9a3f7, 0xb2c67915), mk_uint64_c(0xc67178f2, 0xe372532b),
	mk_uint64_c(0xca273ece, 0xea26619c), mk_uint64_c(0xd186b8c7, 0x21c0c207), mk_uint64_c(0xeada7dd6, 0xcde0eb1e), mk_uint64_c(0xf57d4f7f, 0xee6ed178),
	mk_uint64_c(0x06f067aa, 0x72176fba), mk_uint64_c(0x0a637dc5, 0xa2c898a6), mk_uint64_c(0x113f9804, 0xbef90dae), mk_uint64_c(0x1b710b35, 0x131c471b),
	mk_uint64_c(0x28db77f5, 0x23047d84), mk_uint64_c(0x32caab7b, 0x40c72493), mk_uint64_c(0x3c9ebe0a, 0x15c9bebc), mk_uint64_c(0x431d67c4, 0x9c100d4c),
	mk_uint64_c(0x4cc5d4be, 0xcb3e42b6), mk_uint64_c(0x597f299c, 0xfc657e2a), mk_uint64_c(0x5fcb6fab, 0x3ad6faec), mk_uint64_c(0x6c44198c, 0x4a475817),
};


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:5045) /* warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified */
#endif


static mk_inline void mk_sha2_detail_512_ch(struct mk_uint64_s* out, struct mk_uint64_s const* x, struct mk_uint64_s const* y, struct mk_uint64_s const* z)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ ((~x) & z); */
	
	mk_uint64_and(&tmp1, x, y);
	mk_uint64_cmplmnt(&tmp2, x);
	mk_uint64_and(&tmp2, &tmp2, z);
	mk_uint64_xor(out, &tmp1, &tmp2);
}

static mk_inline void mk_sha2_detail_512_maj(struct mk_uint64_s* out, struct mk_uint64_s const* x, struct mk_uint64_s const* y, struct mk_uint64_s const* z)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s tmp3;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ (x & z) ^ (y & z); */

	mk_uint64_and(&tmp1, x, y);
	mk_uint64_and(&tmp2, x, z);
	mk_uint64_and(&tmp3, y, z);
	mk_uint64_xor(&tmp1, &tmp1, &tmp2);
	mk_uint64_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_sha2_detail_512_sum0(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 28) ^ rotr(x, 34) ^ rotr(x, 39); */

	mk_uint64_rotr(&tmp1, x, 28);
	mk_uint64_rotr(&tmp2, x, 34);
	mk_uint64_rotr(&tmp3, x, 39);
	mk_uint64_xor(&tmp1, &tmp1, &tmp2);
	mk_uint64_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_sha2_detail_512_sum1(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 14) ^ rotr(x, 18) ^ rotr(x, 41); */

	mk_uint64_rotr(&tmp1, x, 14);
	mk_uint64_rotr(&tmp2, x, 18);
	mk_uint64_rotr(&tmp3, x, 41);
	mk_uint64_xor(&tmp1, &tmp1, &tmp2);
	mk_uint64_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_sha2_detail_512_sig0(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 1) ^ rotr(x, 8) ^ shr(x, 7); */

	mk_uint64_rotr(&tmp1, x, 1);
	mk_uint64_rotr(&tmp2, x, 8);
	mk_uint64_shr(&tmp3, x, 7);
	mk_uint64_xor(&tmp1, &tmp1, &tmp2);
	mk_uint64_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_sha2_detail_512_sig1(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 19) ^ rotr(x, 61) ^ shr(x, 6); */

	mk_uint64_rotr(&tmp1, x, 19);
	mk_uint64_rotr(&tmp2, x, 61);
	mk_uint64_shr(&tmp3, x, 6);
	mk_uint64_xor(&tmp1, &tmp1, &tmp2);
	mk_uint64_xor(out, &tmp1, &tmp3);
}


void mk_sha2_detail_512_process_block(struct mk_uint64_s state[8], unsigned char const msg[128])
{
	struct mk_uint64_s hh[8];
	struct mk_uint64_s w[80];
	struct mk_uint64_s t1;
	struct mk_uint64_s t2;
	struct mk_uint64_s tmp1;
	struct mk_uint64_s tmp2;
	struct mk_uint64_s* a;
	struct mk_uint64_s* b;
	struct mk_uint64_s* c;
	struct mk_uint64_s* d;
	struct mk_uint64_s* e;
	struct mk_uint64_s* f;
	struct mk_uint64_s* g;
	struct mk_uint64_s* h;
	int i;

	mk_assert(state);
	mk_assert(msg);

	hh[0] = state[0];
	hh[1] = state[1];
	hh[2] = state[2];
	hh[3] = state[3];
	hh[4] = state[4];
	hh[5] = state[5];
	hh[6] = state[6];
	hh[7] = state[7];

	a = &hh[0];
	b = &hh[1];
	c = &hh[2];
	d = &hh[3];
	e = &hh[4];
	f = &hh[5];
	g = &hh[6];
	h = &hh[7];

	for(i = 0; i != 16; ++i)
	{
		mk_uint64_from_buff_be(&w[i], msg + i * 8);
	}
	for(i = 16; i != 80; ++i)
	{
		/* w[i] = sig1(w[i - 2]) + w[i - 7] + sig0(w[i - 15]) + w[i - 16]; */
		mk_sha2_detail_512_sig1(&tmp1, &w[i - 2]);
		mk_uint64_add(&tmp1, &tmp1, &w[i - 7]);
		mk_sha2_detail_512_sig0(&tmp2, &w[i - 15]);
		mk_uint64_add(&tmp2, &tmp2, &w[i - 16]);
		mk_uint64_add(&w[i], &tmp1, &tmp2);
	}

	for(i = 0; i != 80; ++i)
	{
		/* t1 = h + sum1(e) + ch(e, f, g) + table[i] + w[i]; */
		mk_sha2_detail_512_sum1(&tmp1, e);
		mk_sha2_detail_512_ch(&tmp2, e, f, g);
		mk_uint64_add(&tmp1, &tmp1, h);
		mk_uint64_add(&tmp2, &tmp2, &mk_sha2_detail_512_table[i]);
		mk_uint64_add(&tmp1, &tmp1, &tmp2);
		mk_uint64_add(&t1, &tmp1, &w[i]);

		/* t2 = sum0(a) + maj(a, b, c); */
		mk_sha2_detail_512_sum0(&tmp1, a);
		mk_sha2_detail_512_maj(&tmp2, a, b, c);
		mk_uint64_add(&t2, &tmp1, &tmp2);

		*h = *g;
		*g = *f;
		*f = *e;
		mk_uint64_add(e, d, &t1);
		*d = *c;
		*c = *b;
		*b = *a;
		mk_uint64_add(a, &t1, &t2);
	}

	mk_uint64_add(&state[0], &state[0], &hh[0]);
	mk_uint64_add(&state[1], &state[1], &hh[1]);
	mk_uint64_add(&state[2], &state[2], &hh[2]);
	mk_uint64_add(&state[3], &state[3], &hh[3]);
	mk_uint64_add(&state[4], &state[4], &hh[4]);
	mk_uint64_add(&state[5], &state[5], &hh[5]);
	mk_uint64_add(&state[6], &state[6], &hh[6]);
	mk_uint64_add(&state[7], &state[7], &hh[7]);
}

void mk_sha2_detail_512_append(struct mk_uint64_s state[8], struct mk_uint128_s* len, unsigned char block[128], void const* msg, size_t msg_len_bytes)
{
	unsigned char const* input;
	size_t remaining;
	int idx;
	int capacity;
	struct mk_uint128_s tmp;
	size_t blocks;
	size_t i;

	mk_assert(state);
	mk_assert(len);
	mk_assert(block);

	input = (unsigned char const*)msg;
	remaining = msg_len_bytes;

	idx = mk_uint128_to_int(len) % 128;
	capacity = 128 - idx;
	mk_uint128_from_sizet(&tmp, msg_len_bytes);
	mk_uint128_add(len, len, &tmp);

	if(remaining >= (size_t)capacity)
	{
		if(idx != 0)
		{
			memcpy(block + idx, input, capacity);
			mk_sha2_detail_512_process_block(state, block);
			input += capacity;
			remaining -= capacity;
		}
		blocks = remaining / 128;
		for(i = 0; i != blocks; ++i)
		{
			mk_sha2_detail_512_process_block(state, input);
			input += 128;
		}
		remaining -= blocks * 128;
		idx = 0;
	}
	memcpy(block + idx, input, remaining);
}

void mk_sha2_detail_512_finish(struct mk_uint64_s state[8], struct mk_uint128_s* len, unsigned char block[128], void* digest)
{
	#define s_mandatory_padding_len ((int)(1 + 16))

	static unsigned char const mk_sha2_detail_512_padding[128] =
	{
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	unsigned char* output;
	int idx;
	int capacity;
	int zero_cnt;
	struct mk_uint128_s tmp;
	unsigned char buff[16];

	mk_assert(state);
	mk_assert(len);
	mk_assert(digest);

	output = (unsigned char*)digest;
	idx = mk_uint128_to_int(len) % 128;
	capacity = 128 - idx;
	zero_cnt =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity - s_mandatory_padding_len + 128);

	mk_uint128_shl(&tmp, len, 3);
	mk_uint128_to_buff_be(&tmp, &buff);

	mk_sha2_detail_512_append(state, len, block, mk_sha2_detail_512_padding, 1 + zero_cnt);
	mk_sha2_detail_512_append(state, len, block, buff, 16);

	mk_uint64_to_buff_be(&state[0], output + 0 * 8);
	mk_uint64_to_buff_be(&state[1], output + 1 * 8);
	mk_uint64_to_buff_be(&state[2], output + 2 * 8);
	mk_uint64_to_buff_be(&state[3], output + 3 * 8);
	mk_uint64_to_buff_be(&state[4], output + 4 * 8);
	mk_uint64_to_buff_be(&state[5], output + 5 * 8);
	mk_uint64_to_buff_be(&state[6], output + 6 * 8);
	mk_uint64_to_buff_be(&state[7], output + 7 * 8);

	#undef s_mandatory_padding_len
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
