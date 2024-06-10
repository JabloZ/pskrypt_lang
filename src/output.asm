section .text
	global _start
_start:
	push rbp
	mov rbp, rsp
	mov rax, 60
	mov rdi, 7
	syscall
section .data
	b dd 24
	c dd 25
	d dd 37
	