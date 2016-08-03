//vector::assign
//vector::at
//vector::back
//vector::begin
//vector::cbegin
//vector::cend
//vector::clear
//vector::crbegin
//vector::crend
//vector::data
//vector::emplace
//vector::emplace_back
//vector::empty
//vector::end
//vector::erase
//vector::front
//vector::get_allocator
//vector::max_size
//vector::rbegin
//vector::rend
//vector::reserve
//vector::resize
//vector::shrink_to_fit
//vector::swap

#include <iostream>
#include <stdexcept>
#include <new>
#include <iterator>

namespace Vector {
    typedef unsigned long long ull;
    template<typename T>
    class vector {

        class iterator : public std::iterator<std::random_access_iterator_tag, T, std::ptrdiff_t, T*, T&> {
            private:
                T *iter;
            public:
                iterator() :iter{nullptr}{};
                explicit iterator(T* ptr) : iter{ptr}{}
                iterator(const iterator &other) : iter{other.ptr}{}
                //==================COMPARSION====================
                inline bool operator== (const T &other) const {
                    return iter == other.iter;
                }  
                inline bool operator!= (const T &other) const {
                    return !(this == other);
                }
                inline bool operator >(const iterator &other) const {
                    return std::distance(iter, other.iter) > 0 ? true : false;
                }
                inline bool operator <(const iterator &other) const {
                    return std::distance(iter, other.iter) < 0 ? true : false;
                }
                inline bool operator >=(const iterator &other) const {
                    return std::distance(iter, other.iter) >= 0 ? true : false;
                }
                inline bool operator <=(const iterator &other) const {
                    return std::distance(iter, other.iter) <= 0 ? true : false;
                }
                //================================================
                //==================ARITMETICS====================
                inline iterator& operator++() {
                    iter++;
                    return *this;
                }
                inline iterator operator++(int) {
                    iterator tmp(*this);  
                    iter++;
                    return *this;
                }
                inline iterator& operator--() {
                    iter--;
                    return *this;
                }
                inline iterator operator--(int) {
                    iterator tmp(*this);
                    iter--;
                    return tmp;
                }
                inline iterator operator+(const iterator &other) const {
                    return iterator(iter + other.iter);
                }
                inline iterator operator-(const iterator &other) const {
                    return iterator(iter - other.iter);
                }
                inline iterator operator+(const int n) const {
                    return iterator(iter + n);
                }
                inline iterator& operator+=(const int n) {
                    iter+=n;
                    return *this;
                }
                inline iterator& operator-=(const int n) {
                    iter-=n;
                    return *this;
                }
                inline iterator operator-(const int n) const {
                    return iterator(iter - n);
                }
                inline friend iterator operator+(iterator &iter, int n);
                inline friend iterator operator-(iterator &iter, int n);
                //================================================
                //==============REFENCE/DEREFERENCE===============
                inline T& operator*() {
                    return *iter;
                }
                inline const T& operator*() const {
                    return *iter;
                }
                inline T *operator->() {
                    return iter;
                }
                inline const T *operator->() const{
                    return iter;
                }
                //=============================================== 
                //=====================MISC======================
                inline iterator& operator[](const int index) const {
                    return iter + index;
                }
        };

        public:
            vector() {
                m_container = allocate(m_capacity);
            }
            vector(const vector &other) : m_size{other.m_size}, m_capacity{other.m_capacity} {
                m_container = allocate(m_capacity);
                copy_content(other.m_container, m_container);
            }
            vector& operator= (const vector& other) {
                if(this != &other) {
                    clear();
                    m_size = other.m_size;
                    m_capacity = other.m_capacity;
                    m_container = allocate(m_capacity);
                    copy_content(other.m_container, m_container);
                }
                return *this;
            }
            ~vector() {
                clear();
            }
            inline ull size() {
                return size;
            }
            T& operator[](int index) {
                return m_container[index];
            }
            inline ull capacity() {
                return m_capacity;
            }
            void push_back(T &new_element) {
                if(m_size < m_capacity) {
                    append(new_element);
                } else {
                    grow();
                    append(new_element);
                }
            }
            T& at(int index) {
                if(index < 0 || index > m_capacity) {
                    throw std::out_of_range("Vector range check");
                }
                return m_container[index];
            }
            inline void pop_back() {
                m_size--;
            }
            void insert(ull index, const T &value) {
                if(m_size < m_capacity) {
                    shift_right(index);
                } else {
                    grow();
                    shift_right(index);
                }
                m_container[index] = value;
            }
        private:
            T *m_container = nullptr;
            ull m_size = 0, m_capacity = 4; 
            inline void clear() {
                delete[](m_container);
            }
            T* allocate(ull capacity) {
                return new T[capacity]; 
            }
            void copy_content(T *from, T *to) {
                for(ull i = 0; i < m_size; i++) {
                    new(to + i) T(from[i]);
                }
            }
            inline void append(T &new_element) {
                m_container[m_size++] = new_element;
            }
            void grow() {
                m_capacity*=2;
                T* buffer = allocate(m_capacity);
                copy_content(m_container, buffer);
                clear();
                m_container = buffer;
            }
            void shift_right(ull index) {
                for(ull i = m_size; i > index; i--) {
                    m_container[i] = m_container[i-1];
                }
            }
    };
}
