 #pragma once
template<typename T>
class IContainer {
    protected: typedef unsigned long long ull;
    public:
        virtual ull size() = 0;
        virtual ull capacity() = 0;
        virtual void clear() = 0;
};
