#include "mk_sha2_detail_256.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include "../../mk_int/src/exact/mk_uint_32.h"
#include "../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memcpy */


static struct mk_uint32_s const mk_sha2_detail_256_table[64] =
{
	mk_uint32_c(0x428a2f98), mk_uint32_c(0x71374491), mk_uint32_c(0xb5c0fbcf), mk_uint32_c(0xe9b5dba5),
	mk_uint32_c(0x3956c25b), mk_uint32_c(0x59f111f1), mk_uint32_c(0x923f82a4), mk_uint32_c(0xab1c5ed5),
	mk_uint32_c(0xd807aa98), mk_uint32_c(0x12835b01), mk_uint32_c(0x243185be), mk_uint32_c(0x550c7dc3),
	mk_uint32_c(0x72be5d74), mk_uint32_c(0x80deb1fe), mk_uint32_c(0x9bdc06a7), mk_uint32_c(0xc19bf174),
	mk_uint32_c(0xe49b69c1), mk_uint32_c(0xefbe4786), mk_uint32_c(0x0fc19dc6), mk_uint32_c(0x240ca1cc),
	mk_uint32_c(0x2de92c6f), mk_uint32_c(0x4a7484aa), mk_uint32_c(0x5cb0a9dc), mk_uint32_c(0x76f988da),
	mk_uint32_c(0x983e5152), mk_uint32_c(0xa831c66d), mk_uint32_c(0xb00327c8), mk_uint32_c(0xbf597fc7),
	mk_uint32_c(0xc6e00bf3), mk_uint32_c(0xd5a79147), mk_uint32_c(0x06ca6351), mk_uint32_c(0x14292967),
	mk_uint32_c(0x27b70a85), mk_uint32_c(0x2e1b2138), mk_uint32_c(0x4d2c6dfc), mk_uint32_c(0x53380d13),
	mk_uint32_c(0x650a7354), mk_uint32_c(0x766a0abb), mk_uint32_c(0x81c2c92e), mk_uint32_c(0x92722c85),
	mk_uint32_c(0xa2bfe8a1), mk_uint32_c(0xa81a664b), mk_uint32_c(0xc24b8b70), mk_uint32_c(0xc76c51a3),
	mk_uint32_c(0xd192e819), mk_uint32_c(0xd6990624), mk_uint32_c(0xf40e3585), mk_uint32_c(0x106aa070),
	mk_uint32_c(0x19a4c116), mk_uint32_c(0x1e376c08), mk_uint32_c(0x2748774c), mk_uint32_c(0x34b0bcb5),
	mk_uint32_c(0x391c0cb3), mk_uint32_c(0x4ed8aa4a), mk_uint32_c(0x5b9cca4f), mk_uint32_c(0x682e6ff3),
	mk_uint32_c(0x748f82ee), mk_uint32_c(0x78a5636f), mk_uint32_c(0x84c87814), mk_uint32_c(0x8cc70208),
	mk_uint32_c(0x90befffa), mk_uint32_c(0xa4506ceb), mk_uint32_c(0xbef9a3f7), mk_uint32_c(0xc67178f2),
};


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:5045) /* warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified */
#endif


static mk_inline void mk_sha2_detail_256_ch(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ ((~x) & z); */
	
	mk_uint32_and(&tmp1, x, y);
	mk_uint32_cmplmnt(&tmp2, x);
	mk_uint32_and(&tmp2, &tmp2, z);
	mk_uint32_xor(out, &tmp1, &tmp2);
}

static mk_inline void mk_sha2_detail_256_maj(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ (x & z) ^ (y & z); */

	mk_uint32_and(&tmp1, x, y);
	mk_uint32_and(&tmp2, x, z);
	mk_uint32_and(&tmp3, y, z);
	mk_uint32_xor(&tmp1, &tmp1, &tmp2);
	mk_uint32_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_sha2_detail_256_sum0(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); */

	mk_uint32_rotr(&tmp1, x, 2);
	mk_uint32_rotr(&tmp2, x, 13);
	mk_uint32_rotr(&tmp3, x, 22);
	mk_uint32_xor(&tmp1, &tmp1, &tmp2);
	mk_uint32_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_sha2_detail_256_sum1(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); */

	mk_uint32_rotr(&tmp1, x, 6);
	mk_uint32_rotr(&tmp2, x, 11);
	mk_uint32_rotr(&tmp3, x, 25);
	mk_uint32_xor(&tmp1, &tmp1, &tmp2);
	mk_uint32_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_sha2_detail_256_sig0(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3); */

	mk_uint32_rotr(&tmp1, x, 7);
	mk_uint32_rotr(&tmp2, x, 18);
	mk_uint32_shr(&tmp3, x, 3);
	mk_uint32_xor(&tmp1, &tmp1, &tmp2);
	mk_uint32_xor(out, &tmp1, &tmp3);
}

static mk_inline void mk_sha2_detail_256_sig1(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s tmp3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10); */

	mk_uint32_rotr(&tmp1, x, 17);
	mk_uint32_rotr(&tmp2, x, 19);
	mk_uint32_shr(&tmp3, x, 10);
	mk_uint32_xor(&tmp1, &tmp1, &tmp2);
	mk_uint32_xor(out, &tmp1, &tmp3);
}


