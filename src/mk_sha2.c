#include "mk_sha2.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include "../../mk_int/src/exact/mk_uint_32.h"
#include "../../mk_int/src/exact/mk_uint_64.h"
#include "../../mk_int/src/exact/mk_uint_128.h"

#include <stddef.h> /* size_t */
#include <string.h> /* memcpy memset */


static struct mk_uint32_s const mk_sha2_256_detail_table[64] =
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

static struct mk_uint64_s const mk_sha2_512_detail_table[80] =
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


static mk_inline void mk_sha2_detail_ints2be32(struct mk_uint32_s const* input, int n, void* buff)
{
	unsigned char* output;
	int i;

	mk_assert(input);
	mk_assert(n >= 1);
	mk_assert(buff);

	output = (unsigned char*)buff;
	for(i = 0; i != n; ++i)
	{
		mk_uint32_to_buff_be(&input[i], output + i * sizeof(struct mk_uint32_s));
	}
}

static mk_inline void mk_sha2_detail_be2ints32(void const* buff, struct mk_uint32_s* output, int n)
{
	unsigned char const* input;
	int i;

	mk_assert(buff);
	mk_assert(output);
	mk_assert(n >= 1);

	input = (unsigned char const*)buff;
	for(i = 0; i != n; ++i)
	{
		mk_uint32_from_buff_be(&output[i], input + i * sizeof(struct mk_uint32_s));
	}
}

static mk_inline void mk_sha2_detail_ints2be64(struct mk_uint64_s const* input, int n, void* buff)
{
	unsigned char* output;
	int i;

	mk_assert(input);
	mk_assert(n >= 1);
	mk_assert(buff);

	output = (unsigned char*)buff;
	for(i = 0; i != n; ++i)
	{
		mk_uint64_to_buff_be(&input[i], output + i * sizeof(struct mk_uint64_s));
	}
}

static mk_inline void mk_sha2_detail_be2ints64(void const* buff, struct mk_uint64_s* output, int n)
{
	unsigned char const* input;
	int i;

	mk_assert(buff);
	mk_assert(output);
	mk_assert(n >= 1);

	input = (unsigned char const*)buff;
	for(i = 0; i != n; ++i)
	{
		mk_uint64_from_buff_be(&output[i], input + i * sizeof(struct mk_uint64_s));
	}
}

static mk_inline void mk_sha2_256_detail_ch(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s t1;
	struct mk_uint32_s t2;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ ((~x) & z); */
	
	mk_uint32_and(&t1, x, y);
	mk_uint32_cmplmnt(&t2, x);
	mk_uint32_and(&t2, &t2, z);
	mk_uint32_xor(out, &t1, &t2);
}

static mk_inline void mk_sha2_256_detail_maj(struct mk_uint32_s* out, struct mk_uint32_s const* x, struct mk_uint32_s const* y, struct mk_uint32_s const* z)
{
	struct mk_uint32_s t1;
	struct mk_uint32_s t2;
	struct mk_uint32_s t3;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ (x & z) ^ (y & z); */

	mk_uint32_and(&t1, x, y);
	mk_uint32_and(&t2, x, z);
	mk_uint32_and(&t3, y, z);
	mk_uint32_xor(&t1, &t1, &t2);
	mk_uint32_xor(out, &t1, &t3);
}

static mk_inline void mk_sha2_256_detail_sum0(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s t1;
	struct mk_uint32_s t2;
	struct mk_uint32_s t3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); */

	mk_uint32_rotr(&t1, x, 2);
	mk_uint32_rotr(&t2, x, 13);
	mk_uint32_rotr(&t3, x, 22);
	mk_uint32_xor(&t1, &t1, &t2);
	mk_uint32_xor(out, &t1, &t3);
}

static mk_inline void mk_sha2_256_detail_sum1(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s t1;
	struct mk_uint32_s t2;
	struct mk_uint32_s t3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); */

	mk_uint32_rotr(&t1, x, 6);
	mk_uint32_rotr(&t2, x, 11);
	mk_uint32_rotr(&t3, x, 25);
	mk_uint32_xor(&t1, &t1, &t2);
	mk_uint32_xor(out, &t1, &t3);
}

