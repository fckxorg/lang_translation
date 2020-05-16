#ifndef IOSTREAM
#include <iostream>

char RAX[] = "rax";
char RBX[] = "rbx";
char RCX[] = "rcx";

char RBP[] = "rbp";
char RSP[] = "rsp";
char RDI[] = "rdi";

void PUSH(FILE* out, char reg[]) {
    fprintf(out, "\t\tpush\t%s\n", reg);
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

void XOR(FILE* out, char reg1[], char reg2[]) {
    fprintf(out, "\t\txor\t\t%s, %s\n", reg1, reg2);
}

void ADD(FILE* out, char reg[], int immed) {
    fprintf(out, "\t\tadd\t\t%s, %d\n", reg, immed);
}

void CMP(FILE* out, char reg1[], char reg2[]) {
    fprintf(out, "\t\tcmp\t\t%s, %s\n", reg1, reg2);
}

void SYSCALL(FILE* out) {
    fprintf(out, "\t\tsyscall\n\n");
}

void RET(FILE* out) {
    fprintf(out, "\t\tret\n");
}

#endif