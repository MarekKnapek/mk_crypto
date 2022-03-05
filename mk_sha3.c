#include "mk_sha3.h"

#include "mk_assert.h"

#include <assert.h> /* static_assert */
#include <limits.h> /* CHAR_BIT SIZE_MAX */
#include <stdbool.h> /* bool true false */ /* C99 */
#include <stdint.h> /* uint16_t uint64_t */ /* C99 */
#include <string.h> /* memcpy memset */


static_assert(CHAR_BIT == 8, "Must have 8bit byte.");


struct mk_sha3_detail_state_s
{
	uint64_t m_data[5][5];
};


static inline int mk_sha3_detail_mod(int m, int n)
{
	MK_ASSERT(n > 0);

	int r;

	r = m % n;
	r = r < 0 ? r + n : r;

	return r;
}

static inline bool mk_sha3_detail_string_get_bit(void const* s, int n)
{
	MK_ASSERT(s);
	MK_ASSERT(n >= 0);

	unsigned char const* input = (unsigned char const*)s;

	int byte = n / CHAR_BIT;
	int bit = n % CHAR_BIT;
	bool val = ((input[byte] >> bit) & 0x01) == 0 ? false : true;

	return val;
}

static inline void mk_sha3_detail_string_set_bit(void* s, int n, bool val)
{
	MK_ASSERT(s);
	MK_ASSERT(n >= 0);

	unsigned char* output = (unsigned char*)s;

	int byte = n / CHAR_BIT;
	int bit = n % CHAR_BIT;

	if(val)
	{
		output[byte] |= (unsigned char)(1u << bit);
	}
	else
	{
		output[byte] &= (unsigned char)(~(1u << bit));
	}
}

static inline int mk_sha3_detail_b2l(int b)
{
	MK_ASSERT(b == 25 || b == 50 || b == 100 || b == 200 || b == 400 || b == 800 || b == 1600);

	int l = b == 25 ? 0 : b == 50 ? 1 : b == 100 ? 2 : b == 200 ? 3 : b == 400 ? 4 : b == 800 ? 5 : 6;

	return l;
}

static inline int mk_sha3_detail_b2w(int b)
{
	MK_ASSERT(b == 25 || b == 50 || b == 100 || b == 200 || b == 400 || b == 800 || b == 1600);

	int w = b == 25 ? 1 : b == 50 ? 2 : b == 100 ? 4 : b == 200 ? 8 : b == 400 ? 16 : b == 800 ? 32 : 64;

	return w;
}

static inline int mk_sha3_detail_l2b(int l)
{
	MK_ASSERT(l == 0 || l == 1 || l == 2 || l == 3 || l == 4 || l == 5 || l == 6);

	int b = l == 0 ? 25 : l == 1 ? 50 : l == 2 ? 100 : l == 3 ? 200 : l == 4 ? 400 : l == 5 ? 800 : 1600;

	return b;
}

static inline int mk_sha3_detail_l2w(int l)
{
	MK_ASSERT(l == 0 || l == 1 || l == 2 || l == 3 || l == 4 || l == 5 || l == 6);

	int w = l == 0 ? 1 : l == 1 ? 2 : l == 2 ? 4 : l == 3 ? 8 : l == 4 ? 16 : l == 5 ? 32 : 64;

	return w;
}

static inline int mk_sha3_detail_w2b(int w)
{
	MK_ASSERT(w == 1 || w == 2 || w == 4 || w == 8 || w == 16 || w == 32 || w == 64);

	int b = w == 1 ? 25 : w == 2 ? 50 : w == 4 ? 100 : w == 8 ? 200 : w == 16 ? 400 : w == 20 ? 800 : 1600;

	return b;
}

static inline int mk_sha3_detail_w2l(int w)
{
	MK_ASSERT(w == 1 || w == 2 || w == 4 || w == 8 || w == 16 || w == 32 || w == 64);

	int l = w == 1 ? 0 : w == 2 ? 1 : w == 4 ? 2 : w == 8 ? 3 : w == 16 ? 4 : w == 20 ? 5 : 6;

	return l;
}

bool mk_sha3_detail_state_arr_get_bit(int w, struct mk_sha3_detail_state_s const* arr, int x, int y, int z)
{
	MK_ASSERT(w == 1 || w == 2 || w == 4 || w == 8 || w == 16 || w == 32 || w == 64);
	MK_ASSERT(arr);
	MK_ASSERT(x >= 0 && x < 5);
	MK_ASSERT(y >= 0 && y < 5);
	MK_ASSERT(z >= 0 && z < w);

	uint64_t data = arr->m_data[y][x];

	return ((data >> (w-1-z)) & 0x01) == 0 ? false : true;
}

