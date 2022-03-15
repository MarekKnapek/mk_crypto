#include "mk_sha3.h"

#include "mk_assert.h"

#include "../mk_int/src/exact/mk_uint_64.h"

#include <assert.h> /* static_assert */
#include <limits.h> /* CHAR_BIT SIZE_MAX */
#include <stdbool.h> /* bool true false */ /* C99 */
#include <string.h> /* memcpy memset */


static_assert(CHAR_BIT == 8, "Must have 8bit byte.");


struct mk_sha3_detail_state_s
{
	struct mk_uint64_s m_data[5][5];
};


static inline struct mk_uint64_s mk_sha3_binary_le_to_uint64(void const* binary)
{
	struct mk_uint64_s ret;

	mk_uint64_from_buff_le(&ret, binary);

	return ret;
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
	output[byte] = (output[byte] & ~(1u << bit)) | (val ? (1u << bit) : 0u);
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
			bool bit = mk_sha3_detail_string_get_bit(input + i / CHAR_BIT, src_bit_offset + i % CHAR_BIT);
			mk_sha3_detail_string_set_bit(output + i / CHAR_BIT, dst_bit_offset + i % CHAR_BIT, bit);
		}
	}
}

static inline int mk_sha3_detail_mod(int m, int n)
{
	MK_ASSERT(n > 0);

	int r;

	r = m % n;
	r = r < 0 ? r + n : r;

	return r;
}

static inline void mk_sha3_detail_theta(struct mk_sha3_detail_state_s* state)
{
	MK_ASSERT(state);

	struct mk_uint64_s c[5];
	for(int x = 0; x != 5; ++x)
	{
		c[x] = state->m_data[0][x];
		for(int y = 1; y != 5; ++y)
		{
			mk_uint64_xor(&c[x], &c[x], &state->m_data[y][x]);
		}
	}

	struct mk_uint64_s d[5];
	for(int x = 0; x != 5; ++x)
	{
		struct mk_uint64_s tmp;
		mk_uint64_rotl(&tmp, &c[(x + 1) % 5], 1);
		mk_uint64_xor(&d[x], &c[(x + 4) % 5], &tmp);
	}

	for(int y = 0; y != 5; ++y)
	{
		for(int x = 0; x != 5; ++x)
		{
			mk_uint64_xor(&state->m_data[y][x], &state->m_data[y][x], &d[x]);
		}
	}
}

static inline void mk_sha3_detail_rho(struct mk_sha3_detail_state_s* state)
{
	MK_ASSERT(state);

	int x = 1;
	int y = 0;
	for(int t = 0; t != 24; ++t)
	{
		mk_uint64_rotl(&state->m_data[y][x], &state->m_data[y][x], (((t + 1) * (t + 2)) / 2) % 64);
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
			struct mk_uint64_s tmp;
			mk_uint64_cmplmnt(&tmp, &in->m_data[y][(x + 1) % 5]);
			mk_uint64_and(&tmp, &tmp, &in->m_data[y][(x + 2) % 5]);
			mk_uint64_xor(&out->m_data[y][x], &in->m_data[y][x], &tmp);
		}
	}
}

static inline struct mk_uint64_s mk_sha3_detail_rc_next_bit(unsigned* rc)
{
	MK_ASSERT(rc);

	struct mk_uint64_s ret;
	unsigned r = *rc;
	mk_uint64_from_int(&ret, r & 0x01);

	r <<= 1;
	r = (r & ~(1u << 0)) | ((((r >> 0) & 0x1) ^ ((r >> 8) & 0x1)) << 0);
	r = (r & ~(1u << 4)) | ((((r >> 4) & 0x1) ^ ((r >> 8) & 0x1)) << 4);
	r = (r & ~(1u << 5)) | ((((r >> 5) & 0x1) ^ ((r >> 8) & 0x1)) << 5);
	r = (r & ~(1u << 6)) | ((((r >> 6) & 0x1) ^ ((r >> 8) & 0x1)) << 6);

	*rc = r;

	return ret;
}

