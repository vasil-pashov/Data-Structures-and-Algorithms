#pragma once
#include <stdexcept>
#include "../../../Interfaces/random_access_container.h"


namespace Vector {
    template<typename T>
    class vector : IRandomAccessContainer<T> {
        typedef typename IRandomAccessContainer<T>::ull ull;
        public: class iterator : public std::iterator<std::random_access_iterator_tag, T, std::ptrdiff_t, T*, T&> {
            private:
                T *iter;
            public:
                iterator() :iter{nullptr}{};
                explicit iterator(T* ptr) : iter{ptr}{}
                iterator(const iterator &other) : iter{other.iter}{}
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
                    std::ptrdiff_t diff = other.iter - iter, add = diff < 0? -diff : diff;
                    return iterator(iter + add);
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
                inline friend iterator operator+(ull n, iterator &iter) {
                    return iter + n;
                }
                inline friend iterator operator-(ull n, iterator &iter) {
                    return iter - n;
                }
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
                inline T& operator[](const int index) const {
                    return *(iter + index);
                }
            };

            vector() : m_container{allocate(m_capacity)} {}
            vector(const vector &other) : m_size{other.m_size}, m_capacity{other.m_capacity}, m_container{allocate(m_capacity)} {
                copy_content(other.m_container, m_container, m_size);
            }
            vector& operator= (const vector& other) {
                if(this != &other) {
                    clear_array(m_container);
                    m_size = other.m_size;
                    m_capacity = other.m_capacity;
                    m_container = allocate(m_capacity);
                    copy_content(other.m_container, m_container, m_size);
                }
                return *this;
            }
            ~vector() {
                clear_array(m_container);
            }
            inline ull size() {
                return m_size;
            }
            T& operator[](ull index) {
                return m_container[index];
            }
            inline ull capacity() {
                return m_capacity;
            }
            void push_back(const T &new_element) {
                if(m_size < m_capacity) {
                    append(new_element);
                } else {
                    grow();
                    append(new_element);
                }
            }
            T& at(ull index) {
                if(index < 0 || index > m_capacity) {
                    throw std::out_of_range("Vector range check");
                }
                return m_container[index];
            }
            inline void pop_back() {
                m_container[m_size-1].~T();
                m_size--;
            }
            void insert(ull index, const T &value) {
                if(m_size < m_capacity) {
                    shift_right(index);
                } else {
                    grow();
                    shift_right(index);
                }
                m_size++;
                m_container[index] = value;
            }
            inline iterator begin() {
                return iterator(m_container);
            }
            inline iterator end() {
                return iterator(m_container + m_size);
            }
            void erase(ull position) {
                m_container[position].~T();
                shift_left(position); 
                m_size--;
            }
            inline T& front() {
                return m_container[0];
            }
            void shrink_to_fit() {
                T *buffer = allocate(m_size);
                copy_content(m_container, buffer, m_size);
                clear_array(m_container);
                m_container = buffer;
                m_capacity = m_size;
            }
            void clear() {
                clear_array(m_container);    
                m_size = 0;
                m_capacity = 4;
                m_container = allocate(m_capacity);
            }
            inline T* data() {
                return m_container;
            }
            inline const T* data() const {
                return m_container;
            }
            inline bool empty() {
                return m_size == 0;
             }
        private:
            ull m_size = 0, m_capacity = 4; 
            T *m_container;
            inline void clear_array(T *array) {
                delete[] array;
            }
            T* allocate(ull capacity) {
                return new T[capacity]; 
            }
            void copy_content(T *source, T *destination, ull size) {
                for(ull i = 0; i < size; i++) {
                    destination[i] = source[i];
                }
            }
            inline void append(const T &new_element) {
                m_container[m_size++] = new_element;
            }
            void grow() {
                m_capacity*=2;
                T* buffer = allocate(m_capacity);
                copy_content(m_container, buffer, m_size);
                clear_array(m_container);
                m_container = buffer;
            }
            void shift_right(ull index) {
                for(ull i = m_size; i > index; i--) {
                    m_container[i] = m_container[i-1];
                }
            }
            void shift_left(ull index) {
                for(; index < m_size -1; index++) {
                    m_container[index] = m_container[index + 1]; 
                }
            }
    };
}