void mk_sha3_detail_state_arr_set_bit(int w, struct mk_sha3_detail_state_s* arr, int x, int y, int z, bool bit)
{
	MK_ASSERT(w == 1 || w == 2 || w == 4 || w == 8 || w == 16 || w == 32 || w == 64);
	MK_ASSERT(arr);
	MK_ASSERT(x >= 0 && x < 5);
	MK_ASSERT(y >= 0 && y < 5);
	MK_ASSERT(z >= 0 && z < w);

	uint64_t data = arr->m_data[y][x];

	if(bit)
	{
		data |= ((uint64_t)1u) << z;
	}
	else
	{
		data &= ~(((uint64_t)1u) << z);
	}

	arr->m_data[y][x] = data;
}

static inline void mk_sha3_detail_state_arr_from_string(int w, void const* string, struct mk_sha3_detail_state_s* arr)
{
	MK_ASSERT(w == 1 || w == 2 || w == 4 || w == 8 || w == 16 || w == 32 || w == 64);
	MK_ASSERT(string);
	MK_ASSERT(arr);

	for(int x = 0; x != 5; ++x)
	{
		for(int y = 0; y != 5; ++y)
		{
			for(int z = 0; z != w; ++z)
			{
				int idx = w * (5 * y + x) + z;
				bool bit = mk_sha3_detail_string_get_bit(string, idx);
				mk_sha3_detail_state_arr_set_bit(w, arr, x, y, z, bit);
			}
		}
	}
}

static inline void mk_sha3_detail_state_arr_to_string(int w, struct mk_sha3_detail_state_s const* arr, void* string)
{
	MK_ASSERT(w == 1 || w == 2 || w == 4 || w == 8 || w == 16 || w == 32 || w == 64);
	MK_ASSERT(arr);
	MK_ASSERT(string);

	for(int x = 0; x != 5; ++x)
	{
		for(int y = 0; y != 5; ++y)
		{
			for(int z = 0; z != w; ++z)
			{
				int idx = w * (5 * y + x) + z;
				bool bit = mk_sha3_detail_state_arr_get_bit(w, arr, x, y, z);
				mk_sha3_detail_string_set_bit(string, idx, bit);
			}
		}
	}
}


static inline int mk_sha3_detail_coordinate_mapping_x(int x)
{
	return (x + 2) % 5;
}

static inline int mk_sha3_detail_coordinate_mapping_y(int y)
{
	return mk_sha3_detail_mod(y - 2, 5);
}

bool mk_sha3_detail_state_arr_get_bit_mapped(int w, struct mk_sha3_detail_state_s const* arr, int x, int y, int z)
{
	return mk_sha3_detail_state_arr_get_bit(w, arr, mk_sha3_detail_coordinate_mapping_x(x), mk_sha3_detail_coordinate_mapping_y(y), z);
}

void mk_sha3_detail_state_arr_set_bit_mapped(int w, struct mk_sha3_detail_state_s* arr, int x, int y, int z, bool bit)
{
	mk_sha3_detail_state_arr_set_bit(w, arr, mk_sha3_detail_coordinate_mapping_x(x), mk_sha3_detail_coordinate_mapping_y(y), z, bit);
}

static inline uint64_t mk_sha3_detail_rot(uint64_t x, int n)
{
	MK_ASSERT(n > 0);
	MK_ASSERT(n < 64);

	return (x << n) | (x >> (64 - n));
}

static inline void mk_sha3_detail_theta(struct mk_sha3_detail_state_s* state)
{
	MK_ASSERT(state);

	uint64_t c[5];
	c[0] = (state->m_data[0][0] ^ state->m_data[1][0]) ^ (state->m_data[2][0] ^ state->m_data[3][0]) ^ state->m_data[4][0];
	c[1] = (state->m_data[0][1] ^ state->m_data[1][1]) ^ (state->m_data[2][1] ^ state->m_data[3][1]) ^ state->m_data[4][1];
	c[2] = (state->m_data[0][2] ^ state->m_data[1][2]) ^ (state->m_data[2][2] ^ state->m_data[3][2]) ^ state->m_data[4][2];
	c[3] = (state->m_data[0][3] ^ state->m_data[1][3]) ^ (state->m_data[2][3] ^ state->m_data[3][3]) ^ state->m_data[4][3];
	c[4] = (state->m_data[0][4] ^ state->m_data[1][4]) ^ (state->m_data[2][4] ^ state->m_data[3][4]) ^ state->m_data[4][4];

	uint64_t d[5];
	d[0] = c[4] ^ mk_sha3_detail_rot(c[1], 1);
	d[1] = c[0] ^ mk_sha3_detail_rot(c[2], 1);
	d[2] = c[1] ^ mk_sha3_detail_rot(c[3], 1);
	d[3] = c[2] ^ mk_sha3_detail_rot(c[4], 1);
	d[4] = c[3] ^ mk_sha3_detail_rot(c[0], 1);

	for(int y = 0; y != 5; ++y)
	{
		state->m_data[y][0] ^= d[0];
		state->m_data[y][1] ^= d[1];
		state->m_data[y][2] ^= d[2];
		state->m_data[y][3] ^= d[3];
		state->m_data[y][4] ^= d[4];
	}
}

