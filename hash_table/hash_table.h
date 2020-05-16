#ifndef CSTRING
#include <cstring>
#endif

#include <functional>

#include "custom_list.h"
#include "murmur_hash.h"

struct Variable {
    const char* name = nullptr;
    int offset = 0;

    Variable(const char* name, const int offset) : name(name), offset(offset) {} 
};

class HashTable {
    List<Variable>* table = nullptr;
    const int size = 0;
    public:
        HashTable(int size = 997) : size(size) {
            table = new List<Variable>[size]();
        }
        ~HashTable() {
            delete[] table;
        }

        HashTable(const HashTable& other) = delete;
        HashTable& operator=(const HashTable& other) = delete;

        bool contains(const char* value) {
            const int len = strlen(value);
            int hash = murmur_hash(value, len) % size;

            return table[hash].contains(value);
        }

        int& operator[](const char* value) {
            const int len = strlen(value);
            int hash = murmur_hash(value, len) % size;

            if(!table[hash].contains(value)) {
                table[hash].push_back(Variable(value, 0));
            }
            return table[hash][value];
        }
};