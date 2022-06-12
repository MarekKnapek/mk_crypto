#include "mk_sha2_additional_test_examples.h"

#include "mk_sha2_additional_test_examples_224.h"
#include "mk_sha2_additional_test_examples_256.h"
#include "mk_sha2_additional_test_examples_384.h"
#include "mk_sha2_additional_test_examples_512.h"

#include "../src/utils/mk_try.h"


int mk_sha2_additional_test_examples(void)
{
	mk_try(mk_sha2_additional_test_examples_224());
	mk_try(mk_sha2_additional_test_examples_256());
	mk_try(mk_sha2_additional_test_examples_384());
	mk_try(mk_sha2_additional_test_examples_512());
	return 0;
}
