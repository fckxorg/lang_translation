#include <vector>
#include <unordered_map>
#include "tree.h"
#include "instructions.h"


struct FunctionData {
    string_view name = "";
    int n_args = 0;
    int n_vars = 0;

    //positive offset stands for argmunets, relative to return address
    //negative offset stands for local vars, relative to last push-saved register
    std::unordered_map<string_view, int> variables = {}; 

    FunctionData() = default;
    ~FunctionData() = default;
};

std::vector<FunctionData*> functions = {};

namespace process {
    void DeclarationVarlist(Node* node, FunctionData* func); //Offset fix needed
    void ProgramRoot(Node* node, std::ofstream& out); // done
    void Declaration(Node* node, std::ofstream& out); // done
    void CallVarlist(Node* node, std::ofstream& out);
    void Expression(Node* node, std::ofstream& out);
    void Intialize(Node* node, FunctionData* func, std::ofstream& out);
    void GetLocals(Node* node, FunctionData* func);   // done
    void Branches(Node* node, std::ofstream& out);
    void Function(Node* node, std::ofstream& out);    // done
    void Operator(Node* node, FunctionData* func, std::ofstream& out); // done
    void Assign(Node* node, FunctionData* func, std::ofstream& out);
    void Output(Node* node, FunctionData* func, std::ofstream& out);
    void Return(Node* node, FunctionData* func, std::ofstream& out);
    void Block(Node* node, FunctionData* func, std::ofstream& out); // done
    void While(Node* node, FunctionData* func, std::ofstream& out);
    void Input(Node* node, FunctionData* func, std::ofstream& out);
    void Call(Node* node, FunctionData* func, std::ofstream& out);
    void If(Node* node, FunctionData* func, std::ofstream& out);
    void ID(Node* node, std::ofstream& out);
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

void process::Declaration(Node* node, std::ofstream& out) {
    if(node->left) {
        process::Declaration(node->left, out);
    }
    process::Function(node->right, out);
}

void process::Function(Node* node, std::ofstream& out) {
    // new function data storage for function table
    FunctionData* func = new FunctionData();

    // setting function name in structure
    func->name = node->right->value;

    out << func->name << ":\n";
    
    // getting number of args, their names and setting their offsets in stack
    process::DeclarationVarlist(node->left, func);
    
    // getting local variables names and setting theit offsets in stack
    process::GetLocals(node->right->right, func);

    // process and output block
    process::Block(node->right->right, func, out);

    functions.push_back(func);

}

void process::DeclarationVarlist(Node* node, FunctionData* func) {

    // if list has variable add it to function structure

    if(node->right) {
        func->variables[node->right->value] = func->n_args * 8; //TODO find out the right offset for local varibles
        ++(func->n_args);
    }

    // if it is not list end continue adding variables
    if(node->left) {
        process:DeclarationVarlist(node->left, func);
    }
}

void process::GetLocals(Node* node, FunctionData* func) {
    // if INITIALIZE block was found, add variable to fucntion structure
    if(node->value == "INITIALIZE") {
        func->variables[node->right->value] = - func->n_vars * 8; //TODO find out the right offset for local varibles
        ++(func->n_vars);
    }

    // continue search if possible

    if(node->left) {
        GetLocals(node->left, func);
    }

    if(node->right) {
        GetLocals(node->right, func);
    }
}

void process::Block(Node* node, FunctionData* func, std::ofstream& out) {
    if(node->right) {
        process::Operator(node->right, func, out);
    }
}

void process::Operator(Node* node, FunctionData* func, std::ofstream& out) {
    if(node->right) {
        string_view operation = node->right->value;

        if(operation == "INITIALIZE") {
            process::Intialize(node->right, func, out);
        }
        if(operation == "INPUT") {
            process::Input(node->right, func, out);
        }
        if(operation == "OUTPUT") {
            process::Output(node->right, func, out);
        }
        if(operation == "CALL") {
            process::Call(node->right, func, out);
        }
        if(operation == "IF") {
            process::If(node->right, func, out);
        }
        if(operation == "WHILE") {
            process::While(node->right, func, out);
        }
        if(operation == "RETURN") {
            process::Return(node->right, func, out);
        }
        if(operation == "ASSIGN") {
            process::Assign(node->right, func, out);
        }
    }
    if(node->left) {
        process::Operator(node->left, func, out);
    }

}

void process::Intialize(Node* node, FunctionData* func, std::ofstream& out) {}
void process::Input(Node* node, FunctionData* func, std::ofstream& out) {}
void process::Output(Node* node, FunctionData* func, std::ofstream& out) {}
void process::Call(Node* node, FunctionData* func, std::ofstream& out) {}
void process::If(Node* node, FunctionData* func, std::ofstream& out) {}
void process::While(Node* node, FunctionData* func, std::ofstream& out) {}
void process::Return(Node* node, FunctionData* func, std::ofstream& out) {}
void process::Assign(Node* node, FunctionData* func, std::ofstream& out) {}
