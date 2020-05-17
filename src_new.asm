		global _start
		section .text
_start:
		call	main
		mov		rax, 60
		xor		rdi, rdi
		syscall

atoi:
		xor		rax, rax
		xor		rdi, rdi
		mov		rdx, 32
		mov		rsi, io_buffer
		syscall

		xor		rax, rax
		xor		rbx, rbx
		mov		rcx, 10
atoi_loop:
		mov		bl, byte [rsi]
		cmp		bl, 10
		je		atoi_loop_end
		sub		bl, 48
		mul		rcx
		add		al, bl
		inc		rsi
		jmp     atoi_loop
atoi_loop_end:
		ret
itoa:
		mov		rbx, 31
		mov		rcx, 10
.renomLoop:
		cmp		rax, 0
		je		.renomLoopEnd
		xor		rdx, rdx
		div		rcx
		push	rax
		mov		rax, rdx
		add		rax, 48
		mov		[io_buffer + rbx], al
		pop		rax
		dec		rbx
		xor		rdx, rdx
		jmp 	.renomLoop
.renomLoopEnd:
		mov		rsi, io_buffer
		add		rsi, rbx
		inc		rsi
		mov		rax, 32
		sub		rax, rbx
		mov		rdx, rax
		mov		rax, 1
		mov		rdi, 1
		syscall

		ret
factorial:
		push	rbp
		mov		rbp, rsp
		add		rbp, 16
		sub		rsp, 8
		push	rbx
		push	rcx
		push	rdx
		push	rdi
		push	rsi
		mov		rax, [rbp + 0]
; Saving left expression result to stack
		push	rax
		mov		rax, 1
; Moving right expression to RCX
		mov		rcx, rax
; Popping first expression result to RBX
		pop		rbx
		cmp		rbx, rcx
		jne		cond0x5566aa1cdd90

; Placing return value (num) to RAX register
		mov		rax, [rbp + 0]
		pop		rsi
		pop		rdi
		pop		rdx
		pop		rcx
		pop		rbx
		add		rsp, 8
		pop		rbp
		ret
		jmp		cond0x5566aa1cde50
cond0x5566aa1cdd90:
; Writing num to stdout
		mov		rax, [rbp + 0]
		call	itoa
; Initializing variable: subnum
		mov		rax, [rbp + 0]
		push	rax
		mov		rax, 1
		mov		rcx, rax
		pop		rax
		mov		rbx, rax
		sub		rbx, rcx
		mov		rax, rbx
		mov		[rbp - 24], rax
		push	qword [rbp - 24]
		call	factorial
		add		rsp, 8
; Assigning to variable: subnum
		mov		[rbp - 24], rax
		mov		rax, [rbp + 0]
		push	rax
		mov		rax, [rbp - 24]
		mov		rcx, rax
		pop		rax
		mov		rbx, rax
		mov		rax, rbx
		mul		rcx
; Assigning to variable: num
		mov		[rbp + 0], rax
; Placing return value (num) to RAX register
		mov		rax, [rbp + 0]
		pop		rsi
		pop		rdi
		pop		rdx
		pop		rcx
		pop		rbx
		add		rsp, 8
		pop		rbp
		ret
cond0x5566aa1cde50:

main:
		push	rbp
		mov		rbp, rsp
		add		rbp, 16
		sub		rsp, 8
		push	rbx
		push	rcx
		push	rdx
		push	rdi
		push	rsi
; Initializing variable: test
		mov		qword [rbp - 24], 0
; Reading test from stdin
		call	atoi
		mov		[rbp - 24], rax
; Writing test to stdout
		mov		rax, [rbp - 24]
		call	itoa
		push	qword [rbp - 24]
		call	factorial
		add		rsp, 0
; Assigning to variable: test
		mov		[rbp - 24], rax
; Writing test to stdout
		mov		rax, [rbp - 24]
		call	itoa
		pop		rsi
		pop		rdi
		pop		rdx
		pop		rcx
		pop		rbx
		add		rsp, 8
		pop		rbp
		ret

		section .data
io_buffer:	times 32 db 0