static inline void mk_sha3_detail_rho(struct mk_sha3_detail_state_s* state)
{
	MK_ASSERT(state);

	int x = 1;
	int y = 0;
	for(int t = 0; t != 24; ++t)
	{
		state->m_data[y][x] = mk_sha3_detail_rot(state->m_data[y][x], (((t + 1) * (t + 2)) / 2) % 64);
		int old_x = x;
		x = y;
		y = (2 * old_x + 3 * y) % 5;
	}
}

static inline void mk_sha3_detail_pi(struct mk_sha3_detail_state_s const* in, struct mk_sha3_detail_state_s* out)
{
	MK_ASSERT(in);
	MK_ASSERT(out);
	MK_ASSERT(in != out);

	for(int y = 0; y != 5; ++y)
	{
		for(int x = 0; x != 5; ++x)
		{
			int target_x = y;
			int target_y = (2 * x + 3 * y) % 5;
			out->m_data[target_y][target_x] = in->m_data[y][x];
		}
	}
}

static inline void mk_sha3_detail_chi(struct mk_sha3_detail_state_s const* in, struct mk_sha3_detail_state_s* out)
{
	MK_ASSERT(in);
	MK_ASSERT(out);
	MK_ASSERT(in != out);

	for(int y = 0; y != 5; ++y)
	{
		for(int x = 0; x != 5; ++x)
		{
			out->m_data[y][x] = in->m_data[y][x] ^ (~in->m_data[y][(x + 1) % 5] & in->m_data[y][(x + 2) % 5]);
		}
	}
}

static inline uint64_t mk_sha3_detail_alg_rc(int t)
{
	int modded = t % 255;

	if(modded == 0)
	{
		return 1;
	}

	unsigned r = 1;
	for(int i = 0; i != modded; ++i)
	{
		r <<= 1;
		r = (r & ~(1u << 0)) | ((((r >> 0) & 0x1) ^ ((r >> 8) & 0x1)) << 0);
		r = (r & ~(1u << 4)) | ((((r >> 4) & 0x1) ^ ((r >> 8) & 0x1)) << 4);
		r = (r & ~(1u << 5)) | ((((r >> 5) & 0x1) ^ ((r >> 8) & 0x1)) << 5);
		r = (r & ~(1u << 6)) | ((((r >> 6) & 0x1) ^ ((r >> 8) & 0x1)) << 6);
	}

	return r & 0x1;
}

static inline uint64_t mk_sha3_detail_get_rc(int ir)
{
	uint64_t rc = 0;

	rc |= mk_sha3_detail_alg_rc(0 + 7 * ir) << 0;
	rc |= mk_sha3_detail_alg_rc(1 + 7 * ir) << 1;
	rc |= mk_sha3_detail_alg_rc(2 + 7 * ir) << 3;
	rc |= mk_sha3_detail_alg_rc(3 + 7 * ir) << 7;
	rc |= mk_sha3_detail_alg_rc(4 + 7 * ir) << 15;
	rc |= mk_sha3_detail_alg_rc(5 + 7 * ir) << 31;
	rc |= mk_sha3_detail_alg_rc(6 + 7 * ir) << 63;

	return rc;
}

static inline void mk_sha3_detail_iota(struct mk_sha3_detail_state_s* state, int ir)
{
	MK_ASSERT(state);

	uint64_t rc = mk_sha3_detail_get_rc(ir);

	state->m_data[0][0] ^= rc;
}

static inline void mk_sha3_detail_rnd(struct mk_sha3_detail_state_s* state, int ir)
{
	MK_ASSERT(state);

	struct mk_sha3_detail_state_s tmp;

	mk_sha3_detail_theta(state);
	mk_sha3_detail_rho(state);
	mk_sha3_detail_pi(state, &tmp);
	mk_sha3_detail_chi(&tmp, state);
	mk_sha3_detail_iota(state, ir);
}

