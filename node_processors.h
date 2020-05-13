#include <vector>
#include "tree.h"

struct Function {
    string_view name = "";
    int n_args = 0;
};

std::vector<Function> functions = {};

void processProgramRoot(std::ofstream& out){
    out << "\t\tglobal _start\n";
    out << "\t\tsection .text\n";
    out << "_start:\n";
    out << "\t\tcall\tmain\n";
    out << "\t\txor\trdi, rdi\n";
    out << "\t\tmov\trax, 60\n";
    out << "\t\tsyscall\n";
}

void processDeclaration(){}

void processFunction() {}