static inline struct mk_uint64_s mk_sha3_detail_rc_next_num(unsigned* rc)
{
	MK_ASSERT(rc);

	struct mk_uint64_s rc_num;
	mk_uint64_zero(&rc_num);

	{ struct mk_uint64_s tmp; tmp = mk_sha3_detail_rc_next_bit(rc); mk_uint64_shl(&tmp, &tmp,  0); mk_uint64_or(&rc_num, &rc_num, &tmp); }
	{ struct mk_uint64_s tmp; tmp = mk_sha3_detail_rc_next_bit(rc); mk_uint64_shl(&tmp, &tmp,  1); mk_uint64_or(&rc_num, &rc_num, &tmp); }
	{ struct mk_uint64_s tmp; tmp = mk_sha3_detail_rc_next_bit(rc); mk_uint64_shl(&tmp, &tmp,  3); mk_uint64_or(&rc_num, &rc_num, &tmp); }
	{ struct mk_uint64_s tmp; tmp = mk_sha3_detail_rc_next_bit(rc); mk_uint64_shl(&tmp, &tmp,  7); mk_uint64_or(&rc_num, &rc_num, &tmp); }
	{ struct mk_uint64_s tmp; tmp = mk_sha3_detail_rc_next_bit(rc); mk_uint64_shl(&tmp, &tmp, 15); mk_uint64_or(&rc_num, &rc_num, &tmp); }
	{ struct mk_uint64_s tmp; tmp = mk_sha3_detail_rc_next_bit(rc); mk_uint64_shl(&tmp, &tmp, 31); mk_uint64_or(&rc_num, &rc_num, &tmp); }
	{ struct mk_uint64_s tmp; tmp = mk_sha3_detail_rc_next_bit(rc); mk_uint64_shl(&tmp, &tmp, 63); mk_uint64_or(&rc_num, &rc_num, &tmp); }

	return rc_num;
}

static inline void mk_sha3_detail_iota(struct mk_sha3_detail_state_s* state, unsigned* rc)
{
	MK_ASSERT(state);
	MK_ASSERT(rc);

	struct mk_uint64_s rc_num = mk_sha3_detail_rc_next_num(rc);

	mk_uint64_xor(&state->m_data[0][0], &state->m_data[0][0], &rc_num);
}

static inline void mk_sha3_detail_rnd(struct mk_sha3_detail_state_s* state, unsigned* rc)
{
	MK_ASSERT(state);
	MK_ASSERT(rc);

	struct mk_sha3_detail_state_s tmp;

	mk_sha3_detail_theta(state);
	mk_sha3_detail_rho(state);
	mk_sha3_detail_pi(state, &tmp);
	mk_sha3_detail_chi(&tmp, state);
	mk_sha3_detail_iota(state, rc);
}

static inline void mk_sha3_detail_keccak_p(void* s)
{
	MK_ASSERT(s);

	struct mk_sha3_detail_state_s* state = (struct mk_sha3_detail_state_s*)s;
	unsigned rc = 1;

	for(int ir = 0; ir != 24; ++ir)
	{
		mk_sha3_detail_rnd(state, &rc);
	}
}

static inline void mk_sha3_detail_keccak_f(void* s)
{
	MK_ASSERT(s);

	mk_sha3_detail_keccak_p(s);
}

static inline void mk_sha3_detail_mix_block(int block_size, void* s, void const* block)
{
	MK_ASSERT(block_size % CHAR_BIT == 0);
	MK_ASSERT(block_size % (CHAR_BIT * sizeof(struct mk_uint64_s)) == 0);
	MK_ASSERT(s);
	MK_ASSERT(block);

	struct mk_uint64_s* state = (struct mk_uint64_s*)s;
	unsigned char const* input = (unsigned char const*)block;

	int block_item_count = block_size / (CHAR_BIT * sizeof(struct mk_uint64_s));
	for(int i = 0; i != block_item_count; ++i)
	{
		struct mk_uint64_s tmp;
		tmp = mk_sha3_binary_le_to_uint64(input);
		mk_uint64_xor(&state[i], &state[i], &tmp);
		input += sizeof(struct mk_uint64_s);
	}
}

