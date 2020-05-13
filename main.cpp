#include <iostream>
#include <string_view>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>

using std::string_view;
using std::string;

class Tree {
    private:    
        struct Node {
            Node* left = nullptr;
            Node* right = nullptr;
            int type = 0;
            string_view value;

            Node() = default;

            Node(string_view value, int type) : type(type), value(value){};

            ~Node() {
                if(left) {
                    delete left;
                }
                if(right) {
                    delete right;
                }
            }

            void readFromBuffer(char* buffer) {
                
            }
        };

};

class TokenHandler {
    char* buffer = nullptr;
    int n_tokens = 0;
    string_view* tokens = nullptr;

    unsigned int countWordsInString(char* data)
    {
        string str = string(data);
        std::stringstream stream(str);
        return std::distance(std::istream_iterator<string>(stream), std::istream_iterator<string>());
    }

    public:
        TokenHandler(char* data) {
            buffer = data;
            n_tokens = countWordsInString(data);
            tokens = new string_view[n_tokens];

            int length = 0;

            char* buf_pos = buffer;
            for(int i = 0; i < n_tokens; ++i) {
                sscanf(buf_pos, "%*s%n", &length);
                tokens[i] = string_view(buf_pos, length);
                buf_pos += length + 1;
            }
        }
    
        inline string_view& operator[](int idx) {
            return tokens[idx];
        }

        inline int Size() const noexcept{
            return n_tokens;
        }

        ~TokenHandler() {
            delete[] tokens;
            delete[] buffer;
        }
};

int main() {
    FILE* tree_file = fopen("factorial.tree", "r");
    fseek(tree_file, 0, SEEK_END);
    int size = ftell(tree_file);
    fseek(tree_file, 0, SEEK_SET);

    char* tree_data = new char[size]();
    fread(tree_data, sizeof(char), size, tree_file);

    TokenHandler handler = TokenHandler(tree_data);

    for(int i = 0; i < handler.Size(); ++i) {
        std::cout << handler[i] << std::endl;
    }

    return 0;
}