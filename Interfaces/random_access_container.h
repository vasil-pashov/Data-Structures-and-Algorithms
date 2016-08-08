#pragma once
#include "container.h"
template<typename T>
class IRandom_access_container : public IContainer<T> {
    public:
        typedef typename IContainer<T>::ull ull;
        virtual void insert(ull index, const T& value) = 0;
        virtual void erase(ull index) = 0;
        virtual T& operator[](const ull index) = 0;
        virtual T& at(const ull index) = 0;
};
