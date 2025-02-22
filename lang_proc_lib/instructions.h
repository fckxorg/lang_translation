#ifndef IOSTREAM
#include <iostream>
#endif

// ===================== //
//  Built-in functions   //
//  and system buffers   //
// ===================== //
char IO_BUFFER[] = "io_buffer";


// ===================== //
//     CPU registers     //
// ===================== //
typedef char*  REGISTER;

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
//        Sizes          //
// ===================== //
char QWORD[] = "qword";
char DWORD[] = "dword";
char WORD[]  = "word";
char BYTE[]  = "byte";


// ===================== //
//      Directives       //
//====================== //

void GLOBAL(FILE* out, const char* label) {
    fprintf(out, "\t\tglobal %s\n", label);
}

void SECTION_TEXT(FILE* out) {
    fprintf(out, "\t\tsection .text\n");
}

void SECTION_DATA(FILE* out) {
    fprintf(out, "\t\tsection .data\n");
}


// ===================== //
//     Instructions      //
// ===================== //

void PUSH(FILE* out, char reg[]) {
    fprintf(out, "\t\tpush\t%s\n", reg);
}

void PUSH(FILE* out, char size[], char reg[], int offset) {
    char sign = offset >= 0 ? '+' : '-'; 
    fprintf(out, "\t\tpush\t%s [%s %c %d]\n", size, reg, sign, abs(offset));
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

void MOV(FILE* out, char size[], char dest_reg[], int offset, int immed) {
    char sign = offset >= 0 ? '+' : '-'; 
    fprintf(out, "\t\tmov\t\t%s [%s %c %d], %d\n", size, dest_reg, sign, abs(offset), immed);
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

void JMP(FILE* out, const char* label) {
    fprintf(out, "\t\tjmp\t\t%s\n", label);
}

void JMP(FILE* out, const char* prefix, void* ptr) {
    fprintf(out, "\t\tjmp\t\t%s%p\n\n", prefix, ptr);
}

void JNE(FILE* out, const char* prefix, void* ptr) {
    fprintf(out, "\t\tjne\t\t%s%p\n\n", prefix, ptr);
}

void JBE(FILE* out, const char* prefix, void* ptr) {
    fprintf(out, "\t\tjbe\t\t%s%p\n\n", prefix, ptr);
}

void JAE(FILE* out, const char* prefix, void* ptr) {
    fprintf(out, "\t\tjae\t\t%s%p\n\n", prefix, ptr);
}

void LABEL(FILE* out, const char* label) {
    fprintf(out, "%s:\n", label);
}

void LABEL(FILE* out, const char* prefix, void* ptr) {
    fprintf(out, "%s%p:\n", prefix, ptr);
}

// ===================== //
//  Assembly commenting  //
//      utilities        //
// ===================== //

void COMMENT_INITIALIZING_VARIABLE(FILE* out, const char* var_name) {
    fprintf(out , "; Initializing variable: %s\n", var_name);
}

void COMMENT_ASSIGNING_TO_VARIABLE(FILE* out, const char* var_name) {
    fprintf(out, "; Assigning to variable: %s\n", var_name);
}

void COMMENT_OUTPUT(FILE* out, const char* var_name) {
    fprintf(out, "; Writing %s to stdout\n", var_name);
}

void COMMENT_INPUT(FILE* out, const char* var_name) {
    fprintf(out, "; Reading %s from stdin\n", var_name);
}

void COMMENT_RETURN(FILE* out, const char* var_name) {
    fprintf(out, "; Placing return value (%s) to RAX register\n", var_name);
}

void COMMENT_EXPRESSION_LEFT_PART_SAVING(FILE* out) {
    fprintf(out, "; Saving left expression result to stack\n");
}

void COMMENT_EXPRESSION_LEFT_PART_RESTORING(FILE* out) {
    fprintf(out, "; Popping left expression result to RBX\n");
}

void COMMENT_EXPRESSION_RIGHT_PART_SAVING(FILE* out) {
    fprintf(out, "; Moving right expression to RCX\n");
}

// ===================== //
//   Miscellaneous       //
// ===================== //

void LINE_FEED(FILE* out) {
    fprintf(out, "\n");
}