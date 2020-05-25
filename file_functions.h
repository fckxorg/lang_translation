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