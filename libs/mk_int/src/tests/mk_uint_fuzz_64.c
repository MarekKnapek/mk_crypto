#include "mk_uint_fuzz_64.h"

#include "../src/mk_uint_64.h"

#include <limits.h> /* CHAR_BIT */
#include <stddef.h> /* NULL */
#include <stdint.h> /* uint64_t */
#include <string.h> /* memcpy memcmp */


#define test(x) do{ if(!(x)){ int volatile* volatile ptr = NULL; *ptr = 0; } }while(0)


void mk_uint_fuzz_64_from_int(unsigned char const* data)
{
	unsigned bn;
	uint64_t br;
	memcpy(&bn, data, sizeof(unsigned));
	br = (uint64_t)bn;

	unsigned mn;
	struct mk_uint64_s mr;
	memcpy(&mn, data, sizeof(unsigned));
	mk_uint64_from_int(&mr, mn);

	test(memcmp(&br, &mr, 64 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_64_to_int(unsigned char const* data)
{
	uint64_t bx;
	unsigned br;
	memcpy(&bx, data, 64 / CHAR_BIT);
	br = (unsigned)bx;

	struct mk_uint64_s mx;
	unsigned mr;
	memcpy(&mx, data, 64 / CHAR_BIT);
	mr = mk_uint64_to_int(&mx);

	test(memcmp(&br, &mr, sizeof(unsigned)) == 0);
}

void mk_uint_fuzz_64_or(unsigned char const* data)
{
	uint64_t ba;
	uint64_t bb;
	uint64_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&bb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	br = ba | bb;

	struct mk_uint64_s ma;
	struct mk_uint64_s mb;
	struct mk_uint64_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&mb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	mk_uint64_or(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 64 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_64_and(unsigned char const* data)
{
	uint64_t ba;
	uint64_t bb;
	uint64_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&bb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	br = ba & bb;

	struct mk_uint64_s ma;
	struct mk_uint64_s mb;
	struct mk_uint64_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&mb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	mk_uint64_and(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 64 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_64_xor(unsigned char const* data)
{
	uint64_t ba;
	uint64_t bb;
	uint64_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&bb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	br = ba ^ bb;

	struct mk_uint64_s ma;
	struct mk_uint64_s mb;
	struct mk_uint64_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&mb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	mk_uint64_xor(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 64 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_64_shl(unsigned char const* data)
{
	uint64_t bx;
	unsigned bn;
	uint64_t br;
	memcpy(&bx, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&bn, data + 64 / CHAR_BIT, sizeof(bn));
	bn = bn % 64;
	br = bx << bn;

	struct mk_uint64_s mx;
	unsigned mn;
	struct mk_uint64_s mr;
	memcpy(&mx, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&mn, data + 64 / CHAR_BIT, sizeof(mn));
	mn = mn % 64;
	mk_uint64_shl(&mr, &mx, mn);

	test(memcmp(&br, &mr, 64 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_64_shr(unsigned char const* data)
{
	uint64_t bx;
	unsigned bn;
	uint64_t br;
	memcpy(&bx, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&bn, data + 64 / CHAR_BIT, sizeof(bn));
	bn = bn % 64;
	br = bx >> bn;

	struct mk_uint64_s mx;
	unsigned mn;
	struct mk_uint64_s mr;
	memcpy(&mx, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&mn, data + 64 / CHAR_BIT, sizeof(mn));
	mn = mn % 64;
	mk_uint64_shr(&mr, &mx, mn);

	test(memcmp(&br, &mr, 64 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_64_lt(unsigned char const* data)
{
	uint64_t ba;
	uint64_t bb;
	int br;
	memcpy(&ba, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&bb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	br = ba < bb;

	struct mk_uint64_s ma;
	struct mk_uint64_s mb;
	int mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&mb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	mr = mk_uint64_lt(&ma, &mb);

	test(memcmp(&br, &mr, sizeof(br)) == 0);
}

void mk_uint_fuzz_64_le(unsigned char const* data)
{
	uint64_t ba;
	uint64_t bb;
	int br;
	memcpy(&ba, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&bb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	br = ba <= bb;

	struct mk_uint64_s ma;
	struct mk_uint64_s mb;
	int mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&mb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	mr = mk_uint64_le(&ma, &mb);

	test(memcmp(&br, &mr, sizeof(br)) == 0);
}

void mk_uint_fuzz_64_add(unsigned char const* data)
{
	uint64_t ba;
	uint64_t bb;
	uint64_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&bb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	br = ba + bb;

	struct mk_uint64_s ma;
	struct mk_uint64_s mb;
	struct mk_uint64_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&mb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	mk_uint64_add(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 64 / CHAR_BIT) == 0);
}

void mk_uint_fuzz_64_sub(unsigned char const* data)
{
	uint64_t ba;
	uint64_t bb;
	uint64_t br;
	memcpy(&ba, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&bb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	br = ba - bb;

	struct mk_uint64_s ma;
	struct mk_uint64_s mb;
	struct mk_uint64_s mr;
	memcpy(&ma, data + 00 / CHAR_BIT, 64 / CHAR_BIT);
	memcpy(&mb, data + 64 / CHAR_BIT, 64 / CHAR_BIT);
	mk_uint64_sub(&mr, &ma, &mb);

	test(memcmp(&br, &mr, 64 / CHAR_BIT) == 0);
}


void mk_uint_fuzz_64(unsigned char const* data)
{
	mk_uint_fuzz_64_from_int(data);
	mk_uint_fuzz_64_to_int(data);
	mk_uint_fuzz_64_or(data);
	mk_uint_fuzz_64_and(data);
	mk_uint_fuzz_64_xor(data);
	mk_uint_fuzz_64_shl(data);
	mk_uint_fuzz_64_shr(data);
	mk_uint_fuzz_64_lt(data);
	mk_uint_fuzz_64_le(data);
	mk_uint_fuzz_64_add(data);
	mk_uint_fuzz_64_sub(data);
}


#undef test
