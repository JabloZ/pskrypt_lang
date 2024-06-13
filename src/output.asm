section .text
	global _start
_start:
	push rbp
	mov rbp, rsp
	mov rax, [b]
	mov rax, 0
	mov [b], rax
	mov rax, [c]
	mov rax, [b]
	mov [c], rax
	mov rax, [d]
	mov rax, 0
	mov [d], rax
	mov rax, 0
.loop0:
	mov rax, [c]
	cmp rax, 10
	jge .end0
	mov rax, [c]
	mov [c], rax
	push rax
	mov rax, 1
	pop rbx
	add rax, rbx
	mov [c], rax
	jmp .loop0
.end0:
	mov rax, 60
	mov rdi, [c]
	syscall
section .data
	b dd 0
	c dd 0
	d dd 0