static inline void mk_sha3_detail_keccak_p(int b, int nr, void* s)
{
	MK_ASSERT(b == 25 || b == 50 || b == 100 || b == 200 || b == 400 || b == 800 || b == 1600);
	MK_ASSERT(s);

	int l = mk_sha3_detail_b2l(b);

	struct mk_sha3_detail_state_s* state = (struct mk_sha3_detail_state_s*)s;

	for(int ir = 12 + 2 * l - nr; ir != 12 + 2 * l; ++ir)
	{
		mk_sha3_detail_rnd(state, ir);
	}
}

static inline void mk_sha3_detail_keccak_f(int b, void* s)
{
	MK_ASSERT(b == 25 || b == 50 || b == 100 || b == 200 || b == 400 || b == 800 || b == 1600);
	MK_ASSERT(s);

	int l = mk_sha3_detail_b2l(b);
	int nr = 12 + 2 * l;

	mk_sha3_detail_keccak_p(b, nr, s);
}

static inline void mk_sha3_detail_keccak_pad_101(int x, int m, void* p)
{
	MK_ASSERT(x > 0);
	MK_ASSERT(m >= 0);
	MK_ASSERT(p);

	int j = mk_sha3_detail_mod(-m - 2, x);

	mk_sha3_detail_string_set_bit(p, 0, true);
	for(int i = 0; i != j; ++i)
	{
		mk_sha3_detail_string_set_bit(p, 1 + i, false);
	}
	mk_sha3_detail_string_set_bit(p, 1 + j, true);
}








enum mk_sha3_detail_sponge_fnc_e
{
	mk_sha3_detail_sponge_fnc_e_begin,
	mk_sha3_detail_sponge_fnc_e_p_1600_24 = 0,
	mk_sha3_detail_sponge_fnc_e_end,
};

enum mk_sha3_detail_sponge_pad_e
{
	mk_sha3_detail_sponge_pad_e_begin,
	mk_sha3_detail_sponge_pad_e_101 = 0,
	mk_sha3_detail_sponge_pad_e_end,
};

static inline void mk_sha3_detail_sponge_block(int w, int block_size, enum mk_sha3_detail_sponge_fnc_e fnc, int r, void* state_, void const* block)
{
	MK_ASSERT(w == 1 || w == 2 || w == 4 || w == 8 || w == 16 || w == 32 || w == 64);
	MK_ASSERT(block_size % CHAR_BIT == 0);
	MK_ASSERT(fnc >= mk_sha3_detail_sponge_fnc_e_begin && fnc < mk_sha3_detail_sponge_fnc_e_end);
	MK_ASSERT(r > 0);
	MK_ASSERT(r < mk_sha3_detail_w2b(w));
	MK_ASSERT(r == block_size);
	MK_ASSERT(state_);
	MK_ASSERT(block);

	#define worst_case_b 1600
	#define s_elems (worst_case_b / CHAR_BIT / sizeof(uint64_t))

	int b = mk_sha3_detail_w2b(w);
	uint64_t* state = (uint64_t*)state_;

	uint64_t tmp[s_elems];

	unsigned char* tt = (unsigned char*)tmp;
	memcpy(tt + 0, block, block_size / CHAR_BIT);
	memset(tt + block_size/ CHAR_BIT, 0, sizeof(tmp) - block_size/ CHAR_BIT);

	for(int i = 0; i != s_elems; ++i)
	{
		state[i] ^= tmp[i];
	}

	switch(fnc)
	{
		case mk_sha3_detail_sponge_fnc_e_p_1600_24:
		{
			mk_sha3_detail_keccak_f(b, state);
		}
		break;
		default:
		{
			MK_ASSERT(0);
		}
		break;
	}

	#undef worst_case_b
	#undef s_elems
}

static inline void mk_sha3_detail_keccak_block(int c, int block_size, void* state, void const* block)
{
	MK_ASSERT(state);
	MK_ASSERT(block);

	int b = 1600;
	int w = mk_sha3_detail_b2w(b);
	int r = b - c;

	mk_sha3_detail_sponge_block(w, block_size, mk_sha3_detail_sponge_fnc_e_p_1600_24, r, state, block);
}

enum mk_sha3_detail_domain_e
{
	mk_sha3_detail_domain_e_sha3,
	mk_sha3_detail_domain_e_shake,
	mk_sha3_detail_domain_e_raw_shake,
};

enum mk_sha3_detail_pad_e
{
	mk_sha3_detail_pad_e_101,
};

