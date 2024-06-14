section .text
	global _start
_start:
	push rbp
	mov rbp, rsp
	mov rax, [c]
	mov rax, 2
	mov [c], rax
	mov rax, [d]
	mov rax, 0
	mov [d], rax
	jmp .loop0
	mov rax, 0
.loop0:
	mov rax, [c]
	cmp rax, 0
	jl .end0
	mov rax, [d]
	mov rax, [d]
	mov [d], rax
	push rax
	mov rax, 2
	pop rbx
	add rax, rbx
	mov [d], rax
	mov rax, [c]
	mov rax, [c]
	mov [c], rax
	push rax
	pop rbx
	mov rax, 1
	sub rbx, rax
	mov [c], rbx
	mov rax, rbx
	jmp .loop0
.end0:
	mov rax, 60
	mov rdi, [d]
	syscall
section .data
	c dq 0
	d dq 0
