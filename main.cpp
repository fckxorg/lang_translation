#include <cstring>
#include "lang_proc_lib/node_processors.h"
#include "file_functions.h"


int main() {

    char* tree_data = readFile("factorial.tree");
    if(!tree_data) return 1;

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
