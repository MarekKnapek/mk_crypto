#include "mk_uint_fuzz_8.h"

#include "../src/mk_uint_8.h"

#include <limits.h> /* CHAR_BIT */
#include <stddef.h> /* NULL */
#include <stdint.h> /* uint8_t */
#include <string.h> /* memcpy memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


void mk_uint_fuzz_8_from_int(unsigned char const* data)
{
	unsigned bn;
	uint8_t br;
	memcpy(&bn, data, sizeof(unsigned));
	br = (uint8_t)bn;

	unsigned mn;
	struct mk_uint8_s mr;
	memcpy(&mn, data, sizeof(unsigned));
	mk_uint8_from_int(&mr, mn);

	test(memcmp(&br, &mr, 8 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_8_or(unsigned char const* data)
{
	uint8_t ba;
	uint8_t bb;
	uint8_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&bb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	br = ba | bb;

	struct mk_uint8_s ma;
	struct mk_uint8_s mb;
	struct mk_uint8_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&mb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	mk_uint8_or(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 8 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_8_and(unsigned char const* data)
{
	uint8_t ba;
	uint8_t bb;
	uint8_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&bb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	br = ba & bb;

	struct mk_uint8_s ma;
	struct mk_uint8_s mb;
	struct mk_uint8_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&mb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	mk_uint8_and(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 8 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_8_xor(unsigned char const* data)
{
	uint8_t ba;
	uint8_t bb;
	uint8_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&bb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	br = ba ^ bb;

	struct mk_uint8_s ma;
	struct mk_uint8_s mb;
	struct mk_uint8_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&mb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	mk_uint8_xor(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 8 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_8_shl(unsigned char const* data)
{
	uint8_t bx;
	unsigned bn;
	uint8_t br;
	memcpy(&bx, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&bn, data + 8 / CHAR_BIT, sizeof(bn));
	bn = bn % 8;
	br = bx << bn;

	struct mk_uint8_s mx;
	unsigned mn;
	struct mk_uint8_s mr;
	memcpy(&mx, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&mn, data + 8 / CHAR_BIT, sizeof(mn));
	mn = mn % 8;
	mk_uint8_shl(&mr, &mx, mn);

	test(memcmp(&br, &mr, 8 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_8_shr(unsigned char const* data)
{
	uint8_t bx;
	unsigned bn;
	uint8_t br;
	memcpy(&bx, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&bn, data + 8 / CHAR_BIT, sizeof(bn));
	bn = bn % 8;
	br = bx >> bn;

	struct mk_uint8_s mx;
	unsigned mn;
	struct mk_uint8_s mr;
	memcpy(&mx, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&mn, data + 8 / CHAR_BIT, sizeof(mn));
	mn = mn % 8;
	mk_uint8_shr(&mr, &mx, mn);

	test(memcmp(&br, &mr, 8 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_8_lt(unsigned char const* data)
{
	uint8_t ba;
	uint8_t bb;
	int br;
	memcpy(&ba, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&bb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	br = ba < bb;

	struct mk_uint8_s ma;
	struct mk_uint8_s mb;
	int mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&mb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	mr = mk_uint8_lt(&ma, &mb);

	test(memcmp(&br, &mr, sizeof(br)) == 0);
}

void mk_uint_fuzz_8_le(unsigned char const* data)
{
	uint8_t ba;
	uint8_t bb;
	int br;
	memcpy(&ba, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&bb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	br = ba <= bb;

	struct mk_uint8_s ma;
	struct mk_uint8_s mb;
	int mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&mb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	mr = mk_uint8_le(&ma, &mb);

	test(memcmp(&br, &mr, sizeof(br)) == 0);
}

void mk_uint_fuzz_8_add(unsigned char const* data)
{
	uint8_t ba;
	uint8_t bb;
	uint8_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&bb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	br = ba + bb;

	struct mk_uint8_s ma;
	struct mk_uint8_s mb;
	struct mk_uint8_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&mb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	mk_uint8_add(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 8 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_8_sub(unsigned char const* data)
{
	uint8_t ba;
	uint8_t bb;
	uint8_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&bb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	br = ba - bb;

	struct mk_uint8_s ma;
	struct mk_uint8_s mb;
	struct mk_uint8_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 8 / CHAR_BIT);
	memcpy(&mb, data + 8 / CHAR_BIT, 8 / CHAR_BIT);
	mk_uint8_sub(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 8 / CHAR_BIT) == 0);
}


void mk_uint_fuzz_8(unsigned char const* data)
{
	mk_uint_fuzz_8_from_int(data);
	mk_uint_fuzz_8_or(data);
	mk_uint_fuzz_8_and(data);
	mk_uint_fuzz_8_xor(data);
	mk_uint_fuzz_8_shl(data);
	mk_uint_fuzz_8_shr(data);
	mk_uint_fuzz_8_lt(data);
	mk_uint_fuzz_8_le(data);
	mk_uint_fuzz_8_add(data);
	mk_uint_fuzz_8_sub(data);
}


#undef test
