#include "../include/vector.hpp"

namespace Vector {

template<typename T> vector<T>::iterator::iterator() :iter{nullptr}{};
template<typename T> vector<T>::iterator::iterator(const iterator &other) : iter{other.iter}{}
//=================================COMPARSION==================================
    template<typename T>
    inline bool vector<T>::iterator::operator== (const iterator &other) const {
        return iter == other.iter;
    } 
template<typename T>
    inline bool vector<T>::iterator::operator!= (const iterator &other) const {
        return !(this == other);
    }
template<typename T>
    inline bool vector<T>::iterator::operator >(const iterator &other) const {
        return std::distance(iter, other.iter) > 0 ? true : false;
    }
template<typename T>
    inline bool vector<T>::iterator::operator <(const iterator &other) const {
        return std::distance(iter, other.iter) < 0 ? true : false; 
    }
template<typename T>
    inline bool vector<T>::iterator::operator >=(const iterator &other) const {
        return std::distance(iter, other.iter) >= 0 ? true : false; 
    }
template<typename T>
    inline bool vector<T>::iterator::operator <=(const iterator &other) const {
        return std::distance(iter, other.iter) <= 0 ? true : false; 
    }
//=============================================================================
//=================================ARITMETICS==================================
template<typename T>
    inline typename vector<T>::iterator& vector<T>::iterator::operator++() {
        iter++; return *this;
    }

template<typename T>
    inline typename vector<T>::iterator vector<T>::iterator::operator++(int) {
        iterator tmp(*this);  iter++; return *this; 
    }

template<typename T>
    inline typename vector<T>::iterator& vector<T>::iterator::operator--() {
        iter--; return *this; 
    }

template<typename T>
    inline typename vector<T>::iterator vector<T>::iterator::operator--(int) {
        iterator tmp(*this); iter--; return tmp; 
    }

template<typename T>
    inline typename vector<T>::iterator vector<T>::iterator::operator+(const iterator &other) const {
        return iterator(iter + other.iter); 
    }

template<typename T>
    inline typename vector<T>::iterator vector<T>::iterator::operator-(const iterator &other) const {
        return iterator(iter - other.iter); 
    }

template<typename T>
    inline typename vector<T>::iterator vector<T>::iterator::operator+(const int n) const {
        return iterator(iter + n); 
    }

template<typename T>
    inline typename vector<T>::iterator& vector<T>::iterator::operator+=(const int n) {
        iter+=n; return *this; 
    }

template<typename T>
    inline typename vector<T>::iterator& vector<T>::iterator::operator-=(const int n) {
        iter-=n; return *this; 
    }

template<typename T>
    inline typename vector<T>::iterator vector<T>::iterator::operator-(const int n) const {
        return iterator(iter - n); 
    }

//========================================================================================================
//=============================================MISC=======================================================
template<typename T>
    inline typename vector<T>::iterator& vector<T>::iterator::operator[](const int index) const {
        return iter + index; 
    }
}