void mk_sha2_detail_256_process_block(struct mk_uint32_s state[8], unsigned char const msg[64])
{
	struct mk_uint32_s hh[8];
	struct mk_uint32_s w[64];
	struct mk_uint32_s t1;
	struct mk_uint32_s t2;
	struct mk_uint32_s tmp1;
	struct mk_uint32_s tmp2;
	struct mk_uint32_s* a;
	struct mk_uint32_s* b;
	struct mk_uint32_s* c;
	struct mk_uint32_s* d;
	struct mk_uint32_s* e;
	struct mk_uint32_s* f;
	struct mk_uint32_s* g;
	struct mk_uint32_s* h;
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
		mk_uint32_from_buff_be(&w[i], msg + i * 4);
	}
	for(i = 16; i != 64; ++i)
	{
		/* w[i] = sig1(w[i - 2]) + w[i - 7] + sig0(w[i - 15]) + w[i - 16]; */
		mk_sha2_detail_256_sig1(&tmp1, &w[i - 2]);
		mk_uint32_add(&tmp1, &tmp1, &w[i - 7]);
		mk_sha2_detail_256_sig0(&tmp2, &w[i - 15]);
		mk_uint32_add(&tmp2, &tmp2, &w[i - 16]);
		mk_uint32_add(&w[i], &tmp1, &tmp2);
	}
	
	for(i = 0; i != 64; ++i)
	{
		/* t1 = h + sum1(e) + ch(e, f, g) + table[i] + w[i]; */
		mk_sha2_detail_256_sum1(&tmp1, e);
		mk_sha2_detail_256_ch(&tmp2, e, f, g);
		mk_uint32_add(&tmp1, &tmp1, h);
		mk_uint32_add(&tmp2, &tmp2, &mk_sha2_detail_256_table[i]);
		mk_uint32_add(&tmp1, &tmp1, &tmp2);
		mk_uint32_add(&t1, &tmp1, &w[i]);
		
		/* t2 = sum0(a) + maj(a, b, c); */
		mk_sha2_detail_256_sum0(&tmp1, a);
		mk_sha2_detail_256_maj(&tmp2, a, b, c);
		mk_uint32_add(&t2, &tmp1, &tmp2);

		*h = *g;
		*g = *f;
		*f = *e;
		mk_uint32_add(e, d, &t1);
		*d = *c;
		*c = *b;
		*b = *a;
		mk_uint32_add(a, &t1, &t2);
	}

	mk_uint32_add(&state[0], &state[0], &hh[0]);
	mk_uint32_add(&state[1], &state[1], &hh[1]);
	mk_uint32_add(&state[2], &state[2], &hh[2]);
	mk_uint32_add(&state[3], &state[3], &hh[3]);
	mk_uint32_add(&state[4], &state[4], &hh[4]);
	mk_uint32_add(&state[5], &state[5], &hh[5]);
	mk_uint32_add(&state[6], &state[6], &hh[6]);
	mk_uint32_add(&state[7], &state[7], &hh[7]);
}

void mk_sha2_detail_256_append(struct mk_uint32_s state[8], struct mk_uint64_s* len, unsigned char block[64], void const* msg, size_t msg_len_bytes)
{
	unsigned char const* input;
	size_t remaining;
	int idx;
	int capacity;
	struct mk_uint64_s tmp;
	size_t blocks;
	size_t i;

	mk_assert(state);
	mk_assert(len);
	mk_assert(block);

	input = (unsigned char const*)msg;
	remaining = msg_len_bytes;

	idx = mk_uint64_to_int(len) % 64;
	capacity = 64 - idx;
	mk_uint64_from_sizet(&tmp, msg_len_bytes);
	mk_uint64_add(len, len, &tmp);

	if(remaining >= (size_t)capacity)
	{
		if(idx != 0)
		{
			memcpy(block + idx, input, capacity);
			mk_sha2_detail_256_process_block(state, block);
			input += capacity;
			remaining -= capacity;
		}
		blocks = remaining / 64;
		for(i = 0; i != blocks; ++i)
		{
			mk_sha2_detail_256_process_block(state, input);
			input += 64;
		}
		remaining -= blocks * 64;
		idx = 0;
	}
	memcpy(block + idx, input, remaining);
}

void mk_sha2_detail_256_finish(struct mk_uint32_s state[8], struct mk_uint64_s* len, unsigned char block[64], void* digest)
{
	#define s_mandatory_padding_len ((int)(1 + 8))

	static unsigned char const mk_sha2_detail_256_padding[64] =
	{
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	unsigned char* output;
	int idx;
	int capacity;
	int zero_cnt;
	struct mk_uint64_s tmp;
	unsigned char buff[8];

	mk_assert(state);
	mk_assert(len);
	mk_assert(digest);

	output = (unsigned char*)digest;
	idx = mk_uint64_to_int(len) % 64;
	capacity = 64 - idx;
	zero_cnt =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity - s_mandatory_padding_len + 64);

	mk_uint64_shl(&tmp, len, 3);
	mk_uint64_to_buff_be(&tmp, &buff);

	mk_sha2_detail_256_append(state, len, block, mk_sha2_detail_256_padding, 1 + zero_cnt);
	mk_sha2_detail_256_append(state, len, block, buff, 8);

	mk_uint32_to_buff_be(&state[0], output + 0 * 4);
	mk_uint32_to_buff_be(&state[1], output + 1 * 4);
	mk_uint32_to_buff_be(&state[2], output + 2 * 4);
	mk_uint32_to_buff_be(&state[3], output + 3 * 4);
	mk_uint32_to_buff_be(&state[4], output + 4 * 4);
	mk_uint32_to_buff_be(&state[5], output + 5 * 4);
	mk_uint32_to_buff_be(&state[6], output + 6 * 4);
	mk_uint32_to_buff_be(&state[7], output + 7 * 4);

	#undef s_mandatory_padding_len
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
