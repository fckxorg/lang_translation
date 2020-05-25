#ifndef CSTRING
#include <cstring>
#endif

const int MAX_EXTENSION_SIZE = 4;

const char ASM_EXTENSION[] = ".asm";
const char OBJECT_EXTENSION[] = ".o";

char* changeExtension(char* filename, const char* extension) {
    char* dot_position = strchr(filename, '.');
    size_t name_length = dot_position - filename;
    char* new_filename = new char[name_length + MAX_EXTENSION_SIZE]();
    memcpy(new_filename, filename, name_length);
    strcat(new_filename, extension);

    return new_filename;
}