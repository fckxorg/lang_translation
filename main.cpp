#include <cstring>
#include "lang_proc_lib/node_processors.h"
#include "file_functions.h"
#include "cmd.h"


const char HELP_MESSAGE[] = "Usage: translator [input_filename] [output_filename]\n";

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << HELP_MESSAGE;
    }
    char* input = argv[1];
    char* output = argv[2];

    char* asm_filename = changeExtension(input, ASM_EXTENSION);
    char* object_filename = changeExtension(input, OBJECT_EXTENSION);

    char* tree_data = readFile(input);
    if(!tree_data) return 1;

    TokenHandler handler = TokenHandler(tree_data);
    Tree ast = Tree(handler);
    ast.Process(cleanTree);

    FILE* assembly = fopen(asm_filename, "w");
    if(!fileOpened(assembly)) return 1;
    process::ProgramRoot(ast.GetRoot(), assembly);
    fclose(assembly);

    NASMCompile(asm_filename);
    system("ld src_new.o");

    delete[] asm_filename;
    delete[] object_filename;
    return 0;
}
