#include <iostream>
#include <fstream>
#include "token_handler.h"

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int type = 0;
    string_view value = "";

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

    Node(TokenHandler& handler) {
        handler.Get();
        value = handler.Get();

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