static inline void mk_sha3_detail_keccak_pad(enum mk_sha3_detail_domain_e domain, int block_size, void* state, int* block_idx, void* block_)
{
	MK_ASSERT(state);
	MK_ASSERT(block_idx);
	MK_ASSERT(*block_idx < block_size);
	MK_ASSERT(block_);

	enum mk_sha3_detail_pad_e pad = mk_sha3_detail_sponge_pad_e_101; /* TODO move from keccak to sponge */

	unsigned char suffix;
	int suffix_bits;

	switch(domain)
	{
		case mk_sha3_detail_domain_e_sha3:
		{
			suffix = 0x02;
			suffix_bits = 2;
		}
		break;
		case mk_sha3_detail_domain_e_shake:
		{
			suffix = 0x0f;
			suffix_bits = 4;
		}
		break;
		case mk_sha3_detail_domain_e_raw_shake:
		{
			suffix = 0x03;
			suffix_bits = 2;
		}
		break;
		default:
		{
			MK_ASSERT(0);
			/* To silence warning. */
			suffix = 0; 
			suffix_bits = 0;
		}
		break;
	}

	switch(pad)
	{
		case mk_sha3_detail_pad_e_101:
		{
			unsigned char* block = (unsigned char*)block_;
			unsigned idx_byte = (*block_idx + (CHAR_BIT - 1)) / CHAR_BIT;
			memset(block + idx_byte, 0, block_size / CHAR_BIT - idx_byte);

			idx_byte = *block_idx / CHAR_BIT;
			unsigned idx = *block_idx % CHAR_BIT;
			for(int i = 0; i != suffix_bits; ++i)
			{
				bool bit = mk_sha3_detail_string_get_bit(&suffix, i);
				mk_sha3_detail_string_set_bit(block + idx_byte, idx + i, bit);
			}

			mk_sha3_detail_string_set_bit(block + idx_byte, idx + suffix_bits, true);
			for(int i = 0; i != CHAR_BIT - 1; ++i)
			{
				mk_sha3_detail_string_set_bit(block + idx_byte, idx + suffix_bits + 1 + i, false);
			}
			mk_sha3_detail_string_set_bit(block + block_size / CHAR_BIT - 1, CHAR_BIT - 1, true);

#if 0
			/*
			#define worst_case_b 1600
			#define worst_case_c 448
			#define worst_case_block_size ((1600 - worst_case_c) / CHAR_BIT)
			#define worst_min_padding_bits (4 + 2)
			#define worst_min_padding_bytes ((worst_min_padding_bits - 1) / CHAR_BIT + 1)
			#define worst_case_padding_len (worst_case_block_size + worst_min_padding_bytes - 1)

			unsigned char padding[worst_case_padding_len];
			memset(padding, 0, sizeof(padding));
			*/

			unsigned char* padding = (unsigned char*)block + *block_idx;
			memset(padding + 1, 0, block_size - *block_idx - 1);

			padding[0] = suffix;

			/* padding[0] = (padding[0] << 1) | 0x01; */
			mk_sha3_detail_string_set_bit(padding, suffix_bits, true);
			int len_n = *block_idx * CHAR_BIT + suffix_bits;
			int j = mk_sha3_detail_mod(-len_n - 2, r);
			mk_sha3_detail_string_set_bit(padding, suffix_bits + 1 + j, true);

			int padding_bits = len_n + 1 + j + 1;
			MK_ASSERT((padding_bits % CHAR_BIT) == 0);
			int padding_bytes = padding_bits / CHAR_BIT;
			
			MK_ASSERT(*block_idx + padding_bytes == (unsigned)block_size);
			*block_idx = 0;
			
			/*#undef worst_case_b
			#undef worst_case_c
			#undef worst_case_block_size
			#undef worst_min_padding_bits
			#undef worst_min_padding_bytes
			#undef worst_case_padding_len*/
#endif
		}
		break;
		default:
		{
			MK_ASSERT(0);
		}
		break;
	}
}


static inline void mk_sha3_detail_process_block(int c, int block_size, void* state, void const* block)
{
	MK_ASSERT(state);
	MK_ASSERT(block);

	mk_sha3_detail_keccak_block(c, block_size, state, block);
}


static inline void mk_sha3_detail_init(uint64_t* state, int* idx)
{
	MK_ASSERT(state);
	MK_ASSERT(idx);

	memset(state, 0, 25 * sizeof(uint64_t));
	*idx = 0;
}

