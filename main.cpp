#include "node_processors.h"

using std::vector;

void ProcessNode(Node* node, std::ofstream& out) {
    if(node->value == "PROGRAM_ROOT") {
        processProgramRoot(out);
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

    std::ofstream assembly("src.asm");

    ast.Process(ProcessNode, assembly);

    assembly.close();

    return 0;
}
