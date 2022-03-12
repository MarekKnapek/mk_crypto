#include "mk_uint_fuzz_32.h"

#include "../src/mk_uint_32.h"

#include <limits.h> /* CHAR_BIT */
#include <stddef.h> /* NULL */
#include <stdint.h> /* uint32_t */
#include <string.h> /* memcpy memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


void mk_uint_fuzz_32_or(unsigned char const* data)
{
	uint32_t ba;
	uint32_t bb;
	uint32_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&bb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	br = ba | bb;

	struct mk_uint32_s ma;
	struct mk_uint32_s mb;
	struct mk_uint32_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&mb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	mk_uint32_or(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 32 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_32_and(unsigned char const* data)
{
	uint32_t ba;
	uint32_t bb;
	uint32_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&bb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	br = ba & bb;

	struct mk_uint32_s ma;
	struct mk_uint32_s mb;
	struct mk_uint32_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&mb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	mk_uint32_and(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 32 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_32_xor(unsigned char const* data)
{
	uint32_t ba;
	uint32_t bb;
	uint32_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&bb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	br = ba ^ bb;

	struct mk_uint32_s ma;
	struct mk_uint32_s mb;
	struct mk_uint32_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&mb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	mk_uint32_xor(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 32 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_32_shl(unsigned char const* data)
{
	uint32_t bx;
	unsigned bn;
	uint32_t br;
	memcpy(&bx, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&bn, data + 32 / CHAR_BIT, sizeof(bn));
	bn = bn % 32;
	br = bx << bn;

	struct mk_uint32_s mx;
	unsigned mn;
	struct mk_uint32_s mr;
	memcpy(&mx, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&mn, data + 32 / CHAR_BIT, sizeof(mn));
	mn = mn % 32;
	mk_uint32_shl(&mr, &mx, mn);

	test(memcmp(&br, &mr, 32 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_32_shr(unsigned char const* data)
{
	uint32_t bx;
	unsigned bn;
	uint32_t br;
	memcpy(&bx, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&bn, data + 32 / CHAR_BIT, sizeof(bn));
	bn = bn % 32;
	br = bx >> bn;

	struct mk_uint32_s mx;
	unsigned mn;
	struct mk_uint32_s mr;
	memcpy(&mx, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&mn, data + 32 / CHAR_BIT, sizeof(mn));
	mn = mn % 32;
	mk_uint32_shr(&mr, &mx, mn);

	test(memcmp(&br, &mr, 32 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_32_lt(unsigned char const* data)
{
	uint32_t ba;
	uint32_t bb;
	int br;
	memcpy(&ba, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&bb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	br = ba < bb;

	struct mk_uint32_s ma;
	struct mk_uint32_s mb;
	int mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&mb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	mr = mk_uint32_lt(&ma, &mb);

	test(memcmp(&br, &mr, sizeof(br)) == 0);
}

void mk_uint_fuzz_32_le(unsigned char const* data)
{
	uint32_t ba;
	uint32_t bb;
	int br;
	memcpy(&ba, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&bb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	br = ba <= bb;

	struct mk_uint32_s ma;
	struct mk_uint32_s mb;
	int mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&mb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	mr = mk_uint32_le(&ma, &mb);

	test(memcmp(&br, &mr, sizeof(br)) == 0);
}

void mk_uint_fuzz_32_add(unsigned char const* data)
{
	uint32_t ba;
	uint32_t bb;
	uint32_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&bb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	br = ba + bb;

	struct mk_uint32_s ma;
	struct mk_uint32_s mb;
	struct mk_uint32_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&mb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	mk_uint32_add(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 32 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_32_sub(unsigned char const* data)
{
	uint32_t ba;
	uint32_t bb;
	uint32_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&bb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	br = ba - bb;

	struct mk_uint32_s ma;
	struct mk_uint32_s mb;
	struct mk_uint32_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 32 / CHAR_BIT);
	memcpy(&mb, data + 32 / CHAR_BIT, 32 / CHAR_BIT);
	mk_uint32_sub(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 32 / CHAR_BIT) == 0);
}


void mk_uint_fuzz_32(unsigned char const* data)
{
	mk_uint_fuzz_32_or(data);
	mk_uint_fuzz_32_and(data);
	mk_uint_fuzz_32_xor(data);
	mk_uint_fuzz_32_shl(data);
	mk_uint_fuzz_32_shr(data);
	mk_uint_fuzz_32_lt(data);
	mk_uint_fuzz_32_le(data);
	mk_uint_fuzz_32_add(data);
	mk_uint_fuzz_32_sub(data);
}


#undef test
