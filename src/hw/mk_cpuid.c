#include "mk_cpuid.h"

#include "mk_cpuid_hw.h"

#include "../../utils/mk_assert.h"


void mk_cpuid(int leaf, struct mk_cpuid_registers_s* registers)
{
	mk_assert(registers);
	
	mk_cpuid_hw(leaf, (struct mk_cpuid_hw_registers_s*)registers);
}
