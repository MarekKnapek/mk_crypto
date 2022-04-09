#include "mk_sha3_detail.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include "../../mk_int/src/exact/mk_uint_64.h"

#include <string.h> /* memcpy memset */


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4701) /* warning C4701: potentially uninitialized local variable 'xxx' used */
#pragma warning(disable:4710)/* warning C4710: 'xxx': function not inlined */
#pragma warning(disable:4711) /* warning C4711: function 'xxx' selected for automatic inline expansion */
#pragma warning(disable:5045) /* warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified6 */
#endif


static mk_inline int mk_sha3_detail_string_bit_get(void const* str, int byte_idx, int bit_idx)
{
	unsigned char const* input;
	int byte_offset;
	int bit_offset;
	int bit;

	mk_assert(str);
	mk_assert(byte_idx >= 0);
	mk_assert(bit_idx >= 0);

	input = (unsigned char const*)str;
	byte_offset = byte_idx + bit_idx / CHAR_BIT;
	bit_offset = bit_idx % CHAR_BIT;

	bit = (input[byte_offset] >> bit_offset) & 0x01;
	return bit;
}

static mk_inline void mk_sha3_detail_string_bit_set(void const* str, int byte_idx, int bit_idx, int bit)
{
	unsigned char* output;
	int byte_offset;
	int bit_offset;

	mk_assert(str);
	mk_assert(byte_idx >= 0);
	mk_assert(bit_idx >= 0);
	mk_assert(bit == 0 || bit == 1);

	output = (unsigned char*)str;
	byte_offset = byte_idx + bit_idx / CHAR_BIT;
	bit_offset = bit_idx % CHAR_BIT;

	output[byte_offset] = (output[byte_offset] & ~((unsigned char)1u << bit_offset)) | ((unsigned char)bit << bit_offset);
}

static mk_inline void mk_sha3_detail_memcpy_bits(void* dst, int dst_idx_bits, void const* src, int src_idx_bits, int count_bits)
{
	unsigned char* output;
	unsigned char const* input;
	int dst_idx_bytes;
	int src_idx_bytes;
	int count_bytes;
	int i;
	int bit;

	mk_assert(dst);
	mk_assert(dst_idx_bits >= 0);
	mk_assert(src);
	mk_assert(src_idx_bits >= 0);
	mk_assert(count_bits >= 0);

	output = (unsigned char*)dst;
	input = (unsigned char const*)src;
	dst_idx_bytes = dst_idx_bits / CHAR_BIT;
	src_idx_bytes = src_idx_bits / CHAR_BIT;
	dst_idx_bits = dst_idx_bits % CHAR_BIT;
	src_idx_bits = src_idx_bits % CHAR_BIT;
	output += dst_idx_bytes;
	input += src_idx_bytes;
	if(dst_idx_bits == 0 && src_idx_bits == 0)
	{
		count_bytes = count_bits / CHAR_BIT;
		memcpy(output, input, count_bytes);
		input += count_bytes;
		output += count_bytes;
		count_bits = count_bits % CHAR_BIT;
		for(i = 0; i != count_bits; ++i)
		{
			bit = mk_sha3_detail_string_bit_get(input, 0, i);
			mk_sha3_detail_string_bit_set(output, 0, i, bit);
		}
	}
	else
	{
		for(i = 0; i != count_bits; ++i)
		{
			bit = mk_sha3_detail_string_bit_get(input, 0, src_idx_bits + i);
			mk_sha3_detail_string_bit_set(output, 0, dst_idx_bits + i, bit);
		}
	}
}