static mk_inline void mk_sha2_256_detail_sig0(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s t1;
	struct mk_uint32_s t2;
	struct mk_uint32_s t3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3); */

	mk_uint32_rotr(&t1, x, 7);
	mk_uint32_rotr(&t2, x, 18);
	mk_uint32_shr(&t3, x, 3);
	mk_uint32_xor(&t1, &t1, &t2);
	mk_uint32_xor(out, &t1, &t3);
}

static mk_inline void mk_sha2_256_detail_sig1(struct mk_uint32_s* out, struct mk_uint32_s const* x)
{
	struct mk_uint32_s t1;
	struct mk_uint32_s t2;
	struct mk_uint32_s t3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10); */

	mk_uint32_rotr(&t1, x, 17);
	mk_uint32_rotr(&t2, x, 19);
	mk_uint32_shr(&t3, x, 10);
	mk_uint32_xor(&t1, &t1, &t2);
	mk_uint32_xor(out, &t1, &t3);
}

static mk_inline void mk_sha2_512_detail_ch(struct mk_uint64_s* out, struct mk_uint64_s const* x, struct mk_uint64_s const* y, struct mk_uint64_s const* z)
{
	struct mk_uint64_s t1;
	struct mk_uint64_s t2;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ ((~x) & z); */
	
	mk_uint64_and(&t1, x, y);
	mk_uint64_cmplmnt(&t2, x);
	mk_uint64_and(&t2, &t2, z);
	mk_uint64_xor(out, &t1, &t2);
}

static mk_inline void mk_sha2_512_detail_maj(struct mk_uint64_s* out, struct mk_uint64_s const* x, struct mk_uint64_s const* y, struct mk_uint64_s const* z)
{
	struct mk_uint64_s t1;
	struct mk_uint64_s t2;
	struct mk_uint64_s t3;

	mk_assert(out);
	mk_assert(x);
	mk_assert(y);
	mk_assert(z);

	/* return (x & y) ^ (x & z) ^ (y & z); */

	mk_uint64_and(&t1, x, y);
	mk_uint64_and(&t2, x, z);
	mk_uint64_and(&t3, y, z);
	mk_uint64_xor(&t1, &t1, &t2);
	mk_uint64_xor(out, &t1, &t3);
}

static mk_inline void mk_sha2_512_detail_sum0(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s t1;
	struct mk_uint64_s t2;
	struct mk_uint64_s t3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 28) ^ rotr(x, 34) ^ rotr(x, 39); */

	mk_uint64_rotr(&t1, x, 28);
	mk_uint64_rotr(&t2, x, 34);
	mk_uint64_rotr(&t3, x, 39);
	mk_uint64_xor(&t1, &t1, &t2);
	mk_uint64_xor(out, &t1, &t3);
}

static mk_inline void mk_sha2_512_detail_sum1(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s t1;
	struct mk_uint64_s t2;
	struct mk_uint64_s t3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 14) ^ rotr(x, 18) ^ rotr(x, 41); */

	mk_uint64_rotr(&t1, x, 14);
	mk_uint64_rotr(&t2, x, 18);
	mk_uint64_rotr(&t3, x, 41);
	mk_uint64_xor(&t1, &t1, &t2);
	mk_uint64_xor(out, &t1, &t3);
}

static mk_inline void mk_sha2_512_detail_sig0(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s t1;
	struct mk_uint64_s t2;
	struct mk_uint64_s t3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 1) ^ rotr(x, 8) ^ shr(x, 7); */

	mk_uint64_rotr(&t1, x, 1);
	mk_uint64_rotr(&t2, x, 8);
	mk_uint64_shr(&t3, x, 7);
	mk_uint64_xor(&t1, &t1, &t2);
	mk_uint64_xor(out, &t1, &t3);
}

