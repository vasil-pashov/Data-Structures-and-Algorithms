#pragma once
#include "../../Interfaces/random_access_container.h"
#include <iterator>
#include <stdexcept>

namespace LinkedListN {
    template <typename T>
    class LinkedList : IRandomAccessContainer<T> {
        private:
            typedef typename IRandomAccessContainer<T>::ull ull;
            struct Node {
                Node *next=nullptr;
                T value;
                Node(Node *n, const T& v) : next{n}, value{v}{}
                explicit Node(const T& v) : next{nullptr}, value{v}{}
            };
            void copy_content(const LinkedList &other) {
                Node *it = other.m_head, *current;
                m_head = new Node(it->value);
                current = m_head;
                it = it->next;
                while(it != other.m_tail) {
                    current->next = new Node(it->value);
                    it = it->next;
                    current = current->next;
                }
                current->next = new Node(it->value);
                m_tail = current->next;
            }
            void delete_content() {
                Node *current = m_head, *next;
                while(current != nullptr) { //although this loop is correct im makes valgrind complain,
                    next = current->next;   // becouse I dont explicitly delete m_tail
                    delete current;         // anyway no memmory losses registerd by vlgrind
                    current = next;
                }
                m_head = m_tail = nullptr;
            }
            Node *m_head = nullptr, *m_tail = nullptr;
            ull m_size = 0;
        public:
            class iterator : public std::iterator<std::forward_iterator_tag, T, std::ptrdiff_t, T*, T&> {
                private:
                    Node *it=nullptr; 
                public:
                    iterator(const iterator& other) : it{other.it}{}
                    iterator& operator=(T& other) {
                        this->it = other.it;
                    }
                    iterator(Node* head): it{head}{}
                    inline bool operator==(const iterator &other) const {
                        return it == other.it;
                    }
                    inline bool operator!=(const iterator &other) const {
                        return !(*this == other);
                    }
                    inline iterator& operator++() {
                        it = it->next;
                        return *this;
                    }
                    inline iterator operator++(int) {
                        iterator tmp(*this);
                        ++(*this);
                        return tmp;
                    }
                    inline T& operator* () {
                        return it->value;
                    }
                    inline const T& operator* () const {
                        return it->value;
                    }
                    inline T *operator-> () {
                        return it;
                    }
                    inline const T *operator-> () const {
                        return it;
                    }
            };
            LinkedList() {}
            LinkedList(const LinkedList& other) :m_size{other.m_size} {
                copy_content(other); 
            }
            LinkedList& operator= (const LinkedList& other) {
                if(this != &other) {
                    m_size = other.m_size;
                    copy_content(other);
                }
                return *this;
            }
            ~LinkedList() {
                delete_content();
            }
            ull size() {
                return m_size;
            }
            void push_back(const T& element) {
                Node *new_node = new Node(nullptr, element);
                if(m_size != 0) {
                    m_tail->next = new_node;
                } else {
                    m_head = new_node;
                }
                m_tail = new_node;
                m_size++;
            }
            void push_front(const T& element) {
                Node *new_node = new Node(m_head, element);
                if(m_size == 0) {
                   m_tail = new_node; 
                }
                m_head = new_node;
                m_size++;
            }
            void clear() {
                delete_content();
                m_size = 0;
            }
            void insert(ull index, const T& element) {
                ull i = 0;
                Node *current = m_head;
                if(index == 0) {
                    push_front(element);
                } else if(index == m_size){
                   push_back(element); 
                } else {
                    while(i++ < index - 1) {
                        current = current->next;
                    }
                    Node *new_node = new Node(current->next, element);
                    current->next = new_node;
                    m_size++; 
                }
            }
            inline bool empty() {
                return m_size == 0;
            }
            inline iterator begin() const {
                return iterator(m_head);
            }
            inline iterator end() const {
                return iterator(m_tail->next);
            }
            void erase(ull index) {
                if(index == 0) {
                    pop_front();
                } else if(index == m_size - 1) {
                    pop_back();
                } else {
                    ull i = 0;
                    Node *current = m_head, *next;
                    while(i++ < index - 1) {
                        current = current->next;
                    }
                    next = current->next;
                    current->next = current->next->next;
                    delete next;
                    m_size--;
                }
            }
            void pop_back() {
                if(m_size) {
                    if(m_size == 1) {
                        delete m_head;
                        m_head = m_tail = nullptr;
                    } else {
                        Node *current = m_head;
                        while(current->next != m_tail) {
                            current = current->next;
                        }
                        m_tail = current;
                        delete m_tail->next;
                    }
                    m_size--;
                }
            }
            void pop_front() {
                if(m_size > 1) {
                    Node *current_head = m_head;
                    m_head = m_head->next;
                    delete current_head;
                } else {
                    delete m_head;
                    m_head = m_tail = nullptr;
                }
                m_size--;
            }
            T& operator[](const ull index) {
                iterator it = begin();
                for(ull i = 0; i < index; i++, ++it){}
                return *it;
            }
            T& at(ull index) {
                if(index < 0 || index > m_size) {
                    throw std::out_of_range("Vector range check");
                }
                return (*this)[index];
            }
    };
}
