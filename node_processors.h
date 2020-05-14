#include <vector>
#include "tree.h"
#include "instructions.h"


struct Function {
    string_view name = "";
    int n_args = 0;
};

std::vector<Function> functions = {};

namespace process {
    void ProgramRoot(Node* node, std::ofstream& out);
    void Declaration(Node* node, std::ofstream& out);
    void Function();
    void DeclarationVarlist();
    void ID();
    void Block();
    void Operator();
    void Intialize();
    void Input();
    void Output();
    void Call();
    void CallVarlist();
    void Assign();
    void If();
    void Branches();
    void Arithmetic();
    void Return();
    void At();
};

void process::ProgramRoot(Node* node, std::ofstream& out) {
    // calls main and finishes program

    out << "\t\tglobal _start\n";
    out << "\t\tsection .text\n";
    out << "_start:\n";
    out << CALL << "main\n";
    out << MOV << RAX << ", 60\n";
    out << XOR << RDI << ", " << RDI << "\n";
    out << SYS << "\n";

    // calling declaration processing
    // declarations always start on the right, as it defined in standard
    process::Declaration(node->right, out);
}

void process::Declaration(Node* node, std::ofstream& out){}