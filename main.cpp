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

void prepareStrings(Node* node) {
    const_cast<char*>(node->value.data())[node->value.size()] = '\0';
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
    ast.Process(prepareStrings);

#ifdef DUMP
    std::ofstream out("dump.dot");
    ast.Dump(out);
    out.close();
#endif

    FILE* assembly = fopen("src_new.asm", "w");

    process::ProgramRoot(ast.GetRoot(), assembly);

    fclose(assembly);

    return 0;
}
