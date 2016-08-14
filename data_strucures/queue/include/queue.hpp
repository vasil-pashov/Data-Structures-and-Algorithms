#include "../../../Interfaces/container.h"

namespace QueueN {
    template <typename T>
    class Queue : IContainer<T> {
        typedef typename IContainer<T>::ull ull;
        public:
            Queue() {}
            Queue(const Queue &other) :m_head {new Node(other.m_head->value)}, m_size(other.m_size) {
                copy(other.m_head, m_head, m_size);
            }
            Queue& operator= (const Queue &other) {
                if(this != &other) {
                    m_size = other.m_size;
                    m_head = new Node(other.m_head->value);
                    copy(other.m_head, m_head, m_size);
                }
                return *this;
            }
            ~Queue() {
                clear_content(m_head);
            }
            inline bool empty() {
                return m_size == 0;
            }
            inline ull size() {
                return m_size;
            }
            inline void clear() {
                clear_content(m_head);
            }
            void push(const T &element) {
                Node *new_node = new Node(element);
                if(m_size == 0) {
                    m_head = new_node;
                } else {
                    m_tail->next = new_node;
                }
                m_tail = new_node;
                m_size++;
            }
            inline T &peek() {
                return m_head->value;
            }
            T pop() {
                T val = m_head->value;
                --m_size;
                Node *next = m_head->next;
                delete m_head;
                m_head = next;
                return val;
            }
        private:
            struct Node {
                Node *next = nullptr;
                T value;
                explicit Node(const T &val) :value{val} {}
            };
            void copy(Node *src, Node *dest, ull size) {
                src = src->next;
                for(ull i = 0; i < size - 1; i++) {
                    dest->next = new Node(src->value);
                    dest = dest->next;
                    src = src->next;
                }

            }
            void clear_content(Node *src) {
                Node *next;
                for(ull i = 0; i < m_size; i++) {
                    next = src->next; 
                    delete src;
                    src = next;
                }
            }
            Node *m_head = nullptr, *m_tail=nullptr;
            ull m_size = 0;
    };
}
