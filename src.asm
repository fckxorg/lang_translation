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
; Saving left expression result to stack
		push	rax
; Moving right expression to RCX
		mov		rcx, rax
; Popping first expression result to RBX
		pop		rbx
		cmp		rbx, rcx
		jne		0x562c4d92cd90

; Placing return value (num) to RAX register
		mov		rax, [rbp + 0]
		ret
		jmp		0x562c4d92ce50
0x562c4d92cd90:
; Initializing variable: subnum
		mov		[rbp + 0], rax
; Assigning to variable: subnum
		mov		[rbp + 0], rax
; Assigning to variable: num
		mov		[rbp + 0], rax
; Placing return value (num) to RAX register
		mov		rax, [rbp + 0]
		ret
0x562c4d92ce50:

main:
		push	rbp
		mov		rbp, rsp
		add		rbp, 0x10
; Initializing variable: test
		mov		[rbp + 0], 0
; Assigning to variable: test
		mov		[rbp + 0], rax

