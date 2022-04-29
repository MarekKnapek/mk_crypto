#include "mk_operation_mode_base.h"

#include "../../utils/mk_assert.h"

#include <string.h> /* memcpy */


void mk_operation_mode_init_base(struct mk_operation_mode_base_s* base, enum mk_block_cipher_e block_cipher, unsigned char const* key)
{
	mk_assert(base);

	base->m_block_cipher = block_cipher;
	memcpy(base->m_key, key, mk_block_cipher_get_key_len(block_cipher));
}

enum mk_block_cipher_e mk_operation_mode_get_block_cipher_base(struct mk_operation_mode_base_s* base)
{
	mk_assert(base);

	return base->m_block_cipher;
}

unsigned char const* mk_operation_mode_get_key_base(struct mk_operation_mode_base_s* base)
{
	mk_assert(base);

	return base->m_key;
}
