#pragma once
#include "container.h"
template<typename T>
class IRandomAccessContainer : public IContainer<T> {
    public:
        typedef typename IContainer<T>::ull ull;
        virtual void insert(ull, const T&) = 0;
        virtual void erase(ull) = 0;
        virtual T& operator[](ull) = 0;
        virtual T& at(ull) = 0;
};
