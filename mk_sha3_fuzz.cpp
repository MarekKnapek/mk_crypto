#include "mk_sha3.h"


extern "C" int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size)
{
	mk_sha3_224_state_s mk_sha3_224_state;
	unsigned char mk_sha3_224_digest[28];

	mk_sha3_224_init(&mk_sha3_224_state);
	mk_sha3_224_append(&mk_sha3_224_state, NULL, 0);
	mk_sha3_224_finish(&mk_sha3_224_state, mk_sha3_224_digest);

	return 0;
}
