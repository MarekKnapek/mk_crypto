#include "mk_md2.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <string.h> /* memcpy memset */


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4710) /* warning C4710: 'xxx': function not inlined */
#pragma warning(disable:4711) /* warning C4711: function 'xxx' selected for automatic inline expansion */
#pragma warning(disable:5045) /* warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified */
#endif


static unsigned char const s_mk_md2_detail_table[256] =
{
	0x29, 0x2e, 0x43, 0xc9, 0xa2, 0xd8, 0x7c, 0x01, 0x3d, 0x36, 0x54, 0xa1, 0xec, 0xf0, 0x06, 0x13,
	0x62, 0xa7, 0x05, 0xf3, 0xc0, 0xc7, 0x73, 0x8c, 0x98, 0x93, 0x2b, 0xd9, 0xbc, 0x4c, 0x82, 0xca,
	0x1e, 0x9b, 0x57, 0x3c, 0xfd, 0xd4, 0xe0, 0x16, 0x67, 0x42, 0x6f, 0x18, 0x8a, 0x17, 0xe5, 0x12,
	0xbe, 0x4e, 0xc4, 0xd6, 0xda, 0x9e, 0xde, 0x49, 0xa0, 0xfb, 0xf5, 0x8e, 0xbb, 0x2f, 0xee, 0x7a,
	0xa9, 0x68, 0x79, 0x91, 0x15, 0xb2, 0x07, 0x3f, 0x94, 0xc2, 0x10, 0x89, 0x0b, 0x22, 0x5f, 0x21,
	0x80, 0x7f, 0x5d, 0x9a, 0x5a, 0x90, 0x32, 0x27, 0x35, 0x3e, 0xcc, 0xe7, 0xbf, 0xf7, 0x97, 0x03,
	0xff, 0x19, 0x30, 0xb3, 0x48, 0xa5, 0xb5, 0xd1, 0xd7, 0x5e, 0x92, 0x2a, 0xac, 0x56, 0xaa, 0xc6,
	0x4f, 0xb8, 0x38, 0xd2, 0x96, 0xa4, 0x7d, 0xb6, 0x76, 0xfc, 0x6b, 0xe2, 0x9c, 0x74, 0x04, 0xf1,
	0x45, 0x9d, 0x70, 0x59, 0x64, 0x71, 0x87, 0x20, 0x86, 0x5b, 0xcf, 0x65, 0xe6, 0x2d, 0xa8, 0x02,
	0x1b, 0x60, 0x25, 0xad, 0xae, 0xb0, 0xb9, 0xf6, 0x1c, 0x46, 0x61, 0x69, 0x34, 0x40, 0x7e, 0x0f,
	0x55, 0x47, 0xa3, 0x23, 0xdd, 0x51, 0xaf, 0x3a, 0xc3, 0x5c, 0xf9, 0xce, 0xba, 0xc5, 0xea, 0x26,
	0x2c, 0x53, 0x0d, 0x6e, 0x85, 0x28, 0x84, 0x09, 0xd3, 0xdf, 0xcd, 0xf4, 0x41, 0x81, 0x4d, 0x52,
	0x6a, 0xdc, 0x37, 0xc8, 0x6c, 0xc1, 0xab, 0xfa, 0x24, 0xe1, 0x7b, 0x08, 0x0c, 0xbd, 0xb1, 0x4a,
	0x78, 0x88, 0x95, 0x8b, 0xe3, 0x63, 0xe8, 0x6d, 0xe9, 0xcb, 0xd5, 0xfe, 0x3b, 0x00, 0x1d, 0x39,
	0xf2, 0xef, 0xb7, 0x0e, 0x66, 0x58, 0xd0, 0xe4, 0xa6, 0x77, 0x72, 0xf8, 0xeb, 0x75, 0x4b, 0x0a,
	0x31, 0x44, 0x50, 0xb4, 0x8f, 0xed, 0x1f, 0x1a, 0xdb, 0x99, 0x8d, 0x33, 0x9f, 0x11, 0x83, 0x14,
};


static mk_inline void mk_md2_detail_process_block(struct mk_md2_state_s* self, unsigned char const msg[16])
{
	unsigned char x[48];
	int j;
	unsigned t;
	int k;
	unsigned l;

	mk_assert(self);
	mk_assert(msg);

	memcpy(x + 0 * 16, self->m_state, 16);
	memcpy(x + 1 * 16, msg, 16);
	for(j = 0; j != 16; ++j)
	{
		x[2 * 16 + j] = self->m_state[j] ^ msg[j];
	}

	t = 0;
	for(j = 0; j != 18; ++j)
	{
		for(k = 0; k != 48; ++k)
		{
			t = x[k] ^= s_mk_md2_detail_table[t];
		}
		t = (t + j) & 0xff;
	}

	l = self->m_checksum[15];
	for(j = 0; j != 16; ++j)
	{
		l = self->m_checksum[j] ^= s_mk_md2_detail_table[msg[j] ^ l];
	}

	memcpy(self->m_state, x, 16);
}


void mk_md2_init(struct mk_md2_state_s* self)
{
	mk_assert(self);

	memset(self->m_state, 0, 16);
	memset(self->m_checksum, 0, 16);
	self->m_idx = 0;
}

void mk_md2_append(struct mk_md2_state_s* self, void const* msg, size_t msg_len_bytes)
{
	unsigned char const* input;
	size_t remaining;
	int idx;
	int capacity;
	size_t blocks;
	size_t i;

	mk_assert(self);

	input = (unsigned char const*)msg;
	remaining = msg_len_bytes;

	idx = self->m_idx;
	capacity = 16 - idx;
	self->m_idx = (self->m_idx + remaining) & 0xf;

	if(remaining >= (size_t)capacity)
	{
		if(idx != 0)
		{
			memcpy(self->m_block + idx, input, capacity);
			mk_md2_detail_process_block(self, self->m_block);
			input += capacity;
			remaining -= capacity;
		}
		blocks = remaining / 16;
		for(i = 0; i != blocks; ++i)
		{
			mk_md2_detail_process_block(self, input);
			input += 16;
		}
		remaining -= blocks * 16;
		idx = 0;
	}
	memcpy(self->m_block + idx, input, remaining);
}

void mk_md2_finish(struct mk_md2_state_s* self, void* digest)
{
	int idx;
	int capacity;
	int padding_len;
	unsigned char padding[16];

	mk_assert(self);
	mk_assert(digest);

	idx = self->m_idx;
	capacity = 16 - idx;

	padding_len = capacity;
	memset(padding, padding_len, padding_len);

	mk_md2_append(self, padding, padding_len);
	mk_md2_append(self, self->m_checksum, 16);

	memcpy(digest, self->m_state, 16);
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
