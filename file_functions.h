#ifndef IOSTREAM
#include <iostream>
#endif

size_t getFileSize(FILE* file) {
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

bool fileOpened(FILE* file) {
    if(!file) {
        std::cerr << "Error opening file!\n";
    }
    return file;
}

char* readFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if(!fileOpened(file)) return nullptr;

    size_t size = getFileSize(file);

    char* data = new char[size + 1]();
    fread(data, sizeof(char), size, file);
    fclose(file);
    return data;
}