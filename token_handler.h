#include <string_view>
#include <string>
#include <iterator>
#include <algorithm>
#include <sstream>

using std::string;
using std::string_view;

class TokenHandler {
    char* buffer = nullptr;
    int n_tokens = 0;
    int current = 0;
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

        inline string_view& Get() {
            return tokens[current++];
        }

        inline string_view Look() {
            return tokens[current];
        }

        void Unget() {
            --current;
        }

        void Seek(int idx) {
            current = idx;
        }

        ~TokenHandler() {
            delete[] tokens;
            delete[] buffer;
        }
};