static mk_inline void mk_sha3_detail_theta(struct mk_uint64_s state[5][5])
{
	struct mk_uint64_s c[5];
	struct mk_uint64_s d[5];
	struct mk_uint64_s tmp_1;
	struct mk_uint64_s tmp_2;
	int x;
	int y;

	mk_assert(state);

	for(x = 0; x != 5; ++x)
	{
		mk_uint64_xor(&tmp_1, &state[0][x], &state[1][x]);
		mk_uint64_xor(&tmp_2, &state[2][x], &state[3][x]);
		mk_uint64_xor(&tmp_1, &tmp_1, &tmp_2);
		mk_uint64_xor(&c[x], &tmp_1, &state[4][x]);
	}
	for(x = 0; x != 5; ++x)
	{
		mk_uint64_rotl(&tmp_1, &c[(x + 1) % 5], 1);
		mk_uint64_xor(&d[x], &c[(x + 4) % 5], &tmp_1);
	}
	for(y = 0; y != 5; ++y)
	{
		for(x = 0; x != 5; ++x)
		{
			mk_uint64_xor(&state[y][x], &state[y][x], &d[x]);
		}
	}
}

static mk_inline void mk_sha3_detail_rho(struct mk_uint64_s state[5][5])
{
	int x;
	int y;
	int t;
	int old_x;

	mk_assert(state);

	x = 1;
	y = 0;
	for(t = 0; t != 24; ++t)
	{
		mk_uint64_rotl(&state[y][x], &state[y][x], (((t + 1) * (t + 2)) / 2) % 64);
		old_x = x;
		x = y;
		y = (2 * old_x + 3 * y) % 5;
	}
}

static mk_inline void mk_sha3_detail_pi(struct mk_uint64_s in[5][5], struct mk_uint64_s out[5][5])
{
	int x;
	int y;
	int target_x;
	int target_y;

	mk_assert(in);
	mk_assert(out);
	mk_assert(in != out);

	for(y = 0; y != 5; ++y)
	{
		for(x = 0; x != 5; ++x)
		{
			target_x = y;
			target_y = (2 * x + 3 * y) % 5;
			out[target_y][target_x] = in[y][x];
		}
	}
}

static mk_inline void mk_sha3_detail_chi(struct mk_uint64_s in[5][5], struct mk_uint64_s out[5][5])
{
	int y;
	int x;
	struct mk_uint64_s tmp;

	mk_assert(in);
	mk_assert(out);
	mk_assert(in != out);

	for(y = 0; y != 5; ++y)
	{
		for(x = 0; x != 5; ++x)
		{
			mk_uint64_cmplmnt(&tmp, &in[y][(x + 1) % 5]);
			mk_uint64_and(&tmp, &tmp, &in[y][(x + 2) % 5]);
			mk_uint64_xor(&out[y][x], &in[y][x], &tmp);
		}
	}
}

static mk_inline unsigned mk_sha3_detail_rc_next_bit(unsigned* rc)
{
	unsigned ret;
	unsigned r;

	mk_assert(rc);

	r = *rc;
	ret = r & 0x01;

	r <<= 1;
	r = (r & ~(1u << 0)) | ((((r >> 0) & 0x1) ^ ((r >> 8) & 0x1)) << 0);
	r = (r & ~(1u << 4)) | ((((r >> 4) & 0x1) ^ ((r >> 8) & 0x1)) << 4);
	r = (r & ~(1u << 5)) | ((((r >> 5) & 0x1) ^ ((r >> 8) & 0x1)) << 5);
	r = (r & ~(1u << 6)) | ((((r >> 6) & 0x1) ^ ((r >> 8) & 0x1)) << 6);

	*rc = r;

	return ret;
}

static mk_inline void mk_sha3_detail_rc_next_num(struct mk_uint64_s* out, unsigned* rc)
{
	struct mk_uint64_s tmp;

	mk_assert(out);
	mk_assert(rc);

	mk_uint64_zero(out);
	mk_uint64_from_int(&tmp, mk_sha3_detail_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp,  0); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_sha3_detail_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp,  1); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_sha3_detail_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp,  3); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_sha3_detail_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp,  7); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_sha3_detail_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp, 15); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_sha3_detail_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp, 31); mk_uint64_or(out, out, &tmp);
	mk_uint64_from_int(&tmp, mk_sha3_detail_rc_next_bit(rc)); mk_uint64_shl(&tmp, &tmp, 63); mk_uint64_or(out, out, &tmp);
}

