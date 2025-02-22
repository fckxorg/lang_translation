#include <vector>
#include <unordered_map>
#include "../tree/tree.h"
#include "instructions.h"
#include "../hash_table/hash_table.h"
#include "constants.h"


struct FunctionData {
    const char* name = nullptr;
    int n_args = 0;
    int n_vars = 0;

    //positive offset stands for argmunets, relative to RBP position
    //negative offset stands for local vars, relative to RBP position
    HashTable variables = {};

    FunctionData() = default;
    ~FunctionData() = default;
};


void CheckVariableExists(FunctionData* func, const char* var) {
    if(func->variables.contains(var)) {
        std::runtime_error("Variable does not exist! Aborting...");
    }
}

void PrintAtoi(FILE* out) {
    LABEL(out, ATOI);
    XOR(out, RAX, RAX);
    XOR(out, RDI, RDI);
    MOV(out, RDX, IO_BUFFER_SIZE);
    MOV(out, RSI, IO_BUFFER);
    SYSCALL(out);

    XOR(out, RAX, RAX);
    XOR(out, RBX, RBX);      
    MOV(out, RCX, INPUT_NUMBER_SYSTEM);     
    LABEL(out, ATOI_LOOP);
    fprintf(out, "\t\tmov\t\tbl, byte [rsi]\n");
    CMP(out, BL, '\n');
    JE(out, ATOI_LOOP_END);
    SUB(out, BL, '0');
    MUL(out, RCX);
    ADD(out, AL, BL);
    INC(out, RSI);
    JMP(out, ATOI_LOOP);
    LABEL(out, ATOI_LOOP_END);
    RET(out);
}

void printItoa(FILE* out) {
    LABEL(out, ITOA);
    MOV(out, RBX, IO_BUFFER_SIZE - 1);
    MOV(out, RCX, OUTPUT_NUMBER_SYSTEM);
    LABEL(out, RENOMINATION_LOOP);
    CMP(out, RAX, 0);
    JE(out, RENOMINATION_LOOP_END);
    XOR(out, RDX, RDX);
    DIV(out, RCX);
    PUSH(out, RAX);
    MOV(out, RAX, RDX);
    ADD(out, RAX, '0');
    MOV(out, IO_BUFFER, RBX, AL);
    POP(out, RAX);
    DEC(out, RBX);
    XOR(out, RDX, RDX);
    JMP(out, RENOMINATION_LOOP);		
		
    LABEL(out, RENOMINATION_LOOP_END);
    MOV(out, RSI, IO_BUFFER);
    ADD(out, RSI, RBX);
    INC(out, RSI);
    MOV(out, RAX, IO_BUFFER_SIZE);
    SUB(out, RAX, RBX);
    MOV(out, RDX, RAX);
    MOV(out, RAX, 1);
    MOV(out, RDI, 1);
    SYSCALL(out);
    RET(out);
}

namespace process {
    void DeclarationVarlist(Node* node, FunctionData* func);                    // done
    void ProgramRoot(Node* node, FILE* out);                                    // done
    void Declaration(Node* node, FILE* out);                                    // done
    void CallVarlist(Node* node, FunctionData* func, FILE* out, int& n_args);   // done
    void Expression(Node* node, FunctionData* func, FILE* out);                 // done
    void Intialize(Node* node, FunctionData* func, FILE* out);                  // done
    void Condition(Node* node, FunctionData* func, FILE* out);                  // done
    void GetLocals(Node* node, FunctionData* func);                             // done
    void Function(Node* node, FILE* out);                                       // done
    void Operator(Node* node, FunctionData* func, FILE* out);                   // done
    void Assign(Node* node, FunctionData* func, FILE* out);                     // done
    void Output(Node* node, FunctionData* func, FILE* out);                     // done
    void Return(Node* node, FunctionData* func, FILE* out);                     // done
    void Block(Node* node, FunctionData* func, FILE* out);                      // done
    void While(Node* node, FunctionData* func, FILE* out);                      // done
    void Input(Node* node, FunctionData* func, FILE* out);                      // done
    void Call(Node* node, FunctionData* func, FILE* out);                       // done
    void If(Node* node, FunctionData* func, FILE* out);                         // done
};