static inline void mk_sha3_detail_memcpy_bits(void* dst, int dst_bit_offset, void const* src, int src_bit_offset, size_t bits)
{
	MK_ASSERT(dst_bit_offset >= 0 && dst_bit_offset < CHAR_BIT);
	MK_ASSERT(src_bit_offset >= 0 && src_bit_offset < CHAR_BIT);

	if(dst_bit_offset == 0 && src_bit_offset == 0)
	{
		size_t bytes = (bits + (CHAR_BIT - 1)) / CHAR_BIT;
		memcpy(dst, src, bytes);
	}
	else
	{
		unsigned char const* input = (unsigned char const*)src;
		unsigned char* output = (unsigned char*)dst;
		for(size_t i = 0; i != bits; ++i)
		{
			bool bit = mk_sha3_detail_string_get_bit(input + i / CHAR_BIT, i % CHAR_BIT + src_bit_offset);
			mk_sha3_detail_string_set_bit(output + i / CHAR_BIT, i % CHAR_BIT + dst_bit_offset, bit);
		}
	}
}

static inline void mk_sha3_detail_append_a(int c, int block_size, void* state, int* block_idx, void* block_, void const* data, size_t data_len_bits)
{
	MK_ASSERT((block_size % CHAR_BIT) == 0);
	MK_ASSERT(state);
	MK_ASSERT(block_idx);
	MK_ASSERT(*block_idx % CHAR_BIT == 0);
	MK_ASSERT(*block_idx < block_size);
	MK_ASSERT(block_);

	unsigned char* block = (unsigned char*)block_;
	unsigned char const* input = (unsigned char const*)data;

	size_t remaining = data_len_bits;

	int idx = *block_idx;
	int capacity = block_size - idx;
	int idx_bytes = idx / CHAR_BIT;
	if(remaining >= (size_t)capacity)
	{
		int capacity_bytes = capacity / CHAR_BIT;
		memcpy(block + idx_bytes, input, capacity_bytes);
		mk_sha3_detail_process_block(c, block_size, state, block);
		input += capacity_bytes;
		remaining -= capacity;
		int block_size_bytes = block_size / CHAR_BIT;
		size_t blocks = remaining / block_size;
		for(size_t i = 0; i != blocks; ++i)
		{
			mk_sha3_detail_process_block(c, block_size, state, input);
			input += block_size_bytes;
		}
		remaining -= blocks * block_size;
		idx_bytes = 0;
	}
	MK_ASSERT(remaining < (size_t)block_size);
	int remaining_bytes = ((int)remaining + (CHAR_BIT - 1)) / CHAR_BIT;
	memcpy(block + idx_bytes, input, remaining_bytes);
	*block_idx = idx_bytes * CHAR_BIT + (int)remaining;
}

static inline void mk_sha3_detail_append_u(int c, int block_size, void* state, int* block_idx, void* block_, void const* data, size_t data_len_bits)
{
{
	MK_ASSERT((block_size % CHAR_BIT) == 0);
	MK_ASSERT(state);
	MK_ASSERT(block_idx);
	MK_ASSERT(*block_idx % CHAR_BIT != 0);
	MK_ASSERT(*block_idx < block_size);
	MK_ASSERT(block_);

	unsigned char* block = (unsigned char*)block_;
	unsigned char const* input = (unsigned char const*)data;

	size_t remaining = data_len_bits;

	int input_idx = 0;
	int idx = *block_idx;
	int capacity = block_size - idx;
	int idx_bytes = idx / CHAR_BIT;
	idx = idx % CHAR_BIT;
	if(remaining >= (size_t)capacity)
	{
		mk_sha3_detail_memcpy_bits(block + idx_bytes, idx, input, 0, capacity);
		mk_sha3_detail_process_block(c, block_size, state, block);
		input += capacity / CHAR_BIT;
		input_idx = capacity % CHAR_BIT;
		remaining -= capacity;
		int block_size_bytes = block_size / CHAR_BIT;
		size_t blocks = remaining / block_size;
		for(size_t i = 0; i != blocks; ++i)
		{
			mk_sha3_detail_memcpy_bits(block, 0, input, input_idx, block_size);
			mk_sha3_detail_process_block(c, block_size, state, block);
			input += block_size_bytes;
		}
		remaining -= blocks * block_size;
		idx_bytes = 0;
		idx = 0;
	}
	MK_ASSERT(remaining < (size_t)block_size);
	mk_sha3_detail_memcpy_bits(block + idx_bytes, idx, input, input_idx, (int)remaining);
	*block_idx = idx_bytes * CHAR_BIT + (int)remaining;
}
}