static mk_inline void mk_sha3_detail_iota(struct mk_uint64_s state[5][5], unsigned* rc)
{
	struct mk_uint64_s rc_num;

	mk_assert(state);
	mk_assert(rc);

	mk_sha3_detail_rc_next_num(&rc_num, rc);
	mk_uint64_xor(&state[0][0], &state[0][0], &rc_num);
}

static mk_inline void mk_sha3_detail_rnd(struct mk_uint64_s state[5][5], unsigned* rc)
{
	struct mk_uint64_s tmp[5][5];

	mk_assert(state);
	mk_assert(rc);

	mk_sha3_detail_theta(state);
	mk_sha3_detail_rho(state);
	mk_sha3_detail_pi(state, tmp);
	mk_sha3_detail_chi(tmp, state);
	mk_sha3_detail_iota(state, rc);
}

static mk_inline void mk_sha3_detail_keccak_p(struct mk_uint64_s state[5][5])
{
	unsigned rc;
	int ir;

	mk_assert(state);

	rc = 1;
	for(ir = 0; ir != 24; ++ir)
	{
		mk_sha3_detail_rnd(state, &rc);
	}

}

static mk_inline void mk_sha3_detail_keccak_f(struct mk_uint64_s state[5][5])
{
	mk_assert(state);

	mk_sha3_detail_keccak_p(state);
}

static mk_inline void mk_sha3_detail_mix_block(struct mk_uint64_s state[5][5], unsigned char const* block, int block_len_bits)
{
	#define element_size 8

	int block_elements;
	int i;
	int y;
	int x;
	struct mk_uint64_s element;

	mk_assert(state);
	mk_assert(block);
	mk_assert(block_len_bits >= 0);

	block_elements = block_len_bits / CHAR_BIT / element_size;
	for(i = 0; i != block_elements; ++i)
	{
		y = i / 5;
		x = i % 5;
		mk_uint64_from_buff_le(&element, block + i * element_size);
		mk_uint64_xor(&state[y][x], &state[y][x], &element);
	}

	#undef element_size
}

static mk_inline void mk_sha3_detail_process_block(struct mk_uint64_s state[5][5], unsigned char const* block, int block_len_bits)
{
	mk_assert(state);
	mk_assert(block);
	mk_assert(block_len_bits >= 0);

	mk_sha3_detail_mix_block(state, block, block_len_bits);
	mk_sha3_detail_keccak_f(state);
}


static mk_inline void mk_sha3_detail_pad(struct mk_uint64_s state[5][5], int* idx, unsigned char* block, int block_len_bits, enum mk_sha3_detail_domain_e domain)
{
	unsigned char padding[169];
	unsigned char suffix;
	int suffix_bits;
	int capacity;
	int bits;

	mk_assert(state);
	mk_assert(idx);
	mk_assert(block);
	mk_assert(block_len_bits >= 0);
	mk_assert(domain >= mk_sha3_detail_domain_e_sha3 && domain <= mk_sha3_detail_domain_e_rawshake);

	memset(padding + 1, 0, sizeof(padding) - 1);
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
		case mk_sha3_detail_domain_e_rawshake:
		{
			suffix = 0x07;
			suffix_bits = 3;
		}
		break;
	}
	padding[0] = suffix;
	capacity = block_len_bits - *idx;
	bits = capacity < suffix_bits + 1 ? capacity + block_len_bits : capacity;
	mk_sha3_detail_string_bit_set(padding, 0, bits - 1, 1);

	mk_sha3_detail_append_bits(state, idx, block, block_len_bits, padding, bits);
}


