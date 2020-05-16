		global _start
		section .text
_start:
		call	main
		mov		rax, 60
		xor		rdi, rdi
		syscall

factorial { @ } { BLOCK { @ } { OP { @ } { IF { EQUAL { num } { 1 } } { C { BLOCK { @ } { OP { OP { OP { OP { OP { @ } { RETURN { @ } { num } } } { ASSIGN { num } { MUL { num } { subnum } } } } { ASSIGN { subnum } { CALL { factorial } { VARLIST { @ } { subnum } } } } } { INITIALIZE { SUB { num } { 1 } } { subnum } } } { OUTPUT { @ } { num } } } } { BLOCK { @ } { OP { @ } { RETURN { @ } { num } } } } } } } } } } } { FUNCTION { VARLIST } { main { @ } { BLOCK { @ } { OP { OP { OP { OP { OP { @ } { OUTPUT { @ } { test } } } { ASSIGN { test } { CALL { factorial } { VARLIST { @ } { test } } } } } { OUTPUT { @ } { test } } } { INPUT { @ } { test } } } { INITIALIZE { @ } { test } } } } } } } } :
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
		jne		0x55730bdafd90

; Placing return value (num } } } } } } } } } } } { FUNCTION { VARLIST } { main { @ } { BLOCK { @ } { OP { OP { OP { OP { OP { @ } { OUTPUT { @ } { test } } } { ASSIGN { test } { CALL { factorial } { VARLIST { @ } { test } } } } } { OUTPUT { @ } { test } } } { INPUT { @ } { test } } } { INITIALIZE { @ } { test } } } } } } } } ) to RAX register
		mov		rax, [rbp + 0]
		ret
		jmp		0x55730bdafe50
0x55730bdafd90:
; Initializing variable: subnum } } } { OUTPUT { @ } { num } } } } { BLOCK { @ } { OP { @ } { RETURN { @ } { num } } } } } } } } } } } { FUNCTION { VARLIST } { main { @ } { BLOCK { @ } { OP { OP { OP { OP { OP { @ } { OUTPUT { @ } { test } } } { ASSIGN { test } { CALL { factorial } { VARLIST { @ } { test } } } } } { OUTPUT { @ } { test } } } { INPUT { @ } { test } } } { INITIALIZE { @ } { test } } } } } } } } 
		mov		[rbp + 0], rax
; Assigning to variable: subnum } { CALL { factorial } { VARLIST { @ } { subnum } } } } } { INITIALIZE { SUB { num } { 1 } } { subnum } } } { OUTPUT { @ } { num } } } } { BLOCK { @ } { OP { @ } { RETURN { @ } { num } } } } } } } } } } } { FUNCTION { VARLIST } { main { @ } { BLOCK { @ } { OP { OP { OP { OP { OP { @ } { OUTPUT { @ } { test } } } { ASSIGN { test } { CALL { factorial } { VARLIST { @ } { test } } } } } { OUTPUT { @ } { test } } } { INPUT { @ } { test } } } { INITIALIZE { @ } { test } } } } } } } } 
		mov		[rbp + 0], rax
; Assigning to variable: num } { MUL { num } { subnum } } } } { ASSIGN { subnum } { CALL { factorial } { VARLIST { @ } { subnum } } } } } { INITIALIZE { SUB { num } { 1 } } { subnum } } } { OUTPUT { @ } { num } } } } { BLOCK { @ } { OP { @ } { RETURN { @ } { num } } } } } } } } } } } { FUNCTION { VARLIST } { main { @ } { BLOCK { @ } { OP { OP { OP { OP { OP { @ } { OUTPUT { @ } { test } } } { ASSIGN { test } { CALL { factorial } { VARLIST { @ } { test } } } } } { OUTPUT { @ } { test } } } { INPUT { @ } { test } } } { INITIALIZE { @ } { test } } } } } } } } 
		mov		[rbp + 0], rax
; Placing return value (num } } } { ASSIGN { num } { MUL { num } { subnum } } } } { ASSIGN { subnum } { CALL { factorial } { VARLIST { @ } { subnum } } } } } { INITIALIZE { SUB { num } { 1 } } { subnum } } } { OUTPUT { @ } { num } } } } { BLOCK { @ } { OP { @ } { RETURN { @ } { num } } } } } } } } } } } { FUNCTION { VARLIST } { main { @ } { BLOCK { @ } { OP { OP { OP { OP { OP { @ } { OUTPUT { @ } { test } } } { ASSIGN { test } { CALL { factorial } { VARLIST { @ } { test } } } } } { OUTPUT { @ } { test } } } { INPUT { @ } { test } } } { INITIALIZE { @ } { test } } } } } } } } ) to RAX register
		mov		rax, [rbp + 0]
		ret
0x55730bdafe50:

main { @ } { BLOCK { @ } { OP { OP { OP { OP { OP { @ } { OUTPUT { @ } { test } } } { ASSIGN { test } { CALL { factorial } { VARLIST { @ } { test } } } } } { OUTPUT { @ } { test } } } { INPUT { @ } { test } } } { INITIALIZE { @ } { test } } } } } } } } :
		push	rbp
		mov		rbp, rsp
		add		rbp, 0x10
; Initializing variable: test } } } } } } } } 
		mov		[rbp + 0], 0
; Assigning to variable: test } { CALL { factorial } { VARLIST { @ } { test } } } } } { OUTPUT { @ } { test } } } { INPUT { @ } { test } } } { INITIALIZE { @ } { test } } } } } } } } 
		mov		[rbp + 0], rax

