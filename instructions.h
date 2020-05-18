#ifndef IOSTREAM
#include <iostream>
#endif

// ===================== //
//  Built-in functions   //
//  and system buffers   //
// ===================== //
char ATOI[] = "atoi";
char ITOA[] = "itoa";

char IO_BUFFER[] = "io_buffer";



// ===================== //
//     CPU registers     //
// ===================== //
char RAX[] = "rax";
char RBX[] = "rbx";
char RCX[] = "rcx";
char RDX[] = "rdx";

char AL[]  = "al";
char BL[]  = "bl";

char RBP[] = "rbp";
char RSP[] = "rsp";
char RDI[] = "rdi";
char RSI[] = "rsi";


// ===================== //
//     Instructions      //
// ===================== //

void PUSH(FILE* out, char reg[]) {
    fprintf(out, "\t\tpush\t%s\n", reg);
}

void PUSH_Q(FILE* out, char reg[], int offset) {
    char sign = offset >= 0 ? '+' : '-'; 
    fprintf(out, "\t\tpush\tqword [%s %c %d]\n", reg, sign, abs(offset));
}

void POP(FILE* out, char reg[]) {
    fprintf(out, "\t\tpop\t\t%s\n", reg);
}

void MOV(FILE* out, char dest_reg[], char src_reg[]) {
    fprintf(out, "\t\tmov\t\t%s, %s\n", dest_reg, src_reg);
}

void MOV(FILE* out, char dest[], int immed) {
    fprintf(out, "\t\tmov\t\t%s, %d\n", dest, immed);
}

void MOV(FILE* out, char dest_reg[], int offset, char src_reg[]) {
    char sign = offset >= 0 ? '+' : '-'; 
    fprintf(out, "\t\tmov\t\t[%s %c %d], %s\n",dest_reg, sign, abs(offset), src_reg);
}

void MOV(FILE* out, char dest_reg[], int offset, int immed) {
    char sign = offset >= 0 ? '+' : '-'; 
    fprintf(out, "\t\tmov\t\t[%s %c %d], %d\n",dest_reg, sign, abs(offset), immed);
}

void MOV(FILE* out, char dest_reg[], char src_reg[], int offset) {
    char sign = offset >= 0 ? '+' : '-'; 
    fprintf(out, "\t\tmov\t\t%s, [%s %c %d]\n", dest_reg, src_reg, sign, abs(offset));
}

void MOV(FILE* out, char dest_reg[], char offset_reg[], char src_reg[]) {
    fprintf(out, "\t\tmov\t\t[%s + %s], %s\n", dest_reg, offset_reg, src_reg);
}

void XOR(FILE* out, char reg1[], char reg2[]) {
    fprintf(out, "\t\txor\t\t%s, %s\n", reg1, reg2);
}

void ADD(FILE* out, char reg[], int immed) {
    fprintf(out, "\t\tadd\t\t%s, %d\n", reg, immed);
}

void ADD(FILE* out, char dest_reg[], char src_reg[]) {
    fprintf(out, "\t\tadd\t\t%s, %s\n", dest_reg, src_reg);
}

void CMP(FILE* out, char reg1[], char reg2[]) {
    fprintf(out, "\t\tcmp\t\t%s, %s\n", reg1, reg2);
}

void CMP(FILE* out, char reg[], int immed) {
    fprintf(out, "\t\tcmp\t\t%s, %d\n", reg, immed);
}

void SYSCALL(FILE* out) {
    fprintf(out, "\t\tsyscall\n\n");
}

void RET(FILE* out) {
    fprintf(out, "\t\tret\n");
}

void CALL(FILE* out, const char* function) {
    fprintf(out, "\t\tcall\t%s\n", function);
}

void SUB(FILE* out, char reg[], int immed) {
    fprintf(out, "\t\tsub\t\t%s, %d\n", reg, immed);
}

void SUB(FILE* out, char reg1[], char reg2[]) {
    fprintf(out, "\t\tsub\t\t%s, %s\n", reg1, reg2);
}

void MUL(FILE* out, char reg[]) {
    fprintf(out, "\t\tmul\t\t%s\n", reg);
}

void INC(FILE* out, char reg[]) {
    fprintf(out, "\t\tinc\t\t%s\n", reg);
}

void DEC(FILE* out, char reg[]) {
    fprintf(out, "\t\tdec\t\t%s\n", reg);
}

void DIV(FILE* out, char reg[]) {
    fprintf(out, "\t\tdiv\t\t%s\n", reg);
}

void PUSHA(FILE* out) {
    PUSH(out, RBX);
    PUSH(out, RCX);
    PUSH(out, RDX);
    PUSH(out, RDI);
    PUSH(out, RSI);
}

void POPA(FILE* out) {
    POP(out, RSI);
    POP(out, RDI);
    POP(out, RDX);
    POP(out, RCX);
    POP(out, RBX);
}

void JE(FILE* out, const char* label) {
    fprintf(out, "\t\tje\t\t%s\n", label);
}