void process::ProgramRoot(Node* node, FILE* out) {
    // calls main and finishes program
    GLOBAL(out, START_LABEL);
    SECTION_TEXT(out);
    LABEL(out, START_LABEL);
    CALL(out, "main");
    MOV(out, RAX, 60);
    XOR(out, RDI, RDI);
    SYSCALL(out);

    PrintAtoi(out);
    printItoa(out);
    // calling declaration processing
    // declarations always start on the right, as it defined in standard
    process::Declaration(node->right, out);
    SECTION_DATA(out);
    fprintf(out, "io_buffer:\ttimes 32 db 0\n");
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
    func->name = node->right->value;
    LABEL(out, func->name);;
    PUSH(out, RBP);
    MOV(out, RBP, RSP);
    ADD(out, RBP, STACK_FRAME_OFFSET);

    // getting number of args, their names and setting their offsets in stack
    process::DeclarationVarlist(node->left, func);
    
    // getting local variables names and setting theit offsets in stack
    process::GetLocals(node->right->right, func);
    SUB(out, RSP, func->n_vars * ELEMENT_SIZE);
    PUSHA(out);
    // process and output block
    process::Block(node->right->right, func, out);

    // as it defined in standard main 
    // doesn't have return instruction by default
    if(strcmp(func->name, "main") == 0) {
        POPA(out);
        ADD(out, RSP, func->n_vars * ELEMENT_SIZE);
        POP(out, RBP);
        RET(out);
    }
    LINE_FEED(out);
    delete func;
}

void process::DeclarationVarlist(Node* node, FunctionData* func) {

    // if list has variable add it to function structure

    if(node->right) {
        func->variables[node->right->value] = func->n_args * ELEMENT_SIZE; //TODO find out the right offset for local varibles
        ++(func->n_args);
    }

    // if it is not list end continue adding variables
    if(node->left) {
        process:DeclarationVarlist(node->left, func);
    }
}

void process::GetLocals(Node* node, FunctionData* func) {
    // if INITIALIZE block was found, add variable to fucntion structure
    if(strcmp(node->value, "INITIALIZE") == 0) {
        ++func->n_vars;
        func->variables[node->right->value] = - (func->n_vars) * ELEMENT_SIZE - STACK_FRAME_OFFSET; //TODO find out the right offset for local varibles
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
        const char* operation = node->right->value;

        if(strcmp(operation, "INITIALIZE") == 0) {
            process::Intialize(node->right, func, out);
        }
        if(strcmp(operation, "INPUT") == 0) {
            process::Input(node->right, func, out);
        }
        if(strcmp(operation, "OUTPUT") == 0) {
            process::Output(node->right, func, out);
        }
        if(strcmp(operation, "CALL") == 0) {
            process::Call(node->right, func, out);
        }
        if(strcmp(operation, "IF") == 0) {
            process::If(node->right, func, out);
        }
        if(strcmp(operation, "WHILE") == 0) {
            process::While(node->right, func, out);
        }
        if(strcmp(operation, "RETURN") == 0) {
            process::Return(node->right, func, out);
        }
        if(strcmp(operation, "ASSIGN") == 0) {
            process::Assign(node->right, func, out);
        }
    }
    if(node->left) {
        process::Operator(node->left, func, out);
    }
}

void process::Intialize(Node* node, FunctionData* func, FILE* out) {
    const char* var_name = node->right->value;
    CheckVariableExists(func, var_name);
    int var_offset = func->variables[var_name];

    COMMENT_INITIALIZING_VARIABLE(out, var_name);

    if(node->left) {
        process::Expression(node->left, func, out);
        MOV(out, RBP, var_offset, RAX);
    }
    else {
        MOV(out, QWORD, RBP, var_offset, 0);
    }
}

void process::Assign(Node* node, FunctionData* func, FILE* out) {
    const char* var_name = node->left->value;
    CheckVariableExists(func, var_name);
    
    process::Expression(node->right, func, out);

    int var_offset = func->variables[var_name];
    COMMENT_ASSIGNING_TO_VARIABLE(out, var_name);
    MOV(out, RBP, var_offset, RAX);
}

void process::Return(Node* node, FunctionData* func, FILE* out) {
    const char* var_name = node->right->value;
    CheckVariableExists(func, var_name);

    int var_offset = func->variables[var_name];

    COMMENT_RETURN(out, var_name);
    MOV(out, RAX, RBP, var_offset);
    POPA(out);
    ADD(out, RSP, func->n_vars * ELEMENT_SIZE);
    POP(out, RBP);
    RET(out);

}

