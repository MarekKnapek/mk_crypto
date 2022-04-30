#ifndef mk_include_guard_cpuid_hw
#define mk_include_guard_cpuid_hw


#ifdef __cplusplus
#define mk_extern_c extern "C"
#else
#define mk_extern_c
#endif


struct mk_cpuid_hw_registers_s
{
	unsigned m_eax;
	unsigned m_ebx;
	unsigned m_edx;
	unsigned m_ecx;
};


mk_extern_c void __fastcall mk_cpuid_hw(int leaf, struct mk_cpuid_hw_registers_s* registers);


#undef mk_extern_c


#endif
