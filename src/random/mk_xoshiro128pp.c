#include "mk_xoshiro128pp.h"

#include "../../utils/mk_assert.h"


void mk_xoshiro128pp_seed(struct xoshiro128pp_s* self, void const* buffer)
{
	unsigned char const* input;
	int i;

	mk_assert(self);
	mk_assert(buffer);

	input = (unsigned char const*)buffer;
	for(i = 0; i != 4; ++i)
	{
		mk_uint32_from_buff_le(&self->m_state[i], input + i * 4);
	}
}

struct mk_uint32_s mk_xoshiro128pp_next(struct xoshiro128pp_s* self)
{
	struct mk_uint32_s ret;
	struct mk_uint32_s tmp;

	mk_assert(self);

	mk_uint32_add(&ret, &self->m_state[0], &self->m_state[3]);
	mk_uint32_rotl(&ret, &ret, 7);
	mk_uint32_add(&ret, &ret, &self->m_state[0]);

	mk_uint32_shl(&tmp, &self->m_state[1], 9);

	mk_uint32_xor(&self->m_state[2], &self->m_state[2], &self->m_state[0]);
	mk_uint32_xor(&self->m_state[3], &self->m_state[3], &self->m_state[1]);
	mk_uint32_xor(&self->m_state[1], &self->m_state[1], &self->m_state[2]);
	mk_uint32_xor(&self->m_state[0], &self->m_state[0], &self->m_state[3]);

	mk_uint32_xor(&self->m_state[2], &self->m_state[2], &tmp);

	mk_uint32_rotl(&self->m_state[3], &self->m_state[3], 11);

	return ret;
}
