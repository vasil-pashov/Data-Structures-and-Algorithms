#include "../../Interfaces/container.h"

namespace StackN {
    template <typename T>
    class Stack : IContainer<T> {
        typedef typename IContainer<T>::ull ull;
        public:
            Stack() : m_container{allocate(m_capacity)} {}
            inline ~Stack() {
                delete [] m_container;
            }
            Stack(const Stack &other): m_size{other.m_size}, m_capacity{other.m_capacity}, m_container{allocate(m_capacity)}  {
                copy(other.m_container, m_container, m_size);
            }
            Stack& operator= (const Stack &other) {
                if(this != &other) {
                    m_size = other.m_size;
                    m_capacity = other.m_capacity;
                    m_container = allocate(m_capacity);
                    copy(other.m_container, m_container, m_size);
                }
                return *this;
            }
            inline bool empty() {
                return m_size == 0;
            }
            inline void clear() {
                delete [] m_container;
                m_size = 0;
            }
            inline ull size() {
                return m_size;
            }
            inline T &peek() {
                return m_container[m_size-1];
            }
            inline T pop() {
                m_size--;
                return m_container[m_size];
            }
            void push(const T &element) {
                if(m_size == m_capacity) {
                    m_capacity *= 2;
                    grow(m_capacity);
                }
                m_container[m_size++] = element;
            }
        private:
            ull m_size = 0, m_capacity = 4;
            T* m_container = 0;
            T* allocate(ull size) {
                return new T[size];
            }
            void copy(T *src, T *dest, ull size) {
                for(ull i = 0; i <size; i++) {
                    dest[i] = src[i];
                }
            }
            void grow(ull capacity) {
                T *temp = allocate(capacity);
                copy(m_container, temp, m_size);
                delete [] m_container;
                m_container = temp;
            }
    };
}