static inline void mk_sha3_detail_process_block(int block_size, void* state, void const* block)
{
	MK_ASSERT(state);
	MK_ASSERT(block);

	mk_sha3_detail_mix_block(block_size, state, block);
	mk_sha3_detail_keccak_f(state);
}

static inline void mk_sha3_detail_init(struct mk_uint64_s* state, int* idx)
{
	MK_ASSERT(state);
	MK_ASSERT(idx);

	memset(state, 0, 25 * sizeof(struct mk_uint64_s));
	*idx = 0;
}

static inline void mk_sha3_detail_append_a(int block_size, void* state, int* block_idx, void* block_, void const* data, size_t data_len_bits)
{
	MK_ASSERT((block_size % CHAR_BIT) == 0);
	MK_ASSERT((block_size % (sizeof(struct mk_uint64_s) * CHAR_BIT)) == 0);
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
		mk_sha3_detail_process_block(block_size, state, block);
		input += capacity_bytes;
		remaining -= capacity;
		int block_size_bytes = block_size / CHAR_BIT;
		size_t blocks = remaining / block_size;
		for(size_t i = 0; i != blocks; ++i)
		{
			mk_sha3_detail_process_block(block_size, state, input);
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

static inline void mk_sha3_detail_append_u(int block_size, void* state, int* block_idx, void* block_, void const* data, size_t data_len_bits)
{
	MK_ASSERT((block_size % CHAR_BIT) == 0);
	MK_ASSERT((block_size % (sizeof(struct mk_uint64_s) * CHAR_BIT)) == 0);
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
		mk_sha3_detail_process_block(block_size, state, block);
		input += capacity / CHAR_BIT;
		input_idx = capacity % CHAR_BIT;
		remaining -= capacity;
		int block_size_bytes = block_size / CHAR_BIT;
		size_t blocks = remaining / block_size;
		for(size_t i = 0; i != blocks; ++i)
		{
			mk_sha3_detail_memcpy_bits(block, 0, input, input_idx, block_size);
			mk_sha3_detail_process_block(block_size, state, block);
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

static inline void mk_sha3_detail_append(int block_size, void* state, int* block_idx, void* block, void const* data, size_t data_len_bits)
{
	MK_ASSERT((block_size % CHAR_BIT) == 0);
	MK_ASSERT((block_size % (sizeof(struct mk_uint64_s) * CHAR_BIT)) == 0);
	MK_ASSERT(state);
	MK_ASSERT(block_idx);
	MK_ASSERT(block);

	bool aligned = *block_idx % CHAR_BIT == 0 ? true : false;
	if(aligned)
	{
		mk_sha3_detail_append_a(block_size, state, block_idx, block, data, data_len_bits);
	}
	else
	{
		mk_sha3_detail_append_u(block_size, state, block_idx, block, data, data_len_bits);
	}
}

enum mk_sha3_detail_domain_e
{
	mk_sha3_detail_domain_e_sha3,
	mk_sha3_detail_domain_e_shake,
	mk_sha3_detail_domain_e_raw_shake,
};

static inline void mk_sha3_detail_pad(int block_size, enum mk_sha3_detail_domain_e domain, void* state, int* block_idx, void* block_)
{
	MK_ASSERT(state);
	MK_ASSERT(block_idx);
	MK_ASSERT(*block_idx < block_size);
	MK_ASSERT(block_);

	union
	{
		struct mk_uint64_s m_words[21];
		unsigned char m_bytes[21 * sizeof(struct mk_uint64_s) + 1];
	} padding;
	memset(&padding.m_bytes, 0, sizeof(padding.m_bytes));

	unsigned char suffix;
	int suffix_bits;

	switch(domain)
	{
		case mk_sha3_detail_domain_e_sha3:
		{
			suffix = 0x06;
			suffix_bits = 3;
		}
		break;
		case mk_sha3_detail_domain_e_shake:
		{
			suffix = 0x1f;
			suffix_bits = 5;
		}
		break;
		case mk_sha3_detail_domain_e_raw_shake:
		{
			suffix = 0x07;
			suffix_bits = 3;
		}
		break;
		default:
		{
			/* To silence warning. */
			suffix = 0; 
			suffix_bits = 0;
			MK_ASSERT(0);
		}
		break;
	}

	padding.m_bytes[0] = suffix;

	int capacity = block_size - *block_idx;
	int bits = capacity < suffix_bits + 1 ? capacity + block_size : capacity;
	mk_sha3_detail_string_set_bit(padding.m_bytes, bits - 1, true);

	mk_sha3_detail_append(block_size, state, block_idx, block_, padding.m_bytes, bits);
}

static inline void mk_sha3_detail_finish(int block_size, enum mk_sha3_detail_domain_e domain, int d, void* state, int* block_idx, void* block, void* z)
{
	MK_ASSERT((block_size % CHAR_BIT) == 0);
	MK_ASSERT((block_size % (sizeof(struct mk_uint64_s) * CHAR_BIT)) == 0);
	MK_ASSERT(d > 0);
	MK_ASSERT(state);
	MK_ASSERT(block_idx);
	MK_ASSERT(*block_idx < block_size);
	MK_ASSERT(block);
	MK_ASSERT(z);

	mk_sha3_detail_pad(block_size, domain, state, block_idx, block);

	int block_size_bytes = block_size / CHAR_BIT;
	unsigned char* output = (unsigned char*)z;

	int to_copy_bits = d > block_size ? block_size : d;
	int to_copy_bytes = (to_copy_bits + (CHAR_BIT - 1)) / CHAR_BIT;
	memcpy(output, state, to_copy_bytes);
	output += to_copy_bytes;
	int remaining_bits = d - to_copy_bits;

	int remaining_bytes = (remaining_bits + (CHAR_BIT - 1)) / CHAR_BIT;
	int blocks_count = remaining_bytes / block_size_bytes;
	for(int i = 0; i != blocks_count; ++i)
	{
		mk_sha3_detail_keccak_f(state);
		memcpy(output, state, block_size_bytes);
		output += block_size_bytes;
	}
	remaining_bytes -= blocks_count * block_size_bytes;
	if(remaining_bytes != 0)
	{
		mk_sha3_detail_keccak_f(state);
		memcpy(output, state, remaining_bytes);
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

	mk_sha3_detail_append(sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_224_append_bytes(struct mk_sha3_224_state_s* self, void const* msg, size_t msg_len_bytes)
{
	MK_ASSERT(self);
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);

	mk_sha3_224_append(self, msg, msg_len_bytes * CHAR_BIT);
}

void mk_sha3_224_finish(struct mk_sha3_224_state_s* self, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(sizeof(self->m_block) * CHAR_BIT, mk_sha3_detail_domain_e_sha3, 224, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_256_init(struct mk_sha3_256_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_256_append(struct mk_sha3_256_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_256_append_bytes(struct mk_sha3_256_state_s* self, void const* msg, size_t msg_len_bytes)
{
	MK_ASSERT(self);
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);

	mk_sha3_256_append(self, msg, msg_len_bytes * CHAR_BIT);
}

void mk_sha3_256_finish(struct mk_sha3_256_state_s* self, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(sizeof(self->m_block) * CHAR_BIT, mk_sha3_detail_domain_e_sha3, 256, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_384_init(struct mk_sha3_384_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_384_append(struct mk_sha3_384_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_384_append_bytes(struct mk_sha3_384_state_s* self, void const* msg, size_t msg_len_bytes)
{
	MK_ASSERT(self);
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);

	mk_sha3_384_append(self, msg, msg_len_bytes * CHAR_BIT);
}

void mk_sha3_384_finish(struct mk_sha3_384_state_s* self, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(sizeof(self->m_block) * CHAR_BIT, mk_sha3_detail_domain_e_sha3, 384, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_512_init(struct mk_sha3_512_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_512_append(struct mk_sha3_512_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_512_append_bytes(struct mk_sha3_512_state_s* self, void const* msg, size_t msg_len_bytes)
{
	MK_ASSERT(self);
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);

	mk_sha3_512_append(self, msg, msg_len_bytes * CHAR_BIT);
}

void mk_sha3_512_finish(struct mk_sha3_512_state_s* self, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(sizeof(self->m_block) * CHAR_BIT, mk_sha3_detail_domain_e_sha3, 512, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_shake_128_init(struct mk_sha3_shake_128_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_shake_128_append(struct mk_sha3_shake_128_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_shake_128_append_bytes(struct mk_sha3_shake_128_state_s* self, void const* msg, size_t msg_len_bytes)
{
	MK_ASSERT(self);
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);

	mk_sha3_shake_128_append(self, msg, msg_len_bytes * CHAR_BIT);
}

void mk_sha3_shake_128_finish(struct mk_sha3_shake_128_state_s* self, int digest_len_bits, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(sizeof(self->m_block) * CHAR_BIT, mk_sha3_detail_domain_e_shake, digest_len_bits, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_shake_256_init(struct mk_sha3_shake_256_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_shake_256_append(struct mk_sha3_shake_256_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_shake_256_append_bytes(struct mk_sha3_shake_256_state_s* self, void const* msg, size_t msg_len_bytes)
{
	MK_ASSERT(self);
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);

	mk_sha3_shake_256_append(self, msg, msg_len_bytes * CHAR_BIT);
}

void mk_sha3_shake_256_finish(struct mk_sha3_shake_256_state_s* self, int digest_len_bits, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(sizeof(self->m_block) * CHAR_BIT, mk_sha3_detail_domain_e_shake, digest_len_bits, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_raw_shake_128_init(struct mk_sha3_raw_shake_128_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_raw_shake_128_append(struct mk_sha3_raw_shake_128_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_raw_shake_128_append_bytes(struct mk_sha3_raw_shake_128_state_s* self, void const* msg, size_t msg_len_bytes)
{
	MK_ASSERT(self);
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);

	mk_sha3_raw_shake_128_append(self, msg, msg_len_bytes * CHAR_BIT);
}

void mk_sha3_raw_shake_128_finish(struct mk_sha3_raw_shake_128_state_s* self, int digest_len_bits, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(sizeof(self->m_block) * CHAR_BIT, mk_sha3_detail_domain_e_raw_shake, digest_len_bits, self->m_state, &self->m_idx, self->m_block, digest);
}


void mk_sha3_raw_shake_256_init(struct mk_sha3_raw_shake_256_state_s* self)
{
	MK_ASSERT(self);

	mk_sha3_detail_init(self->m_state, &self->m_idx);
}

void mk_sha3_raw_shake_256_append(struct mk_sha3_raw_shake_256_state_s* self, void const* msg, size_t msg_len_bits)
{
	MK_ASSERT(self);

	mk_sha3_detail_append(sizeof(self->m_block) * CHAR_BIT, self->m_state, &self->m_idx, self->m_block, msg, msg_len_bits);
}

void mk_sha3_raw_shake_256_append_bytes(struct mk_sha3_raw_shake_256_state_s* self, void const* msg, size_t msg_len_bytes)
{
	MK_ASSERT(self);
	MK_ASSERT(msg_len_bytes <= SIZE_MAX / CHAR_BIT);

	mk_sha3_raw_shake_256_append(self, msg, msg_len_bytes * CHAR_BIT);
}

void mk_sha3_raw_shake_256_finish(struct mk_sha3_raw_shake_256_state_s* self, int digest_len_bits, void* digest)
{
	MK_ASSERT(self);
	MK_ASSERT(digest_len_bits > 0);
	MK_ASSERT(digest);

	mk_sha3_detail_finish(sizeof(self->m_block) * CHAR_BIT, mk_sha3_detail_domain_e_raw_shake, digest_len_bits, self->m_state, &self->m_idx, self->m_block, digest);
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
