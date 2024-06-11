section .text
	global _start
_start:
	push rbp
	mov rbp, rsp
    mov rax, [b]
    add rax, 7
    mov [b], rax
	mov rax, 60
	mov rdi, [b]
	syscall
section .data
	b dd 24
	c dd 25
	d dd 37
	