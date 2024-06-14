section .text
	global _start
_start:
	push rbp
	mov rbp, rsp
	mov rax, [fiba]
	mov rax, 0
	mov [fiba], rax
	mov rax, [fibb]
	mov rax, 1
	mov [fibb], rax
	mov rax, [sum]
	mov rax, 1
	mov [sum], rax
	mov rax, [nth]
	mov rax, 0
	mov [nth], rax
	jmp .loop0
	mov rax, 0
.loop0:
	mov rax, [sum]
	cmp rax, 100
	jge .end0
	mov rax, [nth]
	mov rax, [fiba]
	mov [nth], rax
	push rax
	mov rax, [fibb]
	pop rbx
	add rax, rbx
	mov [nth], rax
	mov rax, [fibb]
	mov [fiba], rax
	mov rax, [nth]
	mov [fibb], rax
	mov rax, [if_sum_higher]
	mov rax, [sum]
	mov [if_sum_higher], rax
	push rax
	mov rax, [nth]
	pop rbx
	add rax, rbx
	mov [if_sum_higher], rax
	mov rax, [if_sum_higher]
	cmp rax, 100
	jl .end_if0
	mov rax, 60
	mov rdi, [sum]
	syscall
.end_if0:
	mov rax, [sum]
	mov [sum], rax
	push rax
	mov rax, [nth]
	pop rbx
	add rax, rbx
	mov [sum], rax
	jmp .loop0
.end0:
	mov rax, 60
	mov rdi, [sum]
	syscall
section .data
	fiba dq 0
	fibb dq 0
	sum dq 0
	nth dq 0
	if_sum_higher dq 0
