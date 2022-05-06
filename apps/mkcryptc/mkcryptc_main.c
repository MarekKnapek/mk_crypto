#include "mkcryptc.h"

#include <stdio.h>


int main(int argc, char const* const* argv)
{
	int err;

	err = mkcryptc(argc, argv);

	printf("%s\n", err == 0 ? "Success!" : "Fail!");

	return err;
}
