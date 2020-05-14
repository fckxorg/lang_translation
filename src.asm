		global _start
		section .text
_start:
		call	main
		mov		rax, 60
		xor		rdi, rdi
		syscall
factorial:
		push	rbp
		mov		rbp, rsp
		add		rbp, 0x10
main:
		push	rbp
		mov		rbp, rsp
		add		rbp, 0x10
; Initializing variable: test
		mov		[rbp + 0], 0
; Assigning to variable: test
		mov		[rbp + 0], rax