void mk_sha3_detail_init(struct mk_uint64_s state[5][5], int* idx)
{
	int y;
	int x;
	
	mk_assert(state);
	mk_assert(idx);

	for(y = 0; y != 5; ++y)
	{
		for(x = 0; x != 5; ++x)
		{
			mk_uint64_zero(&state[y][x]);
		}
	}
	*idx = 0;
}

void mk_sha3_detail_append_bits(struct mk_uint64_s state[5][5], int* idx, unsigned char* block, int block_len_bits, void const* msg, size_t msg_len_bits)
{
	unsigned char const* input;
	int input_idx;
	size_t remaining;
	int capacity;
	int is_aligned;
	size_t blocks;
	size_t i;

	mk_assert(state);
	mk_assert(idx);
	mk_assert(block);
	mk_assert(block_len_bits % CHAR_BIT == 0);

	input = (unsigned char const*)msg;
	input_idx = 0;
	remaining = msg_len_bits;

	capacity = block_len_bits - *idx;
	if(remaining >= (size_t)capacity)
	{
		if(*idx != 0)
		{
			mk_sha3_detail_memcpy_bits(block, *idx, input, 0, capacity);
			mk_sha3_detail_process_block(state, block, block_len_bits);
			input += capacity / CHAR_BIT;
			input_idx = capacity % CHAR_BIT;
			remaining -= capacity;
		}
		is_aligned = input_idx == 0;
		if(is_aligned)
		{
			blocks = remaining / block_len_bits;
			for(i = 0; i != blocks; ++i)
			{
				mk_sha3_detail_process_block(state, input, block_len_bits);
				input += block_len_bits / CHAR_BIT;
			}
			remaining -= blocks * block_len_bits;
		}
		else
		{
			blocks = remaining / block_len_bits;
			for(i = 0; i != blocks; ++i)
			{
				mk_sha3_detail_memcpy_bits(block, 0, input, input_idx, capacity);
				mk_sha3_detail_process_block(state, input, block_len_bits);
				input += block_len_bits / CHAR_BIT;
			}
			remaining -= blocks * block_len_bits;
		}
		*idx = 0;
	}
	mk_sha3_detail_memcpy_bits(block, *idx, input, input_idx, (int)remaining);
	*idx += (int)remaining;
}

void mk_sha3_detail_finish(struct mk_uint64_s state[5][5], int* idx, unsigned char* block, int block_len_bits, enum mk_sha3_detail_domain_e domain, void* digest, size_t digest_len_bits)
{
	unsigned char* output;
	size_t remaining_bits;
	int to_copy_bits;
	size_t blocks;
	size_t i;

	mk_assert(state);
	mk_assert(idx);
	mk_assert(block);
	mk_assert(block_len_bits >= 0);
	mk_assert(domain >= mk_sha3_detail_domain_e_sha3 && domain <= mk_sha3_detail_domain_e_rawshake);
	mk_assert(digest);

	mk_sha3_detail_pad(state, idx, block, block_len_bits, domain);

	output = (unsigned char*)digest;
	output[(digest_len_bits - 1) / CHAR_BIT] = 0;
	remaining_bits = digest_len_bits;
	to_copy_bits = remaining_bits < (size_t)block_len_bits ? (int)remaining_bits : block_len_bits;
	mk_sha3_detail_memcpy_bits(output, 0, state, 0, to_copy_bits);
	remaining_bits -= to_copy_bits;
	output += to_copy_bits / CHAR_BIT;

	blocks = remaining_bits / block_len_bits;
	for(i = 0; i != blocks; ++i)
	{
		mk_sha3_detail_keccak_f(state);
		mk_sha3_detail_memcpy_bits(output, 0, state, 0, block_len_bits);
		remaining_bits -= block_len_bits;
		output += block_len_bits / CHAR_BIT;
	}

	if(remaining_bits != 0)
	{
		mk_sha3_detail_keccak_f(state);
		mk_sha3_detail_memcpy_bits(output, 0, state, 0, (int)remaining_bits);
	}
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
