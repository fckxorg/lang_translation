#include "node_processors.h"

#define DUMP 0
#define FUNCTIONS_TABLE 0

using std::vector;

void cleanTree(Node* node) {
    if(node->left && node->left->value == "@") {
        delete node->left;
        node->left = nullptr;
    }

    if(node->right && node->right->value == "@") {
        delete node->right;
        node->right = nullptr;
    }
}

int main() {
    FILE* tree_file = fopen("factorial.tree", "r");
    fseek(tree_file, 0, SEEK_END);
    int size = ftell(tree_file);
    fseek(tree_file, 0, SEEK_SET);

    char* tree_data = new char[size]();
    fread(tree_data, sizeof(char), size, tree_file);

    TokenHandler handler = TokenHandler(tree_data);

    Tree ast = Tree(handler);
    ast.Process(cleanTree);

#ifdef DUMP
    std::ofstream out("dump.dot");
    ast.Dump(out);
    out.close();
#endif

    std::ofstream assembly("src.asm");

    process::ProgramRoot(ast.GetRoot(), assembly);

    assembly.close();

#ifdef FUNCTIONS_TABLE
    for(FunctionData* el : functions) {
        std::cout << "Function: " << el->name << "\n";
        std::cout << "n_args: " << el->n_args << "\n";
        std::cout << "n_vars: " << el->n_vars << "\n";
        std::cout << "Varible table:\n";

        for(auto& variable : el->variables){
            std::cout << variable.first << " " << variable.second << "\n";
        }

        std::cout << "\n=======================\n\n";
    }
#endif

    return 0;
}
