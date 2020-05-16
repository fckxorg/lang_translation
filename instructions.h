#ifndef IOSTREAM
#include <iostream>

char RAX[] = "rax";
char RBX[] = "rbx";
char RCX[] = "rcx";

char RBP[] = "rbp";
char RSP[] = "rsp";

void push(FILE* out, char reg[]) {
    fprintf(out, "\t\tpush\t%s\n", reg);
}

void mov(FILE* out, char dest_reg[], char src_reg[]) {
    fprintf(out, "\t\tmov\t\t%s, %s\n", dest_reg, src_reg);
}

void mov(FILE* out, char dest[], int immed) {
    fprintf(out, "\t\tmov\t\t%s, %d\n", dest, immed);
}

void mov(FILE* out, char dest_reg[], int offset, char src_reg[]) {
    char sign = offset >= 0 ? '+' : '-'; 
    fprintf(out, "\t\tmov\t\t[%s %c %d], %s",dest_reg, sign, abs(offset), src_reg);
}

#endif