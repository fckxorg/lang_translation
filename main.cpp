#include <cstring>
#include "lang_proc_lib/node_processors.h"


void cleanTree(Node* node) {
    if(node->left && strcmp(node->left->value, "@") == 0) {
        delete node->left;
        node->left = nullptr;
    }

    if(node->right && strcmp(node->right->value, "@") == 0) {
        delete node->right;
        node->right = nullptr;
    }
}

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

int main() {

    FILE* tree_file = fopen("factorial.tree", "r");
    if(!fileOpened(tree_file)) return 1;

    size_t size = getFileSize(tree_file);

    char* tree_data = new char[size]();
    fread(tree_data, sizeof(char), size, tree_file);
    fclose(tree_file);

    TokenHandler handler = TokenHandler(tree_data);
    Tree ast = Tree(handler);
    ast.Process(cleanTree);

    FILE* assembly = fopen("src_new.asm", "w");
    if(!fileOpened(assembly)) return 1;
    process::ProgramRoot(ast.GetRoot(), assembly);
    
    fclose(assembly);

    system("nasm -felf64 src_new.asm");
    system("ld src_new.o");
    return 0;
}
