 #pragma once
template<typename T>
class IContainer {
    protected: typedef unsigned long long ull;
    public:
        virtual ull size() = 0;
        virtual void clear() = 0;
        virtual bool empty() = 0;
};
