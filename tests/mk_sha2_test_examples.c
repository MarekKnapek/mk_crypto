#include "mk_sha2_test_examples.h"

#include "mk_sha2_224_test_examples.h"
#include "mk_sha2_256_test_examples.h"
#include "mk_sha2_384_test_examples.h"
#include "mk_sha2_512_test_examples.h"
#include "mk_sha2_512224_test_examples.h"
#include "mk_sha2_512256_test_examples.h"
#include "mk_sha2_additional_test_examples.h"


#define mk_try(x) do{ int err; err = (x); if(err != 0){ return err; } }while(0)


int mk_sha2_test_examples(void)
{
	mk_try(mk_sha2_224_test_examples());
	mk_try(mk_sha2_256_test_examples());
	mk_try(mk_sha2_384_test_examples());
	mk_try(mk_sha2_512_test_examples());
	mk_try(mk_sha2_512224_test_examples());
	mk_try(mk_sha2_512256_test_examples());
	mk_try(mk_sha2_additional_test_examples());
	return 0;
}


#undef mk_try
