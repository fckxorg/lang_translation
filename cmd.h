#ifndef CSTRING
#include <cstring>
#endif

#ifndef IOSTREAM
#include <iostream>
#endif


const char ASM_EXTENSION[] = ".asm";
const char OBJECT_EXTENSION[] = ".o";

const char NASM[] = "nasm -felf64 ";
const char LD[] = "ld ";

const int MAX_EXTENSION_SIZE = 4;
const int NASM_COMMAND_LENGTH = 14;
const int LD_COMMAND_LENGTH = 3;

char* changeExtension(char* filename, const char* extension) {
    char* dot_position = strchr(filename, '.');
    size_t name_length = dot_position - filename;
    char* new_filename = new char[name_length + MAX_EXTENSION_SIZE]();
    memcpy(new_filename, filename, name_length);
    strcat(new_filename, extension);

    return new_filename;
}

void NASMCompile(char* filename) {
    size_t filename_length = strlen(filename);
    char* command = new char[NASM_COMMAND_LENGTH + filename_length]();
    memcpy(command, NASM, NASM_COMMAND_LENGTH);
    strcat(command, filename);
    system(command);
}


