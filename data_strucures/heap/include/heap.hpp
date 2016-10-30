template<typename T>
class Heap {
    typedef unsigned long long ull;

    public:

        Heap() {
            m_container = new T[m_capacity];
        }

        Heap(const Heap &other) : m_size{other.m_size},
                                    m_capacity{m_capacity} {
            copy_arr(other.m_container, m_container, m_size);
        }

        ~Heap() {
            delete [] m_container;
        }

        T& operator= (const Heap &other) {
            if(&other != this) {
                m_size = other.m_size;
                m_container = other.m_container;
                copy_arr(other.m_container, m_container, m_size);
            }
            return *this;

        }

        inline void set_comparator(bool (&cmp)(T&, T&)) {
            m_cmp = cmp;
        }

        void insert(T element) {
            m_container[++m_size] = element;
            ull element_pos = m_size, parent_index = parent(m_size);
            if(m_size >= m_capacity) grow();
            bool rise = compare(element_pos, parent_index) == element_pos;
            while(element_pos > 1 && rise) {
                swap(m_container[element_pos], m_container[parent_index]);
                element_pos = parent_index;
                parent_index = parent(parent_index);
                rise = compare(element_pos, parent_index) == element_pos;
            }
        }

        T pop() {
            T top = m_container[1];
            swap(m_container[1], m_container[m_size]);
            --m_size;
            sift_down(1);
            return top;
        }

        inline T peek() {
            return m_container[1];
        }
        
        inline bool empty() {
            return m_size <= 0;
        }

    private:
        T *m_container = nullptr;
        ull m_size = 0, m_capacity = 2048;
        bool (*m_cmp)(T&, T&) = nullptr;

        void grow() {
            m_capacity <<= 1;
            T *buffer = new T[m_capacity];
            copy_arr(m_container, buffer, m_size);
            delete [] m_container;
            m_container = buffer;
        }

        inline void copy_arr(T *src,  T *dest, ull arr_size) {
            for(ull i = 1; i <= arr_size; ++i) {
                dest[i] = src[i];
            }
        }

        inline ull parent(int index) {
            return index >> 1;
        }

        inline ull compare(ull element_index, ull other_index) {
            if(m_cmp) {
                return m_cmp(m_container[element_index], m_container[other_index]) ?
                    element_index : other_index;
            }
            return m_container[other_index] > m_container[element_index] ? other_index : element_index;
        }

        inline ull smaller_son(int index) {
            ull left_son_index = index<<1;
            if(m_size >= left_son_index + 1) {
                return compare(left_son_index, left_son_index + 1);
            } else if(m_size == left_son_index) {
                return left_son_index;
            }
            return 0;
        }

        void sift_down(ull index) {
            ull smaller_son_index = smaller_son(index);
            bool sift = compare(index, smaller_son_index) == smaller_son_index;
            while(smaller_son_index && sift) {
                swap(m_container[smaller_son_index], m_container[index]);
                index = smaller_son_index;
                smaller_son_index = smaller_son(index);
                sift = compare(index, smaller_son_index) == smaller_son_index;
            }
        }
};