static mk_inline void mk_sha2_512_detail_sig1(struct mk_uint64_s* out, struct mk_uint64_s const* x)
{
	struct mk_uint64_s t1;
	struct mk_uint64_s t2;
	struct mk_uint64_s t3;

	mk_assert(out);
	mk_assert(x);

	/* return rotr(x, 19) ^ rotr(x, 61) ^ shr(x, 6); */

	mk_uint64_rotr(&t1, x, 19);
	mk_uint64_rotr(&t2, x, 61);
	mk_uint64_shr(&t3, x, 6);
	mk_uint64_xor(&t1, &t1, &t2);
	mk_uint64_xor(out, &t1, &t3);
}

static mk_inline void mk_sha2_256_detail_process_block(struct mk_sha2_256_state_s* self, void const* data)
{
	unsigned char const* input;
	struct mk_uint32_s w[64];
	struct mk_uint32_s hh[8];
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

	mk_assert(self);
	mk_assert(data);

	input = (unsigned char const*)data;
	a = hh + 0;
	b = hh + 1;
	c = hh + 2;
	d = hh + 3;
	e = hh + 4;
	f = hh + 5;
	g = hh + 6;
	h = hh + 7;
	
	mk_sha2_detail_be2ints32(input, w, 16);
	for(i = 16; i != 64; ++i)
	{
		/* w[i] = sig1(w[i - 2]) + w[i - 7] + sig0(w[i - 15]) + w[i - 16]; */
		mk_sha2_256_detail_sig1(&tmp1, &w[i - 2]);
		mk_uint32_add(&tmp1, &tmp1, &w[i - 7]);
		mk_sha2_256_detail_sig0(&tmp2, &w[i - 15]);
		mk_uint32_add(&tmp2, &tmp2, &w[i - 16]);
		mk_uint32_add(&w[i], &tmp1, &tmp2);
	}

	*a = self->m_hash[0];
	*b = self->m_hash[1];
	*c = self->m_hash[2];
	*d = self->m_hash[3];
	*e = self->m_hash[4];
	*f = self->m_hash[5];
	*g = self->m_hash[6];
	*h = self->m_hash[7];

	for(i = 0; i != 64; ++i)
	{
		/* t1 = *h + sum1(*e) + ch(*e, *f, *g) + table[i] + w[i]; */
		mk_sha2_256_detail_sum1(&tmp1, e);
		mk_sha2_256_detail_ch(&tmp2, e, f, g);
		mk_uint32_add(&tmp1, &tmp1, h);
		mk_uint32_add(&tmp2, &tmp2, &mk_sha2_256_detail_table[i]);
		mk_uint32_add(&tmp1, &tmp1, &tmp2);
		mk_uint32_add(&t1, &tmp1, &w[i]);
		
		/* t2 = sum0(*a) + maj(*a, *b, *c); */
		mk_sha2_256_detail_sum0(&tmp1, a);
		mk_sha2_256_detail_maj(&tmp2, a, b, c);
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

	mk_uint32_add(&self->m_hash[0], &self->m_hash[0], a);
	mk_uint32_add(&self->m_hash[1], &self->m_hash[1], b);
	mk_uint32_add(&self->m_hash[2], &self->m_hash[2], c);
	mk_uint32_add(&self->m_hash[3], &self->m_hash[3], d);
	mk_uint32_add(&self->m_hash[4], &self->m_hash[4], e);
	mk_uint32_add(&self->m_hash[5], &self->m_hash[5], f);
	mk_uint32_add(&self->m_hash[6], &self->m_hash[6], g);
	mk_uint32_add(&self->m_hash[7], &self->m_hash[7], h);
}

static mk_inline void mk_sha2_512_detail_process_block(struct mk_sha2_512_state_s* self, void const* data)
{
	unsigned char const* input;
	struct mk_uint64_s w[80];
	struct mk_uint64_s hh[8];
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

	mk_assert(self);
	mk_assert(data);

	input = (unsigned char const*)data;
	a = hh + 0;
	b = hh + 1;
	c = hh + 2;
	d = hh + 3;
	e = hh + 4;
	f = hh + 5;
	g = hh + 6;
	h = hh + 7;

	mk_sha2_detail_be2ints64(input, w, 16);
	for(i = 16; i != 80; ++i)
	{
		/* w[i] = sig1(w[i - 2]) + w[i - 7] + sig0(w[i - 15]) + w[i - 16]; */
		mk_sha2_512_detail_sig1(&tmp1, &w[i - 2]);
		mk_uint64_add(&tmp1, &tmp1, &w[i - 7]);
		mk_sha2_512_detail_sig0(&tmp2, &w[i - 15]);
		mk_uint64_add(&tmp2, &tmp2, &w[i - 16]);
		mk_uint64_add(&w[i], &tmp1, &tmp2);
	}

	*a = self->m_hash[0];
	*b = self->m_hash[1];
	*c = self->m_hash[2];
	*d = self->m_hash[3];
	*e = self->m_hash[4];
	*f = self->m_hash[5];
	*g = self->m_hash[6];
	*h = self->m_hash[7];

	for(i = 0; i != 80; ++i)
	{
		/* t1 = *h + sum1(*e) + ch(*e, *f, *g) + table[i] + w[i]; */
		mk_sha2_512_detail_sum1(&tmp1, e);
		mk_sha2_512_detail_ch(&tmp2, e, f, g);
		mk_uint64_add(&tmp1, &tmp1, h);
		mk_uint64_add(&tmp2, &tmp2, &mk_sha2_512_detail_table[i]);
		mk_uint64_add(&tmp1, &tmp1, &tmp2);
		mk_uint64_add(&t1, &tmp1, &w[i]);

		/* t2 = sum0(*a) + maj(*a, *b, *c); */
		mk_sha2_512_detail_sum0(&tmp1, a);
		mk_sha2_512_detail_maj(&tmp2, a, b, c);
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

	mk_uint64_add(&self->m_hash[0], &self->m_hash[0], a);
	mk_uint64_add(&self->m_hash[1], &self->m_hash[1], b);
	mk_uint64_add(&self->m_hash[2], &self->m_hash[2], c);
	mk_uint64_add(&self->m_hash[3], &self->m_hash[3], d);
	mk_uint64_add(&self->m_hash[4], &self->m_hash[4], e);
	mk_uint64_add(&self->m_hash[5], &self->m_hash[5], f);
	mk_uint64_add(&self->m_hash[6], &self->m_hash[6], g);
	mk_uint64_add(&self->m_hash[7], &self->m_hash[7], h);
}


void mk_sha2_256_224_init(struct mk_sha2_256_224_state_s* self)
{
	static struct mk_uint32_s const s_init[] =
	{
		mk_uint32_c(0xc1059ed8),
		mk_uint32_c(0x367cd507),
		mk_uint32_c(0x3070dd17),
		mk_uint32_c(0xf70e5939),
		mk_uint32_c(0xffc00b31),
		mk_uint32_c(0x68581511),
		mk_uint32_c(0x64f98fa7),
		mk_uint32_c(0xbefa4fa4),
	};

	mk_assert(self);

	self->m_hash[0] = s_init[0];
	self->m_hash[1] = s_init[1];
	self->m_hash[2] = s_init[2];
	self->m_hash[3] = s_init[3];
	self->m_hash[4] = s_init[4];
	self->m_hash[5] = s_init[5];
	self->m_hash[6] = s_init[6];
	self->m_hash[7] = s_init[7];
	mk_uint64_zero(&self->m_len);
}

void mk_sha2_256_224_append(struct mk_sha2_256_224_state_s* self, void const* data, size_t len)
{
	mk_sha2_256_append((struct mk_sha2_256_state_s*)self, data, len);
}

void mk_sha2_256_224_finish(struct mk_sha2_256_224_state_s* self, void* digest)
{
	unsigned char sha2_256_digest[32];

	mk_assert(self);
	mk_assert(digest);

	mk_sha2_256_finish((struct mk_sha2_256_state_s*)self, &sha2_256_digest);

	memcpy(digest, &sha2_256_digest, 28);
}


void mk_sha2_256_init(struct mk_sha2_256_state_s* self)
{
	static struct mk_uint32_s const s_init[] =
	{
		mk_uint32_c(0x6a09e667),
		mk_uint32_c(0xbb67ae85),
		mk_uint32_c(0x3c6ef372),
		mk_uint32_c(0xa54ff53a),
		mk_uint32_c(0x510e527f),
		mk_uint32_c(0x9b05688c),
		mk_uint32_c(0x1f83d9ab),
		mk_uint32_c(0x5be0cd19),
	};

	mk_assert(self);

	self->m_hash[0] = s_init[0];
	self->m_hash[1] = s_init[1];
	self->m_hash[2] = s_init[2];
	self->m_hash[3] = s_init[3];
	self->m_hash[4] = s_init[4];
	self->m_hash[5] = s_init[5];
	self->m_hash[6] = s_init[6];
	self->m_hash[7] = s_init[7];
	mk_uint64_zero(&self->m_len);
}

void mk_sha2_256_append(struct mk_sha2_256_state_s* self, void const* data, size_t len)
{
	unsigned char const* input;
	size_t remaining;
	unsigned idx;
	unsigned capacity;
	struct mk_uint64_s tmp;
	size_t blocks;
	size_t i;

	mk_assert(self);
	
	input = (unsigned char const*)data;
	remaining = len;

	idx = mk_uint64_to_int(&self->m_len) % 64;
	capacity = 64 - idx;
	mk_uint64_from_sizet(&tmp, len);
	mk_uint64_add(&self->m_len, &self->m_len, &tmp);
	if(remaining >= capacity)
	{
		memcpy((unsigned char*)self->m_block + idx, input, capacity);
		mk_sha2_256_detail_process_block(self, self->m_block);
		input += capacity;
		remaining -= capacity;
		blocks = remaining / 64;
		for(i = 0; i != blocks; ++i)
		{
			mk_sha2_256_detail_process_block(self, input);
			input += 64;
		}
		remaining -= blocks * 64;
		idx = 0;
	}
	memcpy((unsigned char*)self->m_block + idx, input, remaining);
}

void mk_sha2_256_finish(struct mk_sha2_256_state_s* self, void* digest)
{
	#define s_mandatory_padding_len (1 + sizeof(struct mk_uint64_s))
	#define s_worst_padding_len (64 + s_mandatory_padding_len - 1)
	
	unsigned char padding[s_worst_padding_len];
	unsigned idx;
	unsigned capacity;
	unsigned zeros;
	struct mk_uint64_s len;

	mk_assert(self);
	mk_assert(digest);

	idx = mk_uint64_to_int(&self->m_len) % 64;
	capacity = 64 - idx;
	zeros =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity + 64 - s_mandatory_padding_len);

	#undef s_mandatory_padding_len
	#undef s_worst_padding_len

	padding[0] = (unsigned char)(1u << 7);

	memset(padding + 1, 0, zeros);

	mk_uint64_shl(&len, &self->m_len, 3);
	mk_sha2_detail_ints2be64(&len, 1, padding + 1 + zeros);

	mk_sha2_256_append(self, padding, 1 + zeros + sizeof(struct mk_uint64_s));

	mk_sha2_detail_ints2be32(self->m_hash, 8, digest);
}


void mk_sha2_512_224_init(struct mk_sha2_512_224_state_s* self)
{
	static struct mk_uint64_s const s_init[] =
	{
		mk_uint64_c(0x8c3d37c8, 0x19544da2),
		mk_uint64_c(0x73e19966, 0x89dcd4d6),
		mk_uint64_c(0x1dfab7ae, 0x32ff9c82),
		mk_uint64_c(0x679dd514, 0x582f9fcf),
		mk_uint64_c(0x0f6d2b69, 0x7bd44da8),
		mk_uint64_c(0x77e36f73, 0x04c48942),
		mk_uint64_c(0x3f9d85a8, 0x6a1d36c8),
		mk_uint64_c(0x1112e6ad, 0x91d692a1),
	};

	mk_assert(self);

	self->m_hash[0] = s_init[0];
	self->m_hash[1] = s_init[1];
	self->m_hash[2] = s_init[2];
	self->m_hash[3] = s_init[3];
	self->m_hash[4] = s_init[4];
	self->m_hash[5] = s_init[5];
	self->m_hash[6] = s_init[6];
	self->m_hash[7] = s_init[7];
	mk_uint128_zero(&self->m_len);
}

void mk_sha2_512_224_append(struct mk_sha2_512_224_state_s* self, void const* data, size_t len)
{
	mk_sha2_512_append((struct mk_sha2_512_state_s*)self, data, len);
}

void mk_sha2_512_224_finish(struct mk_sha2_512_224_state_s* self, void* digest)
{
	unsigned char sha2_512_digest[64];

	mk_assert(self);
	mk_assert(digest);

	mk_sha2_512_finish((struct mk_sha2_512_state_s*)self, &sha2_512_digest);

	memcpy(digest, &sha2_512_digest, 28);
}


void mk_sha2_512_256_init(struct mk_sha2_512_256_state_s* self)
{
	static struct mk_uint64_s const s_init[] =
	{
		mk_uint64_c(0x22312194, 0xfc2bf72c),
		mk_uint64_c(0x9f555fa3, 0xc84c64c2),
		mk_uint64_c(0x2393b86b, 0x6f53b151),
		mk_uint64_c(0x96387719, 0x5940eabd),
		mk_uint64_c(0x96283ee2, 0xa88effe3),
		mk_uint64_c(0xbe5e1e25, 0x53863992),
		mk_uint64_c(0x2b0199fc, 0x2c85b8aa),
		mk_uint64_c(0x0eb72ddc, 0x81c52ca2),
	};

	mk_assert(self);

	self->m_hash[0] = s_init[0];
	self->m_hash[1] = s_init[1];
	self->m_hash[2] = s_init[2];
	self->m_hash[3] = s_init[3];
	self->m_hash[4] = s_init[4];
	self->m_hash[5] = s_init[5];
	self->m_hash[6] = s_init[6];
	self->m_hash[7] = s_init[7];
	mk_uint128_zero(&self->m_len);
}

void mk_sha2_512_256_append(struct mk_sha2_512_256_state_s* self, void const* data, size_t len)
{
	mk_sha2_512_append((struct mk_sha2_512_state_s*)self, data, len);
}

void mk_sha2_512_256_finish(struct mk_sha2_512_256_state_s* self, void* digest)
{
	unsigned char sha2_512_digest[64];

	mk_assert(self);
	mk_assert(digest);

	mk_sha2_512_finish((struct mk_sha2_512_state_s*)self, &sha2_512_digest);

	memcpy(digest, &sha2_512_digest, 32);
}


void mk_sha2_512_384_init(struct mk_sha2_512_384_state_s* self)
{
	static struct mk_uint64_s const s_init[] =
	{
		mk_uint64_c(0xcbbb9d5d, 0xc1059ed8),
		mk_uint64_c(0x629a292a, 0x367cd507),
		mk_uint64_c(0x9159015a, 0x3070dd17),
		mk_uint64_c(0x152fecd8, 0xf70e5939),
		mk_uint64_c(0x67332667, 0xffc00b31),
		mk_uint64_c(0x8eb44a87, 0x68581511),
		mk_uint64_c(0xdb0c2e0d, 0x64f98fa7),
		mk_uint64_c(0x47b5481d, 0xbefa4fa4),
	};

	mk_assert(self);

	self->m_hash[0] = s_init[0];
	self->m_hash[1] = s_init[1];
	self->m_hash[2] = s_init[2];
	self->m_hash[3] = s_init[3];
	self->m_hash[4] = s_init[4];
	self->m_hash[5] = s_init[5];
	self->m_hash[6] = s_init[6];
	self->m_hash[7] = s_init[7];
	mk_uint128_zero(&self->m_len);
}

void mk_sha2_512_384_append(struct mk_sha2_512_384_state_s* self, void const* data, size_t len)
{
	mk_sha2_512_append((struct mk_sha2_512_state_s*)self, data, len);
}

void mk_sha2_512_384_finish(struct mk_sha2_512_384_state_s* self, void* digest)
{
	unsigned char sha2_512_digest[64];

	mk_assert(self);
	mk_assert(digest);

	mk_sha2_512_finish((struct mk_sha2_512_state_s*)self, &sha2_512_digest);

	memcpy(digest, &sha2_512_digest, 48);
}


void mk_sha2_512_init(struct mk_sha2_512_state_s* self)
{
	static struct mk_uint64_s const s_init[] =
	{
		mk_uint64_c(0x6a09e667, 0xf3bcc908),
		mk_uint64_c(0xbb67ae85, 0x84caa73b),
		mk_uint64_c(0x3c6ef372, 0xfe94f82b),
		mk_uint64_c(0xa54ff53a, 0x5f1d36f1),
		mk_uint64_c(0x510e527f, 0xade682d1),
		mk_uint64_c(0x9b05688c, 0x2b3e6c1f),
		mk_uint64_c(0x1f83d9ab, 0xfb41bd6b),
		mk_uint64_c(0x5be0cd19, 0x137e2179),
	};

	mk_assert(self);

	self->m_hash[0] = s_init[0];
	self->m_hash[1] = s_init[1];
	self->m_hash[2] = s_init[2];
	self->m_hash[3] = s_init[3];
	self->m_hash[4] = s_init[4];
	self->m_hash[5] = s_init[5];
	self->m_hash[6] = s_init[6];
	self->m_hash[7] = s_init[7];
	mk_uint128_zero(&self->m_len);
}

void mk_sha2_512_append(struct mk_sha2_512_state_s* self, void const* data, size_t len)
{
	unsigned char const* input;
	size_t remaining;
	unsigned idx;
	unsigned capacity;
	struct mk_uint128_s len_;
	size_t blocks;
	size_t i;

	mk_assert(self);
	
	input = (unsigned char const*)data;
	remaining = len;

	idx = mk_uint128_to_int(&self->m_len) % 128;
	capacity = 128 - idx;
	
	mk_uint128_from_sizet(&len_, len);
	mk_uint128_add(&self->m_len, &self->m_len, &len_);
	
	if(remaining >= capacity)
	{
		memcpy((unsigned char*)self->m_block + idx, input, capacity);
		mk_sha2_512_detail_process_block(self, self->m_block);
		input += capacity;
		remaining -= capacity;
		blocks = remaining / 128;
		for(i = 0; i != blocks; ++i)
		{
			mk_sha2_512_detail_process_block(self, input);
			input += 128;
		}
		remaining -= blocks * 128;
		idx = 0;
	}
	memcpy((unsigned char*)self->m_block + idx, input, remaining);
}

void mk_sha2_512_finish(struct mk_sha2_512_state_s* self, void* digest)
{
	#define s_mandatory_padding_len (1 + sizeof(struct mk_uint128_s))
	#define s_worst_padding_len (128 + s_mandatory_padding_len - 1)
	
	unsigned char padding[s_worst_padding_len];
	unsigned idx;
	unsigned capacity;
	unsigned zeros;
	struct mk_uint128_s len;

	mk_assert(self);
	mk_assert(digest);

	idx = mk_uint128_to_int(&self->m_len) % 128;
	capacity = 128 - idx;
	zeros =
		(capacity >= s_mandatory_padding_len) ?
		(capacity - s_mandatory_padding_len) :
		(capacity + 128 - s_mandatory_padding_len);

	#undef s_mandatory_padding_len
	#undef s_worst_padding_len

	padding[0] = (unsigned char)(1u << 7);

	memset(padding + 1, 0, zeros);

	mk_uint128_shl(&len, &self->m_len, 3);
	mk_uint128_to_buff_be(&len, padding + 1 + zeros);

	mk_sha2_512_append(self, padding, 1 + zeros + sizeof(struct mk_uint128_s));

	mk_sha2_detail_ints2be64(self->m_hash, 8, digest);
}
