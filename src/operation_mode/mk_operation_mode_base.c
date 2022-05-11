#include "mk_operation_mode_base.h"

#include "../../utils/mk_assert.h"

#include <string.h> /* memcpy */


void mk_operation_mode_init_base(struct mk_operation_mode_base_s* base, enum mk_block_cipher_e block_cipher, enum mk_padding_e padding, void const* key, int key_len)
{
	mk_assert(base);
	mk_assert(key || key_len == 0);
	mk_assert(key_len >= 0);

	mk_assert(key_len == mk_block_cipher_get_key_len(block_cipher));

	base->m_block_cipher = block_cipher;
	base->m_padding = padding;
	memcpy(base->m_key, key, key_len);
}

enum mk_block_cipher_e mk_operation_mode_get_block_cipher_base(struct mk_operation_mode_base_s* base)
{
	mk_assert(base);

	return base->m_block_cipher;
}

enum mk_padding_e mk_operation_mode_get_padding_base(struct mk_operation_mode_base_s* base)
{
	mk_assert(base);

	return base->m_padding;
}

void const* mk_operation_mode_get_key_base(struct mk_operation_mode_base_s* base)
{
	mk_assert(base);

	return base->m_key;
}