static inline void mk_sha3_detail_append(int c, int block_size, void* state, int* block_idx, void* block, void const* data, size_t data_len_bits)
{
	MK_ASSERT((block_size % CHAR_BIT) == 0);
	MK_ASSERT(state);
	MK_ASSERT(block_idx);
	MK_ASSERT(block);

	bool aligned = *block_idx % CHAR_BIT == 0 ? true : false;
	if(aligned)
	{
		mk_sha3_detail_append_a(c, block_size, state, block_idx, block, data, data_len_bits);
	}
	else
	{
		mk_sha3_detail_append_u(c, block_size, state, block_idx, block, data, data_len_bits);
	}
}

static inline void mk_sha3_detail_finish(enum mk_sha3_detail_domain_e domain, int c, int block_size, int d, void* state, int* block_idx, void* block, void* z)
{
	MK_ASSERT(state);
	MK_ASSERT(block_idx);
	MK_ASSERT(*block_idx < block_size);
	MK_ASSERT(block);
	MK_ASSERT(z);

	int b = 1600;
	/*int w = mk_sha3_detail_b2w(b);*/
	int r = b - c;

	mk_sha3_detail_keccak_pad(domain, block_size, state, block_idx, block);
	mk_sha3_detail_process_block(c, block_size, state, block);

	int z_idx = 0;
	for(;;)
	{
		int max_copy = r < (d - z_idx) ? r : (d - z_idx);
		for(int i = 0; i != max_copy; ++i)
		{
			bool bit = mk_sha3_detail_string_get_bit(state, i);
			mk_sha3_detail_string_set_bit(z, z_idx + i, bit);
		}
		z_idx += max_copy;
		if(z_idx == d)
		{
			break;
		}
		mk_sha3_detail_keccak_f(b, state);
	}
}


