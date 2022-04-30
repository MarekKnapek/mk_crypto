public @mk_cpuid_hw@8


.model flat
.code


@mk_cpuid_hw@8 proc
	push edi
	mov edi, edx
	mov eax, ecx
	cpuid
	mov [edi + 0 * 4], eax
	mov [edi + 1 * 4], ebx
	mov [edi + 2 * 4], edx
	mov [edi + 3 * 4], ecx
	pop edi
	ret
@mk_cpuid_hw@8 endp


end
