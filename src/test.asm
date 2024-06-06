global _main
_main:
    mov	DWORD PTR -4[rbp], 10
	mov	DWORD PTR -8[rbp], 22
    mov	DWORD PTR -12[rbp], 0
    mov rax, DWORD PTR -4[rbp]
    add rax, DWORD PTR -8[rbp]
