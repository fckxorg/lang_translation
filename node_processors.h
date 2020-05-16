#include <vector>
#include <unordered_map>
#include "tree.h"
#include "instructions.h"


struct FunctionData {
    const char* name = nullptr;
    int n_args = 0;
    int n_vars = 0;

    //positive offset stands for argmunets, relative to return address
    //negative offset stands for local vars, relative to last push-saved register
    std::unordered_map<string_view, int> variables = {}; 

    FunctionData() = default;
    ~FunctionData() = default;
};


void CheckVariableExists(FunctionData* func, const string_view& var) {
    if(func->variables.find(var) == func->variables.end()) {
        std::runtime_error("Variable does not exist! Aborting...");
    }
}

namespace process {
    void DeclarationVarlist(Node* node, FunctionData* func); //TODO Offset fix needed
    void ProgramRoot(Node* node, FILE* out); // done
    void Declaration(Node* node, FILE* out); // done
    void CallVarlist(Node* node, FILE* out);
    void Expression(Node* node, FunctionData* func, FILE* out); // calculation result must be stored in RAX
    void Intialize(Node* node, FunctionData* func, FILE* out);  // done
    void Condition(Node* node, FunctionData* func, FILE* out);  // done
    void GetLocals(Node* node, FunctionData* func);   // done
    void Function(Node* node, FILE* out);    // TODO add used registers to saved ones
    void Operator(Node* node, FunctionData* func, FILE* out); // done
    void Assign(Node* node, FunctionData* func, FILE* out);   // done
    void Output(Node* node, FunctionData* func, FILE* out);
    void Return(Node* node, FunctionData* func, FILE* out);   // TODO
    void Block(Node* node, FunctionData* func, FILE* out); // done
    void While(Node* node, FunctionData* func, FILE* out); //done
    void Input(Node* node, FunctionData* func, FILE* out);
    void Call(Node* node, FunctionData* func, FILE* out);
    void If(Node* node, FunctionData* func, FILE* out);    // done
};

void process::ProgramRoot(Node* node, FILE* out) {
    // calls main and finishes program
    fprintf(out, "\t\tglobal _start\n");
    fprintf(out, "\t\tsection .text\n");
    fprintf(out, "_start:\n");
    fprintf(out, "\t\tcall\tmain\n");
    MOV(out, RAX, 60);
    XOR(out, RDI, RDI);
    SYSCALL(out);
    // calling declaration processing
    // declarations always start on the right, as it defined in standard
    process::Declaration(node->right, out);
}

void process::Declaration(Node* node, FILE* out) {
    if(node->left) {
        process::Declaration(node->left, out);
    }
    process::Function(node->right, out);
}

void process::Function(Node* node, FILE* out) {
    // new function data storage for function table
    FunctionData* func = new FunctionData();

    // setting function name in structure
    func->name = node->right->value.data();

    fprintf(out, func->name);
    fprintf(out, ":\n");
    PUSH(out, RBP);
    MOV(out, RBP, RSP);
    ADD(out, RBP, 0x10);

    // getting number of args, their names and setting their offsets in stack
    process::DeclarationVarlist(node->left, func);
    
    // getting local variables names and setting theit offsets in stack
    process::GetLocals(node->right->right, func);

    // process and output block
    process::Block(node->right->right, func, out);

    fprintf(out, "\n");
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

void process::Block(Node* node, FunctionData* func, FILE* out) {
    if(node->right) {
        process::Operator(node->right, func, out);
    }
}

void process::Operator(Node* node, FunctionData* func, FILE* out) {
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

void process::Intialize(Node* node, FunctionData* func, FILE* out) {
    string_view var_name = node->right->value;
    CheckVariableExists(func, var_name);

    int var_offset = func->variables[var_name];

    fprintf(out , "; Initializing variable: %s\n", var_name.data());

    if(node->left) {
        process::Expression(node->left, func, out);
        MOV(out, RBP, var_offset, RAX);
    }
    else {
        MOV(out, RBP, var_offset, 0);
    }
}

void process::Assign(Node* node, FunctionData* func, FILE* out) {
    string_view var_name = node->left->value;
    CheckVariableExists(func, var_name);
    
    process::Expression(node->left, func, out);

    int var_offset = func->variables[var_name];
    fprintf(out, "; Assigning to variable: %s\n", var_name.data());
    MOV(out, RBP, var_offset, RAX);
}

void process::Return(Node* node, FunctionData* func, FILE* out) {
    string_view var_name = node->right->value;
    CheckVariableExists(func, var_name);

    int var_offset = func->variables[var_name];
    char sign = var_offset >= 0 ? '+' : '-'; 


    fprintf(out, "; Placing return value (%s) to RAX register\n", var_name.data());
    MOV(out, RAX, RBP, var_offset);
    //TODO Need to pop every saved value here and destroy stack frame;
    RET(out);

}

void process::If(Node* node, FunctionData* func, FILE* out) {
    process::Condition(node, func, out);

    process::Block(node->right->right, func, out);

    if(node->right->left) {
        fprintf(out, "\t\tjmp\t\t%p\n", node->right);
    }

    fprintf(out, "%p:\n", node);

    if(node->right->left) {
        process::Block(node->right->left, func, out);
        fprintf(out, "%p:\n", node->right);
    }
}

void process::While(Node* node, FunctionData* func, FILE* out) {
    fprintf(out, "while_%p:\n", node);
    process::Condition(node, func, out);
    process::Block(node->right, func, out);
    fprintf(out, "%p:\n", node);
    
}

void process::Condition(Node* node, FunctionData* func, FILE* out) {
    process::Expression(node->left->left, func, out);
    fprintf(out, "; Saving left expression result to stack\n");
    PUSH(out, RAX);
    
    process::Expression(node->left->right, func, out);
    fprintf(out, "; Moving right expression to RCX\n");
    MOV(out, RCX, RAX);

    fprintf(out, "; Popping first expression result to RBX\n");
    POP(out, RBX);

    CMP(out, RBX, RCX);

    string_view comp = node->left->value;

    if(comp == "EQUAL") {
        fprintf(out, "\t\tjne\t\t%p\n\n", node);  //using else condition for jump
    }
    else if(comp == "ABOVE") {
        fprintf(out, "\t\tjbe\t\t%p\n\n", node);
    }
    else if(comp == "BELOW") {
        fprintf(out, "\t\tjae\t\t%p\n\n", node);
    }
}

void process::Input(Node* node, FunctionData* func, FILE* out) {}
void process::Output(Node* node, FunctionData* func, FILE* out) {}
void process::Call(Node* node, FunctionData* func, FILE* out) {}
void process::Expression(Node* node, FunctionData* func, FILE* out) {}
void CallVarlist(Node* node, FILE* out);
