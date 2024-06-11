section .text
	global _start
_start:
	push rbp
	mov rbp, rsp
	mov rax, [b]
	mov rax, 24
	mov [b], rax
	push rax
	mov rax, 24
	pop rbx
	mov rax, 6
	add rax, rbx
	mov [b], rax
	push rax
	mov rax, 6
	pop rbx
	mov rax, 5
	add rax, rbx
	mov [b], rax
	push rax
	mov rax, 5
	pop rbx
	mov rax, 7
	sub rax, rbx
	mov [b], rax
	mov rax, [d]
	mov rax, [b]
	mov [d], rax
	push rax
	mov rax, [b]
	pop rbx
	mov rax, 7
	add rax, rbx
	mov [d], rax
	mov rax, [c]
	mov rax, [b]
	mov [c], rax
	push rax
	mov rax, [b]
	pop rbx
	mov rax, [d]
	add rax, rbx
	mov [c], rax
	push rax
	mov rax, [d]
	pop rbx
	mov rax, 7
	sub rax, rbx
	mov [c], rax
	mov rax, 60
	mov rdi, [c]
	syscall
section .data
	b dd 0
	d dd 0
	c dd 0
