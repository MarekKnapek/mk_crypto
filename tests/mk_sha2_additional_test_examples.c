#include "mk_sha2_additional_test_examples.h"

#include "mk_sha2_additional_test_examples_224.h"
#include "mk_sha2_additional_test_examples_256.h"
#include "mk_sha2_additional_test_examples_384.h"
#include "mk_sha2_additional_test_examples_512.h"


#define mk_try(x) do{ int err_ = (x); if(err_ != 0){ return err_; } }while(0)


int mk_sha2_additional_test_examples(void)
{
	mk_try(mk_sha2_additional_test_examples_224());
	mk_try(mk_sha2_additional_test_examples_256());
	mk_try(mk_sha2_additional_test_examples_384());
	mk_try(mk_sha2_additional_test_examples_512());
	return 0;
}


#undef mk_try