void process::If(Node* node, FunctionData* func, FILE* out) {
    process::Condition(node, func, out);

    process::Block(node->right->right, func, out);

    if(node->right->left) {
        JMP(out, "cond", node->right);
    }

    LABEL(out, "cond", node);

    if(node->right->left) {
        process::Block(node->right->left, func, out);
        LABEL(out, "cond", node->right);
    }
}

void process::While(Node* node, FunctionData* func, FILE* out) {
    LABEL(out, "cond", node);
    process::Condition(node, func, out);
    process::Block(node->right, func, out);
    LABEL(out, "cond", node->right);
    
}

void process::Condition(Node* node, FunctionData* func, FILE* out) {
    process::Expression(node->left->left, func, out);
    COMMENT_EXPRESSION_LEFT_PART_SAVING(out);
    PUSH(out, RAX);
    
    process::Expression(node->left->right, func, out);
    COMMENT_EXPRESSION_RIGHT_PART_SAVING(out);
    MOV(out, RCX, RAX);

    COMMENT_EXPRESSION_LEFT_PART_RESTORING(out);
    POP(out, RBX);

    CMP(out, RBX, RCX);

    const char* comp = node->left->value;

    if(strcmp(comp, "EQUAL") == 0) {
        JNE(out, "cond", node); //using else condition for jump
    }
    else if(strcmp(comp, "ABOVE") == 0) {
        JBE(out, "cond", node);
    }
    else if(strcmp(comp, "BELOW") == 0) {
        JAE(out, "cond", node);
    }
}

void process::CallVarlist(Node* node, FunctionData* func, FILE* out, int& n_args) {
    if(node->left) {
        process::CallVarlist(node->left, func, out, n_args);
    }
    if(node->right) {
        CheckVariableExists(func, node->right->value);
        int offset = func->variables[node->right->value];
        PUSH(out, QWORD, RBP, offset);
        ++n_args;
    }
}

void process::Call(Node* node, FunctionData* func, FILE* out) {
    int n_args = 0;
    process::CallVarlist(node->right, func, out, n_args);
    CALL(out, node->left->value);
    ADD(out, RSP, ELEMENT_SIZE * n_args);
}

void process::Input(Node* node, FunctionData* func, FILE* out) {
    CheckVariableExists(func, node->right->value);
    
    COMMENT_INPUT(out, node->right->value);
    int offset = func->variables[node->right->value];
    CALL(out, ATOI);
    MOV(out, RBP, offset, RAX);
}

void process::Output(Node* node, FunctionData* func, FILE* out) {
    CheckVariableExists(func, node->right->value);
    
    COMMENT_OUTPUT(out, node->right->value);
    int offset = func->variables[node->right->value];
    MOV(out, RAX, RBP, offset);
    CALL(out, ITOA);
}

void process::Expression(Node* node, FunctionData* func, FILE* out) {
    if(isdigit(*(node->value))) {
        MOV(out, RAX, atoi(node->value));
        return;
    }
    if(isalpha(*(node->value)) && !node->left && !node->right) {
        CheckVariableExists(func, node->value);
        int offset = func->variables[node->value];
        MOV(out, RAX, RBP, offset);
        return;
    }
    if(strcmp(node->value, "CALL") == 0) {
        process::Call(node, func, out);
        return;
    }
    
    process::Expression(node->left, func, out);
    PUSH(out, RAX);
    process::Expression(node->right, func, out);
    MOV(out, RCX, RAX);
    POP(out, RAX);
    MOV(out, RBX, RAX);

    if(strcmp(node->value, "SUB") == 0) {
        SUB(out, RBX, RCX);
        MOV(out, RAX, RBX);
        return;
    }

    if(strcmp(node->value, "ADD") == 0) {
        ADD(out, RBX, RCX);
        MOV(out, RAX, RBX);
        return;
    }

    if(strcmp(node->value, "MUL") == 0) {
        MOV(out, RAX, RBX);
        MUL(out, RCX);
        return;
    }

    if(strcmp(node->value, "DIV") == 0) {
        MOV(out, RAX, RBX);
        DIV(out, RCX);
        return;
    }

}