void mk_sha3_224_init(struct mk_sha3_224_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_224_append(struct mk_sha3_224_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(448, sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_224_finish(struct mk_sha3_224_state_s* self, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(mk_sha3_detail_domain_e_sha3, 448, sizeof(self->m_block) * CHAR_BIT, 224, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_256_init(struct mk_sha3_256_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_256_append(struct mk_sha3_256_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(512, sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_256_finish(struct mk_sha3_256_state_s* self, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(mk_sha3_detail_domain_e_sha3, 512, sizeof(self->m_block) * CHAR_BIT, 256, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_384_init(struct mk_sha3_384_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_384_append(struct mk_sha3_384_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(768, sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_384_finish(struct mk_sha3_384_state_s* self, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(mk_sha3_detail_domain_e_sha3, 768, sizeof(self->m_block) * CHAR_BIT, 384, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_512_init(struct mk_sha3_512_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_512_append(struct mk_sha3_512_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(1024, sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_512_finish(struct mk_sha3_512_state_s* self, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(mk_sha3_detail_domain_e_sha3, 1024, sizeof(self->m_block) * CHAR_BIT, 512, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_shake_128_init(struct mk_sha3_shake_128_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_shake_128_append(struct mk_sha3_shake_128_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(256, sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_shake_128_finish(struct mk_sha3_shake_128_state_s* self, int digest_len_bits, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(mk_sha3_detail_domain_e_shake, 256, sizeof(self->m_block) * CHAR_BIT, digest_len_bits, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_shake_256_init(struct mk_sha3_shake_256_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_shake_256_append(struct mk_sha3_shake_256_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(512, sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_shake_256_finish(struct mk_sha3_shake_256_state_s* self, int digest_len_bits, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(mk_sha3_detail_domain_e_shake, 512, sizeof(self->m_block) * CHAR_BIT, digest_len_bits, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_raw_shake_128_init(struct mk_sha3_raw_shake_128_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_raw_shake_128_append(struct mk_sha3_raw_shake_128_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(256, sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_raw_shake_128_finish(struct mk_sha3_raw_shake_128_state_s* self, int digest_len_bits, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(mk_sha3_detail_domain_e_raw_shake, 256, sizeof(self->m_block) * CHAR_BIT, digest_len_bits, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_raw_shake_256_init(struct mk_sha3_raw_shake_256_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_raw_shake_256_append(struct mk_sha3_raw_shake_256_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(512, sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_raw_shake_256_finish(struct mk_sha3_raw_shake_256_state_s* self, int digest_len_bits, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(mk_sha3_detail_domain_e_raw_shake, 512, sizeof(self->m_block) * CHAR_BIT, digest_len_bits, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_224_bits(void const* msg, size_t msg_len_bits, void* digest)
{
	MK_ASSERT(digest);

	struct mk_sha3_224_state_s state;

	mk_sha3_224_init(&state);
	mk_sha3_224_append(&state, msg, msg_len_bits);
	mk_sha3_224_finish(&state, digest);
}

void mk_sha3_256_bits(void const* msg, size_t msg_len_bits, void* digest)
{
	MK_ASSERT(digest);

	struct mk_sha3_256_state_s state;

	mk_sha3_256_init(&state);
	mk_sha3_256_append(&state, msg, msg_len_bits);
	mk_sha3_256_finish(&state, digest);
}

void mk_sha3_384_bits(void const* msg, size_t msg_len_bits, void* digest)
{
	MK_ASSERT(digest);

	struct mk_sha3_384_state_s state;

	mk_sha3_384_init(&state);
	mk_sha3_384_append(&state, msg, msg_len_bits);
	mk_sha3_384_finish(&state, digest);
}

void mk_sha3_512_bits(void const* msg, size_t msg_len_bits, void* digest)
{
	MK_ASSERT(digest);

	struct mk_sha3_512_state_s state;

	mk_sha3_512_init(&state);
	mk_sha3_512_append(&state, msg, msg_len_bits);
	mk_sha3_512_finish(&state, digest);
}

void mk_sha3_shake_128_bits(void const* msg, size_t msg_len_bits, int digest_len_bits, void* digest)
{
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	struct mk_sha3_shake_128_state_s state;

	mk_sha3_shake_128_init(&state);
	mk_sha3_shake_128_append(&state, msg, msg_len_bits);
	mk_sha3_shake_128_finish(&state, digest_len_bits, digest);
}

void mk_sha3_shake_256_bits(void const* msg, size_t msg_len_bits, int digest_len_bits, void* digest)
{
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	struct mk_sha3_shake_256_state_s state;

	mk_sha3_shake_256_init(&state);
	mk_sha3_shake_256_append(&state, msg, msg_len_bits);
	mk_sha3_shake_256_finish(&state, digest_len_bits, digest);
}

void mk_sha3_raw_shake_128_bits(void const* msg, size_t msg_len_bits, int digest_len_bits, void* digest)
{
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	struct mk_sha3_raw_shake_128_state_s state;

	mk_sha3_raw_shake_128_init(&state);
	mk_sha3_raw_shake_128_append(&state, msg, msg_len_bits);
	mk_sha3_raw_shake_128_finish(&state, digest_len_bits, digest);
}

void mk_sha3_raw_shake_256_bits(void const* msg, size_t msg_len_bits, int digest_len_bits, void* digest)
{
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	struct mk_sha3_raw_shake_256_state_s state;

	mk_sha3_raw_shake_256_init(&state);
	mk_sha3_raw_shake_256_append(&state, msg, msg_len_bits);
	mk_sha3_raw_shake_256_finish(&state, digest_len_bits, digest);
}


void mk_sha3_224(void const* msg, size_t msg_len_bytes, void* digest)
{
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);
	MK_ASSERT(digest);
	
	mk_sha3_224_bits(msg, msg_len_bytes * CHAR_BIT, digest);
}

void mk_sha3_256(void const* msg, size_t msg_len_bytes, void* digest)
{
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);
	MK_ASSERT(digest);
	
	mk_sha3_256_bits(msg, msg_len_bytes * CHAR_BIT, digest);
}

void mk_sha3_384(void const* msg, size_t msg_len_bytes, void* digest)
{
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);
	MK_ASSERT(digest);
	
	mk_sha3_384_bits(msg, msg_len_bytes * CHAR_BIT, digest);
}

void mk_sha3_512(void const* msg, size_t msg_len_bytes, void* digest)
{
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);
	MK_ASSERT(digest);
	
	mk_sha3_512_bits(msg, msg_len_bytes * CHAR_BIT, digest);
}

void mk_sha3_shake_128(void const* msg, size_t msg_len_bytes, int digest_len_bits, void* digest)
{
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);
	
	mk_sha3_shake_128_bits(msg, msg_len_bytes * CHAR_BIT, digest_len_bits, digest);
}

void mk_sha3_shake_256(void const* msg, size_t msg_len_bytes, int digest_len_bits, void* digest)
{
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);
	
	mk_sha3_shake_256_bits(msg, msg_len_bytes * CHAR_BIT, digest_len_bits, digest);
}

void mk_sha3_raw_shake_128(void const* msg, size_t msg_len_bytes, int digest_len_bits, void* digest)
{
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);
	
	mk_sha3_raw_shake_128_bits(msg, msg_len_bytes * CHAR_BIT, digest_len_bits, digest);
}

void mk_sha3_raw_shake_256(void const* msg, size_t msg_len_bytes, int digest_len_bits, void* digest)
{
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);
	
	mk_sha3_raw_shake_256_bits(msg, msg_len_bytes * CHAR_BIT, digest_len_bits, digest);
}
