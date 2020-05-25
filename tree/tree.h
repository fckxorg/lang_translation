#include <iostream>
#include <fstream>
#include "token_handler.h"

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int type = 0;
    const char* value = nullptr;

    Node() = default;

    Node(const char* value, int type) : type(type), value(value){};

    ~Node() {
        if(left) {
            delete left;
        }
        if(right) {
            delete right;
        }
    }

    Node(TokenHandler& handler) {
        handler.Get();
        string_view cur_value = handler.Get();
        value = cur_value.data();
        const_cast<char*>(value)[cur_value.size()] = '\0';

        if(handler.Look() == "{") {
            left = new Node(handler);
            right = new Node(handler);
        }

        handler.Get();
    }

    void Dump(std::ofstream& dump_file) {
        dump_file << "node" << this << "[label=\"{" << this << "}|{VALUE|" << value << "}|{LEFT|" << this->left << "}|{RIGHT|" << this->right << "}\",shape=record];" << std::endl;
        if (this->left) {
            this->left->Dump(dump_file);
            dump_file << "node" << this << " -> " << "node" << this->left << ";\n";
        }
        if (this->right) {
            this->right->Dump(dump_file);
            dump_file << "node" << this << " -> " << "node" << this->right << ";\n";
        }
    }

    template <typename Functor>
    void Process(Functor func) {
        func(this);
        
        if(left) {
            left->Process(func);
        }

        if(right) {
            right->Process(func);
        }
    }
};

class Tree {
    private:
        Node* root = nullptr;
    public:
        Tree(Node* root) : root(root){};
        Tree& operator=(const Tree& other) = delete;
        Tree(const Tree& other) = delete;
        ~Tree() {
            delete root;
        }

        Node* GetRoot() {
            return root;
        }

        Tree(TokenHandler& handler) {
            root = new Node(handler);
        }

        void Dump(std::ofstream& out) {
            out << "digraph {\n";
            root->Dump(out);
            out << "}";
        }

        template<typename Functor>
        void Process(Functor func) {
            root->Process(func);
        }
};

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