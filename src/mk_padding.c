#include "mk_padding.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include <string.h> /* memset */


#define mk_assert_padding(padding) mk_assert \
	( \
		(padding) == mk_padding_pkcs7 || \
		(padding) == mk_padding_10s || \
		(padding) == mk_padding_10s1 || \
		(padding) == mk_padding_zero || \
		(padding) == mk_padding_none || \
		0 \
	)


static mk_inline int mk_padding_detail_add_pkcs7(int block_len, void* input, int input_len)
{
	unsigned char* in;
	int rem;

	mk_assert(block_len > 0);
	mk_assert(input);
	mk_assert(input_len >= 0 && input_len < block_len);

	in = (unsigned char*)input;
	rem = block_len - input_len;
	memset(in + input_len, rem, rem);

	return block_len;
}

static mk_inline int mk_padding_detail_rem_pkcs7(int block_len, void const* input)
{
	unsigned char* in;
	int len;
	int i;

	mk_assert(block_len > 0);
	mk_assert(input);

	in = (unsigned char*)input;
	len = in[block_len - 1];
	if(len == 0)
	{
		return -1;
	}
	if(len > block_len)
	{
		return -1;
	}
	for(i = 1; i != len; ++i)
	{
		if(in[block_len - 1 - i] != len)
		{
			return -1;
		}
	}
	return block_len - len;
}

static mk_inline int mk_padding_detail_add_10s(int block_len, void* input, int input_len)
{
	unsigned char* in;
	int rem;

	mk_assert(block_len > 0);
	mk_assert(input);
	mk_assert(input_len >= 0 && input_len < block_len);

	in = (unsigned char*)input;
	in[input_len] = 0x80;
	rem = block_len - input_len - 1;
	memset(in + input_len + 1, 0, rem);

	return block_len;
}

static mk_inline int mk_padding_detail_rem_10s(int block_len, void const* input)
{
	unsigned char* in;
	int i;

	mk_assert(block_len > 0);
	mk_assert(input);

	in = (unsigned char*)input;
	for(i = 0; i != block_len; ++i)
	{
		if(in[block_len - 1 - i] == 0x80)
		{
			return block_len - 1 - i;
		}
		if(in[block_len - 1 - i] != 0x00)
		{
			return -1;
		}
	}
	return -1;
}

static mk_inline int mk_padding_detail_add_10s1(int block_len, void* input, int input_len)
{
	unsigned char* in;
	int rem;

	mk_assert(block_len > 0);
	mk_assert(input);
	mk_assert(input_len >= 0 && input_len < block_len);

	in = (unsigned char*)input;
	rem = block_len - input_len;
	in[input_len] = 0x80;
	memset(in + input_len, 0, rem);
	in[block_len - 1] |= 0x01;

	return block_len;
}

static mk_inline int mk_padding_detail_rem_10s1(int block_len, void const* input)
{
	unsigned char* in;
	int i;

	mk_assert(block_len > 0);
	mk_assert(input);

	in = (unsigned char*)input;
	if(in[block_len - 1] == 0x81)
	{
		return block_len - 1;
	}
	if(in[block_len - 1] != 0x01)
	{
		return -1;
	}
	for(i = 1; i != block_len; ++i)
	{
		if(in[block_len - 1 - i] == 0x80)
		{
			return block_len - 1 - i;
		}
		if(in[block_len - 1 - i] != 0x00)
		{
			return -1;
		}
	}
	return -1;
}

static mk_inline int mk_padding_detail_add_zero(int block_len, void* input, int input_len)
{
	unsigned char* in;
	int rem;

	mk_assert(block_len > 0);
	mk_assert(input);
	mk_assert(input_len >= 0 && input_len < block_len);

	in = (unsigned char*)input;
	rem = block_len - input_len;
	memset(in + input_len, 0, rem);

	return block_len;
}

static mk_inline int mk_padding_detail_rem_zero(int block_len, void const* input)
{
	mk_assert(block_len > 0);
	mk_assert(input);

	return block_len;
}

static mk_inline int mk_padding_detail_add_none(int block_len, void* input, int input_len)
{
	mk_assert(block_len > 0);
	mk_assert(input);
	mk_assert(input_len >= 0 && input_len < block_len);

	return input_len;
}

static mk_inline int mk_padding_detail_rem_none(int block_len, void const* input)
{
	mk_assert(block_len > 0);
	mk_assert(input);

	return block_len;
}


int mk_padding_add(enum mk_padding_e padding, int block_len, void* input, int input_len)
{
	int ret;

	mk_assert_padding(padding);
	mk_assert(block_len > 0);
	mk_assert(input);
	mk_assert(input_len >= 0 && input_len < block_len);

	switch(padding)
	{
		case mk_padding_pkcs7: ret = mk_padding_detail_add_pkcs7(block_len, input, input_len); break;
		case mk_padding_10s: ret = mk_padding_detail_add_10s(block_len, input, input_len); break;
		case mk_padding_10s1: ret = mk_padding_detail_add_10s1(block_len, input, input_len); break;
		case mk_padding_zero: ret = mk_padding_detail_add_zero(block_len, input, input_len); break;
		case mk_padding_none: ret = mk_padding_detail_add_none(block_len, input, input_len); break;
		default: mk_assert((ret = 0, 0)); break;
	}
	return ret;
}

int mk_padding_rem(enum mk_padding_e padding, int block_len, void const* input)
{
	int ret;

	mk_assert_padding(padding);
	mk_assert(block_len > 0);
	mk_assert(input);

	switch(padding)
	{
		case mk_padding_pkcs7: ret = mk_padding_detail_rem_pkcs7(block_len, input); break;
		case mk_padding_10s: ret = mk_padding_detail_rem_10s(block_len, input); break;
		case mk_padding_10s1: ret = mk_padding_detail_rem_10s1(block_len, input); break;
		case mk_padding_zero: ret = mk_padding_detail_rem_zero(block_len, input); break;
		case mk_padding_none: ret = mk_padding_detail_rem_none(block_len, input); break;
		default: mk_assert((ret = 0, 0)); break;
	}
	return ret;
}


#undef mk_assert_padding
