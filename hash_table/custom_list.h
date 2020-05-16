template <typename T>
class List
{
    private:

        template <typename Node_T>
        class Node
        {
            public:
                Node<Node_T>* prev = nullptr;
                Node_T value;
                Node(Node_T value) : value(value), prev(nullptr){}
                ~Node() = default;
        };

        int size_ = 0;
        Node<T>* back_ = nullptr;
    public:
        List() = default;
        ~List() 
        {
            clear();
        }

        void push_back(T value)
        {
            if(!size_)
            {
                back_ = new Node<T>(value);
                ++size_;
                return;
            }

            Node<T>* new_node = new Node<T>(value);
            new_node->prev = back_;
            back_ = new_node;
            ++size_;
        }

        int size() const noexcept
        {
            return size_;
        }

        int& operator[](const char* value) noexcept
        {
            Node<T>* cur = back_;
            while(cur && strcmp(cur->value.name, value) != 0)
            {
                cur = cur->prev;
            }
            return cur->value.offset;
        }

        bool contains(const char* value) noexcept 
        {
            Node<T>* cur = back_;
            while(cur && strcmp(cur->value.name, value) != 0)
            {
                cur = cur->prev;
            }
            return cur ? true : false;
        }

        void pop_back()
        {
            if(size_)
            {
                Node<T>* old_back = back_;
                back_ = back_->prev;
                --size_;
                
                delete old_back;
            }
        }

        void erase(T value)
        {
            Node<T>* cur = back_;
            Node<T>* next = nullptr;
            while (cur && cur->value != value)
            {
                next = cur;
                cur = cur->prev;
            }

            if(!cur)
            {
                return;
            }

            next->prev = cur->prev;
            delete cur;
            --size_;
        }

        void clear()
        {
            while(size_)
            {
                pop_back();
            }
        }

};
