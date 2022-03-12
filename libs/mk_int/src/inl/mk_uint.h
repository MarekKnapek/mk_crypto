#include <limits.h> /* CHAR_BIT */


#define mk_uint_detail_bits_to_words(x) (((x) + (sizeof(mk_uint_small_t) * CHAR_BIT - 1)) / (sizeof(mk_uint_small_t) * CHAR_BIT))


mk_uint_t
{
	mk_uint_small_t m_data[mk_uint_detail_bits_to_words(mk_uint_bits)];
};


void mk_uint_zero(mk_uint_t* out);
void mk_uint_one(mk_uint_t* out);
void mk_uint_from_int(mk_uint_t* out, unsigned in);

void mk_uint_or(mk_uint_t* out, mk_uint_t const* a, mk_uint_t const* b);
void mk_uint_and(mk_uint_t* out, mk_uint_t const* a, mk_uint_t const* b);
void mk_uint_xor(mk_uint_t* out, mk_uint_t const* a, mk_uint_t const* b);

void mk_uint_shl(mk_uint_t* out, mk_uint_t const* x, int n);
void mk_uint_shr(mk_uint_t* out, mk_uint_t const* x, int n);

int mk_uint_lt(mk_uint_t const* a, mk_uint_t const* b);
int mk_uint_le(mk_uint_t const* a, mk_uint_t const* b);

void mk_uint_add(mk_uint_t* out, mk_uint_t const* a, mk_uint_t const* b);
void mk_uint_sub(mk_uint_t* out, mk_uint_t const* a, mk_uint_t const* b);


#undef mk_uint_detail_bits_to_words
