#ifndef MK_INCLUDE_GUARD_WIN_SHA3
#define MK_INCLUDE_GUARD_WIN_SHA3


#include "../mk_int/src/exact/mk_uint_64.h"

#include <stddef.h> /* size_t */


#ifdef __cplusplus
#define MK_EXTERN_C extern "C"
#else
#define MK_EXTERN_C
#endif


struct mk_sha3_224_state_s
{
	struct mk_uint64_s m_state[25];
	int m_idx;
	struct mk_uint64_s m_block[18];
};


MK_EXTERN_C void mk_sha3_224_init(struct mk_sha3_224_state_s* self);
MK_EXTERN_C void mk_sha3_224_append(struct mk_sha3_224_state_s* self, void const* msg, size_t msg_len_bits);
MK_EXTERN_C void mk_sha3_224_finish(struct mk_sha3_224_state_s* self, void* digest);


struct mk_sha3_256_state_s
{
	struct mk_uint64_s m_state[25];
	int m_idx;
	struct mk_uint64_s m_block[17];
};


MK_EXTERN_C void mk_sha3_256_init(struct mk_sha3_256_state_s* self);
MK_EXTERN_C void mk_sha3_256_append(struct mk_sha3_256_state_s* self, void const* msg, size_t msg_len_bits);
MK_EXTERN_C void mk_sha3_256_finish(struct mk_sha3_256_state_s* self, void* digest);


struct mk_sha3_384_state_s
{
	struct mk_uint64_s m_state[25];
	int m_idx;
	struct mk_uint64_s m_block[13];
};


MK_EXTERN_C void mk_sha3_384_init(struct mk_sha3_384_state_s* self);
MK_EXTERN_C void mk_sha3_384_append(struct mk_sha3_384_state_s* self, void const* msg, size_t msg_len_bits);
MK_EXTERN_C void mk_sha3_384_finish(struct mk_sha3_384_state_s* self, void* digest);


struct mk_sha3_512_state_s
{
	struct mk_uint64_s m_state[25];
	int m_idx;
	struct mk_uint64_s m_block[9];
};


MK_EXTERN_C void mk_sha3_512_init(struct mk_sha3_512_state_s* self);
MK_EXTERN_C void mk_sha3_512_append(struct mk_sha3_512_state_s* self, void const* msg, size_t msg_len_bits);
MK_EXTERN_C void mk_sha3_512_finish(struct mk_sha3_512_state_s* self, void* digest);


struct mk_sha3_shake_128_state_s
{
	struct mk_uint64_s m_state[25];
	int m_idx;
	struct mk_uint64_s m_block[21];
};


MK_EXTERN_C void mk_sha3_shake_128_init(struct mk_sha3_shake_128_state_s* self);
MK_EXTERN_C void mk_sha3_shake_128_append(struct mk_sha3_shake_128_state_s* self, void const* msg, size_t msg_len_bits);
MK_EXTERN_C void mk_sha3_shake_128_finish(struct mk_sha3_shake_128_state_s* self, int digest_len_bits, void* digest);


struct mk_sha3_shake_256_state_s
{
	struct mk_uint64_s m_state[25];
	int m_idx;
	struct mk_uint64_s m_block[17];
};


MK_EXTERN_C void mk_sha3_shake_256_init(struct mk_sha3_shake_256_state_s* self);
MK_EXTERN_C void mk_sha3_shake_256_append(struct mk_sha3_shake_256_state_s* self, void const* msg, size_t msg_len_bits);
MK_EXTERN_C void mk_sha3_shake_256_finish(struct mk_sha3_shake_256_state_s* self, int digest_len_bits, void* digest);


struct mk_sha3_raw_shake_128_state_s
{
	struct mk_uint64_s m_state[25];
	int m_idx;
	struct mk_uint64_s m_block[21];
};


MK_EXTERN_C void mk_sha3_raw_shake_128_init(struct mk_sha3_raw_shake_128_state_s* self);
MK_EXTERN_C void mk_sha3_raw_shake_128_append(struct mk_sha3_raw_shake_128_state_s* self, void const* msg, size_t msg_len_bits);
MK_EXTERN_C void mk_sha3_raw_shake_128_finish(struct mk_sha3_raw_shake_128_state_s* self, int digest_len_bits, void* digest);


struct mk_sha3_raw_shake_256_state_s
{
	struct mk_uint64_s m_state[25];
	int m_idx;
	struct mk_uint64_s m_block[17];
};


MK_EXTERN_C void mk_sha3_raw_shake_256_init(struct mk_sha3_raw_shake_256_state_s* self);
MK_EXTERN_C void mk_sha3_raw_shake_256_append(struct mk_sha3_raw_shake_256_state_s* self, void const* msg, size_t msg_len_bits);
MK_EXTERN_C void mk_sha3_raw_shake_256_finish(struct mk_sha3_raw_shake_256_state_s* self, int digest_len_bits, void* digest);


MK_EXTERN_C void mk_sha3_224_bits(void const* msg, size_t msg_len_bits, void* digest);
MK_EXTERN_C void mk_sha3_256_bits(void const* msg, size_t msg_len_bits, void* digest);
MK_EXTERN_C void mk_sha3_384_bits(void const* msg, size_t msg_len_bits, void* digest);
MK_EXTERN_C void mk_sha3_512_bits(void const* msg, size_t msg_len_bits, void* digest);
MK_EXTERN_C void mk_sha3_shake_128_bits(void const* msg, size_t msg_len_bits, int digest_len_bits, void* digest);
MK_EXTERN_C void mk_sha3_shake_256_bits(void const* msg, size_t msg_len_bits, int digest_len_bits, void* digest);
MK_EXTERN_C void mk_sha3_raw_shake_128_bits(void const* msg, size_t msg_len_bits, int digest_len_bits, void* digest);
MK_EXTERN_C void mk_sha3_raw_shake_256_bits(void const* msg, size_t msg_len_bits, int digest_len_bits, void* digest);


MK_EXTERN_C void mk_sha3_224(void const* msg, size_t msg_len_bytes, void* digest);
MK_EXTERN_C void mk_sha3_256(void const* msg, size_t msg_len_bytes, void* digest);
MK_EXTERN_C void mk_sha3_384(void const* msg, size_t msg_len_bytes, void* digest);
MK_EXTERN_C void mk_sha3_512(void const* msg, size_t msg_len_bytes, void* digest);
MK_EXTERN_C void mk_sha3_shake_128(void const* msg, size_t msg_len_bytes, int digest_len_bits, void* digest);
MK_EXTERN_C void mk_sha3_shake_256(void const* msg, size_t msg_len_bytes, int digest_len_bits, void* digest);
MK_EXTERN_C void mk_sha3_raw_shake_128(void const* msg, size_t msg_len_bytes, int digest_len_bits, void* digest);
MK_EXTERN_C void mk_sha3_raw_shake_256(void const* msg, size_t msg_len_bytes, int digest_len_bits, void* digest);


#undef MK_EXTERN_C


#endif
