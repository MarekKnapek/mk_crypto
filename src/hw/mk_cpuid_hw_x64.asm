public mk_cpuid_hw


.code


mk_cpuid_hw proc
	push rdi
	mov rdi, rdx
	mov eax, ecx
	cpuid
	mov [rdi + 0 * 4], eax
	mov [rdi + 1 * 4], ebx
	mov [rdi + 2 * 4], edx
	mov [rdi + 3 * 4], ecx
	pop rdi
	ret
mk_cpuid_hw endp


end
