#include "mk_md2.h"

#include <assert.h> /* assert, static_assert */ /* C11 */
#include <limits.h> /* CHAR_BIT */
#include <string.h> /* memcpy, memset */


static_assert(CHAR_BIT == 8, "Must have 8bit byte.");


static unsigned char const mk_md2_detail_table[256] =
{
	 41,  46,  67, 201, 162, 216, 124,   1,  61,  54,  84, 161, 236, 240,   6,  19,
	 98, 167,   5, 243, 192, 199, 115, 140, 152, 147,  43, 217, 188,  76, 130, 202,
	 30, 155,  87,  60, 253, 212, 224,  22, 103,  66, 111,  24, 138,  23, 229,  18,
	190,  78, 196, 214, 218, 158, 222,  73, 160, 251, 245, 142, 187,  47, 238, 122,
	169, 104, 121, 145,  21, 178,   7,  63, 148, 194,  16, 137,  11,  34,  95,  33,
	128, 127,  93, 154,  90, 144,  50,  39,  53,  62, 204, 231, 191, 247, 151,   3,
	255,  25,  48, 179,  72, 165, 181, 209, 215,  94, 146,  42, 172,  86, 170, 198,
	 79, 184,  56, 210, 150, 164, 125, 182, 118, 252, 107, 226, 156, 116,   4, 241,
	 69, 157, 112,  89, 100, 113, 135,  32, 134,  91, 207, 101, 230,  45, 168,   2,
	 27,  96,  37, 173, 174, 176, 185, 246,  28,  70,  97, 105,  52,  64, 126,  15,
	 85,  71, 163,  35, 221,  81, 175,  58, 195,  92, 249, 206, 186, 197, 234,  38,
	 44,  83,  13, 110, 133,  40, 132,   9, 211, 223, 205, 244,  65, 129,  77,  82,
	106, 220,  55, 200, 108, 193, 171, 250,  36, 225, 123,   8,  12, 189, 177,  74,
	120, 136, 149, 139, 227,  99, 232, 109, 233, 203, 213, 254,  59,   0,  29,  57,
	242, 239, 183,  14, 102,  88, 208, 228, 166, 119, 114, 248, 235, 117,  75,  10,
	 49,  68,  80, 180, 143, 237,  31,  26, 219, 153, 141,  51, 159,  17, 131,  20,
};


static inline void mk_md2_detail_process_block(struct mk_md2_state_s* self, unsigned char const* input)
{
	assert(self);
	assert(input);

	unsigned char x[48];
	
	memcpy(x + 0 * 16, self->m_state, 16);
	memcpy(x + 1 * 16, input, 16);
	for(int j = 0; j != 16; ++j)
	{
		x[2 * 16 + j] = self->m_state[j] ^ input[j];
	}

	unsigned t = 0;
	for(int j = 0; j != 18; ++j)
	{
		for(int k = 0; k != 48; ++k)
		{
			t = x[k] ^= mk_md2_detail_table[t];
		}
		t = (t + j) & 0xff;
	}

	unsigned l = self->m_checksum[15];
	for(int j = 0; j != 16; ++j)
	{
		l = self->m_checksum[j] ^= mk_md2_detail_table[input[j] ^ l];
	}

	memcpy(self->m_state, x, 16);
}


void mk_md2_init(struct mk_md2_state_s* self)
{
	assert(self);

	memset(self->m_state, 0, 16);
	memset(self->m_checksum, 0, 16);
	self->m_len = 0;
}

void mk_md2_append(struct mk_md2_state_s* self, void const* data, size_t len)
{
	assert(self);

	unsigned char const* input = (unsigned char const*)data;
	size_t remaining = len;

	unsigned idx = self->m_len;
	unsigned capacity = 16 - idx;
	self->m_len = (self->m_len + len) & 0xf;

	if(remaining >= capacity)
	{
		memcpy(self->m_block + idx, input, capacity);
		mk_md2_detail_process_block(self, self->m_block);
		input += capacity;
		remaining -= capacity;

		size_t blocks = remaining / 16;
		for(size_t i = 0; i != blocks; ++i)
		{
			mk_md2_detail_process_block(self, input);
			input += 16;
		}
		remaining -= blocks * 16;
		idx = 0;
	}

	memcpy(self->m_block + idx, input, remaining);
}

void mk_md2_finish(struct mk_md2_state_s* self, struct mk_md2_digest_s* digest)
{
	assert(self);
	assert(digest);

	unsigned char buff[16];

	unsigned len = self->m_len;
	unsigned capacity = 16 - len;
	assert(capacity >= 1 && capacity <= 16);

	unsigned padding_len = capacity;
	memset(buff, padding_len, padding_len);

	mk_md2_append(self, buff, padding_len);

	mk_md2_append(self, self->m_checksum, 16);

	memcpy(digest->m_data, self->m_state, 16);
}
